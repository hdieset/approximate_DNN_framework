#ifndef acc_full_adder_cell_hpp
#define acc_full_adder_cell_hpp

bool acc_full_adder_cell(bool a, bool b, bool& carry)
{
	bool d = a ^ b; // XOR
	bool sum = d ^ carry;
	carry = (a & b) | (carry & d);
	return sum;
}

#endif // !acc_full_adder_cell_hpp