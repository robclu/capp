//--------------------------------------------------------------------------------------
// Copyright (c) Microsoft Corp. 
//
// File: BlackScholes.h
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this 
// file except in compliance with the License. You may obtain a copy of the License at 
// http://www.apache.org/licenses/LICENSE-2.0  
//  
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, 
// EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR 
// CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT. 
//  
// See the Apache Version 2.0 License for specific language governing permissions and 
// limitations under the License.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Refer README.txt
//--------------------------------------------------------------------------------------

#pragma once

#include <vector>
#include <math.h>
#include <amp.h>

using namespace concurrency;

#define DEFAULT_SIZE                (512*512)
#define DEFAULT_RISK_FREE_RATE      (-0.01f)
#define DEFAULT_VOLATILITY          (0.99f)

#define BSCHOLES_TILE_SIZE          256

class blackscholes
{
public:
    blackscholes(float _volatility = DEFAULT_VOLATILITY, float _riskfreerate = DEFAULT_RISK_FREE_RATE, int _size = DEFAULT_SIZE);
    void execute();
    ~blackscholes();
    void verify();

private:
    bool sequence_equal(std::vector<float>& ref_data, std::vector<float>& compute_data);

    static float cnd_calc(float d) restrict (amp, cpu);

    void blackscholes_CPU(unsigned i, std::vector<float>& out_call_result, std::vector<float>& out_put_result);

    std::vector<float> stock_price, option_strike, option_years, call_result_amp, put_result_amp;
    int data_size;
    float riskfreerate;
    float volatility;
};
