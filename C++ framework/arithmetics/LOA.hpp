#ifndef loa_hpp
#define loa_hpp

#include <functional>

#include "../Q.hpp"
#include "acc_full_adder_cell.hpp"

// Lower-part Or Adder, RCA for accurate part
binary LOA(binary a, binary b, int border)
{
	binary res(0);

	for (int i = 0; i < border; i++)
		if (a.test(i) || b.test(i))
			res.set(i);

	// RCA
	bool carry = (a.test(border-1) && b.test(border-1));
	for (int i = border; i < Q_TOT_BITS; i++)
		res[i] = acc_full_adder_cell(a.test(i), b.test(i), std::ref(carry));

	return res;
}


#endif // !loa_hpp