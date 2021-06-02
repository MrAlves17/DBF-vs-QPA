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

	int seed = (int)time(0);			// random seed

	CRandomMersenne RanGen(seed);		// make instance of random number generator

	float nextSumU;
	std::vector<float> utilizations(n);
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

std::vector<int> GeneratePeriods(int n, int ub){
	int seed = (int)time(0);			// random seed

	CRandomMersenne RanGen(seed);		// make instance of random number generator

	std::vector<int> periods(n);
	periods[n-1] = ub;

	int numIntervals = ceil(log(ub));
	int periodsPerInterval = floor((n-1)/numIntervals);
	int remaining = (n-1)%numIntervals;

	for(int i=0; i<numIntervals-1; i++){
		for(int j=0; j<periodsPerInterval; j++){
			periods[i*periodsPerInterval+j] = RanGen.IRandom(exp(i), exp(i+1));
		}
	}

	for(int j=0; j<periodsPerInterval; j++){
		periods[(numIntervals-1)*periodsPerInterval+j] = RanGen.IRandom(exp(numIntervals-1), ub);
	}

	for(int i=0; i<remaining; i++){
		periods[numIntervals*periodsPerInterval+i] = RanGen.IRandom(exp(i), exp(i+1));
	}

	EndOfProgram();

	return periods;
}

int main(){

	int n = 14;

	std::vector<float> utilizations = UUniFast(n, 1);
	for(int i=0; i<utilizations.size(); i++){
		std::cout << utilizations[i] << std::endl;
	}

	printf("\n");

	std::vector<int> periods = GeneratePeriods(n, 10000);
	for(int i=0; i<periods.size(); i++){
		std::cout << periods[i] << std::endl;
	}

	return 0;
}