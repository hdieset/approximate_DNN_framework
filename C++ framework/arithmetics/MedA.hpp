#ifndef meda_hpp
#define meda_hpp

#include <functional>

#include "../Q.hpp"
#include "acc_full_adder_cell.hpp"

// Median Approximate Adder
binary MedA(binary a, binary b, int border)
{
	binary res(0);

	// border - 1 is zero
	for (int i = border - 2; i >= 0; i--)
		res.set(i);

	// RCA
	bool carry = 0;
	for (int i = border; i < Q_TOT_BITS; i++)
		res[i] = acc_full_adder_cell(a.test(i), b.test(i), std::ref(carry));

	return res;
}

#endif // !meda_hpp