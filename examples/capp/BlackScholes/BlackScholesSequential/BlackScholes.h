/* 
 * Class that can run OpenCL kernels in C++ using the aspect clContext
 * which gets rid of the OpenCL setup overhead.
 *
 * This class will specifically do vector addition 
 * in the form:
 *				C = A + B;
 *
 */

#ifndef BLACK_SCHOLES_CPP_INCLUDED
#define BLACK_SCHOLES_CPP_INCLUDED

#include <vector>
#include <string>
#include <time.h>

using namespace std;

class BlackScholes 
{
	public: 
		timespec start, end;
	public:
		// Sets parameters that OpenCL will need to setup the environment
		BlackScholes() {
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
		}

		// Function to run the kernel, which must be in this form as defined by
		// the clContext aspect (specifically in the clInstance class)
		void runKernel(vector< vector<float> > &inputs,
					   vector< vector<float> > &outputs);
		
		timespec GetRunTime();
	private:
		// 'Kernel' that executes black scholes
		void BlackScholesFull(float* call, float* put, float* S, float* X, 
				              float* T, float* optN, float* out);
};

#endif
