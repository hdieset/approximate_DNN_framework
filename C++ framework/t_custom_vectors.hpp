#ifndef t_custom_vector_hpp
#define t_custom_vector_hpp

#include <vector>
#include <iostream>

#if WINDOWS == true
#pragma warning( disable : 4348 ) // disable forward declaration warnings
#endif
// forward declarations
template <typename T = double> class Vector_2D;
template <typename T = double> class Vector_3D;
template <typename T = double> class Prop_vector;

enum class axis { VERTICAL, HORIZONTAL };
enum class vector_type { NONE, VECTOR_1D, VECTOR_2D, VECTOR_3D, VECTOR_4D };

#if WINDOWS == true
template <typename T = double>
#else
template <typename T>
#endif
class Vector_1D {
public:
	int            length;
	std::vector<T> data;

	Vector_1D();
	Vector_1D(int length);
	Vector_1D(int length, int Q_int_bits);

	void print();

	Vector_1D<T> zero_pad(int nb);

	Prop_vector<T> to_propvector();
};

#if WINDOWS == true
template <typename T = double>
#else
template <typename T>
#endif
class Vector_2D {
public:
	int height, width;
	std::vector<std::vector<T>> data;

	Vector_2D();
	Vector_2D(int height, int width);
	Vector_2D(int height, int width, int Q_int_bits);

	void print();

	Vector_2D<T> zero_pad(int nb);

	Prop_vector<T> to_propvector();
};

#if WINDOWS == true
template <typename T = double>
#else
template <typename T>
#endif
class Vector_3D {
public:
	int channels, height, width;
	std::vector<std::vector<std::vector<T>>> data;

	Vector_3D();
	Vector_3D(int channels, int height, int width);
	Vector_3D(int channels, int height, int width, int Q_int_bits);

	void print();

	Vector_3D<T> zero_pad(int nb);

	Prop_vector<T> to_propvector();
};

#if WINDOWS == true
template <typename T = double>
#else
template <typename T>
#endif
class Vector_4D {
public:
	int input_channels, output_channels, height, width;
	std::vector<std::vector<std::vector<std::vector<T>>>> data;

	Vector_4D();
	Vector_4D(int output_channels, int input_channels, int height, int width); // 0
	Vector_4D(int output_channels, int input_channels, int height, int width, int Q_int_bits);

	void print();

	Prop_vector<T> to_propvector();
};

#if WINDOWS == true
template <typename T = double>
#else
template <typename T>
#endif
class Prop_vector {
public:
	int			Q_int_bits;
	vector_type type;

	// vectors are created in above classes only
	Vector_1D<T> vector_1d;
	Vector_2D<T> vector_2d;
	Vector_3D<T> vector_3d;
	Vector_4D<T> vector_4d;

	Prop_vector();
	Prop_vector(int Q_int_bits);
	void save_vector(std::string filepath, bool use_pbar);

	Vector_1D<T> get_vector_1d();
	Vector_2D<T> get_vector_2d();
	Vector_3D<T> get_vector_3d();
	Vector_4D<T> get_vector_4d();
};

#include "t_custom_vectors.cpp"

#endif // !t_custom_vector_hpp