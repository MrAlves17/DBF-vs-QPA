#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>

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

std::vector<float> UUniFast(int n, int u){

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

int main(){

	int n = 14;
	int TmaxPerTmin = 1000;

	std::vector<float> utilizations = UUniFast(n, 1);
	std::vector<int> periods = GeneratePeriods(n, TmaxPerTmin);
	std::vector<int> relativeDeadlines = GenerateRelativeDeadlines(n, utilizations, periods);

	std::vector< std::vector<float>> taskset = IntegrateTasksData(n, utilizations, periods, relativeDeadlines);
	for(int i=0; i<taskset.size(); i++){
		for(int j=0; j<taskset[i].size(); j++){
			printf("%.3f ", taskset[i][j]);
		}
		printf("\n");
	}
	return 0;
}