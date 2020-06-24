#ifndef imagenet_hpp
#define imagenet_hpp

#include <string>

#include "../t_custom_vectors.hpp"


template <typename T = double>
class IMAGENET_handler {
private:
	Vector_4D<T> images;
	NETWORK_TYPE network_type;
	int          intermediate_start;
	std::string  INTERMEDIATE_PATH;
	std::string  NETWORK_NAME;

public:
	const std::string FOLDERNAME = "ImageNet";

	int tot_nb_images;  // total limit
	int nb_used_images; // total counter
	int img_file_no;
	int img_batch, tot_batches; // batch in file, total batches in file
	int img_channels, img_height, img_width;
	int nb_saved_images;

	IMAGENET_handler(int nb_images);
	IMAGENET_handler(int nb_images, int start_img);
	void set_network_name(std::string name);
	void set_intermediate_start(int start, std::string INTERMEDIATE_PATH);

	Prop_vector<T> get_image();
	void save(Prop_vector<T> vector, int img_nb, bool use_pbar);

};

#include "imagenet.cpp"

#endif // !imagenet_hpp