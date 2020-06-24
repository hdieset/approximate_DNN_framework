#ifndef operator_testbench_hpp
#define operator_testbench_hpp

#include <string>

class operator_testbench {
public:
	bool		is_adder;
	int			nb_tests;
	std::string testname;
	int			parameter;
	int			op_min, op_max;

	operator_testbench(bool is_adder, int nb_tests, std::string testname);
	void set_parameter(int parameter);
	void run();
};

#include "operator_testbench.cpp"

#endif // !operator_testbench_hpp