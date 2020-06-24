#ifndef vgg16_cpp
#define vgg16_cpp

#include <thread>
#include <mutex>
#include <chrono>

#include "vgg16.hpp"
#include "../Q.hpp"
#include "../tools/tools.hpp"
#include "../definitions.hpp"

extern std::mutex mtx_images;
extern std::mutex mtx_parameters;
extern std::mutex mtx_pbar;


template <typename T>
VGG16<T>::VGG16()
{
	this->model_name  = "VGG16";
	this->thread_nb   = 0;
	this->layer_start = 0;
	this->layer_end   = 38;
	this->nb_layers   = this->layer_end - this->layer_start + 1;
	this->save_intermediates_flag = false;
	this->nb_intermediates		  = 0;
	this->find_number_range_flag  = false;
}


template<typename T>
VGG16<T>::VGG16(int nb_first)
{
	this->model_name  = "VGG16";
	this->thread_nb   = 0;
	this->layer_start = 0;
	this->layer_end   = nb_first;
	this->nb_layers   = this->layer_end - this->layer_start + 1;
	this->save_intermediates_flag = false;
	this->nb_intermediates		  = 0;
	this->find_number_range_flag  = false;
}

template<typename T>
VGG16<T>::VGG16(int from, int to)
{
	this->model_name  = "VGG16";
	this->thread_nb   = 0;
	this->layer_start = from;
	this->layer_end   = to;
	this->nb_layers   = this->layer_end - this->layer_start + 1;
	this->save_intermediates_flag = false;
	this->nb_intermediates		  = 0;
	this->find_number_range_flag  = false;
}

template<typename T>
void VGG16<T>::init(int thread_nb)
{
	progress_bar pbar;
	this->thread_nb   = thread_nb;
	int pbar_progress = 0;
	int layer_nb      = 0;

	// Only needing progress bar for first thread
	if (this->thread_nb == 0) pbar.new_bar(PROGRESS_BAR_WIDTH, this->nb_layers, "Loading VGG16");

	// 0
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		model.load_conv2d(224, 224, 1, true, 1); // padding, bias, stride
	}
	else model.skip_layer();
	
	layer_nb++; // 1
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 2
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(224, 224, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 3
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 4
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_maxpool2d(64, 224, 224, 2, 2);
	}
	else model.skip_layer();

	layer_nb++; // 5
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(112, 112, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 6
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 7
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(112, 112, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 8
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 9
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_maxpool2d(128, 112, 112, 2, 2);
	}
	else model.skip_layer();

	layer_nb++; // 10
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(56, 56, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 11
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 12
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(56, 56, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 13
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 14
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(56, 56, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 15
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 16
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_maxpool2d(256, 56, 56, 2, 2);
	}
	else model.skip_layer();

	layer_nb++; // 17
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(28, 28, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 18
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 19
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(28, 28, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 20
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 21 
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(28, 28, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 22
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 23
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_maxpool2d(512, 28, 28, 2, 2);
	}
	else model.skip_layer();

	layer_nb++; // 24
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(14, 14, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 25
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 26
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(14, 14, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 27
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();
	
	layer_nb++; // 28
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_conv2d(14, 14, 1, true, 1);
	}
	else model.skip_layer();

	layer_nb++; // 29
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();
	
	layer_nb++; // 30
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_maxpool2d(512, 14, 14, 2, 2);
	}
	else model.skip_layer();

	layer_nb++; // 31
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_flatten(512, 7, 7);
	}
	else model.skip_layer();
	
	layer_nb++; // 32
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) {
			pbar.remove();
			model.load_linear(true);
		}
		else {
			model.load_linear(false);
		}
	}
	else model.skip_layer();
	
	layer_nb++; // 33
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();
	
	layer_nb++; // 34
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_dropout();
	}
	else model.skip_layer();

	layer_nb++; // 35
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_linear(false);
	}
	else model.skip_layer();

	layer_nb++; // 36
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_relu();
	}
	else model.skip_layer();

	layer_nb++; // 37
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.add_dropout();
	}
	else model.skip_layer();

	layer_nb++; // 38
	if ((this->layer_start <= layer_nb) & (layer_nb <= this->layer_end)) {
		if (this->thread_nb == 0) pbar.update_progress(++pbar_progress);
		model.load_linear(false);
	}
	else model.skip_layer();

	if (this->thread_nb == 0) pbar.remove();
	return;
}

template<typename T>
void VGG16<T>::setname(std::string name)
{
	this->model_name = name;
}

template<typename T>
void VGG16<T>::save_intermediates(bool flag)
{
	this->save_intermediates_flag = flag;
	model.save_intermediates      = flag;
	model.intermediate_path      += "/" + this->model_name + "/";
}

template<typename T>
void VGG16<T>::save_intermediates(int nb)
{
	this->save_intermediates_flag = true;
	this->nb_intermediates	 = nb;
	model.save_intermediates = true;
	model.intermediate_path += "/" + this->model_name + "/";
}

template<typename T>
void VGG16<T>::find_number_ranges(bool flag)
{
	this->find_number_range_flag = flag;
#ifdef QUANTIZE // ILLEGAL!!
	std::cout << "Illegal number format for range finder! Exiting." << std::endl;
	exit(1);
#endif
}

template <typename T>
void th_inference_vgg16(int				     thread_nb,
                        IMAGENET_handler<T>& images,
						progress_bar&		 pbar,
						int					 layer_from,
						int					 layer_end,
						bool				 save_intermediates,
						bool				 find_num_range,
						std::string          modelname,
						int nb_intermediates)
{
	auto network     = VGG16<T>(layer_from, layer_end);
	int th_img_count = 0;
	int th_curr_img  = 0;
	IMAGENET_handler<T> saver(0); // only for saving images
	saver.set_network_name(modelname);

// ************ INITIALIZING THREAD *****************************************
	mtx_parameters.lock();
	network.init(thread_nb);
	mtx_parameters.unlock();

	network.setname(modelname);
	if (save_intermediates) {
		network.model.intermediate_path += saver.FOLDERNAME;
		network.model.start_layer        = layer_from;
		network.save_intermediates(save_intermediates);
	}
	network.model.find_number_range(find_num_range);
// **************************************************************************
	std::cout << "Thread " << std::to_string(thread_nb) << " ready!" << std::endl;

	if (INFERENCE_PROGRESS_BAR & ( thread_nb == 0) )
		pbar.new_bar(PROGRESS_BAR_WIDTH, images.tot_nb_images, "Running inference");

	while (true) {
// ************ LOADING NEW IMAGE *******************************************
		mtx_images.lock();
		Prop_vector<T> img = images.get_image();
		th_curr_img        = images.nb_used_images - 1;
		mtx_images.unlock();
// **************************************************************************

		if (img.type != vector_type::NONE) { 

			// RUNNING INFERENCE and saving output
			if (network.save_intermediates_flag & (th_curr_img < nb_intermediates)) {
				auto res = network.model.forward_save(img, th_curr_img);
				saver.save(res, th_curr_img, false);
			}
			else {
				auto res = network.model.forward(img);
				saver.save(res, th_curr_img, false);
			}

// *********** UPDATING PROGRESS BAR *************************************
			if (INFERENCE_PROGRESS_BAR & (thread_nb == 0)) {
				mtx_pbar.lock();
				pbar.update_progress(saver.nb_saved_images);
				mtx_pbar.unlock();
			}
// **************************************************************************
			
			std::cout << "Thread "           << std::to_string(thread_nb)
					  << " completed image " << std::to_string(th_curr_img) << std::endl;
			th_img_count++;
		}
		else {
			std::cout << "Thread "                       << std::to_string(thread_nb) 
			          << " finished. Total inferences: " << std::to_string(th_img_count) << std::endl;
			
			// ************** PRINTING NUMBER RANGES**********************************
			if (network.model.find_number_range_flag) {
				mtx_pbar.lock();
				std::cout << "Thread " << std::to_string(thread_nb) << " max/min:" << std::endl;
				network.model.print_number_range();
				mtx_pbar.unlock();
			}

			return;
		}
	}
}

template<typename T>
void VGG16<T>::infer(IMAGENET_handler<T> images)
{
	std::cout << "Started inference with VGG16 on ImageNet using "
		      << std::to_string(NB_THREADS) << " threads" << std::endl;

	images.set_network_name(this->model_name);

	if (this->layer_start != 0)
		images.set_intermediate_start(this->layer_start - 1, // load output from previous layer
			INTERMEDIATE_PATH + images.FOLDERNAME + "/" + this->model_name + "/");

	progress_bar pbar;

	std::vector<std::thread> threads;

	for (int i = 0; i < NB_THREADS; i++) {
		threads.push_back(
			std::thread(th_inference_vgg16<T>,
			            i,
						std::ref(images),
						std::ref(pbar),
						this->layer_start,
						this->layer_end,
						this->save_intermediates_flag,
						this->find_number_range_flag,
						this->model_name,
						this->nb_intermediates)
		);
		// allow thread 0 to load first
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	
	for (auto& t : threads) {
		t.join();
	}
	if (INFERENCE_PROGRESS_BAR)
		pbar.remove();
}


#endif // !vgg16_cpp