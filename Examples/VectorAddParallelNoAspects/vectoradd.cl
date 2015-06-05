/* 
 * Kernel source for the vector addition example.
 */

__kernel void vectoradd(__global float* a, __global float* b, __global float* c) {

	/* VectorAdd is a simple example and only required a 1D kernel.
	 * All we need is the global id for the thread. */
	int i = get_global_id(0);							// The id of the element in the array
	c[i] = a[i] + b[i];
}