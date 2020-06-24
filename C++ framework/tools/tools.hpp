#ifndef tools_hpp
#define tools_hpp

#include <vector>
#include <string>

class progress_bar {
private:
	int         bar_length;
	double      it_max;
	std::string proc_name;

	void rep_print(std::string str, int times);

public:
	progress_bar();
	progress_bar(int barlength, int it_max, std::string process_name);
	void new_bar(int barlength, int it_max, std::string process_name);
	void update_progress(int it);
	void remove();
};

void save_failed(std::string path);
void load_failed(std::string path);

#endif // !tools_hpp