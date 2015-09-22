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

#include "black_scholes_sequential.h"

using namespace std;

// For random floats
float randFloat(float low, float high) {
    float t = (float)rand() / (float)RAND_MAX;
    return (1.0f - t) * low + t * high;
}

// Shows full execution of the parallel class - instantiation 
// running of the kernel, highlighting similarity between 
// c++ programming
int main(int argc, char* argv[]) {

	istringstream ss(argv[1]);
	int NUM_OPTIONS;
	ss >> NUM_OPTIONS;

	// Input and output vectors
	vector<vector<float>> in, output;
	vector<float> call, put, S, X, TT, out;
	vector<float> options;

	options.push_back(NUM_OPTIONS);

	// Define input data
	for (size_t i = 0; i < NUM_OPTIONS; i++) {
		call.push_back((float)-1);
		put.push_back((float)-1);
		S.push_back(randFloat(5.0f, 30.0f));
		X.push_back(randFloat(1.0f, 100.0f));
		TT.push_back(randFloat(0.25f, 10.0f));
		out.push_back(0.f);
	}

	in.push_back(call);
	in.push_back(put);
	in.push_back(S);
	in.push_back(X);
	in.push_back(TT);
	in.push_back(options);
	output.push_back(out);

	// Create BlackScholes object
	// NOTE : Timer is started on creation
	BlackScholes bsSeql;

	// Run kernel (one function call once data is ready)
	bsSeql.run_kernel(in, output);

	// Print the runtime 
	cout << NUM_OPTIONS << " " <<
			bsSeql.get_run_time().tv_nsec << endl;
}