#include <vector>
#include <cstdlib>
#include "parameters.hpp"
#include "dbf_qpa_test_data.hpp"
#include "tests.hpp"
#include "qpa_algorithm.hpp"
#include "generate_task_set.hpp"
#include "dbf_star_algorithm.hpp"
#include "dbf_algorithm.hpp"
#include "io_functions.hpp"
#include <getopt.h>

void show_help(const char *name);
void read_args(const int argc, char* argv[], PARAMETERS& param);


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

void show_help(const char *name) {
	fprintf(stderr, "\
usage: %s <parameters>\n\
	-h,		--help						show help.\n\
	-s,		--seed <value>				set seed for randomization.\n\
	-n,		--ntasks <value>			set number of tasks.\n\
	-t,		--TmaxPerTmin <value>		set Tmax/Tmin.\n\
	-u,		--utilization <value>		set utilization.\n\
	-k,		--numTasksets <value>		set number of tasksets.\n\
	-g,		--gen_tasksets				generate tasksets.\n\
	-c,		--schedulable				generate schedulable sets.\n\
	-d,		--dbf_test					dbf test (old method).\n\
	-q,		--qpa_test					qpa test.\n\
	-b,		--dbf_star_qpa_test			dbf* + qpa test.\n", name);
	exit(-1);
}


void read_args(const int argc, char* argv[], PARAMETERS& param) {
	int opt;
	/*
		https://daemoniolabs.wordpress.com/2011/10/07/usando-com-as-funcoes-getopt-e-getopt_long-em-c/
		https://linux.die.net/man/3/getopt_long
	*/
	const option options[] = {
		{"help"						, no_argument       , 0 , 'h' },
		{"seed"						, required_argument , 0 , 's' },
		{"ntasks"					, required_argument , 0 , 'n' },
		{"TmaxPerTmin"				, required_argument , 0 , 't' },
		{"utilization"				, required_argument , 0 , 'u' },
		{"numTasksets"				, required_argument , 0 , 'k' },
		{"gen_tasksets"				, no_argument       , 0 , 'g' },
		{"schedulable"				, no_argument       , 0 , 'c' },
		{"dbf_test"					, no_argument       , 0 , 'd' },
		{"qpa_test"					, no_argument       , 0 , 'q' },
		{"dbf_star_qpa_test"		, no_argument       , 0 , 'b' },
		{0              			, 0                 , 0 ,  0  },
	};

	if (argc < 2) {
		show_help(argv[0]);
	}

	while( (opt = getopt_long(argc, argv, "hs:n:t:u:k:gcdbq", options, NULL)) > 0 ) {
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
			case 'k': /* -k ou --numTasksets */
				param.numTasksets = std::atoi(optarg);
				break;
			case 'g': /* -g ou --gen_tasksets* */
				param.generate_tasksets = true;
				break;
			case 'c': /* -c ou --schedulable* */
				param.schedulable = true;
				break;
			case 'd': /* -d ou --dbf_test */
				param.dbf_test = true;
				break;
			case 'q': /* -q ou --qpa_test */
				param.qpa_test = true;
				break;
			case 'b': /* -b ou --both_test */
				param.dbf_star_qpa_test = true;
				break;
			default:
				fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt);
				exit(-1);
		}
	}

	if(param.dbf_test || param.qpa_test || param.dbf_star_qpa_test){
		param.run_tests = true;
	}
}
