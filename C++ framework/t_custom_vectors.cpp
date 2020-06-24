#ifndef t_custom_vectors_cpp
#define t_custom_vectors_cpp

#include <iostream>
#include <assert.h>
#include <cmath>
#include <fstream>
#include <iomanip>

#include "t_custom_vectors.hpp"
#include "tools/tools.hpp"
#include "definitions.hpp"
#include "Q.hpp"


template<typename T>
Vector_1D<T>::Vector_1D()
{
	this->length = 0;
}

template <typename T>
Vector_1D<T>::Vector_1D(int length) {
#ifdef QUANTIZE
	assert(false);
#else
	this->length = length;
	this->data.resize(length, 0);
#endif
}

template<typename T>
Vector_1D<T>::Vector_1D(int length, int Q_int_bits)
{
#ifdef QUANTIZE
	this->length = length;

	this->data.resize(length);
	for (int i = 0; i < this->length; i++)
		this->data[i] = Q(0, Q_int_bits);
#else
	this->length = length;
	this->data.resize(length, 0);
#endif // QUANTIZE
}

template<class T>
void Vector_1D<T>::print()
{
#ifdef QUANTIZE
	for (int i = 0; i < this->length; i++)
		this->data[i].print();
#else
	for (int i = 0; i < this->length; i++)
		std::cout << " " << this->data[i];
	std::cout << std::endl;
#endif
}


template<typename T>
Vector_1D<T> Vector_1D<T>::zero_pad(int nb)
{
#ifdef QUANTIZE
	int Q_intbits = this->data[0].int_bits;
	Vector_1D<T> res(this->length + 2 * nb, Q_intbits);
#else
	Vector_1D<T> res(this->length + 2*nb);
#endif

	for (int i = 0; i < this->length; i++)
		res.data[i+nb] = this->data[i];
	
	return res;
}

template<typename T>
Prop_vector<T> Vector_1D<T>::to_propvector()
{
	Prop_vector<T> res;
	res.type       = vector_type::VECTOR_1D;
	res.vector_1d  = *this;
#ifdef QUANTIZE
	res.Q_int_bits = this->data[0].int_bits;
#endif
	return res;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
Vector_2D<T>::Vector_2D() {
	this->height = 0;
	this->width  = 0;
}

template<typename T>
Vector_2D<T>::Vector_2D(int height, int width)
{
#ifdef QUANTIZE
	assert(false);
#else
	this->height = height;
	this->width  = width;
	this->data.resize(this->height, std::vector<T>(this->width, 0));
#endif
}

template<typename T>
Vector_2D<T>::Vector_2D(int height, int width, int Q_int_bits)
{
#ifdef QUANTIZE
	this->height = height;
	this->width  = width;

	this->data.resize(this->height, std::vector<T>(this->width));
	for (int h = 0; h < this->height; h++)
		for (int w = 0; w < this->width; w++)
			this->data[h][w] = Q(0, Q_int_bits);
#else
	this->height = height;
	this->width  = width;
	this->data.resize(this->height, std::vector<T>(this->width, 0));
#endif
}

template<typename T>
void Vector_2D<T>::print()
{
#ifdef QUANTIZE
	for (int h = 0; h < this->height; h++) {
		for (int w = 0; w < this->width; w++)
			this->data[h][w].print();
		std::cout << std::endl;
	}
#else
	for (const auto& row : data) {
		for (const auto& elem : row)
			std::cout << ' ' << elem;
		std::cout << std::endl;
	}
#endif
}

template<typename T>
Vector_2D<T> Vector_2D<T>::zero_pad(int nb)
{
#ifdef QUANTIZE
	int Q_intbits = this->data[0][0].int_bits;
	Vector_2D<T> res(this->height + 2 * nb, this->width + 2 * nb, Q_intbits);
#else
	Vector_2D<T> res(this->height + 2*nb, this->width + 2*nb);
#endif

	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			res.data[i + nb][j + nb] = this->data[i][j];

	return res;
}

template<typename T>
Prop_vector<T> Vector_2D<T>::to_propvector()
{
	Prop_vector<T> res;
	res.type      = vector_type::VECTOR_2D;
	res.vector_2d = *this;
#ifdef QUANTIZE
	res.Q_int_bits = this->data[0][0].int_bits;
#endif
	return res;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
Vector_3D<T>::Vector_3D() {
	this->channels = 0;
	this->height   = 0;
	this->width    = 0;
}

template<typename T>
Vector_3D<T>::Vector_3D(int channels, int height, int width)
{
#ifdef QUANTIZE
	assert(false);
#else
	this->channels = channels;
	this->height   = height;
	this->width    = width;

	this->data.resize(this->channels,
		  std::vector(this->height,
		  std::vector<T>(this->width, 0)
		)
	);
#endif
}

template<typename T>
Vector_3D<T>::Vector_3D(int channels, int height, int width, int Q_int_bits)
{
#ifdef QUANTIZE
	this->channels = channels;
	this->height = height;
	this->width = width;

	this->data.resize(this->channels,
		std::vector(this->height,
			std::vector<T>(this->width)
		)
	);
	for (int c = 0; c < this->channels; c++)
		for (int h = 0; h < this->height; h++)
			for (int w = 0; w < this->width; w++)
				this->data[c][h][w] = Q(0, Q_int_bits);
#else
	this->channels = channels;
	this->height   = height;
	this->width    = width;

	this->data.resize(this->channels,
		  std::vector(this->height,
		  std::vector<T>(this->width, 0)
		)
	);
#endif
}

template<typename T>
void Vector_3D<T>::print()
{
#ifdef QUANTIZE
	for (int ch = 0; ch < this->channels; ch++) {
		std::cout << "Ch: " << ch << std::endl;
		for (int h = 0; h < this->height; h++) {
			for (int w = 0; w < this->width; w++)
				this->data[ch][h][w].print();
			std::cout << std::endl;
		}
	}
#else
	for (int ch = 0; ch < this->channels; ch++) {
		std::cout << "Ch: " << ch << std::endl;
		for (const auto& row : data[ch]) {
			for (const auto& elem : row)
				std::cout << " " << elem;
			std::cout << std::endl;
		}
	}
#endif // QUANTIZE
}


template<typename T>
Vector_3D<T> Vector_3D<T>::zero_pad(int nb)
{
#ifdef QUANTIZE
	int Q_intbits = this->data[0][0][0].int_bits;
	Vector_3D<T> res(this->channels, this->height + 2 * nb, this->width + 2 * nb, Q_intbits);
#else
	Vector_3D<T> res(this->channels, this->height + 2 * nb, this->width + 2 * nb);
#endif

	for (int ch = 0; ch < this->channels; ch++)
		for (int i = 0; i < this->height; i++)
			for (int j = 0; j < this->width; j++)
				res.data[ch][i + nb][j + nb] = this->data[ch][i][j];

	return res;
}

template<typename T>
Prop_vector<T> Vector_3D<T>::to_propvector()
{
	Prop_vector<T> res;
	res.type      = vector_type::VECTOR_3D;
	res.vector_3d = *this;
#ifdef QUANTIZE
	res.Q_int_bits = this->data[0][0][0].int_bits;
#endif
	return res;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
Vector_4D<T>::Vector_4D() {
	this->input_channels  = 0;
	this->output_channels = 0;
	this->height          = 0;
	this->width           = 0;
}

template<typename T>
Vector_4D<T>::Vector_4D(int output_channels, int input_channels, int height, int width)
{
#ifdef QUANTIZE
	assert(false);
#else
	this->input_channels  = input_channels;
	this->output_channels = output_channels;
	this->height          = height;
	this->width           = width;

	this->data.resize(this->output_channels,
		  std::vector(this->input_channels,
		  std::vector(this->height,
		  std::vector<T>(this->width, 0)
			)
		)
	);
#endif
}

template<typename T>
Vector_4D<T>::Vector_4D(int output_channels, int input_channels, int height, int width, int Q_int_bits)
{
#ifdef QUANTIZE
	this->input_channels  = input_channels;
	this->output_channels = output_channels;
	this->height		  = height;
	this->width			  = width;

	this->data.resize(this->output_channels,
		std::vector(this->input_channels,
			std::vector(this->height,
				std::vector<T>(this->width)
			)
		)
	);

	for (int o = 0; o < this->output_channels; o++)
		for (int i = 0; i < this->input_channels; i++)
			for (int h = 0; h < this->height; h++)
				for (int w = 0; w < this->width; w++)
					this->data[o][i][h][w] = Q(0, Q_int_bits);
#else
	this->input_channels  = input_channels;
	this->output_channels = output_channels;
	this->height          = height;
	this->width           = width;

	this->data.resize(this->output_channels,
		  std::vector(this->input_channels,
		  std::vector(this->height,
		  std::vector<T>(this->width, 0)
			)
		)
	);
#endif
}

template<typename T>
void Vector_4D<T>::print()
{
	for (int ch_out = 0; ch_out < this->output_channels; ch_out++) {
		for (int ch_in = 0; ch_in < this->input_channels; ch_in++) {
			std::cout << "Ch_out: " << ch_in << " ch_in: " << ch_out << std::endl;
#ifdef QUANTIZE
			for (int h = 0; h < this->height; h++) {
				for (int w = 0; w < this->width; w++)
					this->data[ch_out][ch_in][h][w].print();
				std::cout << std::endl;
			}
#else
			for (const auto& row : data[ch_out][ch_in]) {
				for (const auto& elem : row)
					std::cout << " " << elem;
				std::cout << std::endl;
			}
#endif
		}
	}
}

template<typename T>
Prop_vector<T> Vector_4D<T>::to_propvector()
{
	Prop_vector<T> res;
	res.type      = vector_type::VECTOR_4D;
	res.vector_4d = *this;
#ifdef QUANTIZE
	res.Q_int_bits = this->data[0][0][0][0].int_bits;
#endif
	return res;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

template<typename T>
Prop_vector<T>::Prop_vector() {
	this->type = vector_type::NONE;
}

template<typename T>
Prop_vector<T>::Prop_vector(int Q_int_bits)
{
	Prop_vector();
	this->Q_int_bits = Q_int_bits;
}

template<typename T>
void Prop_vector<T>::save_vector(std::string filepath, bool use_pbar)
{
	std::ofstream ofile(filepath);
	if (ofile.fail())
		save_failed(filepath);

	int precision = std::numeric_limits<double>::max_digits10;

	switch (this->type)
	{
	case vector_type::NONE:
		break;

	case vector_type::VECTOR_1D:
	{
		progress_bar pbar;
		if (use_pbar)
			pbar.new_bar(PROGRESS_BAR_WIDTH, this->vector_1d.length, "Saving");

		ofile << "1" << std::endl; // batch
		ofile << "1" << std::endl; // channels
		ofile << "1" << std::endl; // height
		ofile << std::to_string(this->vector_1d.length) << std::endl; // width

		for (int i = 0; i < this->vector_1d.length; i++) {
#ifdef QUANTIZE
			ofile << std::setprecision(precision) << this->vector_1d.data[i].get_double() << std::endl;
#else
			ofile << std::setprecision(precision) << this->vector_1d.data[i] << std::endl;
#endif // QUANTIZE

			if (use_pbar & (i % 1000 == 0))
				pbar.update_progress(i);
		}
		if (use_pbar)
			pbar.remove();
	}
		break;

	case vector_type::VECTOR_2D:
	{
		progress_bar pbar;
		if (use_pbar)
			pbar.new_bar(PROGRESS_BAR_WIDTH, this->vector_2d.height, "Saving");

		ofile << "1" << std::endl; // batch
		ofile << "1" << std::endl; // channels
		ofile << std::to_string(this->vector_2d.height) << std::endl; // height
		ofile << std::to_string(this->vector_2d.width)  << std::endl; // width

		for (int h = 0; h < this->vector_2d.height; h++) {
			for (int w = 0; w < this->vector_2d.width; w++)
#ifdef QUANTIZE
				ofile << std::setprecision(precision) << this->vector_2d.data[h][w].get_double() << std::endl;
#else
				ofile << std::setprecision(precision) << this->vector_2d.data[h][w] << std::endl;
#endif
			if (use_pbar)
				pbar.update_progress(h);
		}

		if (use_pbar)
			pbar.remove();
	}
		break;

	case vector_type::VECTOR_3D:
	{
		progress_bar pbar;
		if (use_pbar)
			pbar.new_bar(PROGRESS_BAR_WIDTH, this->vector_3d.channels, "Saving");

		ofile << "1" << std::endl; // batch
		ofile << std::to_string(this->vector_3d.channels) << std::endl; // channels
		ofile << std::to_string(this->vector_3d.height)   << std::endl; // height
		ofile << std::to_string(this->vector_3d.width)    << std::endl; // width

		for (int ch = 0; ch < this->vector_3d.channels; ch++) {
			for (int h = 0; h < this->vector_3d.height; h++)
				for (int w = 0; w < this->vector_3d.width; w++)
#ifdef QUANTIZE
					ofile << std::setprecision(precision) << this->vector_3d.data[ch][h][w].get_double() << std::endl;
#else
					ofile << std::setprecision(precision) << this->vector_3d.data[ch][h][w] << std::endl;
#endif
			if (use_pbar)
				pbar.update_progress(ch);
		}

		if (use_pbar)
			pbar.remove();
	}
		break;

	case vector_type::VECTOR_4D:
	{
		progress_bar pbar;
		if (use_pbar)
			pbar.new_bar(PROGRESS_BAR_WIDTH, this->vector_4d.input_channels * this->vector_4d.output_channels, "Saving");

		ofile << std::to_string(this->vector_4d.input_channels)  << std::endl; // batch
		ofile << std::to_string(this->vector_4d.output_channels) << std::endl; // channels
		ofile << std::to_string(this->vector_4d.height)          << std::endl; // height
		ofile << std::to_string(this->vector_4d.width)           << std::endl; // width

		for (int bz = 0; bz < this->vector_4d.input_channels; bz++)
			for (int ch = 0; ch < this->vector_4d.output_channels; ch++) {
				for (int h = 0; h < this->vector_4d.height; h++)
					for (int w = 0; w < this->vector_4d.width; w++)
#ifdef QUANTIZE
						ofile << std::setprecision(precision) << this->vector_4d.data[bz][ch][h][w].get_double() << std::endl;
#else
						ofile << std::setprecision(precision) << this->vector_4d.data[bz][ch][h][w] << std::endl;
#endif
				if (use_pbar)
					pbar.update_progress(bz * this->vector_4d.output_channels + ch);
			}

		if (use_pbar)
			pbar.remove();
	}
		break;
	default:
		break;
	}

	ofile.close();
}

template<typename T>
Vector_1D<T> Prop_vector<T>::get_vector_1d()
{
	assert(this->type == vector_type::VECTOR_1D);
	return vector_1d;
}

template<typename T>
Vector_2D<T> Prop_vector<T>::get_vector_2d()
{
	assert(this->type == vector_type::VECTOR_2D);
	return vector_2d;
}

template<typename T>
Vector_3D<T> Prop_vector<T>::get_vector_3d()
{
	assert(this->type == vector_type::VECTOR_3D);
	return vector_3d;
}

template<typename T>
Vector_4D<T> Prop_vector<T>::get_vector_4d()
{
	assert(this->type == vector_type::VECTOR_4D);
	return vector_4d;
}

#endif