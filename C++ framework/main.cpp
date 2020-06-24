#ifndef main_cpp
#define main_cpp

#include <iostream>

#define DO 'INF' // 'INF', 'INT', 'OPS', 'PLAY', 'FILT'


#if DO == 'INF' // Inference
#include "dataset_handlers/imagenet.hpp"
#include "models/vgg16.hpp"
#include "models/AlexNet.hpp"

std::mutex mtx_images;
std::mutex mtx_parameters;
std::mutex mtx_pbar;

int main() {

	// MODEL CREATION
	auto model = VGG16<double>();
	model.setname("VGG16_double");

	// DATASET LOADER
	int nb_images = 10000;
	auto image_handler = IMAGENET_handler<double>(nb_images);

	// RUNNING INFERENCE
	model.save_intermediates(256);
	//model.find_number_ranges(true);

	model.infer(image_handler);

	std::cout << "Finished!" << std::endl;
}

#elif DO == 'INT' // Analyze intermediate tensors

#include "tools/intermediate_analyzer.hpp"

int main() {
	std::string testname = "AlexNet_20bit_TA_4";

	auto analyzer = intermediate_analyzer(NETWORK_TYPE::ALEXNET, 256, testname);
	analyzer.run();
}


#elif DO == 'OPS'
#include "tools/operator_testbench.hpp"
//#include "Q.hpp"

int main(){
	// Operator testbench, set operator in definitions.hpp

	operator_testbench test(true, 1e6, "APA2"); // first: is_adder
	test.set_parameter(10);					   // max parameter
	test.run();
}

#elif DO == 'PLAY'
#include "Q.hpp"

int main() {
	// Operator playground

	//Q q1(9.279296875, Q_F_S_INT_BITS);
	//q1.print();
	//q1.set_new_intlen(Q_C_S_INT_BITS);
	//q1.print();

	/*
	Q q2(0.18371724, 1);
	q2.print();*/


	Q q1(3.75,6);
	q1.print();

	Q q2(-6.25,6);
	q2.print();

	(q1 + q2).print();

}

#elif DO ==  'FILT'
#include "tools/highpass_filtering.hpp"

// High-pass filtering operator test, Q24.4 ok
int main()
{
	std::cout << "High-pass filtering test!" << std::endl;

	highpass_filter test("inputname", 20);
	test.filter();
	test.merge(0.16);
	test.save("name");
}

#endif

#endif // !main_cpp