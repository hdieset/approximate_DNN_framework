#ifndef q_hpp
#define q_hpp

#include <bitset>

#include "definitions.hpp"

typedef std::bitset<Q_TOT_BITS> binary;

class Q {
public:
	int int_bits;
	int frac_bits;
	binary v;

	Q();
	//Q(double val);
	Q(double val, int int_bits);

	double get_double();
	void   set_new_intlen(int new_int_bitlen);

	binary double_to_Q(double val);
	binary take_2s_complement(binary in);
	double Q_to_double(binary in);
	void   print();

	Q  operator +  (Q   const& rhs);
	Q& operator += (Q   const& rhs);
	Q  operator -  (Q   const& rhs);
	Q  operator *  (Q   const& rhs);
	Q  operator << (int const& s);
	Q  operator >> (int const& s);
	Q  abs();

	Q approx_add(Q rhs, int parameter);
};

template <int B>
std::bitset<B> take_2s_complement(std::bitset<B> in);

// Linux-specific fix
#if WINDOWS == false
binary take_2s_complement(binary in);
#endif

void binary_print(binary in, int frac_bits);

//#include "Q.cpp"

#endif // !q_hpp