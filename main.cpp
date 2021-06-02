#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include "parameters.hpp"
#include <getopt.h>

#include <time.h>						// define time()
#include "randomc/randomc.h"			// define classes for random number generators

#ifndef MULTIFILE_PROJECT
// If compiled as a single file then include these cpp files, 
// If compiled as a project then compile and link in these cpp files.
   // Include code for the chosen random number generator:
   #include "randomc/mersenne.cpp"
   // define system specific user interface:
   #include "randomc/userintf.cpp"
#endif

void show_help(const char *name);
void read_args(const int argc, char* argv[], PARAMETERS& param);
float sum_utilizations(std::vector<float>& utilizations);

std::vector<float> UUniFast(int n, float u);
std::vector<int> GeneratePeriods(int n, int TmaxPerTmin);
std::vector<int> GenerateRelativeDeadlines(int n, std::vector<float>& utilizations, std::vector<int>& periods);
std::vector< std::vector<float>> IntegrateTasksData(int n, std::vector<float>& utilizations, std::vector<int>& periods, std::vector<int>& relativeDeadlines);

float dbf_sum(std::vector< std::vector<float>>& taskset, float deadlineTask);
bool restrictionsDBFValidated(std::vector< std::vector<float>>& taskset, float total_utilization);

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
		printf("did not prove\n");
	}

	return 0;
}

float dbf_sum(std::vector< std::vector<float>>& taskset, float deadlineTask){
	float sum = 0;
	for(int i=0; i<taskset.size(); i++){
		if(deadlineTask >= taskset[i][2]){
			sum += taskset[i][0]*taskset[i][1] + (deadlineTask - taskset[i][2])*taskset[i][0];
		}
	}

	return sum;
}

bool restrictionsDBFValidated(std::vector< std::vector<float>>& taskset, float total_utilization){
	for(int i=0; i<taskset.size(); i++){
		if(taskset[i][2] - dbf_sum(taskset, taskset[i][2]) < taskset[i][0]*taskset[i][1]){
			return false;
		}
		if(1 - total_utilization < taskset[i][0]){
			return false;
		}
	}

	return true;
}

float sum_utilizations(std::vector<float>& utilizations){
	float sum = 0;
	for(int i=0; i<utilizations.size(); i++){
		sum += utilizations[i];
	}

	return sum;
}

std::vector<float> UUniFast(int n, float u){

	int seed = (int)time(0);

	CRandomMersenne RanGen(seed);

	std::vector<float> utilizations(n);
	float nextSumU;
	float sumU = u;
	for(int i=0; i<n-1;i++){
		nextSumU = sumU*std::pow(RanGen.Random(),1.0/(n-i));
		utilizations[i] = sumU - nextSumU;
		sumU = nextSumU;
	}

	utilizations[n-1] = sumU;

	EndOfProgram();

	return utilizations;
}

std::vector<int> GeneratePeriods(int n, int TmaxPerTmin){
	int seed = (int)time(0);

	CRandomMersenne RanGen(seed);

	std::vector<int> periods(n);
	periods[n-1] = TmaxPerTmin;

	int numIntervals = ceil(log(TmaxPerTmin));
	int periodsPerInterval = floor((n-1)/numIntervals);
	int remaining = (n-1)%numIntervals;

	for(int i=0; i<numIntervals-1; i++){
		for(int j=0; j<periodsPerInterval; j++){
			periods[i*periodsPerInterval+j] = RanGen.IRandom(exp(i), exp(i+1));
		}
	}

	for(int j=0; j<periodsPerInterval; j++){
		periods[(numIntervals-1)*periodsPerInterval+j] = RanGen.IRandom(exp(numIntervals-1), TmaxPerTmin);
	}

	for(int i=0; i<remaining; i++){
		periods[numIntervals*periodsPerInterval+i] = RanGen.IRandom(exp(i), exp(i+1));
	}

	EndOfProgram();

	return periods;
}

std::vector<int> GenerateRelativeDeadlines(int n, std::vector<float>& utilizations, std::vector<int>& periods){
	int seed = (int)time(0);

	CRandomMersenne RanGen(seed);

	std::vector<int> relativeDeadlines(n);

	for(int i=0; i<n; i++){
		float a, b = 1.2*periods[i];
		float computationTime = utilizations[i]*periods[i];

		if(computationTime < 10){
			a = computationTime;
		}else if(computationTime < 100){
			a = 2*computationTime;
		}else if(computationTime < 1000){
			a = 3*computationTime;
		}else{
			a = 4*computationTime;
		}

		relativeDeadlines[i] = RanGen.IRandom(ceil(a),ceil(b));
	}

	EndOfProgram();

	return relativeDeadlines;
}

std::vector< std::vector<float>> IntegrateTasksData(int n, std::vector<float>& utilizations, std::vector<int>& periods, std::vector<int>& relativeDeadlines){
	std::vector< std::vector<float>> taskset;
	taskset.resize(n);

	for(int i=0; i<n; i++){
		taskset[i].push_back(utilizations[i]);
		taskset[i].push_back(periods[i]);
		taskset[i].push_back(relativeDeadlines[i]);
	}

	return taskset;
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
