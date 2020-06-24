#ifndef highpass_filtering_hpp
#define highpass_filtering_cpp

#include <iostream>
#include "tools.hpp"
#include "../t_custom_vectors.hpp"


class highpass_filter {
public:
	std::string imagename;
	int Q_int_bits;
	int height, width;

	Vector_2D<Q> img, filtered;
	Vector_2D<Q> kernel;

	highpass_filter(std::string imagename, int Q_int_bits);

	void filter();
	void merge(double amount_of_filtered);
	void save(std::string fname);
};


#endif // !highpass_filtering_hpp