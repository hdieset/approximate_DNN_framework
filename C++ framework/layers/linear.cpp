#ifndef linear_cpp
#define linear_cpp

#include <string>
#include <iostream>

#include "linear.hpp"
#include "../tools/tools.hpp"
#include "../Q.hpp"


template<typename T>
Linear<T>::Linear(std::string fname, bool use_pbar)
{
	// Loading weights
	{
		std::ifstream ifile(fname + "_w.txt");
		if (!ifile.is_open())
			load_failed(fname + "_w.txt");

		if (ifile.good()) {
			ifile >> this->nb_hidden;
			ifile >> this->input_size;

			progress_bar pbar;
			if (use_pbar)
				pbar.new_bar(PROGRESS_BAR_WIDTH, this->nb_hidden, "Loading linear layer");

			this->w = Vector_2D<T>(this->nb_hidden, this->input_size, Q_C_W_INT_BITS);

#ifdef QUANTIZE
			double tmp;
#endif
			for (int i = 0; i < this->nb_hidden; i++) {
				if (use_pbar & (i % 10 == 0))
					pbar.update_progress(i);

				for (int j = 0; j < this->input_size; j++) {
#ifdef QUANTIZE
					ifile >> tmp;
					this->w.data[i][j] = Q(tmp, Q_C_W_INT_BITS); // linear always classification
#else
					ifile >> this->w.data[i][j];
#endif
				}
			}

			if (use_pbar)
				pbar.remove();
		}
		else
			load_failed(fname + "_w.txt");

		ifile.close();
	} {
		std::ifstream ifile(fname + "_b.txt");
		if (!ifile.is_open())
			load_failed(fname + "_b.txt");

		if (ifile.good()) {

			double tmp;
			ifile >> tmp; // skip first line

			this->b = Vector_1D<T>(this->nb_hidden, Q_C_S_INT_BITS);

			for (int i = 0; i < this->nb_hidden; i++) {
#ifdef QUANTIZE
				ifile >> tmp;
				this->b.data[i] = Q(tmp, Q_C_S_INT_BITS);
#else
				ifile >> this->b.data[i];
#endif

			}
		}
		else
			load_failed(fname + "_w.txt");
	}

	this->name = "linear      [" + std::to_string(input_size)
						   + ',' + std::to_string(nb_hidden) + ']';
}

template<typename T>
Prop_vector<T> Linear<T>::forward(Prop_vector<T> x)
{
	Vector_1D<T> _x = x.get_vector_1d();

	Vector_1D<T> s(this->nb_hidden, x.Q_int_bits);

#ifndef QUANTIZE
	if (this->find_number_range_flag)
		for (int o = 0; o < this->nb_hidden; o++) {	 // # outputs
			for (int i = 0; i < this->input_size; i++) {
				s.data[o] += this->w.data[o][i] * _x.data[i];
				if (this->num_max < s.data[0])
					this->num_max = s.data[0];
				if (this->num_min > s.data[0])
					this->num_min = s.data[0];
			}
			s.data[o] += this->b.data[o];
			if (this->num_max < s.data[0])
				this->num_max = s.data[0];
			if (this->num_min > s.data[0])
				this->num_min = s.data[0];
		}
	else
#endif // !QUANTIZE
		for (int o = 0; o < this->nb_hidden; o++) {	 // # outputs
			for (int i = 0; i < this->input_size; i++) {
				s.data[o] += _x.data[i] * this->w.data[o][i];
			}
			s.data[o] += this->b.data[o];
		}

	return s.to_propvector();
}

template<typename T>
void Linear<T>::print_number_range(int i)
{
	std::cout << "Layer "         << std::to_string(i)
		      << ": Linear: max " << std::to_string(this->num_max)
		      << ", min "         << std::to_string(this->num_min) << std::endl;
}

#endif // !linear_cpp