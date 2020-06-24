#ifndef dropout_hpp
#define dropout_hpp

#include <string>

#include "../t_custom_vectors.hpp"
#include "base_layer.hpp"


template <typename T = double>
class Dropout : public base_layer<T> {
private:
	std::string name;
public:
	Dropout();
	Prop_vector<T> forward(Prop_vector<T> x);
};

#include "dropout.cpp"

#endif // !dropout_hpp