#ifndef flatten_hpp
#define flatten_hpp

#include "../t_custom_vectors.hpp"
#include "base_layer.hpp"


template <typename T = double>
class Flatten : public base_layer<T> {
private:
	int input_channels, input_height, input_width;
	int output_length;

public:
	Flatten(int input_channels, int input_height, int input_width);

	Prop_vector<T> forward(Prop_vector<T> x);
};

#include "flatten.cpp"

#endif // !flatten_hpp