#ifndef dbf_algorithm
#define dbf_algorithm

#include <vector>

float dbf_sum(std::vector< std::vector<float>>& taskset, float deadlineTask, int id_task);
bool restrictionsDBFValidated(std::vector< std::vector<float>>& taskset, float total_utilization);

#endif