#include "clContext.ah"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <iterator>
#include <fstream>

void clContext::clInstance::setupOpenCL(const string& deviceType, const string& kernelSource, string& kernelName) 
{
	// Define the name of the kernel from the kernel source file
	// Just get rid of the .cl part of the kernel source name
	kernelName = kernelSource.substr(0, kernelSource.length() - 3);

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

