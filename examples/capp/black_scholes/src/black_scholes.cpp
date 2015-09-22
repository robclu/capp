/* 
 * Class implementation for the vector addition example.
 */

#include "black_scholes.h"
#include <iostream>
#include <cstring>

void BlackScholes::runKernel(std::vector< std::vector<float> > &inputs,	
							 std::vector< std::vector<float> > &outputs) 
{
    // Don't need to do anything here
}


void BlackScholes::PrintResults() {

	std::cout << std::endl 
			  << "Displaying the results : " 
			  << std::endl  << std::endl;

	/* Then the outputs */
	for (int i = 0; i < out.size(); i++) {
		for (int j = 0; j < out[i].size(); j++) 
			std::cout << out[i][j] << " ";
		std::cout << std::endl;
	}
}
