#include <iostream>
#include <math.h>
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

int main(){

	std::vector<float> utilizations = UUniFast(9, 1);
	for(int i=0; i<utilizations.size(); i++){
		std::cout << utilizations[i] << std::endl;
	}


	return 0;
}