#ifndef tools_cpp
#define tools_cpp

#include <iostream>
#include <fstream>

#include "../definitions.hpp"
#include "tools.hpp"


void progress_bar::rep_print(std::string str, int times) {
	for (int i = 0; i < times; i++)
		std::cout << str;
}

progress_bar::progress_bar() {
	this->bar_length = 0;
	this->it_max     = 0;
	this->proc_name  = "unnamed";
};

progress_bar::progress_bar(int barlength, int it_max, std::string process_name) {
	this->bar_length = barlength;
	this->it_max     = (double)it_max;
	this->proc_name  = process_name;
	
	std::cout << proc_name << " [";
	rep_print(" ", barlength);
	std::cout              << "]   0%";
};

void progress_bar::new_bar(int barlength, int it_max, std::string process_name) {
	this->bar_length = barlength;
	this->it_max     = (double)it_max;
	this->proc_name  = process_name;
	
	std::cout << proc_name << " [";
	rep_print(" ", barlength);
	std::cout              << "]   0%";
}

void progress_bar::update_progress(int it) {
	double progress = it / it_max;
	
	std::cout << "\r" << this->proc_name << " [";
	rep_print("=", (int)(progress * bar_length));
	std::cout << ">";
	rep_print(" ", bar_length - (int)(progress * bar_length));
	std::cout << "] " << it << "/" << it_max << " " << (int)(progress * 100) << " %";
}

void progress_bar::remove() {
	std::cout << "\r";
	rep_print(" ", bar_length + 40);
	std::cout << "\r";
}


void save_failed(std::string path)
{
	std::cout << "Failed to save to path:" << std::endl;
	std::cout << path << std::endl;
	std::cout << "Did you create the folder structure required?" << std::endl;
	exit(1);
}

void load_failed(std::string path)
{
	std::cout << "Failed to load from path:" << std::endl;
	std::cout << path << std::endl;
	std::cout << "Does the target path exist?" << std::endl;
	exit(1);
}

#endif // !tools_cpp