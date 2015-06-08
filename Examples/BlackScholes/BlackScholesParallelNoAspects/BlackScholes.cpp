/*
 *  Parallel Black Scholes option pricing example in OpenCl without aspects.
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

// Make sure we are using version 1.1
// otherwise NVIDIA GPU's wont work
#ifdef __APPLE__
	#include <OpenCL/opencl.hpp>
#else
	#include <CL/cl.hpp>
	#undef   CL_VERSION_1_2
#endif

#define T float
#define OP_COUNT 512 
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

int main(int argc, char** argv) {

	// Timer variables 
	timespec start, end;

	// Start the clock
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	// OpenCl variables
	vector<cl::Platform> platforms;
	vector<cl::Device> devices;
	vector<cl::Buffer> buffers;
	cl::Context context;
	cl::CommandQueue queue;
	cl::Program program;
	cl::Kernel kernel;

	// Input and output vectors
	vector<vector<T>> in;
	vector<T> call, put, S, X, T, out;

	// Allocate data 
	for (size_t i = 0; i < N; i++) {
		out.push_back(static_cast<T>(0));
	}

	// Define input data
	for (size_t i = 0; i < OP_COUNT; i++) {
		call.push_back((T)-1);
		put.push_back((T)-1);
		S.push_back(randFloat(5.0f, 30.0f));
		X.push_back(randFloat(1.0f, 100.0f));
		T.push_back(randFloat(0.25f, 10.0f));
	}


	// ------------- Start OpenCL Setup ----------------- //
	
	cl::Platform::get(&platforms);

	cl_context_properties cps[3] = {
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)(platforms[0])(),
		0
	};

	context = cl::Context(CL_DEVICE_TYPE_GPU, cps);

	devices = context.getInfo<CL_CONTEXT_DEVICES>();

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

	program.build(devices);

	kernel = cl::Kernel(program, "vectkernel");

	// Create buffers for input
	for (auto& input : in ) {
		buffers.emplace_back( 
				context,
				CL_MEM_READ_ONLY,
				input.size() * sizeof(T)
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

	cl::NDRange global(in[0].size(), 1, 1);
	cl::NDRange local(512, 1, 1);

	// ------------ Run Kernel --------------- //
	
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);

	// Read results back
	
	T result[N];
	queue.enqueueReadBuffer(
			buffers.back(),
			CL_TRUE,
			0, 
			out.size() * sizeof(T),
			result
	);

	// Stop the timer
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	cout << "Time in nanoseconds: " << diff(start, end).tv_nsec << endl;
	return 1;

}