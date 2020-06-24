#ifndef sequential_cpp
#define sequential_cpp

#include <iostream>
#include <algorithm>

#include "sequential.hpp"
#include "../tools/tools.hpp" // for progressbar


template<typename T>
Sequential<T>::Sequential()
{
	this->layers.clear();
	this->layer_list.clear();
	this->nb_layers              = 0;
	this->addlayer_counter       = 0;
	this->network_type           = NETWORK_TYPE::NONE;
	this->save_intermediates     = false;
	this->find_number_range_flag = false;
	this->start_layer            = 0;
}

template <typename T>
Sequential<T>::Sequential(NETWORK_TYPE network_type)
{
	this->layers.clear();
	this->layer_list.clear();
	this->nb_layers              = 0;
	this->addlayer_counter       = 0;
	this->save_intermediates     = false;
	this->find_number_range_flag = false;
	this->start_layer            = 0;

	//this->analyze = false;
	//this->A_passes = 0;

	this->network_type = network_type;
	switch (network_type)
	{
	case NETWORK_TYPE::VGG16:
		this->parameter_path    = MODELS_PATH + "VGG16/";
		this->intermediate_path = INTERMEDIATE_PATH;
		break;
	case NETWORK_TYPE::ALEXNET:
		this->parameter_path    = MODELS_PATH + "AlexNet/";
		this->intermediate_path = INTERMEDIATE_PATH;
		break;
	default:
	case NETWORK_TYPE::NONE:
		std::cout << "No network type selected!" << std::endl;
		break;
	}
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
void Sequential<T>::load_linear(bool use_pbar)
{
	this->layer_list.push_back(layer_types::LINEAR);

	std::string path = this->parameter_path + std::to_string(this->addlayer_counter) + "_" + get_layer_type(this->nb_layers);

	this->addlayer_counter++;
	this->nb_layers++;
	
	layers.push_back(std::unique_ptr<Linear<T>>(new Linear<T>(path, use_pbar)));	
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
void Sequential<T>::load_conv2d(int height, int width, int padding, bool bias, int stride)
{
	this->layer_list.push_back(layer_types::CONV_2D);

	std::string path = this->parameter_path + std::to_string(this->addlayer_counter) + "_" + get_layer_type(this->nb_layers);

	this->addlayer_counter++;
	this->nb_layers++;

	layers.push_back(std::unique_ptr<Conv_2D<T>>(new Conv_2D<T>(path, height, width, padding, bias, stride)));
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
void Sequential<T>::add_maxpool2d(int channels, int input_height, int input_width, int kernel_size, int stride)
{
	this->layer_list.push_back(layer_types::MAXPOOL_2D);

	this->addlayer_counter++;
	this->nb_layers++;

	layers.push_back(std::unique_ptr<MaxPool2D<T>>(new MaxPool2D<T>(channels, input_height, input_width, kernel_size, stride)));
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
void Sequential<T>::add_flatten(int input_channels, int input_height, int input_width)
{
	this->layer_list.push_back(layer_types::FLATTEN);

	this->addlayer_counter++;
	this->nb_layers++;

	layers.push_back(std::unique_ptr<Flatten<T>>(new Flatten<T>(input_channels, input_height, input_width)));
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
void Sequential<T>::add_relu()
{
	layers.push_back(std::unique_ptr<ReLU<T>>(new ReLU<T>()));
	this->addlayer_counter++;
	this->nb_layers++;
	this->layer_list.push_back(layer_types::RELU);
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

//template<typename T>
//void Sequential<T>::add_tanh(int length)
//{
//	layers.push_back(std::unique_ptr<Tanh<T>>(new Tanh<T>(length)));
//	this->nb_layers++;
//	this->layer_list.push_back(layer_types::TANH);
//}
//
//template<typename T>
//void Sequential<T>::load_tanh(std::string fname)
//{
//	this->layer_list.push_back(layer_types::TANH);
//	std::string path = fname + "_" + std::to_string(this->nb_layers++) + "_" + get_layer_type(this->nb_layers);
//
//	layers.push_back(std::unique_ptr<Tanh<T>>(new Tanh<T>(path)));
//}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

//void Sequential::add_Log_softmax(int length)
//{
//	layers.push_back(std::unique_ptr<Log_softmax<T>>(new Log_softmax<T>(length)));
//	this->nb_layers++;
//}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
void Sequential<T>::add_dropout()
{
	layers.push_back(std::unique_ptr<Dropout<T>>(new Dropout<T>()));
	this->addlayer_counter++;
	this->nb_layers++;
	this->layer_list.push_back(layer_types::DROPOUT);
}

template<typename T>
void Sequential<T>::skip_layer()
{
	this->addlayer_counter++;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
Prop_vector<T> Sequential<T>::forward(Prop_vector<T> x)
{
	for (auto&& layer : this->layers) {
		x = layer->forward(x);
	}
	return x;
}

template<typename T>
Prop_vector<T> Sequential<T>::forward_save(Prop_vector<T> x, int img_nb)
{
	int it = this->start_layer;
	for (auto&& layer : this->layers) {
		x = layer->forward(x);
		x.save_vector(this->intermediate_path + std::to_string(img_nb) + "_"
			+ std::to_string(it++) + ".txt", false);
	}
	return x;
}

template<typename T>
void Sequential<T>::describe()
{
	std::cout << "----------------------" << std::endl;
	for (auto&& layer : this->layers) {
		std::cout << layer->name << std::endl;
	}
	std::cout << "----------------------" << std::endl;
}

template<typename T>
std::string Sequential<T>::get_layer_type(int layer_nb)
{	
	switch (layer_list[layer_nb]) {
	case layer_types::LINEAR:
		return "linear";
		break;
	case layer_types::CONV_2D:
		return "conv2d";
		break;
	case layer_types::MAXPOOL_2D:
		return "maxpool2d";
		break;
	case layer_types::FLATTEN:
		return "squeeze";
		break;
	case layer_types::RELU:
		return "relu";
		break;
	case layer_types::TANH:
		return "tanh";
		break;
	case layer_types::DROPOUT:
		return "dropout";
		break;
	default:
		return "_error!_";
		break;
	}
}

template<typename T>
void Sequential<T>::find_number_range(bool flag)
{
	this->find_number_range_flag = flag;
	for (auto&& layer : this->layers)
		layer->find_number_range_flag = this->find_number_range_flag;
}

template<typename T>
void Sequential<T>::print_number_range()
{
	int i = this->start_layer;
	if (this->find_number_range_flag) {
		for (auto&& layer : this->layers)
			layer->print_number_range(i++);
	}
	else
		std::cout << "Number range finder not enabled!" << std::endl;
}

#endif // !sequential_cpp