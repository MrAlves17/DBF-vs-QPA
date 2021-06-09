#ifndef tests
#define tests

#include "parameters.hpp"
#include "dbf_star_algorithm.hpp"
#include "qpa_algorithm.hpp"
#include "io_functions.hpp"
#include <vector>
#include <cstdio>

void run_tests(PARAMETERS& param);
float sum_utilizations(std::vector< std::vector<float>>& tasksets);

#endif