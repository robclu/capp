/*
 * Windows version of test suite. Gtest requiring pthreads makes the mingw g++
 * linker segfault. This driver code is provided as an alternate to ittulstrace
 * the same concepts
 *
 */
#include <windows.h>
#include "VectorAdd.hpp"

#include <vector>
#include <iostream>
#include <stdio.h>

#define VECTOR_SIZE 16

// Kernel name must be the source file without the .cl
string cpuDevice = "CPU";
string kSource   = "vectoradd.cl";
string kName     = "vectoradd";

// Data vectors
vector<T> a(VECTOR_SIZE), b(VECTOR_SIZE), c(VECTOR_SIZE);

// Vectors for vector addition, T is defined in VectAdd.h
vector< vector<T> > inputs;
vector< vector<T> > outputs;

// Initialise the tests
void TESTS_INIT(int numTests)
{
	cout << "[=================RUNNING TEST=================]" << endl;
	cout << "[================" << numTests << "TESTS TO RUN================]\n" << endl;
}

// Simple test display function 
void TEST_INIT(string testName)
{
	cout << "[-----------RUN] " << testName << endl;
}

// Simple test end display function 
void TEST_END(string testName, bool result)
{
	if (result) {
		cout << "[PASSED--------] " << testName << endl;
	}
	else {
		cout << "[FAILED--------] " << testName << endl;
	}
}

/* --- --- -- -- CPU tests -- -- --- --- */

void canReturnDeviceType(VectorAddParallel* X, string testName)
{
	TEST_INIT(testName);
	TEST_END(testName, cpuDevice == X->getDeviceType());
	//TEST_END(testName, [] (VectorAddParallel* X) { return (cpuDevice == X->getDeviceType()); } );
}

void aspectCanDetectCPUDevices(VectorAddParallel* X, string testName)
{
	// At lest one cpu device (will fail if amd or 
	// intel OpenCl SDK is not installed)
	TEST_INIT(testName);
	TEST_END(testName, X->devices.size() > 0);
}

void vectorAdditionIsCorrectlyPerformedWithAspectSetup(VectorAddParallel* X, string testName)
{
	TEST_INIT(testName);

	// Run the kernel
	X->runKernel(inputs, outputs);

	TEST_END(testName, [] () { 
		size_t counter = 0;
		for (int i = 0; i < VECTOR_SIZE; i++) {
			3 * i ==  outputs[0][i] ? counter++ : counter--;
		}
		return (counter == VECTOR_SIZE);
	});
}

void aspectCanDetectAndStoreOpenCLPlatforms(VectorAddParallel* X, string testName)
{
	TEST_INIT(testName);
	// Must be at least 1 platform
	TEST_END(testName, X->platforms.size() > 0);
}

void aspectCanCreateOpenCLContext(VectorAddParallel* X, string testName)
{
	TEST_INIT(testName);
	// Error codes are all negative, so no errors is the requirement
	TEST_END(testName, X->context.getInfo<CL_CONTEXT_REFERENCE_COUNT>() >= 0);
}

void aspectCanCreateOpenCLCommandQueue(VectorAddParallel* X, string testName)
{
	TEST_INIT(testName);
	TEST_END(testName, X->queue.getInfo<CL_QUEUE_REFERENCE_COUNT>() > 0);
}

void aspectCanCreateOpenCLProgram(VectorAddParallel* X, string testName)
{
	TEST_INIT(testName);
	TEST_END(testName, X->program.getInfo<CL_PROGRAM_NUM_DEVICES>() > 0);
}

void aspectCanLoadOpenCLKernelSourceAsBinary(VectorAddParallel* X, string testName)
{
	TEST_INIT(testName);
	// Size of source binary is greater than 0 (not empty)
	TEST_END(testName, X->program.getInfo<CL_PROGRAM_BINARY_SIZES>()[0] > 0);
}

void aspectCreatesNonVoidKernel(VectorAddParallel* X, string testName)
{
	TEST_INIT(testName);
	TEST_END(testName, X->kernel.getInfo<CL_KERNEL_REFERENCE_COUNT>() >= 0);
}

void aspectCanCreateBuffersWhenKernelIsRun(VectorAddParallel* X, string testName)
{
	TEST_INIT(testName);

	// Buffers are created when kernel is run
	// 2 input and 1 output buffer
	X->runKernel(inputs, outputs);
	TEST_END(testName, X->buffers.size() == 3);
}

// Shows full execution of the parallel class - instantiation 
// running of the kernel, highlighting similarity between 
// c++ programming
void aspectCanPerformVectorAdditionCPU(string testName)
{
	TEST_INIT(testName);

	// Create vector addition object
	VectorAddParallel  vectadd(cpuDevice, kSource, kName);

	vector< vector<T> > input;
	vector< vector<T> > output;

	// Vector size, and T, are defined in VectorAdd.h
	vector<T> A(VECTOR_SIZE);
	vector<T> B(VECTOR_SIZE);
	vector<T> C(VECTOR_SIZE);

	// Create some data
	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		A[i] = i; B[i] = i; C[i] = 0;
	}

	input.push_back(A); 
	input.push_back(B);
	output.push_back(C);

	// Run kernel (one function call once data is ready)
	vectadd.runKernel(input, output);

	TEST_END(testName, [] () {
			size_t counter = 0;
			for (int i = 0; i < VECTOR_SIZE; i++) {
				2*i == outputs[0][i] ? counter++ : counter--;
			}
			return (counter == VECTOR_SIZE);
		});
}


int main() 
{	

	VectorAddParallel vectadd(cpuDevice, kSource, kName);

	// Fill data vectors with data
	for (int i = 0; i < VECTOR_SIZE; i++) {
			a[i] = i; b[i] = 3*i; c[i] = 0;
	}
	inputs.push_back(a);
	inputs.push_back(b);
	outputs.push_back(c);

	// RUn Tests 
	TESTS_INIT(11);

	canReturnDeviceType(&vectadd, "CanReturnDeviceType");
	aspectCanDetectCPUDevices(&vectadd, "ASpectCanDetectCPUDevices");
	aspectCanDetectAndStoreOpenCLPlatforms(&vectadd, "AspectCanDetectAndStoreOpenCLPlatforms");
	aspectCanCreateOpenCLContext(&vectadd, "AspectCanCreateOpenCLContext");
	aspectCanCreateOpenCLCommandQueue(&vectadd, "AspectCanCreateOpenCLCommandQueue");
	aspectCanCreateOpenCLProgram(&vectadd, "AspectCanCreateOpenCLProgram");
	aspectCanLoadOpenCLKernelSourceAsBinary(&vectadd, "AspectCanLoadOpenCLKernelSourceAsBinary");
	aspectCreatesNonVoidKernel(&vectadd, "AspectCreatesNonVoidKernel");
	aspectCanCreateBuffersWhenKernelIsRun(&vectadd, "AspectCanCreateBuffersWhenKernelIsRun");
	vectorAdditionIsCorrectlyPerformedWithAspectSetup(&vectadd, "VectorAdditionIsCorrectlyPerformedWithAspectSetup");
	aspectCanPerformVectorAdditionCPU("AspectCanPerformVectorAdditionCPU");

	cout << "Enter 'x' to exit!" << endl;

	while (getchar() != 'x') {};

	return 0;
}
