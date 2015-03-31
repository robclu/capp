#include <gtest/gtest.h>
#include "VectorAdd.h"

using namespace std;

// Define some variables for setting up a parallel class
TEST(VectorAddParallelTest, canSetClParametersCorrectly)
{
	const string devType = "CPU";
	const string kSource = "vadd.cl";
	const string kName   = "VectorAddKernel";
	VectorAddParallel vAddPar(devType, kSource, kName);

	EXPECT_EQ(devType, vAddPar.getDeviceType());
	EXPECT_EQ(kName, vAddPar.getKernelName());
}

TEST(VectorAddTest, canDetermineIfKernelSourceIsValid)
{
	const string devType = "CPU";
	const string kSource = "vadd.cl";
	const string kName   = "VectorAddKernel";
	VectorAddParallel vAddPar(devType, kSource, kName);

	ASSERT_FALSE(vAddPar.validKernelSourceFile());
}

int main(int argc, char** argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
