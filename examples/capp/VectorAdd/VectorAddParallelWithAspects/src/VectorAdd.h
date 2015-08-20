/* 
 * Class that can run OpenCL kernels in C++ using the aspect clContext
 * which gets rid of the OpenCL setup overhead.
 *
 * This class will specifically do vector addition 
 * in the form:
 *				C = A + B;
 *
 */

#ifndef __VECADD__H__
#define __VECADD__H_

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#undef CL_VERSION_1_2
#endif

#include <vector>
#include <string>

//#define VECTOR_SIZE 16
#define T			float

using namespace std;

class VectorAddParallel 
{
	public:
		// Sets parameters that OpenCL will need to setup the environment
		VectorAddParallel(const string dType,
					      const string kSource,
						  const string kName) 
			: deviceType(dType), kernelSource(kSource), kernelName(kName) {}

		// Function to run the kernel, which must be in this form as defined by
		// the clContext aspect (specifically in the clInstance class)
		void runKernel(vector< vector<T> > &inputs,
					   vector< vector<T> > &outputs);

		// Function to print the results 
		void printResults();

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
		vector< vector<T> > in;			// Input data
		vector< vector<T> > out;			// Output data
};

#endif
