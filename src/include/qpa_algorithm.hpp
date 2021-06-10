#ifndef qpa_algorithm
#define qpa_algorithm

#include <cstdio>
#include <vector>
#include <cmath>
#include "statistical_data.hpp"

float upper_bound_L_a(std::vector< std::vector<float>>& taskset, float total_utilization);
float upper_bound_L_b(std::vector< std::vector<float>>& taskset);
float h_function(std::vector< std::vector<float>>& taskset, float t);
float maximum_deadline(std::vector< std::vector<float>>& taskset, float t);
bool qpa(std::vector< std::vector<float>>& taskset, float L, float d_min, STATISTICAL_DATA& st_data);
float minimum_deadline(std::vector< std::vector<float>>& taskset);
std::vector<float> absolute_deadlines(std::vector< std::vector<float>>& taskset, float L);
bool validated_by_qpa(std::vector< std::vector<float>>& taskset, float total_utilization, STATISTICAL_DATA& st_data);

#endif