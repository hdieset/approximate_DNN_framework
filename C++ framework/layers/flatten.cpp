#ifndef flatten_cpp
#define flatten_cpp

#include "flatten.hpp"


template <typename T>
Flatten<T>::Flatten(int input_channels, int input_height, int input_width)
{
	this->input_channels = input_channels;
	this->input_height   = input_height;
	this->input_width    = input_width;
	this->output_length  = input_channels * input_height * input_width;
	this->name = "Flatten     [" + std::to_string(input_channels)
					       + "," + std::to_string(input_height)
						   + "," + std::to_string(input_width)
						   + "," + std::to_string(output_length) + "]";
}


template<typename T>
Prop_vector<T> Flatten<T>::forward(Prop_vector<T> x)
{
	Vector_3D<T> _x = x.get_vector_3d();
	Vector_1D<T> res(_x.channels * _x.height * _x.width, x.Q_int_bits);


	for (int ch = 0; ch < _x.channels; ch++)
		for (int h = 0; h < _x.height; h++)
			for (int w = 0; w < _x.width; w++) 
				res.data[ch * (_x.height * _x.width) + h * _x.width + w] = _x.data[ch][h][w];

	// Change Q format if needed
#if defined(QUANTIZE) && (Q_F_S_INT_BITS - Q_C_S_INT_BITS != 0)
	for (int i = 0; i < res.length; i++)
		res.data[i].set_new_intlen(Q_C_S_INT_BITS);
#endif

	return res.to_propvector();
}

#endif // !flatten_cpp