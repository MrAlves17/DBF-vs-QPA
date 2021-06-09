#include "io_functions.hpp"

void output_task_set(std::vector< std::vector<float>>& taskset, int taskset_id){
	std::fstream file;
	std::string outputfilename = "tasksets/taskset_"+std::to_string(taskset_id);

	file.open(outputfilename,std::fstream::out);
	
	file << "TASKSET " << taskset_id << "\n";
	file << std::fixed << std::setprecision(6);
	for(int i=0; i<taskset.size(); i++){
		file << taskset[i][0] << "\t\t" << taskset[i][1] << "\t\t" << taskset[i][2] << "\n";
	}

	file.close();
}

std::vector< std::vector<float>> read_taskset(int taskset_id, int ntasks){
	std::ifstream file;
	std::string inputfilename = "tasksets/taskset_"+std::to_string(taskset_id);

	file.open(inputfilename);

	std::vector< std::vector<float>> taskset(ntasks);
	
	std::string aux;
	file >> aux >> taskset_id;
	file >> std::fixed >> std::setprecision(6);
	for(int i=0; i<taskset.size(); i++){
		taskset[i].resize(3);
		file >> taskset[i][0] >> taskset[i][1] >> taskset[i][2];
	}

	file.close();

	return taskset;
}