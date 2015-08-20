/*
 * Member definitions for the clInstance class which is part of the clContext
 * aspect. The clInstance class will be put into any class that uses the
 * clContext aspect.
 *
 */

#include "clContext.ah"

#include <string>
#include <utility>
#include <iterator>
#include <fstream>

#define LOCAL_SIZE 128

timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ( (end.tv_nsec - start.tv_nsec) < 0 ) {
		temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	} else {
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return temp;
}

void clContext::clInstance::setupOpenCL(const string& deviceType, const string& kernelSource) 
{
	// Start the timer 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	
	// Get the available OpenCL platforms 
	cl::Platform::get(&platforms);

	// Setup the context depending on the deviceType
	// NOTE: device type needs to be passed a string in the derived class
	//		 constructor. The lack of checking this is due to the inability to
	//		 get the constructor arguments for derived class in AspectC++.
	if (deviceType == "GPU") {
		cl_context_properties cps[3] = {
			CL_CONTEXT_PLATFORM,	
			(cl_context_properties)(platforms[0])(),
			0
		};
		context = cl::Context(CL_DEVICE_TYPE_GPU, cps);
	}
	else if (deviceType == "CPU") {
		cl_context_properties cps[3] = {
			CL_CONTEXT_PLATFORM, 
			(cl_context_properties)(platforms[0])(),
			0
		};
		context = cl::Context(CL_DEVICE_TYPE_CPU, cps);
	}
	else {
		// Use the default platform
		cl_context_properties cps[3] = {
			CL_CONTEXT_PLATFORM,
			(cl_context_properties)(platforms[0])(),
			0
		};
		context = cl::Context(CL_DEVICE_TYPE_DEFAULT, cps);
	}

	// Get the devices for the created context (and platform)
	devices = context.getInfo<CL_CONTEXT_DEVICES>();

	// If there is an available device create a command queue
	// Could add options displaying available devices and letting the user
	// choose the device to use 
	if (devices.size() > 0) {
		queue = cl::CommandQueue(context, devices[0]);
	}
}

void clContext::clInstance::setupKernel(const string& kernelSource, const string& kernelName)
{
	ifstream kSource(("kernels/" + kernelSource).c_str());

	// Convert the source to a string 
	string sourceString(istreambuf_iterator<char>(kSource), (istreambuf_iterator<char>()));

	// Create and OpenCL Source from the kernel source string 
	cl::Program::Sources clSource(1, make_pair(sourceString.c_str(), sourceString.length() + 1));

	// Create and OpenCL program from the source and the context
	program = cl::Program(context, clSource);
	program.build(devices);

	// Make the OpenCL kernel
	kernel = cl::Kernel(program, kernelName.c_str());
}

void clContext::clInstance::manageClBuffers(vector< vector<T> > * inputs, vector< vector<T> > * outputs)
{
	buffers.clear();						// Make sure buffers are empty

	// Create buffers from each of the input vectors 
	for (size_t i = 0; i < inputs->size(); i++) {
		buffers.push_back(cl::Buffer(context, CL_MEM_READ_ONLY, (*inputs)[i].size() * sizeof(T)));
		// Create a buffer (copy from host to device mem) with a pointer to the first element in inputs[i]
		queue.enqueueWriteBuffer(buffers.back(), CL_TRUE, 0, (*inputs)[i].size() * sizeof(T), &((*inputs)[i][0]));
	}

	// Create the output buffer(s), these should all be initialised to 0 in host
	// code for safety
	for (size_t i = 0; i < outputs->size(); i++) {
		buffers.push_back(cl::Buffer(context, CL_MEM_WRITE_ONLY, (*outputs)[i].size() * sizeof(T)));
	}

	// Set the arguments for the kernel as the buffers 
	for (size_t i = 0; i < buffers.size(); i++) {
		kernel.setArg(i, buffers[i]);
	}

	// This should be set by the derived aspect or the implemented class
	cl::NDRange global((*inputs)[0].size(), 1, 1);		// Number of elements to process
	cl::NDRange local(LOCAL_SIZE, 1, 1);							

	// Place the kernel on the command queue
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);

	// Get the results back to the output vector
	for (size_t i = 0; i < outputs->size(); i++) {
		// Create a buffer for the results from the kernel
		T * results = new T[(*outputs)[i].size()];

		// Move the result from the device to the host
		queue.enqueueReadBuffer(buffers[inputs->size() + i], CL_TRUE, 0, (*outputs)[i].size() * sizeof(T), results);

		// Move the result from the temp buffer into the output vector
		(*outputs)[i] = vector<T>(results, results + (*outputs)[i].size());
		free(results);
	}

	// Stop the timer
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	//cout << "Time in nanoseconds: " << diff(start, end).tv_nsec << endl;
}

timespec clContext::clInstance::GetRunTime() {
	return diff(start,end);
}
