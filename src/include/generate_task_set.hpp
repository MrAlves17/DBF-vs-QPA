#ifndef generate_task_set
#define generate_task_set

#include <vector>

void init_seed(int seed);
std::vector<float> UUniFast(int seed, int n, float u);
std::vector<int> GeneratePeriods(int seed, int n, int TmaxPerTmin);
std::vector<int> GenerateRelativeDeadlines(int seed, int n, std::vector<float>& utilizations, std::vector<int>& periods);
std::vector< std::vector<float>> IntegrateTasksData(int n, std::vector<float>& utilizations, std::vector<int>& periods, std::vector<int>& relativeDeadlines);

#endif