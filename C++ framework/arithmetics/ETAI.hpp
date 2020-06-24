#ifndef etai_hpp
#define etai_hpp

#include <functional>

#include "../Q.hpp"
#include "acc_full_adder_cell.hpp"

// Error Tolerant Adder Type 1
binary ETAI(binary a, binary b, int border)
{
	binary res(0);

	for (int i = border - 1; i >= 0; i--) {
		if (a.test(i) ^ b.test(i)) { // XOR
			res.set(i); 
		}
		else if (a.test(i) & b.test(i)) {
			for (int j = i; j >= 0; j--)
				res.set(j);
			break;
		}
	}

	// RCA for accurate part
	bool carry = 0;
	for (int i = border; i < Q_TOT_BITS; i++)
		res[i] = acc_full_adder_cell(a.test(i), b.test(i), std::ref(carry));

	return res;
}

#endif // !etai_hpp