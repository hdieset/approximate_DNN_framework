#ifndef intermediate_analyzer_cpp
#define intermediate_analyzer_cpp

#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <assert.h>

#include "intermediate_analyzer.hpp"
#include "tools.hpp"

// Global variables for analyzer threads
std::mutex mtx_img, mtx_write_vectors;
std::vector<double> l1_loss, l2_loss, min, max;
int curr_img;

intermediate_analyzer::intermediate_analyzer(NETWORK_TYPE network_type, int nb_images, std::string name)
{
	this->nb_images     = nb_images;
	this->network_type  = network_type;
	if (network_type == NETWORK_TYPE::ALEXNET) {
		this->nb_layers = 20;
		this->golden_name = "AlexNet_double"; // Set golden network model name here!
	}
	else {
		this->nb_layers = 38;
		this->golden_name = "VGG16_double";
	}
	this->candiate_name = name;

	curr_img = 0;
	l1_loss.resize(this->nb_layers+1, 0);
	l2_loss.resize(this->nb_layers+1, 0);
	min.resize(this->nb_layers+1, 0);
	max.resize(this->nb_layers+1, 0);
}


void th_analyzer(int thread_nb,
				 int nb_layers,
				 int max_img,
				 std::string golden_name,
				 std::string candidate_name)
{
	int th_curr_img = -1;
	int th_completed = 0;
	double th_l1, th_l2, th_min, th_max;

	int batches_a, channels_a, height_a, width_a;
	int batches_b, channels_b, height_b, width_b;

	double tmp_a, tmp_b, diff;

	while (true) {
		// Get new image number
		mtx_img.lock();
		th_curr_img = curr_img++;
		mtx_img.unlock();

		if (th_curr_img >= max_img) {
			std::cout << "Thread " << std::to_string(thread_nb) << " analyzed "
				<< std::to_string(th_completed) << " inferences." << std::endl;
			return;
		}

		for (int l = 0; l <= nb_layers; l++) {
			// Open files
			std::string img_string = std::to_string(th_curr_img) + "_" + std::to_string(l) + ".txt";
			std::ifstream file_golden(golden_name    + "/" + img_string);
			std::ifstream file_candid(candidate_name + "/" + img_string);

			if (!file_golden.is_open())
				load_failed(golden_name + "/" + img_string);

			if (!file_candid.is_open())
				load_failed(candidate_name + "/" + img_string);

			// Loading tensor shapes and checking size compatibility
			file_golden >> batches_a;
			file_golden >> channels_a;
			file_golden >> height_a;
			file_golden >> width_a;

			file_candid >> batches_b;
			file_candid >> channels_b;
			file_candid >> height_b;
			file_candid >> width_b;

			assert((batches_a == batches_b)
				& (channels_a == channels_b) 
				& (height_a == height_b)
				& (width_a == width_b) );

			// Calculate losses
			th_l1 = 0;
			th_l2 = 0;
			th_min =  999999;
			th_max = -999999;
			tmp_a = 0;
			tmp_b = 0;

			int nb_elements = batches_a * channels_a * height_a * width_a;
			for (int i = 0; i < nb_elements; i++) {
				file_golden >> tmp_a;
				file_candid >> tmp_b;

				diff = tmp_a - tmp_b;
				th_l1 += std::abs(diff);
				th_l2 += std::pow(diff, 2);
				if (th_max < diff)
					th_max = diff;
				if (th_min > diff)
					th_min = diff;
			}

			th_l2 /= nb_elements;

			// Write losses to shared vectors
			mtx_write_vectors.lock();
			l1_loss[l] += th_l1;
			l2_loss[l] += th_l2;
			if (min[l] > th_min)
				min[l] = th_min;
			if (max[l] < th_max)
				max[l] = th_max;
			mtx_write_vectors.unlock();

			// Close files
			file_golden.close();
			file_candid.close();

			th_completed++;
		}
	}
}

void write_results_to_csv(std::string path, int nb_layers, int nb_imgs) {
	// Creating output file
	std::ofstream ofile(path);
	if (ofile.fail())
		save_failed(path);

	int precision = std::numeric_limits<double>::max_digits10;

	// Writing header
	ofile << "layer,l1,l2,min,max" << std::endl;

	for (int l = 0; l <= nb_layers; l++)
		ofile << std::to_string(l) << "," << std::setprecision(precision) 
			  << std::to_string(l1_loss[l]) << ","
			  << std::to_string(l2_loss[l]/nb_imgs) << ","
			  << std::to_string(min[l])		<< ","
			  << std::to_string(max[l])		<< std::endl;

	ofile.close();
}

void intermediate_analyzer::run()
{
	std::cout << "Started analyzing " << this->candiate_name << " with "
		<< std::to_string(NB_THREADS) << " threads" << std::endl;

	std::string golden_path = INTERMEDIATE_PATH + "/ImageNet/" + this->golden_name;
	std::string candid_path = INTERMEDIATE_PATH + "/ImageNet/" + this->candiate_name;

	std::vector<std::thread> threads;

	for (int i = 0; i < NB_THREADS; i++) {
		threads.push_back(
			std::thread(th_analyzer,
						i,
						this->nb_layers,
						this->nb_images,
						golden_path,
						candid_path)
		);
		// allow thread 0 to load first
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	for (auto& t : threads)
		t.join();

	write_results_to_csv(INTERMEDIATE_PATH + "/ImageNet/" + this->candiate_name + ".csv",
		this->nb_layers, this->nb_images);

	std::cout << "Analysis finished!" << std::endl;
}

#endif // !intermediate_analyzer_cpp