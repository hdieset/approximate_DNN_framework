#ifndef intermediate_analyzer_hpp
#define intermediate_analyzer_hpp

#include <iostream>
#include <string>

#include "../definitions.hpp"

class intermediate_analyzer {
private:
	NETWORK_TYPE network_type;
	int			 nb_images;
	int			 nb_layers;
	std::string  golden_name;
	std::string  candiate_name;
public:
	intermediate_analyzer(NETWORK_TYPE network_type, int nb_images, std::string name);
	void run();
};

#endif // !intermediate_analyzer_hpp