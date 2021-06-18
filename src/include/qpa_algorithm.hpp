#ifndef qpa_algorithm
#define qpa_algorithm

#include <cstdio>
#include <vector>
#include <cmath>
#include "dbf_qpa_test_data.hpp"

float upper_bound_L_a(std::vector< std::vector<float>>& taskset, float total_utilization);
float upper_bound_L_b(std::vector< std::vector<float>>& taskset);
float h_function(std::vector< std::vector<float>>& taskset, float t);
float maximum_deadline(std::vector< std::vector<float>>& taskset, float t);
DBF_QPA_TEST_DATA qpa(std::vector< std::vector<float>>& taskset, float L, float d_min);
float minimum_deadline(std::vector< std::vector<float>>& taskset);
std::vector<float> absolute_deadlines(std::vector< std::vector<float>>& taskset, float L);
DBF_QPA_TEST_DATA validated_by_qpa(std::vector< std::vector<float>>& taskset, float total_utilization);

#endif