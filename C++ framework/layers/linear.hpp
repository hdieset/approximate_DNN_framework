#ifndef linear_hpp
#define linear_hpp

#include "../t_custom_vectors.hpp"
#include "base_layer.hpp"


template <typename T = double>
class Linear : public base_layer<T> {
private:
	int input_size, nb_hidden;
	Vector_2D<T> w;
	Vector_1D<T> b;

public:
	Linear(std::string fname, bool use_pbar);

	Prop_vector<T> forward(Prop_vector<T> x);

	void print_number_range(int i);
};

#include "linear.cpp"

#endif // !linear_hpp