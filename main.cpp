/*UUnifast algorithm*/

#include<iostream>
#include<math.h>
#include<vector>
#include<stdlib.h>

std::vector<int> UUniFast(int n, int u){
	int nextSumU;
	std::vector<int> vectU(n);
	int sumU = u;
	for(int i=0; i<n-1;i++){
		nextSumU = sumU*std::pow(rand(),1/(n-i));
		vectU[i] = sumU - nextSumU;
		sumU = nextSumU;
	}

	vectU[n-1] = sumU;

	return vectU;
}

int main(){

	std::vector<int> vectU = UUniFast(20, 1);
	for(int i=0; i<vectU.size(); i++){
		std::cout << vectU[i] << std::endl;
	}
	return 0;
}