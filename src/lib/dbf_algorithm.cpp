#include "dbf_algorithm.hpp"
#include "qpa_algorithm.hpp"

bool dbf(std::vector< std::vector<float>>& taskset, float L){

	for(int i=0; i<taskset.size(); i++){
		int k = 0;
		float d_i = k*taskset[i][1] + taskset[i][2];
		float h_t = h_function(taskset, d_i);
		while(d_i < L && h_t <= d_i){
			k++;
			d_i = k*taskset[i][1] + taskset[i][2];
			h_t = h_function(taskset, d_i);
		}

		if(d_i < L && h_t > d_i){
			return false;
		}
	}

	return true;
}

bool validated_by_dbf(std::vector< std::vector<float>>& taskset, float total_utilization){
	if(total_utilization > 1){
		return false;
	}

	float L_a = upper_bound_L_a(taskset, total_utilization);
	// printf("deadlines (< L_a = %f): %ld\n", L_a, absolute_deadlines(taskset, L_a).size());
	float L_b = upper_bound_L_b(taskset);
	// printf("deadlines (< L_b = %f): %ld\n", L_b, absolute_deadlines(taskset, L_b).size());

	float L = std::min(L_a, L_b);

	return dbf(taskset, L);
}
