#ifndef vgg16_hpp
#define vgg16_hpp

#include "../t_custom_vectors.hpp"
#include "../layers/sequential.hpp"
#include "../dataset_handlers/imagenet.hpp"


template <typename T = double>
class VGG16 {
private:
	int thread_nb;
	int layer_start;
	int layer_end;
	int nb_layers;
	std::string model_name;
	
public:
	Sequential<T> model = Sequential<T>(NETWORK_TYPE::VGG16);
	bool save_intermediates_flag;
	int  nb_intermediates;
	bool find_number_range_flag;

	VGG16();				 // entire network
	VGG16(int nb_first);	 // layer 0 to nb_first (inclusive)
	VGG16(int from, int to); // layer from to to (inclusive)
	void init(int thread_nb);
	void setname(std::string name);
	void save_intermediates(bool flag);
	void save_intermediates(int nb);
	void find_number_ranges(bool flag);

	void infer(IMAGENET_handler<T> images);
};

#include "vgg16.cpp"

#endif // !vgg16_hpp