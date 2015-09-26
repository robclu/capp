/*
 *  Parallel vector addition example in OpenCl without aspects.
 *
 *  Copyright (C) 2015 Rob Clucas robclu1818@gmail.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT AN_size.y WARRANTY; without even the implied warranty of
 *  MERCHANTABILIT_size.y or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  _size.you should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation,
 *	Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
 * NOTE : Since the current version of aspectc++ (1.2) does not support c++11
 *        the timers that were using for the parallel aspect implementation 
 *        were c timers. To ensure that the comparison is accurate the same 
 *        timers were used.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <sstream>

#define __CL_ENABLE_EXCEPTIONS

// Make sure we are using version 1.1
// otherwise NVIDIA GPU's wont work
#ifdef __APPLE__
	#include <OpenCL/opencl.hpp>
#else
	#include <CL/cl.hpp>
	#undef   CL_VERSION_1_2
#endif

#define T float
#define I 2

using namespace std;

// Function for computing the time between two time points
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

int main(int argc, char** argv) 
{
	vector<cl::Platform>    platforms;
	vector<cl::Device>      devices;
	vector<cl::Buffer>      buffers;
	cl::Context             context;
	cl::CommandQueue        queue;
	cl::Program             program;
	cl::Kernel              kernel;

    // ...
    
	// ------------- Start OpenCL Setup ----------------- //
	
	cl::Platform::get(&platforms);

	cl_context_properties cps[3] = {
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)(platforms[0])(),
		0
	};

	context = cl::Context(CL_DEVICE_TYPE_GPU, cps);

	devices = context.getInfo<CL_CONTEXT_DEVICES>();

	queue = cl::CommandQueue(context, devices[0]);
	
	// -------------- Kernel Execution Setup ------------ //
	
	ifstream kSource("vectkernel.cl");

	string sourcestr(
			istreambuf_iterator<char>(kSource),
			(istreambuf_iterator<char>())		);

	cl::Program::Sources source(
			1, 
			make_pair(
				sourcestr.c_str(), 
				sourcestr.length() + 1		
			)
	);

	program = cl::Program(context, source);

	err = program.build(devices);
	if(err != CL_SUCCESS){
		std::cout << "Build Status: " << program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(devices[0]) << std::endl;
		std::cout << "Build Options:\t" << program.getBuildInfo<CL_PROGRAM_BUILD_OPTIONS>(devices[0]) << std::endl;
		std::cout << "Build Log:\t " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]) << std::endl;
	}

	try{
		kernel = cl::Kernel(program, "vectkernel", &err);
	}
	catch (cl::Error er) {
		    printf("ERROR: %s(%d)\n", er.what(), er.err());
	}

	// Create buffers for input
	for (auto& input : in ) {
		buffers.push_back( 
			cl::Buffer(
				context,
				CL_MEM_READ_ONLY,
				input.size() * sizeof(T)
				)
		);
		queue.enqueueWriteBuffer(
				buffers.back(),
				CL_TRUE,
				0,
				input.size() * sizeof(T),
				&input[0]
		);
	}

	buffers.emplace_back( 
			context,
			CL_MEM_WRITE_ONLY,
			out.size() * sizeof(T)
	);

	for (size_t i = 0; i < buffers.size(); i++) {
		kernel.setArg(i, buffers[i]);
	}

	cl::NDRange global(N,1,1);
	cl::NDRange local(256,1,1);

	// ------------ Run Kernel --------------- //
	
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);
	
	T* result = new T[N];
	queue.enqueueReadBuffer(
			buffers.back(),
			CL_TRUE,
			0, 
			out.size() * sizeof(T),
			result
	);

	// Stop the timer
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	free(result);

	cout << N << " "  << diff(start, end).tv_nsec << endl;
	return 1;

}