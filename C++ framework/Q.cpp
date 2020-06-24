#ifndef q_cpp
#define q_cpp

#include <cmath>
#include <iostream>
#include <string>
#include <assert.h>

#include "Q.hpp"

#include "arithmetics/acc_naive_multiplier.hpp"
#include "arithmetics/acc_full_adder_cell.hpp"
#include "arithmetics/RCA.hpp"
#include "arithmetics/LOA.hpp"
#include "arithmetics/ESA.hpp"
#include "arithmetics/TruA.hpp"
#include "arithmetics/APA.hpp"
#include "arithmetics/APAII.hpp"
#include "arithmetics/ETAI.hpp"
#include "arithmetics/MedA.hpp"
#include "arithmetics/booth_acc.hpp"
#include "arithmetics/booth_acc_4.hpp"


Q::Q()
{
	this->int_bits = Q_TOT_BITS;
	this->frac_bits = 0;
	this->v.reset();
}

Q::Q(double val, int int_bits)
{
	this->int_bits = int_bits;
	this->frac_bits = Q_TOT_BITS - int_bits;
	this->v			= double_to_Q(val);
}

double Q::get_double()
{
	return Q_to_double(this->v);
}

void Q::set_new_intlen(int new_int_bitlen)
{
	if (new_int_bitlen > this->int_bits) {
		bool signbit = this->v[Q_TOT_BITS - 1];
		this->v >>= (new_int_bitlen - this->int_bits);
		for (int i = Q_TOT_BITS - (new_int_bitlen - this->int_bits); i < Q_TOT_BITS; i++)
			this->v.set(i, signbit);
	}
	else {
		this->v <<= (this->int_bits - new_int_bitlen);
	}

	this->int_bits = new_int_bitlen;
	this->frac_bits = Q_TOT_BITS - this->int_bits;
}

binary Q::double_to_Q(double val)
{
	bool is_positive;
	if (val > 0) {
		is_positive = true;
	}
	else {
		is_positive = false;
		val         = std::abs(val);
	}

	binary res(val * std::pow(2, this->frac_bits));

	return (is_positive) ? res : take_2s_complement(res);
}

binary Q::take_2s_complement(binary in)
{
	in = ~in;
	// Always use accurate arithmetics here
	return RCA<Q_TOT_BITS>(in, binary(1));
}

double Q::Q_to_double(binary in)
{
	if (in.test(in.size() - 1)) { // negative
		return -(double)take_2s_complement(in).to_ulong() * std::pow(2, -this->frac_bits);
	}
	else {
		return (double)in.to_ulong() * std::pow(2, -this->frac_bits);
	}
}

void Q::print()
{
	for (int i = Q_TOT_BITS - 1; i >= this->frac_bits; i--)
		std::cout << this->v[i];

	std::cout << ".";

	for (int i = this->frac_bits - 1; i >= 0; i--)
		std::cout << this->v[i];

	std::cout << " = " << std::to_string(get_double()) << std::endl;
}

/******************************** arithmetics *******************************/

Q Q::operator+(Q const& rhs)
{
	assert(this->frac_bits == rhs.frac_bits); // only supported/needed mode

	Q res(0, this->int_bits);

	// Choose adder type here
#if ADDER == 'RCA'
	res.v = RCA<Q_TOT_BITS>(this->v, rhs.v);

#elif ADDER == 'LOA'
	res.v = LOA(this->v, rhs.v, A_PARAM);

#elif ADDER == 'ESA'
	res.v = ESA(this->v, rhs.v, A_PARAM);

#elif ADDER == 'TRUA'
	res.v = TruA(this->v, rhs.v, A_PARAM);

#elif ADDER == 'APA'
	res.v = APA(this->v, rhs.v, A_PARAM);

#elif ADDER == 'APA2'
	res.v = APAII(this->v, rhs.v, A_PARAM);

#elif ADDER == 'ETAI'
	res.v = ETAI(this->v, rhs.v, A_PARAM);

#elif ADDER == 'MEDA'
	res.v = MedA(this->v, rhs.v, A_PARAM);

#else
	res.v = 0;
#endif

	res.frac_bits = this->frac_bits;
	return res;
}

Q& Q::operator+=(Q const& rhs)
{
	assert(this->frac_bits == rhs.frac_bits);

#if ADDER == 'RCA'
	this->v = RCA<Q_TOT_BITS>(this->v, rhs.v);

#elif ADDER == 'LOA'
	this->v = LOA(this->v, rhs.v, A_PARAM);

#elif ADDER == 'ESA'
	this->v = ESA(this->v, rhs.v, A_PARAM);

#elif ADDER == 'TRUA'
	this->v = TruA(this->v, rhs.v, A_PARAM);

#elif ADDER == 'APA'
	this->v = APA(this->v, rhs.v, A_PARAM);

#elif ADDER == 'APA2'
	this->v = APAII(this->v, rhs.v, A_PARAM);

#elif ADDER == 'ETAI'
	this->v = ETAI(this->v, rhs.v, A_PARAM);

#elif ADDER == 'MEDA'
	this->v = MedA(this->v, rhs.v, A_PARAM);

#endif

	return *this;
}

Q Q::operator-(Q const& rhs)
{
	assert(this->frac_bits == rhs.frac_bits);

	Q res(0, this->int_bits);

#if ADDER == 'RCA'
	res.v = RCA<Q_TOT_BITS>(this->v, take_2s_complement(rhs.v));

#elif ADDER == 'LOA'
	res.v = LOA(this->v, take_2s_complement(rhs.v), A_PARAM);

#elif ADDER == 'ESA'
	res.v = ESA(this->v, take_2s_complement(rhs.v), A_PARAM);

#elif ADDER == 'TRUA'
	res.v = TruA(this->v, take_2s_complement(rhs.v), A_PARAM);

#elif ADDER == 'APA'
	res.v = APA(this->v, take_2s_complement(rhs.v), A_PARAM);

#elif ADDER == 'APA2'
	res.v = APAII(this->v, take_2s_complement(rhs.v), A_PARAM);

#elif ADDER == 'ETAI'
	res.v = ETAI(this->v, take_2s_complement(rhs.v), A_PARAM);

#elif ADDER == 'MEDA'
	res.v = MedA(this->v, take_2s_complement(rhs.v), A_PARAM);

#endif

	res.frac_bits = this->frac_bits;
	return res;
}

Q Q::operator*(Q const& rhs)
{
	// Q-format of multiplicand is used for product

	Q res(0, this->int_bits);

#if MULT == 'NAI'						// Naive
	res = ACC_MULT(*this, rhs);

#elif MULT == 'BMA2'					// Booth accurate
	res = BOOTH_ACC(*this, rhs);

#elif MULT == 'BMA4'
	res = BOOTH_ACC_RAD4(*this, rhs);   // Booth radix-4 accurate
	
#endif

	return res;
}

Q Q::operator<<(int const& s)
{
	Q res(0, this->int_bits);
	res.frac_bits = this->frac_bits;
	res.v = this->v << s;
	return res;
}

Q Q::operator>>(int const& s)
{
	Q res(0, this->int_bits);
	res.frac_bits = this->frac_bits;
	res.v = this->v >> s;
	return res;
}

Q Q::abs()
{
	Q res(0, this->int_bits);
	res.frac_bits = this->frac_bits;
	if (this->v.test(Q_TOT_BITS - 1))
		res.v = take_2s_complement(this->v);
	else
		res.v = this->v;
	return res;
}

Q Q::approx_add(Q rhs, int parameter)
{
	assert(this->frac_bits == rhs.frac_bits); // only supported/needed mode

	Q res(0, this->int_bits);

#if ADDER == 'LOA'
	res.v = LOA(this->v, rhs.v, parameter);

#elif ADDER == 'ESA'
	res.v = ESA(this->v, rhs.v, parameter);

#elif ADDER == 'TRUA'
	res.v = TruA(this->v, rhs.v, parameter);

#elif ADDER == 'APA'
	res.v = APA(this->v, rhs.v, parameter);

#elif ADDER == 'APA2'
	res.v = APAII(this->v, rhs.v, parameter);

#elif ADDER == 'ETAI'
	res.v = ETAI(this->v, rhs.v, parameter);

#elif ADDER == 'MEDA'
	res.v = MedA(this->v, rhs.v, parameter);

#else // This function should never be called if an accurate adder is chosen

	res.v = 0;
#endif

	res.frac_bits = this->frac_bits;
	return res;
}

/****************************************************/

template <int B>
std::bitset<B> take_2s_complement(std::bitset<B> in)
{
	in = ~in;
	// Always use accurate arithmetics here
	return RCA<B>(in, binary(1));
}

#if WINDOWS == false
binary take_2s_complement(binary in)
{
	in = ~in;
	// Always use accurate arithmetics here
	return RCA<Q_TOT_BITS>(in, binary(1));
}
#endif

void binary_print(binary in, int frac_bits)
{
	for (int i = Q_TOT_BITS - 1; i >= frac_bits; i--)
		std::cout << in[i];

	std::cout << ".";

	for (int i = frac_bits - 1; i >= 0; i--)
		std::cout << in[i];

	std::cout << std::endl;
}

#endif // !q_cpp
