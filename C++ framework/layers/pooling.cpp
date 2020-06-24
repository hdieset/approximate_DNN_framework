#ifndef pooling_cpp
#define pooling_cpp

#include <cmath>

#include "pooling.hpp"

template <typename T>
MaxPool2D<T>::MaxPool2D(int channels, int input_height, int input_width, int kernel_size, int stride)
{
	this->channels      = channels;
	this->kernel_size   = kernel_size;
	this->stride        = stride;
	this->input_height  = input_height;
	this->input_width   = input_width;
	this->output_height = (int)std::floor((this->input_height - kernel_size) / stride) + 1;
	this->output_width  = (int)std::floor((this->input_width  - kernel_size) / stride) + 1;

	this->name = "MaxPool2D   [" + std::to_string(this->channels)
						   + "," + std::to_string(this->kernel_size)
						   + "," + std::to_string(this->stride)
						   + "," + std::to_string(this->input_height)
						   + "," + std::to_string(this->input_width)
						   + "," + std::to_string(this->output_height)
						   + "," + std::to_string(this->output_width) + "]";
}


template <typename U>
U max(U a, U b) {
#ifdef QUANTIZE
	return (a + b + (a - b).abs()) >> 1;
#else
	return (a + b + std::abs(a - b)) / 2; // note: >> with double is not allowed in C++
#endif
};


template<typename T>
Prop_vector<T> MaxPool2D<T>::forward(Prop_vector<T> x)
{
	Vector_3D<T> s(this->channels, this->output_height, this->output_width, x.Q_int_bits);
	Vector_3D<T> _x = x.get_vector_3d();

	for (int ch = 0; ch < this->channels; ch++)
		for (int sh = 0; sh < this->output_height; sh++)
			for (int sw = 0; sw < this->output_width; sw++) {

				s.data[ch][sh][sw] = _x.data[ch][sh * this->stride][sw * this->stride];
				
				for (int kh = 0; kh < this->kernel_size; kh++)
					for (int kw = 0; kw < this->kernel_size; kw++)
						s.data[ch][sh][sw] = max(s.data[ch][sh][sw],
												_x.data[ch][sh * this->stride + kh][sw * stride + kw]);
			}

	return s.to_propvector();
}

#endif // !pooling_cpp