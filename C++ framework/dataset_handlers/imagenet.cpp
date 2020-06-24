#ifndef imagenet_cpp
#define imagenet_cpp

#include <iostream>
#include <string>

#include "imagenet.hpp"
#include "../definitions.hpp"
#include "../tools/tools.hpp"

template <typename T>
IMAGENET_handler<T>::IMAGENET_handler(int nb_images)
{
	this->tot_nb_images	     = nb_images;
	this->nb_used_images     = 0;
	this->img_file_no	     = 0;
	this->tot_batches        = 0;
	this->img_batch          = 0;
	this->img_channels       = 0;
	this->img_height         = 0;
	this->img_width          = 0;
	this->nb_saved_images    = 0;
	this->intermediate_start = 0;
	this->INTERMEDIATE_PATH  = "";
	this->NETWORK_NAME       = "UNNAMED";
}

template<typename T>
IMAGENET_handler<T>::IMAGENET_handler(int nb_images, int start_img)
{
	this->tot_nb_images	     = nb_images + start_img;
	this->nb_used_images     = start_img;
	this->img_file_no	     = start_img;
	this->tot_batches        = 0;
	this->img_batch          = 0;
	this->img_channels       = 0;
	this->img_height         = 0;
	this->img_width          = 0;
	this->nb_saved_images    = 0;
	this->intermediate_start = 0;
	this->INTERMEDIATE_PATH  = "";
	this->NETWORK_NAME       = "UNNAMED";
}

template<typename T>
void IMAGENET_handler<T>::set_network_name(std::string name)
{
	this->NETWORK_NAME = name;
}

template<typename T>
void IMAGENET_handler<T>::set_intermediate_start(int start, std::string INTERMEDIATE_PATH)
{
	this->intermediate_start = start;
	this->INTERMEDIATE_PATH = INTERMEDIATE_PATH;
}


template <typename T>
Prop_vector<T> IMAGENET_handler<T>::get_image()
{
	if (this->nb_used_images < this->tot_nb_images) {
		if (this->intermediate_start == 0) {
			if (this->img_batch == this->tot_batches) { // no batches in loaded file, load new file

				std::string filepath = DATASET_PATH + FOLDERNAME + "/"
					+ std::to_string(this->img_file_no) + ".txt";

				std::ifstream ifile(filepath);

				if (!ifile.is_open())
					assert(false);

				if (ifile.good()) {
					ifile >> this->tot_batches;
					ifile >> this->img_channels;
					ifile >> this->img_height;
					ifile >> this->img_width;

					this->img_batch = 0;

					this->images = Vector_4D<T>(this->tot_batches, this->img_channels,
						this->img_height, this->img_width, Q_F_S_INT_BITS);
#ifdef QUANTIZE
					double tmp;
#endif
					for (int bz = 0; bz < this->tot_batches; bz++)
						for (int ch = 0; ch < this->img_channels; ch++)
							for (int h = 0; h < this->img_height; h++)
								for (int w = 0; w < this->img_width; w++) {
#ifdef QUANTIZE
									ifile >> tmp;
									this->images.data[bz][ch][h][w] = Q(tmp, Q_F_S_INT_BITS);
#else
									ifile >> this->images.data[bz][ch][h][w];
#endif
								}

					this->img_file_no++;
				}
				else
					load_failed(filepath);

				ifile.close();
			}

			Vector_3D<T> res(this->img_channels, this->img_height, this->img_width, Q_F_S_INT_BITS);

			for (int ch = 0; ch < this->img_channels; ch++)
				for (int h = 0; h < this->img_height; h++)
					for (int w = 0; w < this->img_width; w++)
						res.data[ch][h][w] = this->images.data[this->img_batch][ch][h][w];

			this->img_batch++;
			this->nb_used_images++;
			return res.to_propvector();
		}
		else { // Load intermediate tensor

			std::string filepath = INTERMEDIATE_PATH
				+ std::to_string(this->img_file_no) + "_" 
				+ std::to_string(this->intermediate_start) + ".txt";

			std::ifstream ifile(filepath);

			if (!ifile.is_open())
				assert(false);

			if (ifile.good()) {
				ifile >> this->tot_batches; // unused
				ifile >> this->img_channels;
				ifile >> this->img_height;
				ifile >> this->img_width;

				Vector_3D<T> res(this->img_channels, this->img_height, this->img_width, Q_F_S_INT_BITS);
#ifdef QUANTIZE
				double tmp;
#endif
				for (int ch = 0; ch < this->img_channels; ch++)
					for (int h = 0; h < this->img_height; h++)
						for (int w = 0; w < this->img_width; w++){
#ifdef QUANTIZE
							ifile >> tmp;
							res.data[ch][h][w] = Q(tmp, 
								(this->intermediate_start < 13 ? Q_F_S_INT_BITS : Q_C_S_INT_BITS));
#else
							ifile >> res.data[ch][h][w];
#endif
						}

				this->img_file_no++;
				ifile.close();

				this->nb_used_images++;
				return res.to_propvector();
			}
			else
			{
				load_failed(filepath);
				return Prop_vector<T>();
			}
		}
	}
	else {
		return Prop_vector<T>();
	}
}

template<typename T>
void IMAGENET_handler<T>::save(Prop_vector<T> vector, int img_nb, bool use_pbar)
{
	this->nb_saved_images++;
	std::string filepath = INFERENCE_PATH + "ImageNet/" 
		+ this->NETWORK_NAME + "/"
		+ std::to_string(img_nb) + ".txt";

	vector.save_vector(filepath, use_pbar);
}


#endif // !imagenet_cpp
