#ifndef activations_cpp
#define activations_cpp

#include <string>
#include <cmath>

#include "activations.hpp"
#include "../definitions.hpp"
#include "../t_custom_vectors.hpp"

template <typename T>
ReLU<T>::ReLU() {
	this->name = "ReLU";
}

template<typename T>
Prop_vector<T> ReLU<T>::forward(Prop_vector<T> x)
{
	Prop_vector<T> res(x.Q_int_bits);

	switch (x.type) {
	case vector_type::VECTOR_1D:

		res.vector_1d = Vector_1D<T>(x.vector_1d.length, x.Q_int_bits);
		res.type      = vector_type::VECTOR_1D;

		for (int i = 0; i < x.vector_1d.length; i++) {
#ifdef QUANTIZE
			if (x.vector_1d.data[i].v.test(Q_TOT_BITS - 1)) // negative
				res.vector_1d.data[i].v.reset();
			else
				res.vector_1d.data[i] = x.vector_1d.data[i];
#else
			if (x.vector_1d.data[i] < 0)
				res.vector_1d.data[i] = 0;
			else
				res.vector_1d.data[i] = x.vector_1d.data[i];
#endif // QUANTIZE

		}
		return res;
		break;

	case vector_type::VECTOR_2D:
		res.vector_2d = Vector_2D<T>(x.vector_2d.height, x.vector_2d.width, x.Q_int_bits);
		res.type      = vector_type::VECTOR_2D;

		for (int i = 0; i < res.vector_2d.height; i++) {
			for (int j = 0; j < res.vector_2d.width; j++) {
#ifdef QUANTIZE
				if (x.vector_2d.data[i][j].v.test(Q_TOT_BITS - 1))
					res.vector_2d.data[i][j].v.reset();
				else
					res.vector_2d.data[i][j] = x.vector_2d.data[i][j];
#else
				if (x.vector_2d.data[i][j] < 0)
					res.vector_2d.data[i][j] = 0;
				else
					res.vector_2d.data[i][j] = x.vector_2d.data[i][j];
#endif
			}
		}
		return res;
		break;

	case vector_type::VECTOR_3D:

		res.vector_3d = Vector_3D<T>(x.vector_3d.channels, x.vector_3d.height, x.vector_3d.width, x.Q_int_bits);
		res.type      = vector_type::VECTOR_3D;

		for (int ch = 0; ch < res.vector_3d.channels; ch++) {
			for (int i = 0; i < res.vector_3d.height; i++) {
				for (int j = 0; j < res.vector_3d.width; j++) {
#ifdef QUANTIZE
					if (x.vector_3d.data[ch][i][j].v.test(Q_TOT_BITS - 1))
						res.vector_3d.data[ch][i][j].v.reset();
					else
						res.vector_3d.data[ch][i][j] = x.vector_3d.data[ch][i][j];
#else
					if (x.vector_3d.data[ch][i][j] < 0)
						res.vector_3d.data[ch][i][j] = 0;
					else
						res.vector_3d.data[ch][i][j] = x.vector_3d.data[ch][i][j];
#endif
				}
			}
		}
		return res;
		break;

	default:
	case vector_type::VECTOR_4D:
	case vector_type::NONE:
		return Prop_vector<T>();
		break;
	}
}


#endif // !activations_cpp