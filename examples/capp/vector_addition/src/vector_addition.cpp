/* 
 * Class implementation for the vector addition example.
 */

#include "vector_addition.h"
#include <iostream>
#include <cstring>

void VectorAddParallel::runKernel(std::vector< std::vector<float> > &inputs,    
                                  std::vector< std::vector<float> > &outputs) 
{
    in  = inputs;           // Copy inputs to class
    out = outputs;          // Copy outputs to class
    
    // Aspect then manages memory and invokes kernel
}


void VectorAddParallel::printResults() 
{
    std::cout << std::endl 
              << "Displaying the results : " 
              << std::endl  << std::endl;

    // Print the inputs
    for (int i = 0; i < in.size(); i++) {
        for (int j = 0; j < in[i].size(); j++) 
            std::cout << in[i][j] << " ";
        std::cout << std::endl;
    }
    // Print the outputs
    for (int i = 0; i < out.size(); i++) {
        for (int j = 0; j < out[i].size(); j++) 
            std::cout << out[i][j] << " ";
        std::cout << std::endl;
    }
}
