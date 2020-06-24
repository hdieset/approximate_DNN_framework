#ifndef dropout_cpp
#define dropout_cpp

#include "dropout.hpp"

template <typename T>
Dropout<T>::Dropout()
{
	this->name = "dropout     []";
}

template <typename T>
Prop_vector<T> Dropout<T>::forward(Prop_vector<T> x)
{
	return x; // pass
}

#endif // !dropout_cpp