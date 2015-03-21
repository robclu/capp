/* 
 * Class that can run OpenCL kernels in C++.
 *
 * This class will specifically do vector addition 
 * in the form:
 *				C = A + B;
 *
 */

#ifdef __APPLE__
	#include <OpenCL/opencl.hpp>
#else
	#include <CL/cl.hpp>
	#undef  CL_VERSION_1_2
#endif 

#define VECTOR_SIZE 16
#define T			float
		
class VectorAddParallel 
{
	public :
	
		/* Constructor */
		VectorAddParallel(const std::string dType,
					      const std::string kSource,
						  const std::string kName) 
			: deviceType(dType), kernelSource(kSource), kernelName(kName) {}

		/* Destructor so that the memory can be freed */
		~VectorAddParallel() {};

		/* Function to create a kernel */
		void createKernel(const std::string kernelSource, std::string kernelName);

		/* Function to run the kernel */
		void runKernel(std::vector< std::vector<T> > &inputs,
					   std::vector< std::vector<T> > &outputs);

		/* Function to print the results */
		void printResults();

	private:

		// Device type to use 
		//		: GPU
		//		: CPU
		std::string deviceType;

		// The name of the kernel source file
		std::string kernelSource;

		// The name of the kernel
		std::string kernelName;

		/* The data for the program */
		std::vector< std::vector<T> > in;			// Input data
		std::vector< std::vector<T> > out;			// Output data
};
