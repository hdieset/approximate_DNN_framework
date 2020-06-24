#ifndef convolutions_cpp
#define convolutions_cpp

#include <cmath>
#include <random>
#include <iostream>

#include "convolutions.hpp"
#include "../tools/tools.hpp"
#include "../Q.hpp"


template <typename T>
Conv_2D<T>::Conv_2D(std::string fname, int height, int width, int padding, bool bias, int stride)
{
	this->height  = height;
	this->width   = width;
	this->padding = padding;
	this->bias    = bias;
	this->stride  = stride;

	// Loading weights
	std::ifstream ifile(fname + "_w.txt");
	if (!ifile.is_open())
		load_failed(fname + "_w.txt");

	if (ifile.good()) {

		ifile >> this->output_channels;
		ifile >> this->input_channels;
		ifile >> this->kernel_size;

		double tmp;
		ifile >> tmp;

		this->w = Vector_4D<T>(this->output_channels, this->input_channels, this->kernel_size, this->kernel_size, 0);

		for (int o = 0; o < this->output_channels; o++)
			for (int i = 0; i < this->input_channels; i++)
				for (int kh = 0; kh < this->kernel_size; kh++)
					for (int kw = 0; kw < this->kernel_size; kw++) {
#ifdef QUANTIZE
						ifile >> tmp;
						this->w.data[o][i][kh][kw] = Q(tmp, Q_F_W_INT_BITS); // Conv always feature extraction
#else
						ifile >> this->w.data[o][i][kh][kw];
#endif
					}
	}
	else
		load_failed(fname + "_w.txt");

	ifile.close();
	
	// Loading bias
	if (this->bias) {
		std::ifstream ifile(fname + "_b.txt");
		if (!ifile.is_open())
			load_failed(fname + "_b.txt");

		if (ifile.good()) {
			double tmp;
			ifile >> tmp; // skip first line

			this->b = Vector_1D<T>(this->output_channels, 0);

			for (int o = 0; o < this->output_channels; o++) {
#ifdef QUANTIZE
				ifile >> tmp;
				this->b.data[o] = Q(tmp, Q_F_S_INT_BITS); // Conv always feature extraction
#else
				ifile >> this->b.data[o];
#endif
			}
		}
		else
			load_failed(fname + "_b.txt");

		ifile.close();
	}

	this->output_height = (int)std::floor((this->height + this->padding * 2 - this->kernel_size)/this->stride + 1);
	this->output_width  = (int)std::floor((this->width  + this->padding * 2 - this->kernel_size)/this->stride + 1);
	this->name = "conv_2d     [" + std::to_string(input_channels)
						   + "," + std::to_string(output_channels)
						   + "," + std::to_string(kernel_size)
						   + "," + std::to_string(stride)
						   + "," + std::to_string(this->height)
						   + "," + std::to_string(this->width)
						   + "," + std::to_string(this->output_height)
						   + "," + std::to_string(this->output_width) + "]";
}

template<typename T>
Prop_vector<T> Conv_2D<T>::forward(Prop_vector<T> x)
{
	Vector_3D<T> s(this->output_channels, this->output_height, this->output_width, x.Q_int_bits);

	Vector_3D<T> _x = x.get_vector_3d();
	if (this->padding != 0)
		_x = _x.zero_pad(this->padding);

#ifndef QUANTIZE
	if (this->find_number_range_flag) {
		for (int o = 0; o < this->output_channels; o++)	      				 // output channels
			for (int i = 0; i < this->input_channels; i++)       			 // input channels
				for (int sh = 0; sh < this->output_height; sh++)    		 // image height
					for (int sw = 0; sw < this->output_width; sw++)    		 // image width
						for (int kh = 0; kh < this->kernel_size; kh++)    	 // kernel height
							for (int kw = 0; kw < this->kernel_size; kw++) { // kernel width
								s.data[o][sh][sw] += _x.data[i][sh * this->stride + kh][sw * this->stride + kw] * this->w.data[o][i][kh][kw];
								if (this->num_max < s.data[o][sh][sw])
									this->num_max = s.data[o][sh][sw];
								if (this->num_min > s.data[o][sh][sw])
									this->num_min = s.data[o][sh][sw];
							}

		if (this->bias)
			for (int o = 0; o < this->output_channels; o++)
				for (int sh = 0; sh < this->output_height; sh++)
					for (int sw = 0; sw < this->output_width; sw++) {
						s.data[o][sh][sw] += this->b.data[o];
						if (this->num_max < s.data[o][sh][sw])
							this->num_max = s.data[o][sh][sw];
						if (this->num_min > s.data[o][sh][sw])
							this->num_min = s.data[o][sh][sw];
					}
	}
	else {
#endif // !QUANTIZE
		for (int o = 0; o < this->output_channels; o++)	 				   // output channels
			for (int i = 0; i < this->input_channels; i++)  			   // input channels
				for (int sh = 0; sh < this->output_height; sh++) 		   // image height
					for (int sw = 0; sw < this->output_width; sw++) 	   // image width
						for (int kh = 0; kh < this->kernel_size; kh++) 	   // kernel height
							for (int kw = 0; kw < this->kernel_size; kw++) // kernel width
								s.data[o][sh][sw] += _x.data[i][sh*this->stride + kh][sw*this->stride + kw] * this->w.data[o][i][kh][kw];

		if (this->bias)
			for (int o = 0; o < this->output_channels; o++)
				for (int sh = 0; sh < this->output_height; sh++)
					for (int sw = 0; sw < this->output_width; sw++)
						s.data[o][sh][sw] += this->b.data[o];
#ifndef QUANTIZE
	}
#endif // !QUANTIZE

	return s.to_propvector();
}

template<typename T>
void Conv_2D<T>::print_number_range(int i)
{
	std::cout << "Layer "         << std::to_string(i) 
		      << ": Conv2d: max " << std::to_string(this->num_max)
		      << ", min "         << std::to_string(this->num_min) << std::endl;
}

#endif // !convolutions_cpp