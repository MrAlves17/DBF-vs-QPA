#include "qpa_algorithm.hpp"

float upper_bound_L_a(std::vector< std::vector<float>>& taskset, float total_utilization){
	float L_a = 0;
	for(int i=0; i<taskset.size(); i++){
		L_a = std::max(L_a, taskset[i][2]);
	}

	float value = 0;
	for(int i=0; i<taskset.size(); i++){
		value += ((taskset[i][1]-taskset[i][2])*taskset[i][0])/(1-total_utilization);
	}

	L_a = std::max(L_a, value);
	return L_a;
}

float upper_bound_L_b(std::vector< std::vector<float>>& taskset){
	float w_0 = 0;
	for(int i=0; i<taskset.size(); i++){
		w_0 += taskset[i][0]*taskset[i][1];
	}

	float w_prev = 0;
	float w_actual = w_0;
	while(w_prev != w_actual){
		w_prev = w_actual;
		w_actual = 0;
		for(int i=0; i<taskset.size(); i++){
			w_actual += taskset[i][0]*taskset[i][1]*ceil(w_prev/taskset[i][1]);
		}
	}

	float L_b = w_actual;

	return L_b;
}

float h_function(std::vector< std::vector<float>>& taskset, float t){
	float h = 0;
	for(int i=0; i<taskset.size(); i++){
		h += std::max(0.0,1+floor((t-taskset[i][2])/taskset[i][1]))*taskset[i][0]*taskset[i][1];
	}

	return h;
}

float maximum_deadline(std::vector< std::vector<float>>& taskset, float t){
	float d_t_max = 0;
	for(int i=0; i<taskset.size(); i++){
		if(taskset[i][2] < t){
			float d_i = floor((t-taskset[i][2])/taskset[i][1])*taskset[i][1] + taskset[i][2];
			if(d_i == t) d_i = d_i - taskset[i][1];
			if(d_i > d_t_max) d_t_max = d_i;
		}
	}

	return d_t_max;
}

bool qpa(std::vector< std::vector<float>>& taskset, float L, float d_min, STATISTICAL_DATA& st_data){
	float t = maximum_deadline(taskset, L);
	bool validated_by_qpa;

	float h_t = h_function(taskset, t);
	int qpa_points=1;
	while(h_t <= t && h_t > d_min){
		if(h_t < t) t = h_t;
		else t = maximum_deadline(taskset, t);

		h_t = h_function(taskset, t);
		qpa_points++;
	}

	if(h_t <= d_min){
		// printf("Task set is schedulable\n");
		validated_by_qpa = true;
	}
	else{
		// printf("Task set is not schedulable\n");
		validated_by_qpa = false;
	}

	st_data.sum_qpa_points += qpa_points;
	st_data.sum_dbf_points += absolute_deadlines(taskset, L).size();

	return validated_by_qpa;
}

float minimum_deadline(std::vector< std::vector<float>>& taskset){
	float minimum_deadline = taskset[0][2];
	for(int i=0; i<taskset.size(); i++){
		minimum_deadline = std::min(minimum_deadline,taskset[i][2]);
	}

	return minimum_deadline;
}

std::vector<float> absolute_deadlines(std::vector< std::vector<float>>& taskset, float L){
	std::vector<float> absolute_deadlines;

	for(int i=0; i<taskset.size(); i++){
		int k = 0;
		float d_i = k*taskset[i][1] + taskset[i][2];
		while(d_i < L && h_function(taskset, d_i) <= d_i){
			absolute_deadlines.push_back(d_i);
			k++;
			d_i = k*taskset[i][1] + taskset[i][2];
		}
	}

	return absolute_deadlines;
}

bool validated_by_qpa(std::vector< std::vector<float>>& taskset, float total_utilization, STATISTICAL_DATA& st_data){
	if(total_utilization > 1){
		return false;
	}
	
	float L_a;
	float L_b = upper_bound_L_b(taskset);
	// printf("deadlines (< L_b = %f): %ld\n", L_b, absolute_deadlines(taskset, L_b).size());
	if(total_utilization != 1){
		L_a = upper_bound_L_a(taskset, total_utilization);
		// printf("deadlines (< L_a = %f): %ld\n", L_a, absolute_deadlines(taskset, L_a).size());
	}else{
		L_a = L_b;
	}

	float L = std::min(L_a, L_b);
	float d_min = minimum_deadline(taskset);

	return qpa(taskset, L, d_min, st_data);
}
