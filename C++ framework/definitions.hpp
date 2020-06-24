#ifndef definitions_hpp
#define definitions_hpp

#include <string>

#define NB_THREADS 16
#define INFERENCE_PROGRESS_BAR false

#define QUANTIZEnn
#define WINDOWS true

#define ADDER 'TRUA'  // RCA, LOA, ESA, TRUA, APA, APA2, ETAI, MEDA
#define MULT  'BMA2' // NAI, BMA2, BMA4
#define A_PARAM 5    // Approximate parameter

// found by exhaustive search
#define Q_TOT_BITS 16

// found by network analysis
#define Q_F_S_INT_BITS 10 // Feature ex bias int length
#define Q_C_S_INT_BITS  8 // Classifier bias int length

// AlexNet
// #define Q_F_W_INT_BITS  3 // Feature ex weight int length
// #define Q_C_W_INT_BITS  1 // Classifier weight int length

// VGG16
#define Q_F_W_INT_BITS  2 // Feature ex weight int length
#define Q_C_W_INT_BITS  1 // Classifier weight int length

enum class NETWORK_TYPE { NONE, VGG16, ALEXNET };

// Program working folder // TODO: use your own folders
#if WINDOWS == true
const std::string MODELS_PATH        = "C:\\Users\\hdies\\Documents\\Master\\master-thesis\\High-level_code\\Models\\";
const std::string DATASET_PATH       = "C:\\Users\\hdies\\Documents\\Master\\master-thesis\\High-level_code\\Preprocessed_datasets\\";
const std::string INFERENCE_PATH     = "C:\\Users\\hdies\\Documents\\Master\\master-thesis\\High-level_code\\Inference_output\\";
const std::string INTERMEDIATE_PATH  = "C:\\Users\\hdies\\Documents\\Master\\master-thesis\\High-level_code\\Intermediate_output\\";
const std::string OPERATOR_TEST_PATH = "C:\\Users\\hdies\\Documents\\Master\\master-thesis\\High-level_code\\Operator_tests\\";
constexpr int PROGRESS_BAR_WIDTH = 70;
#else
exit(1);
#endif

#endif // !definitions_hpp