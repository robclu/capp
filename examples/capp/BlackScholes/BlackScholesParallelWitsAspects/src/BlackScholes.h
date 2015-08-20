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

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#undef CL_VERSION_1_2
#endif

#include <vector>
#include <string>

using namespace std;

class BlackScholes 
{
	public:
		// Sets parameters that OpenCL will need to setup the environment
		BlackScholes(const string dfloat,
					      const string kSource,
						  const string kName) 
			: deviceType(dfloat), kernelSource(kSource), kernelName(kName) {}

		// Function to run the kernel, which must be in this form as defined by
		// the clContext aspect (specifically in the clInstance class)
		void runKernel(vector< vector<float> > &inputs,
					   vector< vector<float> > &outputs);

		// Function to print the results 
		void PrintResults();

		// Get the type of device
		string getDeviceType() const { return deviceType; }

		// Get the kernel name 
		string getKernelName() const { return kernelName; }

	private:
		// Device type (CPU or GPU)
		const string deviceType;

		// The name of the kernel source file
		const string kernelSource;

		// The name of the kernel
		const string kernelName;

		// Data to process
		vector< vector<float> > in;			// Input data
		vector< vector<float> > out;			// Output data
};

#endif
