#ifndef parameters_class
#define parameters_class

class PARAMETERS{
	public: 
	int ntasks, TmaxPerTmin, seed, numTasksets;
	float total_utilization;
	bool generate_tasksets;
	bool run_tests;

	PARAMETERS(){
		seed = 0;
		ntasks = 14;
		TmaxPerTmin = 100;
		total_utilization = 0.70;
		numTasksets = 6000;
		generate_tasksets = false; 
		run_tests = false;
	}
};

#endif