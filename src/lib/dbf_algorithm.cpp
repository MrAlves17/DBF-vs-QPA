#include "dbf_algorithm.hpp"

float dbf_sum(std::vector< std::vector<float>>& taskset, float deadlineTask, int id_task){
	float sum = 0;
	for(int i=0; i<taskset.size(); i++){
		if(i!=id_task && deadlineTask >= taskset[i][2]){
			sum += taskset[i][0]*taskset[i][1] + (deadlineTask - taskset[i][2])*taskset[i][0];
		}
	}

	return sum;
}

bool restrictionsDBFValidated(std::vector< std::vector<float>>& taskset, float total_utilization){
	for(int i=0; i<taskset.size(); i++){
		if(taskset[i][2] - dbf_sum(taskset, taskset[i][2], i) < taskset[i][0]*taskset[i][1]){
			return false;
		}
		if(1 - (total_utilization - taskset[i][0]) < taskset[i][0]){
			return false;
		}
	}

	return true;
}

/*
	D_i - sum(dbf(d_i,t_j)) >= C_i
	1 - sum(u_i) >= u_i
*/