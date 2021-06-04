#include <vector>
#include <cstdlib>
#include "parameters.hpp"
#include "generate_task_set.hpp"
#include "dbf_algorithm.hpp"
#include "qpa_algorithm.hpp"
#include <getopt.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

void show_help(const char *name);
void read_args(const int argc, char* argv[], PARAMETERS& param);

float sum_utilizations(std::vector<float>& utilizations);

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

void generate_task_sets(PARAMETERS& param){
	for(int taskset_id = 1; taskset_id<=6000; taskset_id++){
		std::vector<float> utilizations = UUniFast(param.seed, param.ntasks, param.total_utilization);
		std::vector<int> periods = GeneratePeriods(param.seed, param.ntasks, param.TmaxPerTmin);
		std::vector<int> relativeDeadlines = GenerateRelativeDeadlines(param.seed, param.ntasks, utilizations, periods);

		// [utilization, period, relative deadline]
		std::vector< std::vector<float>> taskset = IntegrateTasksData(param.ntasks, utilizations, periods, relativeDeadlines);

		output_task_set(taskset, taskset_id);
	}
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

void run_tests(PARAMETERS& param){
	int dbf_proved = 0;
	int qpa_proved = 0;
	int qpa_failed = 0;
	for(int taskset_id=1; taskset_id<=6000; taskset_id++){
		std::vector< std::vector<float>> taskset = read_taskset(taskset_id, param.ntasks);
		// printf("TASKSET %d\n", taskset_id);

		// printf("Trying DBF* analysis\n");
		if(restrictionsDBFValidated(taskset, param.total_utilization)){
			// printf("DBF* proved task set is schedulable \n");
			dbf_proved++;
		}else{
			// printf("DBF* didn't prove\n");
			// printf("\nTrying QPA analysis\n");
			if(validated_by_qpa(taskset, param.total_utilization)){
				// printf("QPA proved task set is schedulable \n");
				qpa_proved++;
			}else{
				// printf("QPA didn't prove\n");
				qpa_failed++;
			}
		}
	}
	
	printf("\tdbf_proved: %d\n\tqpa_proved: %d\n\tqpa_failed: %d\n\tsum: %d\n", dbf_proved, qpa_proved, qpa_failed, dbf_proved+qpa_proved+qpa_failed);
}

int main(int argc, char* argv[]){

	PARAMETERS param = PARAMETERS();

	read_args(argc, argv, param);
	init_seed(param.seed);

	if(param.generate_tasksets){
		generate_task_sets(param);
	}
	if(param.run_tests){
		run_tests(param);
	}
	

	return 0;
}

float sum_utilizations(std::vector<float>& utilizations){
	float sum = 0;
	for(int i=0; i<utilizations.size(); i++){
		sum += utilizations[i];
	}

	return sum;
}

void show_help(const char *name) {
	fprintf(stderr, "\
usage: %s <parameters>\n\
	-h,		--help						show help.\n\
	-s,		--seed <value>				set seed for randomization.\n\
	-n,		--ntasks <value>			set number of tasks.\n\
	-t,		--TmaxPerTmin <value>		set Tmax/Tmin.\n\
	-u,		--utilization <value>		set u.\n\
	-g,		--gen_tasksets				generate tasksets.\n\
	-r,		--run_tests					run tests.\n", name);
	exit(-1);
}

void read_args(const int argc, char* argv[], PARAMETERS& param) {
	int opt;
	/*
		https://daemoniolabs.wordpress.com/2011/10/07/usando-com-as-funcoes-getopt-e-getopt_long-em-c/
		https://linux.die.net/man/3/getopt_long
	*/
	const option options[] = {
		{"help"			, no_argument       , 0 , 'h' },
		{"seed"			, required_argument , 0 , 's' },
		{"ntasks"		, required_argument , 0 , 'n' },
		{"TmaxPerTmin"	, required_argument , 0 , 't' },
		{"utilization"	, required_argument , 0 , 'u' },
		{"gen_tasksets"	, no_argument       , 0 , 'g' },
		{"run_tests"	, no_argument       , 0 , 'r' },
		{0              , 0                 , 0 ,  0  },
	};

	if (argc < 2) {
		show_help(argv[0]);
	}

	while( (opt = getopt_long(argc, argv, "hs:n:t:u:gr", options, NULL)) > 0 ) {
		switch ( opt ) {
			case 'h': /* -h ou --help */
				show_help(argv[0]);
				break;
			case 's': /* -s ou --seed */
				param.seed = std::atoi(optarg);
				break;
			case 'n': /* -n ou --ntasks */
				param.ntasks = std::atoi(optarg);
				break;
			case 't': /* -t ou --TmaxPerTmin */
				param.TmaxPerTmin = std::atoi(optarg);
				break;
			case 'u': /* -u ou --utilization */
				param.total_utilization = std::atof(optarg);
				break;
			case 'g': /* -g ou --gen_tasksets* */
				param.generate_tasksets = true;
				break;
			case 'r': /* -r ou --run_tests */
				param.run_tests = true;
				break;
			default:
				fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt);
				exit(-1);
		}
	}
}
