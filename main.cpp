/*
 * Vector addition OpenCL example.
 *
 * This one is using C++. Note that the vectors are std::vector
 * but cl::vector could also be used although apparently there are 
 * some issues with them and pointers returning a copy.
 *
 */

#include <vector>
#include <iostream>
//#include <chrono>						// No C++11 for aspectC++ until version 2.0 

#include "VectorAdd.h"

#define MAX_SOURCE_SIZE (0x100000)		// Largest source file size
const std::string DEVICE_TYPE = "GPU";
const std::string KERNEL_SOURCE = "vectoradd.cl";
const std::string KERNEL_NAME = "vectoradd";

using namespace std;

int main() {
	
	/* Create the VectorAdd object */
	VectorAddParallel vecProgram(DEVICE_TYPE, 
								 KERNEL_SOURCE,	
								 KERNEL_NAME);

	vector< vector<float> > input;
	vector< vector<float> > output;

	vector<float> A(VECTOR_SIZE);
	vector<float> B(VECTOR_SIZE);
	vector<float> C(VECTOR_SIZE);

	/* Create some input data data */
	for (int i = 0; i < VECTOR_SIZE; i++) {
		A[i] = i;
		B[i] = i;
		C[i] = 0;
	}

	input.push_back(A); input.push_back(B);
	output.push_back(C);

	/* Setup opengl */
//	vecProgram.setupOpencl(DEVICE_TYPE);
	vecProgram.createKernel(KERNEL_SOURCE, KERNEL_NAME);

	/* Time and run the kernel */
	vecProgram.runKernel(input, output);

	if (VECTOR_SIZE < 20) {
		vecProgram.printResults();
	}

	return 0;
}
