#ifndef booth_acc_4_hpp
#define booth_acc_4_hpp

#include <assert.h>

#include "../Q.hpp"
#include "RCA.hpp"

Q BOOTH_ACC_RAD4(Q A, Q B)
{
	bool a = 0;
	bool p = 0; // for arithmetics shift
	Q _P(0, A.int_bits);
	int n = Q_TOT_BITS;
	Q _B(0, B.int_bits);
	_B.v = take_2s_complement(B.v); // -B

	assert(n % 2 == 0); // n is even
	
	while (n != 0) {

		if ( (!A.v.test(1) & !A.v.test(0) &  a)      // 001
		   | (!A.v.test(1) &  A.v.test(0) & !a))     // 010
			_P.v = RCA<Q_TOT_BITS>(_P.v, B.v);       // _P = _P + B

		else if (!A.v.test(1) & A.v.test(0) & a)     // 011
			_P.v = RCA<Q_TOT_BITS>(_P.v, B.v << 1);  // _P = _P + 2B
		
		else if (A.v.test(1) & !A.v.test(0) & !a)    // 100
			_P.v = RCA<Q_TOT_BITS>(_P.v, _B.v << 1); // _P = _P - 2B

		else if ( (A.v.test(1) & !A.v.test(0) &  a)  // 101
			    | (A.v.test(1) &  A.v.test(0) & !a)) // 110
			_P.v = RCA<Q_TOT_BITS>(_P.v, _B.v);      // _P = _P - B
		// else no op

		// arithmetic right shift _P -> A -> a twice
		a = A.v.test(1);

		A.v >>= 2;
		A.v.set(Q_TOT_BITS - 1, _P.v.test(1));
		A.v.set(Q_TOT_BITS - 2, _P.v.test(0));

		p = _P.v.test(Q_TOT_BITS - 1);
		_P.v >>= 2;
		_P.v.set(Q_TOT_BITS - 1, p);
		_P.v.set(Q_TOT_BITS - 2, p);

		n -= 2;
	}

	// Answer is _PA, but we truncate 
	A.v >>= B.frac_bits;
	for (int i = 0; i < B.frac_bits; i++)
		A.v.set(Q_TOT_BITS - B.frac_bits + i, _P.v.test(i));

	return A;
}

#endif // !booth_acc_4_hpp