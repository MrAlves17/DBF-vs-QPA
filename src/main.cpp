#include <iostream>
#include <vector>
#include <stdlib.h>
#include "parameters.hpp"
#include "generate_task_set.hpp"
#include "dbf_algorithm.hpp"
#include <getopt.h>

void show_help(const char *name);
void read_args(const int argc, char* argv[], PARAMETERS& param);

float sum_utilizations(std::vector<float>& utilizations);

int main(int argc, char* argv[]){

	PARAMETERS param = PARAMETERS();

	read_args(argc, argv, param);

	std::vector<float> utilizations = UUniFast(param.ntasks, param.total_utilization);
	std::vector<int> periods = GeneratePeriods(param.ntasks, param.TmaxPerTmin);
	std::vector<int> relativeDeadlines = GenerateRelativeDeadlines(param.ntasks, utilizations, periods);

	// [utilization, period, relative deadline]
	std::vector< std::vector<float>> taskset = IntegrateTasksData(param.ntasks, utilizations, periods, relativeDeadlines);

	for(int i=0; i<taskset.size(); i++){
		printf("%.2f\t%.2f\t%.2f\n", taskset[i][0], taskset[i][1], taskset[i][2]);
	}

	float total_utilization = sum_utilizations(utilizations);
	printf("%f\n", total_utilization);
	if(restrictionsDBFValidated(taskset, param.total_utilization)){
		printf("DBF* proved task set is schedule \n");
	}else{
		printf("Didn't prove\n");
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
	-n,		--ntasks <value>			set number of tasks.\n\
	-t,		--TmaxPerTmin <value>		set Tmax/Tmin.\n\
	-u,		--utilization <value>		set u.\n\
	-d,		--DBF*						execute DBF* only.\n\
	-q,		--QPA						execute QPA only.\n\
	-b,		--both						execute both DBF* and QPA.\n", name);
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
		{"ntasks"		, required_argument , 0 , 'n' },
		{"TmaxPerTmin"	, required_argument , 0 , 't' },
		{"utilization"	, required_argument , 0 , 'u' },
		{"DBF*"			, no_argument       , 0 , 'd' },
		{"QPA"			, no_argument       , 0 , 'q' },
		{"both"			, no_argument       , 0 , 'b' },
		{0              , 0                 , 0 ,  0  },
	};

	if (argc < 2) {
		show_help(argv[0]);
	}

	while( (opt = getopt_long(argc, argv, "hn:t:u:dqb", options, NULL)) > 0 ) {
		switch ( opt ) {
			case 'h': /* -h ou --help */
				show_help(argv[0]);
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
			case 'd': /* -d ou --DBF* */
				param.dbf = true;
				break;
			case 'q': /* -q ou --QPA */
				param.qpa = true;
				break;
			case 'b': /* -b ou --both */
				param.both = true;
				break;
			default:
				fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt);
				exit(-1);
		}
	}
}
