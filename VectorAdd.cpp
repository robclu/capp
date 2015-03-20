/* 
 * Class implementation for the vector addition example.
 */

#include "VectorAdd.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <utility>
#include <string>
#include <stdlib.h>
#include <stdio.h>

/* 
 * Creates an OpenCL kernel from a a kernel source file and saves it as a
 * variable of the class.
 */
void VectorAddParallel::createKernel(const std::string kernelSource, std::string kernelName) {

	std::ifstream kSource(kernelSource.c_str());

	/* Convert the kernel to a string */
	std::string sourceString(
			std::istreambuf_iterator<char>(kSource),
			(std::istreambuf_iterator<char>()));

	cl::Program::Sources source(1, std::make_pair(sourceString.c_str(), sourceString.length() + 1));

	/* Create the program from the context and the loaded kernel source */
	program = cl::Program(context, source);

	/* Build the program for the devices. */
	program.build(devices);

	/* Make the kernel. */
	kernel = cl::Kernel(program, kernelName.c_str());
}

void VectorAddParallel::runKernel(std::vector< std::vector<float> > &inputs,	
								  std::vector< std::vector<float> > &outputs) {

	/* Copy the given data to the class data elements. */
	in = inputs;

	/* Create some buffers for the inputs. */
	//for (int i = 0; i < inputs.size(); i++) {
		/* Create a buffer for each of the inputs */
	//	buffers.push_back(cl::Buffer(context, CL_MEM_READ_ONLY, inputs[i].size() * sizeof(float)));

		/* Copy the input data over to the created buffer */
	//	queue.enqueueWriteBuffer(buffers.back(), CL_TRUE, 0, inputs[i].size() * sizeof(float), &inputs[i][0]);
	//}

	/* Create some buffers for the outputs */
	//for (int i = 0; i < outputs.size(); i++) {
	//	buffers.push_back(cl::Buffer(context, CL_MEM_WRITE_ONLY, outputs[i].size() * sizeof(float)));
	//}

	/* Set the arguments for the kernel */
	//for (int i = 0; i < buffers.size(); i++) {
	//	kernel.setArg(i, buffers[i]);
	//}

	/* This should allow the user to set the kernel dimension but for this
	 * simple example it will just be defined as N x 1 */
	//cl::NDRange global(inputs[0].size());
	//cl::NDRange local(4);

	/* Place the kernel on the queue */
	//queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);

	/* Read the results of the kernel into the output vector */
	//float * result = new float[VECTOR_SIZE];
	//size_t counter = 0;
	//for (int i = 0; i < outputs.size(); i++) {
		//queue.enqueueReadBuffer(buffers[inputs.size() + counter++], CL_TRUE, 0, outputs[i].size() * sizeof(float), result);
		///* Copy the result from the buffer into the vector. */
	//	outputs[i] = std::vector<float> (result, result + outputs[i].size());
	//}

	//free(result);

	/* Copy the results to the class */
	out = outputs;
}

void VectorAddParallel::printResults() {

	std::cout << std::endl 
			  << "Displaying the results : " 
			  << std::endl  << std::endl;

	/* First print the inputs */
	for (int i = 0; i < in.size(); i++) {
		for (int j = 0; j < in[i].size(); j++) {
			std::cout << in[i][j] << " ";
		}
		std::cout << std::endl;
	}

	/* Then the outputs */
	for (int i = 0; i < out.size(); i++) {
		for (int j = 0; j < out[i].size(); j++) {
			std::cout << out[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
