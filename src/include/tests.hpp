#ifndef tests
#define tests

#include "parameters.hpp"
#include "dbf_star_algorithm.hpp"
#include "dbf_algorithm.hpp"
#include "qpa_algorithm.hpp"
#include "io_functions.hpp"
#include "statistical_data.hpp"
#include <vector>
#include <cstdio>

void run_tests(PARAMETERS& param);
void dbf_test(PARAMETERS& param);
void qpa_test(PARAMETERS& param);
void dbf_star_qpa_test(PARAMETERS& param);
float sum_utilizations(std::vector< std::vector<float>>& taskset);

#endif