#ifndef apa_hpp
#define apa_hpp

#include <functional>

#include "../Q.hpp"
#include "acc_full_adder_cell.hpp"

// Alternating Passthrough Adder (my adder design)
binary APA(binary a, binary b, int border)
{
	binary res(0);

	for (int i = 0; i < border; i++) {
		if (i % 2 == 0) {
			if (a.test(i))
				res.set(i);
		}
		else {
			if (b.test(i))
				res.set(i);
		}
	}

	// RCA
	bool carry = 0;
	for (int i = border; i < Q_TOT_BITS; i++)
		res[i] = acc_full_adder_cell(a.test(i), b.test(i), std::ref(carry));

	return res;
}


#endif // !apa_hpp