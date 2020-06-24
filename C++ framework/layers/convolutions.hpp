#ifndef convolutions_hpp
#define convolutions_hpp

#include "../t_custom_vectors.hpp"
#include "base_layer.hpp"


template <typename T = double>
class Conv_2D : public base_layer<T> {
private:
	int input_channels, output_channels;
	int output_height,  output_width;
	int height,         width;
	int kernel_size;
	int padding, stride;
	bool bias;
	
	Vector_4D<T> w;
	Vector_1D<T> b;

public:
	Conv_2D(std::string fname, int height, int width, int padding, bool bias, int stride);

	Prop_vector<T> forward(Prop_vector<T> x);

	void print_number_range(int i);
};

#include "convolutions.cpp"

#endif // !convolutions_hpp