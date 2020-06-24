#ifndef acc_mult_hpp
#define acc_mult_hpp

#include "../definitions.hpp"
#include "../Q.hpp"
#include "acc_full_adder_cell.hpp"
#include "RCA.hpp"


Q ACC_MULT(Q a, Q b)
{
	const int tmp_bitlength = 2 * Q_TOT_BITS;
	std::bitset<tmp_bitlength> tmp(0), partial_prod(0);

	for (int i = 0; i < Q_TOT_BITS; i++) {
		if (b.v.test(i)) {

			partial_prod.reset();

			if (i == Q_TOT_BITS - 1)
				a.v = take_2s_complement<Q_TOT_BITS>(a.v);

			// Shifting
			for (int j = 0; j < Q_TOT_BITS; j++)
				partial_prod[i + j] = a.v[j];

			// Sign extension
			if (a.v.test(Q_TOT_BITS - 1))
				for (int j = Q_TOT_BITS + i - 1; j < tmp_bitlength; j++)
					partial_prod.set(j);

			// Summing of partial products
			tmp = RCA<tmp_bitlength>(tmp, partial_prod);
		}
	}

	Q res(0, a.int_bits);

	for (int i = b.frac_bits; i < Q_TOT_BITS + b.frac_bits; i++)
		if (tmp.test(i))
			res.v.set(i - b.frac_bits);

	return res;
}

#endif // !acc_mult_hpp
