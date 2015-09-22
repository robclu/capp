/* 
 * Sequrntial implementation example
 *
 */

#ifndef BLACK_SCHOLES_CPP_INCLUDED
#define BLACK_SCHOLES_CPP_INCLUDED

#include <vector>
#include <string>
#include <time.h>

using namespace std;

class BlackScholes {
public: 
    timespec start, end;
public:
    // Sets parameters that OpenCL will need to setup the environment
    BlackScholes() {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    }

    // Function to run the kernel, which must be in this form as defined by
    // the clContext aspect (specifically in the clInstance class)
    void run_kernel(vector< vector<float> > &inputs,
                    vector< vector<float> > &outputs);
        
    timespec get_run_time();
private:
    // 'Kernel' that executes black scholes
    void black_scholes_full(float* call, float* put   , float* S  , float* X, 
                            float* T   , float* optN  , float* out);
};

#endif
