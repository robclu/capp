/*
 * NOTE: OpenCL will not allow a simultaneous compliation for NVIDIA and AMD. So
 * to test the GPU and CPU either two separate sets of unit tests must be
 * written, or a single set where half fail. 
 *
 * Here Only CPU tests are written as they illustrate the functionality but are 
 * more likely to work (The AMD ADK or INTEL SDK is required for CPU OpenCL computation).
 */

#include <gtest/gtest.h>
#include <iostream>

#include "VectorAdd.hpp"

using namespace std;

// Kernel name must be the source file without the .cl
string cpuDevice = "GPU";
string kSource   = "vectoradd.cl";
string kName     = "vectoradd";

#define VECTOR_SIZE 512 * 8 * 4 * 4 * 4 * 4 * 4 * 2

// Define a CPU fixture class
class AspectTestCpu : public ::testing::Test
{
	// Normally the class would not be declared as a pointer but the compiler
	// was complaining when the instance was not a pointer. To illustrate the
	// instantiation without a pointer see the last test
	protected:
		AspectTestCpu() {
			vectadd = new VectorAddParallel(cpuDevice, kSource, kName);

			// Create some data for vector addition
			vector<T> a(VECTOR_SIZE), b(VECTOR_SIZE), c(VECTOR_SIZE);

			for (int i = 0; i < VECTOR_SIZE; i++) {
				a[i] = i; b[i] = 2*i; c[i] = 0;
			}

			inputs.push_back(a);
			inputs.push_back(b);
			outputs.push_back(c);
		}

		VectorAddParallel * vectadd;

		// Vectors for vector addition, T is defined in VectAdd.h
		vector< vector<T> > inputs;
		vector< vector<T> > outputs;
};

/* --- --- -- -- CPU tests -- -- --- --- */
/*
TEST_F(AspectTestCpu, canReturnDeviceType)
{
	EXPECT_EQ(cpuDevice, vectadd->getDeviceType());
}

TEST_F(AspectTestCpu, aspectCanDetectCPUDevices)
{
	// At lest one cpu device (will fail if amd or 
	// intel OpenCl SDK is not installed)
	EXPECT_GT(vectadd->devices.size(), 0);
}

TEST_F(AspectTestCpu, vectorAdditionIsCorrectlyPerformedWithAspectSetup)
{
	// Run the kernel
	vectadd->runKernel(inputs, outputs);

	for (int i = 0; i < VECTOR_SIZE; i++) {
		EXPECT_EQ(3 * i, outputs[0][i]);
	}
}

TEST_F(AspectTestCpu, aspectCanDetectAndStoreOpenCLPlatforms)
{
	// Must be at least 1 platform
	EXPECT_GT(vectadd->platforms.size(), 0);
}

TEST_F(AspectTestCpu, aspectCanCreateOpenCLContext)
{
	// Error codes are all negative, so no errors is the requirement
	EXPECT_GE(vectadd->context.getInfo<CL_CONTEXT_REFERENCE_COUNT>(), 0);
}

TEST_F(AspectTestCpu, aspectCanCreateOpenCLCommandQueue)
{
	EXPECT_GE(vectadd->queue.getInfo<CL_QUEUE_REFERENCE_COUNT>(), 0);
}

TEST_F(AspectTestCpu, aspectCanCreateOpenCLProgram)
{
	EXPECT_GT(vectadd->program.getInfo<CL_PROGRAM_NUM_DEVICES>(), 0);
}

TEST_F(AspectTestCpu, aspectCanLoadOpenCLKernelSourceAsBinary)
{
	// Size of source binary is greater than 0 (not empty)
	EXPECT_GT(vectadd->program.getInfo<CL_PROGRAM_BINARY_SIZES>()[0], 0);
}

TEST_F(AspectTestCpu, aspectCreatesNonVoidKernel)
{
	EXPECT_GE(vectadd->kernel.getInfo<CL_KERNEL_REFERENCE_COUNT>(), 0);
}

TEST_F(AspectTestCpu, aspectCanCreateBuffersWhenKernelIsRun)
{
	// Buffers are created when kernel is run
	vectadd->runKernel(inputs, outputs);
	EXPECT_EQ(3, vectadd->buffers.size());
}

// Shows non pointer instantiation of the class 
TEST(AspectTesTSetup, canSetClParametersCorrectly)
{	
	VectorAddParallel vectadd(cpuDevice, kSource, kName);

	EXPECT_EQ(cpuDevice, vectadd.getDeviceType());
	EXPECT_EQ(kName, vectadd.getKernelName());
}
*/
#define CONSTANT 4
// Shows full execution of the parallel class - instantiation 
// running of the kernel, highlighting similarity between 
// c++ programming
TEST(AspectTestFull, canPerformVectorAdditionCU)
{
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

	// Create vector addition object
	VectorAddParallel  vectadd(cpuDevice, kSource, kName);

	// Run kernel (one function call once data is ready)
	vectadd.runKernel(input, output);

	for (int i = 0; i < VECTOR_SIZE; i++) {
		EXPECT_EQ(4 * i + i, output[0][i]);
	}
}

int main(int argc, char** argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
