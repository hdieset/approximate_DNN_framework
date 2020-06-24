#ifndef booth_acc_hpp
#define booth_acc_hpp

#include "../Q.hpp"
#include "RCA.hpp"

Q BOOTH_ACC(Q A, Q B)
{
	bool a = 0;
	bool p = 0; // for arithmetic shift
	Q _P(0, A.int_bits);
	int n = Q_TOT_BITS;
	Q _B(0, B.int_bits);
	_B.v = take_2s_complement(B.v); // -B

	while (n != 0) {

		if ((A.v.test(0)) & (!a))			    // Aa = 10
			_P.v = RCA<Q_TOT_BITS>(_P.v, _B.v); // _P = _P - B
		else if ((!A.v.test(0)) & (a))			// Aa = 01
			_P.v = RCA<Q_TOT_BITS>(_P.v, B.v);  // _P = _P + B
		// else no op

		// arithmetic right shifting _P -> A -> a 
		a = A.v.test(0);

		A.v >>= 1;

		A.v.set(Q_TOT_BITS - 1, _P.v.test(0));

		p = _P.v.test(Q_TOT_BITS - 1);
		_P.v >>= 1;
		_P.v.set(Q_TOT_BITS - 1, p);

		n--;
	}

	// Answer is _PA, but we truncate 
	A.v >>= B.frac_bits;
	for (int i = 0; i < B.frac_bits; i++)
		A.v.set(Q_TOT_BITS - B.frac_bits + i, _P.v.test(i));

	return A;
}

#endif // !booth_acc_hpp