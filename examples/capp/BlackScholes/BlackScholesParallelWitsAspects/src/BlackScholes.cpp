/* 
 * Class implementation for the vector addition example.
 */

#include "BlackScholes.h"
#include <iostream>
#include <cstring>

void BlackScholes::runKernel(std::vector< std::vector<float> > &inputs,	
								  std::vector< std::vector<float> > &outputs) 
{
	// Copy the given data to the class data elements. 
	//in = inputs;

	// Copy the results to the class 
	//out = outputs;
}


void BlackScholes::PrintResults() {

	std::cout << std::endl 
			  << "Displaying the results : " 
			  << std::endl  << std::endl;

	/* Then the outputs */
	for (int i = 0; i < out.size(); i++) {
		for (int j = 0; j < out[i].size(); j++) {
			std::cout << out[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
