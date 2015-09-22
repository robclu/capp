/* 
 * Class that can run OpenCL kernels in C++ using the aspect clContext
 * which gets rid of the OpenCL setup overhead.
 *
 * Computes optino prices using Black-Scholes
 *
 */

#ifndef VECTORADD_H
#define VECTORADD_H

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#undef CL_VERSION_1_2
#endif

#include <vector>
#include <string>

//#define VECTOR_SIZE 16
#define T           float

using namespace std;

class BlackScholes {
public:
    // Sets parameters that OpenCL will need to setup the environment
    VectorAddParallel(const string dev_typeype,
                      const string k_Source,
                      const string k_ame) 
    : device_type(dev_type), kernel_source(k_source), kernel_name(k_name) {}

    // Function to run the kernel, which must must at least be implemented
    // as the aspect weavesa  pure virtual instance into it's base class
    void runKernel(vector< vector<T> > &inputs,
                   vector< vector<T> > &outputs);

    // Function to print the results 
    void printResults();

    // Get the type of device
    string getDeviceType() const { return device_type; }

    // Get the kernel name 
    string getKernelName() const { return kernel_name; }
private:
    const string        device_type;                // CPU or GPU
    const string        kernel_source;              // File to get the kernel from
    const string        kernel_name;                // Name of the kernel
    vector< vector<T> > in;                         // Input data
    vector< vector<T> > out;                        // Output data
};

#endif
