#ifndef sequential_hpp
#define sequential_hpp

#include <vector>

#include "../t_custom_vectors.hpp"
#include "../definitions.hpp"

#include "activations.hpp"
#include "convolutions.hpp"
#include "pooling.hpp"
#include "linear.hpp"
#include "flatten.hpp"
#include "dropout.hpp"

enum class layer_types {LINEAR, CONV_2D, MAXPOOL_2D, FLATTEN, RELU, TANH, DROPOUT};


template <typename T = double>
class Sequential {
public:

	NETWORK_TYPE network_type;
	std::string  parameter_path, intermediate_path;
	bool         save_intermediates;
	bool         find_number_range_flag;
	int          start_layer;

	std::vector<std::unique_ptr<base_layer<T>>> layers;
	std::vector<layer_types>                    layer_list;
	int                                         addlayer_counter;
	int                                         nb_layers;

//*****************************************************************
	Sequential();
	Sequential(NETWORK_TYPE network_type);
	
	// Model creation
	void load_linear(bool use_pbar);

	void load_conv2d(int height, int width, int padding, bool bias, int stride);

	void add_maxpool2d(int channels, int input_height, int input_width, int kernel_size, int stride);

	void add_flatten(int input_channels, int input_height, int input_width);

	void add_relu();

	void add_dropout();

	void skip_layer();

	//void add_tanh(int length);
	//void load_tanh(std::string fname);
	//void add_Log_softmax(int length); 

	Prop_vector<T> forward(Prop_vector<T> x);
	Prop_vector<T> forward_save(Prop_vector<T> x, int img_nb);

	void describe();
	std::string get_layer_type(int layer_nb);
	void find_number_range(bool flag);
	void print_number_range();
};

#include "sequential.cpp"

#endif // !sequential_hpp