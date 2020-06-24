#ifndef activations_hpp
#define activations_hpp

#include "../t_custom_vectors.hpp"
#include "base_layer.hpp"


template <typename T = double>
class ReLU : public base_layer<T> {
private:

public:
	ReLU();
	Prop_vector<T> forward(Prop_vector<T> x);
};

#include "activations.cpp"

#endif // !activations_hpp