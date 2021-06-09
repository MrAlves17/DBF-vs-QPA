#ifndef io_functions
#define io_functions

#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>

void output_task_set(std::vector< std::vector<float>>& taskset, int taskset_id);
std::vector< std::vector<float>> read_taskset(int taskset_id, int ntasks);

#endif