#ifndef operator_testbench_cpp
#define operator_testbench_cpp

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <random>
#include <assert.h>

#include "operator_testbench.hpp"
#include "../Q.hpp"
#include "tools.hpp"

// Global variables for testbench threads
std::mutex mtx_write;
std::vector<double> nmed, mred, er, mse;


operator_testbench::operator_testbench(bool is_adder, int nb_tests, std::string testname)
{
    this->is_adder = is_adder;
    if (is_adder) {
        this->op_min = -(int)std::pow(2, Q_TOT_BITS - 2);
        this->op_max =  (int)std::pow(2, Q_TOT_BITS - 2);
    }
    else {
    // MULTIPLIERS
        // todo: implement approximate multipliers?
        // todo: number ranges min, max
        exit(1);
    }

    this->nb_tests = nb_tests;
    this->testname = testname;
    this->parameter = 0;
}

void operator_testbench::set_parameter(int parameter)
{
    assert(parameter < Q_TOT_BITS); // else makes no sense
    this->parameter = parameter;
}

void th_testbench(int      thread_nb,
                  bool     is_addition,
                  int      nb_tests,
                  int      parameter_max,
                  int      op_min,
                  int      op_max)
{
    // Init thread
    double th_nmed;
    double th_mred;
    double th_er;
    double th_mse;

    int a, b, ans, aans; // latter is approximate ans
    Q   A, B,      AANS;

    std::random_device rd;
    std::default_random_engine gen{ rd() };
    std::uniform_int_distribution<int> dist(op_min, op_max);

    // Perform tests
    for (int param = thread_nb + 1; param <= parameter_max; param += NB_THREADS){
        // Init thread parameters
        th_nmed = 0;
        th_mred = 0;
        th_er   = 0;
        th_mse  = 0;

        // Approximate value calculation
        for (int test = 0; test < nb_tests; test++) {
            // find operands
            do {
                a = dist(gen);
                b = dist(gen);
            } while (a + b == 0); // mred would fail if sum is zero

            A = Q(a, Q_TOT_BITS);
            B = Q(b, Q_TOT_BITS);

            // Do arithmetical operation
            if (is_addition) {
                ans  = a + b;
                AANS = A.approx_add(B, param);
            }
            else {
                assert(false);
            }

            // Calculating error metrics
            aans = (int)AANS.get_double();
            int diff = ans - aans;

            th_nmed += std::abs(diff);
            th_mred += std::abs((double)diff / ans);
            th_er   += diff != 0;
            th_mse  += std::pow(diff, 2);

        } // ends Approximate value calculation

        // Normalizations
        th_nmed /= nb_tests * op_max;
        th_mred /= nb_tests;
        th_er   /= nb_tests;
        th_mse  /= nb_tests;

        // Mutex write to globals
        mtx_write.lock();
        nmed[param - 1] = th_nmed;
        mred[param - 1] = th_mred;
        er[param - 1]   = th_er;
        mse[param - 1]  = th_mse;
        mtx_write.unlock();
    }
}

void operator_testbench::run()
{
    // Initialize metric vectors, will perform all tests for each parameter
    nmed.resize(this->parameter, 0);
    mred.resize(this->parameter, 0);
    er.resize(this->parameter, 0);
    mse.resize(this->parameter, 0);

    std::cout << "Started test " << this->testname
        << " using " << std::to_string(NB_THREADS) << " threads" << std::endl;

    std::vector<std::thread> threads;

    for (int i = 0; i < NB_THREADS && i < parameter; i++) {
        threads.push_back(
            std::thread(th_testbench,
                        i,
                        this->is_adder,
                        this->nb_tests,
                        this->parameter,
                        this->op_min,
                        this->op_max)
        );
        // allow thread 0 to load first
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    for (auto& t : threads)
        t.join();

    // Writing results to csv file
    std::string   filepath = OPERATOR_TEST_PATH + this->testname + ".csv";
    std::ofstream ofile(filepath);
    if (ofile.fail())
        save_failed(filepath);

    int precision = std::numeric_limits<double>::max_digits10;

    // Writing header
    ofile << "n,nmed,mred,er,mse" << std::endl;

    // Writing data
    for (int n = 1; n <= this->parameter; n++)
        ofile << std::to_string(n)          << "," << std::setprecision(precision)
              << std::to_string(nmed[n-1])  << ","
              << std::to_string(mred[n-1])  << ","
              << std::to_string(er[n - 1])  << ","
              << std::to_string(mse[n - 1]) << std::endl;

    ofile.close();

    std::cout << "Testbench finished!" << std::endl;
}


#endif // !operator_testbench_cpp