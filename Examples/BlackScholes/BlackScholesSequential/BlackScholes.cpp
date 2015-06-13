#include "BlackScholes.h"
#include <math.h>

static double CND(double d){
    const double       A1 = 0.31938153;
    const double       A2 = -0.356563782;
    const double       A3 = 1.781477937;
    const double       A4 = -1.821255978;
    const double       A5 = 1.330274429;
	const double RSQRT2PI = 0.39894228040143267793994605993438;

    double
        K = 1.0 / (1.0 + 0.2316419 * fabs(d));

    double
        cnd = RSQRT2PI * exp(- 0.5 * d * d) * 
        (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));

    if (d > 0)
        cnd = 1.0 - cnd;

    return cnd;
}

static void BlackScholesBodyCPU(
    float& call, //Call option price
    float& put,  //Put option price
    float Sf,    //Current stock price
    float Xf,    //Option strike price
    float Tf,    //Option years
    float Rf,    //Riskless rate of return
    float Vf     //Stock volatility
){
    double S = Sf, X = Xf, T = Tf, R = Rf, V = Vf;

    double sqrtT = sqrt(T);
    double    d1 = (log(S / X) + (R + 0.5 * V * V) * T) / (V * sqrtT);
    double    d2 = d1 - V * sqrtT;
    double CNDD1 = CND(d1);
    double CNDD2 = CND(d2);

    // Calculate Call and Put simultaneously
    double expRT = exp(- R * T);
    call = (float)(S * CNDD1 - X * expRT * CNDD2);
    put  = (float)(X * expRT * (1.0 - CNDD2) - S * (1.0 - CNDD1));
}

void BlackScholes::BlackScholesFull (
    float *h_Call, //Call option price
    float *h_Put,  //Put option price
    float *h_S,    //Current stock price
    float *h_X,    //Option strike price
    float *h_T,    //Option years
    float* opCount,
	float* out
){
	const float R = 0.02f;
	const float V = 0.3f;

	unsigned int optionCount = (unsigned int)*opCount;

    for(unsigned int i = 0; i < optionCount; i++) {
        BlackScholesBodyCPU(
            h_Call[i],
            h_Put[i],
            h_S[i],
            h_X[i],
            h_T[i],
            R,
            V
        );
		out[i] = h_Call[i];
	}
}

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

void BlackScholes::runKernel(vector<vector<float>>& inputs,
			   vector<vector<float>>& outputs) {
	// Call the BlackScholes kernel
	BlackScholesFull(
			&inputs[0][0],
			&inputs[1][0],
			&inputs[2][0],
			&inputs[3][0],
			&inputs[4][0],
			&inputs[5][0],
			&outputs[0][0] );

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
}

timespec BlackScholes::GetRunTime() {
	return diff(start, end);
}
