#include "tests.hpp"

void run_tests(PARAMETERS& param){
	if(param.dbf_test){
		dbf_test(param);
	}
	if(param.qpa_test){
		qpa_test(param);
	}
	if(param.dbf_star_qpa_test){
		dbf_star_qpa_test(param);
	}
}

void dbf_test(PARAMETERS& param){
	int dbf_schedulable = 0;
	int dbf_unschedulable = 0;

	for(int taskset_id=1; taskset_id<=param.numTasksets; taskset_id++){
		std::vector< std::vector<float>> taskset = read_taskset(taskset_id, param.ntasks);
		// printf("TASKSET %d\n", taskset_id);

		float total_utilization = sum_utilizations(taskset);
		if(validated_by_dbf(taskset, total_utilization)){
			// printf("DBF proved task set is schedulable \n");
			dbf_schedulable++;
		}else{
			// printf("DBF didn't prove\n");
			dbf_unschedulable++;
		}
	}


	printf("%.2f%%;%.2f%%\n", 100.0*dbf_schedulable/param.numTasksets, 100.0*dbf_unschedulable/param.numTasksets);
}

void qpa_test(PARAMETERS& param){
	int qpa_schedulable = 0;
	int qpa_unschedulable = 0;
	DBF_QPA_TEST_DATA DQ_tdata;
	for(int taskset_id=1; taskset_id<=param.numTasksets; taskset_id++){
		std::vector< std::vector<float>> taskset = read_taskset(taskset_id, param.ntasks);
		// printf("TASKSET %d\n", taskset_id);

		float total_utilization = sum_utilizations(taskset);
		DQ_tdata = validated_by_qpa(taskset, total_utilization);
		if(DQ_tdata.feasible){
			// printf("QPA proved task set is schedulable \n");
			qpa_schedulable++;
		}else{
			// printf("QPA didn't prove\n");
			qpa_unschedulable++;
		}
	}

	printf("%lf;%lf\n", (double)DQ_tdata.sum_dbf_points/param.numTasksets, (double)DQ_tdata.sum_qpa_points/param.numTasksets);

	// printf("%.2f%%;%.2f%%\n", 100.0*qpa_schedulable/param.numTasksets, 100.0*qpa_unschedulable/param.numTasksets);
}

void dbf_star_qpa_test(PARAMETERS& param){
	int dbf_star_schedulable = 0;
	int qpa_schedulable = 0;
	int qpa_unschedulable = 0;

	DBF_QPA_TEST_DATA DQ_tdata = DBF_QPA_TEST_DATA();

	for(int taskset_id=1; taskset_id<=param.numTasksets; taskset_id++){
		std::vector< std::vector<float>> taskset = read_taskset(taskset_id, param.ntasks);
		// printf("TASKSET %d\n", taskset_id);

		float total_utilization = sum_utilizations(taskset);
		// printf("Trying DBF* analysis\n");
		if(restrictions_dbf_star_validated(taskset, total_utilization)){
			// printf("DBF* proved task set is schedulable \n");
			dbf_star_schedulable++;
		}else{
			// printf("DBF* didn't prove\n");
			// printf("\nTrying QPA analysis\n");
			DQ_tdata = validated_by_qpa(taskset, total_utilization);
			if(DQ_tdata.feasible){
				// printf("QPA proved task set is schedulable \n");
				qpa_schedulable++;
			}else{
				// printf("QPA didn't prove\n");
				qpa_unschedulable++;
			}
		}
	}


	printf("%.2f%%;%.2f%%;%.2f%%\n", 100.0*dbf_star_schedulable/param.numTasksets, 100.0*qpa_schedulable/param.numTasksets, 100.0*qpa_unschedulable/param.numTasksets);
}

float sum_utilizations(std::vector< std::vector<float>>& taskset){
	float sum = 0;
	for(int i=0; i<taskset.size(); i++){
		sum += taskset[i][0];
	}

	return sum;
}