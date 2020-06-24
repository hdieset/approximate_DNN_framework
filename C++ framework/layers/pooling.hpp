#ifndef pooling_h
#define pooling_h

#include "../t_custom_vectors.hpp"
#include "base_layer.hpp"


template <typename T = double>
class MaxPool2D : public base_layer<T> {
private:
	int channels; // input_channels = output_channels
	int kernel_size,   stride;
	int input_height,  input_width;
	int output_height, output_width;

public:
	MaxPool2D(int channels, int input_height, int input_width, int kernel_size, int stride);
	
	Prop_vector<T> forward(Prop_vector<T> x);
};

#include "pooling.cpp"

#endif // !pooling_hpp