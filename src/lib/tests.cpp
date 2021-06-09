#include "tests.hpp"

void run_tests(PARAMETERS& param){
	int dbf_star_schedulable = 0;
	int qpa_schedulable = 0;
	int qpa_unschedulable = 0;
	for(int taskset_id=1; taskset_id<=param.numTasksets; taskset_id++){
		std::vector< std::vector<float>> taskset = read_taskset(taskset_id, param.ntasks);
		// printf("TASKSET %d\n", taskset_id);

		// printf("Trying DBF* analysis\n");
		if(restrictions_dbf_star_validated(taskset, param.total_utilization)){
			// printf("DBF* proved task set is schedulable \n");
			dbf_star_schedulable++;
		}else{
			// printf("DBF* didn't prove\n");
			// printf("\nTrying QPA analysis\n");
			if(validated_by_qpa(taskset, sum_utilizations(taskset))){
				// printf("QPA proved task set is schedulable \n");
				qpa_schedulable++;
			}else{
				// printf("QPA didn't prove\n");
				qpa_unschedulable++;
			}
		}
	}
	
	printf("\tSchedulable by DBF*: %.2f%%\n\tSchedulable by QPA: %.2f%%\n\tUnschedulable by QPA: %.2f%%\n", 100.0*dbf_star_schedulable/param.numTasksets, 100.0*qpa_schedulable/param.numTasksets, 100.0*qpa_unschedulable/param.numTasksets);
}

float sum_utilizations(std::vector< std::vector<float>>& tasksets){
	float sum = 0;
	for(int i=0; i<tasksets.size(); i++){
		sum += tasksets[i][0];
	}

	return sum;
}