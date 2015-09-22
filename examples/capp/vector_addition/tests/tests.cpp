/*
 * NOTE: OpenCL will not allow a simultaneous compliation for NVIDIA and AMD. So
 * to test the GPU and CPU either two separate sets of unit tests must be
 * written, or a single set where half fail. 
 *
 * Here Only CPU tests are written as they illustrate the functionality but are 
 * more likely to work (The AMD ADK or INTEL SDK is required for CPU OpenCL computation).
 */

#include <iostream>
#include <sstream>

#include "VectorAdd.hpp"

using namespace std;

// Kernel name must be the source file without the .cl
string cpuDevice = "GPU";
string kSource   = "vectoradd.cl";
string kName     = "vectoradd";

int main(int argc, char* argv[]) 
{
	istringstream ss(argv[1]);
	int VECTOR_SIZE;
	ss >> VECTOR_SIZE;

	vector< vector<T> > input;
	vector< vector<T> > output;

	// Vector size, and T, are defined in VectorAdd.h
	vector<T> A(VECTOR_SIZE);
	vector<T> B(VECTOR_SIZE);
	vector<T> C(VECTOR_SIZE);

	// Create some data
	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		A[i] = i; B[i] = i; C[i] = 0;
	}

	input.push_back(A); 
	input.push_back(B);
	output.push_back(C);

	// Create vector addition object
	VectorAddParallel  vectadd(cpuDevice, kSource, kName);

	// Run kernel (one function call once data is ready)
	vectadd.runKernel(input, output);

	cout <<  VECTOR_SIZE << " " << 
		vectadd.GetRunTime().tv_nsec << endl;
}
