#ifndef dbf_start_algorithm
#define dbf_start_algorithm

#include <vector>

float dbf_start_sum(std::vector< std::vector<float>>& taskset, float deadlineTask, int id_task);
bool restrictions_dbf_star_validated(std::vector< std::vector<float>>& taskset, float total_utilization);

#endif