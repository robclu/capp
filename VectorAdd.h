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
		
class VectorAddParallel {

	public :
	
		/* Constructor */
		VectorAddParallel(const std::string dev_type,
					      const std::string k_source_file,
						  const std::string k_name) 
			: device_type(dev_type), 
			  kernel_source(k_source_file),
			  kernel_name(k_name)
		{}

		/* Destructor so that the memory can be freed */
		~VectorAddParallel() {};

		void sayHello() {
			std::cout << "hello" << std::endl;
		}

		/* Function to create a kernel */
		void createKernel(const std::string kernelSource, std::string kernelName);

		/* Function to run the kernel */
		void runKernel(std::vector< std::vector<float> > &inputs,
					   std::vector< std::vector<float> > &outputs);

		/* Function to print the results */
		void printResults();

	private:

		// Device type to use 
		//		: GPU
		//		: CPU
		const std::string device_type;

		// The name of the kernel source file
		const std::string kernel_source;

		// The name of the kernel
		const std::string kernel_name;

		/* The data for the program */
		std::vector< std::vector<float> > in;			// Input data
		std::vector< std::vector<float> > out;			// Output data
};
