#ifndef parameters_struct
#define parameters_struct

struct PARAMETERS{
	int ntasks, TmaxPerTmin, seed, numTasksets;
	float total_utilization;
	bool generate_tasksets;
	bool schedulable;
	bool run_tests;

	bool dbf_test;
	bool qpa_test;
	bool dbf_star_qpa_test;

	PARAMETERS(){
		seed = 0;
		ntasks = 14;
		TmaxPerTmin = 100;
		total_utilization = 0.70;
		numTasksets = 6000;
		generate_tasksets = false; 
		schedulable = false;
		run_tests = false;
		dbf_test = false;
		qpa_test = false;
		dbf_star_qpa_test = false;
	}
};

#endif