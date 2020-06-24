#ifndef highpass_filtering_cpp
#define highpass_filtering_cpp

#include <fstream>
#include <assert.h>
#include <iomanip>

#include "highpass_filtering.hpp"
#include "../definitions.hpp"

highpass_filter::highpass_filter(std::string imagename, int Q_int_bits)
{
#ifndef QUANTIZE
	assert(false);
#endif // !QUANTIZE

	this->imagename = imagename;
	this->Q_int_bits = Q_int_bits;

	// Loading image
	std::string imgpath = DATASET_PATH + "/Highpass/" + imagename + ".txt";
	std::ifstream ifile(imgpath);
	if (!ifile.is_open())
		load_failed(imgpath);

	if (ifile.good()) {
		double tmp;

		ifile >> tmp; // batches
		ifile >> tmp; // img channels
		ifile >> this->height;
		ifile >> this->width;

		this->img = Vector_2D<Q>(this->height, this->width, Q_int_bits);

		for (int h = 0; h < this->img.height; h++)
			for (int w = 0; w < this->img.width; w++) {
				ifile >> tmp;
				this->img.data[h][w] = Q(tmp, this->Q_int_bits);
			}
	}
	else {
		load_failed(imgpath);
	}
	ifile.close();

	// Loading kernel
	this->kernel = Vector_2D<Q>(3, 3, this->Q_int_bits);

	this->kernel.data[0][0] = Q(  3, Q_int_bits);
	this->kernel.data[0][1] = Q(  0, Q_int_bits);
	this->kernel.data[0][2] = Q( -3, Q_int_bits);
	this->kernel.data[1][0] = Q( 10, Q_int_bits);
	this->kernel.data[1][1] = Q(  0, Q_int_bits);
	this->kernel.data[1][2] = Q(-10, Q_int_bits);
	this->kernel.data[2][0] = Q(  3, Q_int_bits);
	this->kernel.data[2][1] = Q(  0, Q_int_bits);
	this->kernel.data[2][2] = Q( -3, Q_int_bits);

	// zero filtered
	this->filtered = Vector_2D<Q>(this->height, this->width, Q_int_bits);
	std::cout << "Initialized." << std::endl;
}

void highpass_filter::filter()
{
	// zero pad once
	Vector_2D<Q> tmp = this->img.zero_pad(1);

	// Convolve with stride 1, no dilation, no bias

	for (int sh = 0; sh < this->height; sh++)
		for (int sw = 0; sw < this->width; sw++)
			for (int kh = 0; kh < this->kernel.height; kh++)
				for (int kw = 0; kw < this->kernel.width; kw++)
					this->filtered.data[sh][sw] += tmp.data[sh + kh][sw + kw] * this->kernel.data[kh][kw];

	std::cout << "Filtered." << std::endl;
}

void highpass_filter::merge(double amount_of_filtered)
{
	assert(amount_of_filtered < 1);
	Q scale(amount_of_filtered, 1);

	for (int h = 0; h < this->height; h++)
		for (int w = 0; w < this->width; w++)
			this->img.data[h][w] += this->filtered.data[h][w] * scale;
}

void highpass_filter::save(std::string fname)
{
	std::string path = DATASET_PATH + "/Highpass/" + fname + ".txt";
	std::ofstream ofile(path);
	if (ofile.fail())
		save_failed(path);

	int precision = 8;//std::numeric_limits<double>::max_digits10;

	// Writing to file
	ofile << "1" << std::endl; // batch
	ofile << "1" << std::endl; // channels, monochomatic
	ofile << std::to_string(this->height) << std::endl; // height
	ofile << std::to_string(this->width) << std::endl; // width

	for (int h = 0; h < this->height; h++)
		for (int w = 0; w < this->width; w++)
			ofile << std::setprecision(precision) << this->img.data[h][w].get_double() << std::endl;

	ofile.close();
	
	std::cout << "Saved." << std::endl;
}


#endif // !highpass_filtering_cpp