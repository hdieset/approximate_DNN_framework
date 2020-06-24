#ifndef base_layer_hpp
#define base_layer_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "../t_custom_vectors.hpp"
#include "../definitions.hpp"

template <typename T = double>
class base_layer {
public: 
	std::string name;

	base_layer() { this->name		= "base_layer_dont_use";
				   this->num_max	= -999999;
				   this->num_min	=  999999;
				   this->Q_int_bits = Q_TOT_BITS;
	}
	
	virtual Prop_vector<T> forward(Prop_vector<T> x) { return Prop_vector<T>(); };

	int	   Q_int_bits;
	double num_max;
	double num_min;
	bool   find_number_range_flag;
	virtual void print_number_range(int i) { NULL; };
};

#endif // ! base_layer_hpp