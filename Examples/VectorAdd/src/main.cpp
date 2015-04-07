/*
 * Vector addition OpenCL example.
 *
 * This one is using C++. Note that the vectors are std::vector
 * but cl::vector could also be used although apparently there are 
 * some issues with them and pointers returning a copy.
 *
 */

#include "VectorAdd.h"

#include <vector>
#include <iostream>
#include <stdio.h>

const string DEVICE_TYPE   = "CPU";
const string KERNEL_SOURCE = "vectoradd.cl";
const string KERNEL_NAME   = "vectoradd";

int main() 
{	
	/* Create the VectorAdd object */
	VectorAddParallel vecProgram(DEVICE_TYPE, 
								 KERNEL_SOURCE,
								 KERNEL_NAME);

	vector< vector<T> > input;
	vector< vector<T> > output;

	vector<T> A(VECTOR_SIZE);
	vector<T> B(VECTOR_SIZE);
	vector<T> C(VECTOR_SIZE);

	vector<cl::Device> dev = vecProgram.devices;

	printf("%d\n",  dev.size());

	/* Create some input data data */
	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		A[i] = i;
		B[i] = i;
		C[i] = 0;
	}

	input.push_back(A); input.push_back(B);
	output.push_back(C);

	/* Time and run the kernel */
	vecProgram.runKernel(input, output);

	if (VECTOR_SIZE < 20) {
		vecProgram.printResults();
	}

	return 0;
}
