#ifndef alexnet_hpp
#define alexnet_hpp

#include "../t_custom_vectors.hpp"
#include "../layers/sequential.hpp"
#include "../dataset_handlers/imagenet.hpp"


template <typename T = double>
class AlexNet {
private:
	int thread_nb;
	int layer_start;
	int layer_end;
	int nb_layers;
	std::string model_name;

public:
	Sequential<T> model = Sequential<T>(NETWORK_TYPE::ALEXNET);
	bool save_intermediates_flag;
	int  nb_intermediates;
	bool find_number_range_flag;

	AlexNet();				   // entire network
	AlexNet(int nb_first);	   // layer 0 to nb_first (inclusive)
	AlexNet(int from, int to); // layer from to to (inclusive)
	void init(int thread_nb);
	void setname(std::string name);
	void save_intermediates(bool flag);
	void save_intermediates(int nb);
	void find_number_ranges(bool flag);

	void infer(IMAGENET_handler<T> images);
};

#include "AlexNet.cpp"

#endif // !alexnet_hpp