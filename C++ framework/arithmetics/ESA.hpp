#ifndef esa_hpp
#define esa_hpp

#include <functional>

#include "../Q.hpp"
#include "acc_full_adder_cell.hpp"


// Equal Segmentation Adder, RCA for accurate part
binary ESA(binary a, binary b, int group_length)
{
	binary res(0);

	int used_bits = 0;
	bool carry;

	while (used_bits < Q_TOT_BITS) {
		carry = 0;
		for (int i = used_bits; (i < used_bits + group_length) & (i != Q_TOT_BITS); i++)
			res[i] = acc_full_adder_cell(a.test(i), b.test(i), std::ref(carry));
		used_bits += group_length;
	}

	return res;
}


#endif // !esa_hpp