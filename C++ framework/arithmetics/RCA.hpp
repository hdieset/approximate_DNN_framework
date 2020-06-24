#ifndef RCA_hpp
#define RCA_hpp

#include <functional>

#include "../Q.hpp"
#include "acc_full_adder_cell.hpp"

template <int B = Q_TOT_BITS>
std::bitset<B> RCA(std::bitset<B> a, std::bitset<B> b)
{
	std::bitset<B> res(0);
	bool carry = 0;
	for (int i = 0; i < B; i++) {
		res[i] = acc_full_adder_cell(a.test(i), b.test(i), std::ref(carry));
	}

	return res;
}

#endif // !RCA_hpp