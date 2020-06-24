#ifndef trua_hpp
#define trua_hpp

#include <functional>

#include "../Q.hpp"
#include "acc_full_adder_cell.hpp"

// Truncation adder, RCA for accurate part
binary TruA(binary a, binary b, int border)
{
	binary res(0);

	// bits up to border are zero

	// RCA
	bool carry = 0;
	for (int i = border; i < Q_TOT_BITS; i++)
		res[i] = acc_full_adder_cell(a.test(i), b.test(i), std::ref(carry));

	return res;
}


#endif // !trua_hpp