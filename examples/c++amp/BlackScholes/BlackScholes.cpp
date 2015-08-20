//--------------------------------------------------------------------------------------
// Copyright (c) Microsoft Corp. 
//
// File: BlackScholes.cpp
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
// Implements Black Scholes sample in C++ AMP
// Refer README.txt
//--------------------------------------------------------------------------------------

#include "BlackScholes.h"

#include <math.h>
#include <amp_math.h>
#include <iostream>
#include <assert.h>

blackscholes::blackscholes(float _volatility, float _riskfreerate, int _size)
{
    data_size = _size;
    riskfreerate = _riskfreerate;
    volatility = _volatility;

    stock_price.resize(data_size);
    option_strike.resize(data_size);
    option_years.resize(data_size);
    call_result_amp.resize(data_size); 
    put_result_amp.resize(data_size);

    srand(2012);

    for (int i = 0; i < data_size; i++)
    {
        stock_price[i] = 100.0f * (((float)rand()) / RAND_MAX);
        option_strike[i] = stock_price[i] * ((float)rand()) / RAND_MAX;
        option_years[i] = 20.0f * ((float)rand()) / RAND_MAX;
        call_result_amp[i] = 0;
        put_result_amp[i] = 0;
    }
}

blackscholes::~blackscholes()
{

}

void blackscholes::execute()
{
    const array<float,1> a_stock_price(data_size, stock_price.begin());
    const array<float,1> a_option_strike(data_size, option_strike.begin());
    const array<float,1> a_option_years(data_size, option_years.begin());
    array<float,1> a_call_result(data_size);
    array<float,1> a_put_result(data_size);

    float R = riskfreerate;
    float V = volatility;

    assert((data_size%BSCHOLES_TILE_SIZE) == 0);

    parallel_for_each(extent<1>(data_size).tile<BSCHOLES_TILE_SIZE>(),
    [=, &a_stock_price, &a_option_strike, &a_option_years, &a_call_result, &a_put_result] (tiled_index<BSCHOLES_TILE_SIZE> tidx) restrict(amp)
    {
        float S = a_stock_price(tidx.global[0]);
        float X = a_option_strike(tidx.global[0]);
        float T = a_option_years(tidx.global[0]);
            
        float sqrtT = fast_math::sqrtf(T);
        float d1 = (fast_math::logf(S / X) + (R + 0.5f * V * V) * T) / (V * sqrtT);
        float d2 = d1 - V * sqrtT;

        float cndd1 = cnd_calc(d1);
        float cndd2 = cnd_calc(d2);
                
        float exp_RT = fast_math::expf(- R * T);
        a_call_result[tidx.global[0]] = S * cndd1 - X * exp_RT * cndd2;
        a_put_result[tidx.global[0]]  = X * exp_RT * (1.0f - cndd2) - S * (1.0f - cndd1);
    });
    
    copy(a_call_result, call_result_amp.begin());
    copy(a_put_result, put_result_amp.begin());    
}

void blackscholes::verify()
{
    std::vector<float> call_result_cpu(data_size);
    std::vector<float> put_result_cpu(data_size);

    for(unsigned i=0; i < stock_price.size(); i++) 
    {
        blackscholes_CPU(i, call_result_cpu, put_result_cpu);
    }

    if (!sequence_equal(call_result_amp, call_result_cpu) | !sequence_equal(put_result_amp, put_result_cpu)) 
    {
        std::cout << "**BlackScholes verification FAILED.**" << std::endl;
    }
    else 
    {
        std::cout << "**BlackScholes verification passed.**" << std::endl;
    }
}

bool blackscholes::sequence_equal(std::vector<float>& ref_data, std::vector<float>& compute_data) 
{
    const float EPS = 1e-4f;
    for(unsigned i=0; i < ref_data.size(); i++) 
    {
        float a = ref_data[i], b = compute_data[i];

        // Is absolute or relative error less than EPS?
        float m = fmax(1, fmax(abs(a), abs(b)));
        if (abs(a - b) / m > EPS) 
        {
            std::cout << "FAIL: "<< a <<',' << b << std::endl;
            return false;
        }
    }

    return true;
}

float blackscholes::cnd_calc(float d) restrict (amp, cpu)
{
    const float a1 = 0.31938153f, a2 = -0.356563782f, a3 = 1.781477937f, a4 = -1.821255978f, a5 = 1.330274429f;
    const float isqrt2pi = 0.39894228040143267793994605993438f;
    float x = 1.0f / (1.0f + 0.2316419f * fast_math::fabsf(d));
    
    float cnd = isqrt2pi * fast_math::expf(- 0.5f * d * d) * (x * (a1 + x * (a2 + x * (a3 + x * (a4 + x * a5)))));
    return (d > 0) ? 1.0f - cnd : cnd;
}

void blackscholes::blackscholes_CPU(unsigned i, std::vector<float>& out_call_result, std::vector<float>& out_put_result)
{
    float S = stock_price[i];
    float X = option_strike[i];
    float T = option_years[i];
    float R = riskfreerate;
    float V = volatility;
    
    float sqrtT = sqrt(T);
    float d1 = (log(S / X) + (R + 0.5f * V * V) * T) / (V * sqrtT);
    float d2 = d1 - V * sqrtT;
    
    float cndd1 = cnd_calc(d1);
    float cndd2 = cnd_calc(d2);
    
    float exp_RT = exp(- R * T);
    out_call_result[i] = S * cndd1 - X * exp_RT * cndd2;
    out_put_result[i]  = X * exp_RT * (1.0f - cndd2) - S * (1.0f - cndd1);
}

int main()
{
    accelerator default_device;
    std::wcout << L"Using device : " << default_device.get_description() << std::endl;
//    if (default_device == accelerator(accelerator::direct3d_ref))
  //      std::cout << "WARNING!! Running on very slow emulator! Only use this accelerator for debugging." << std::endl;

    blackscholes _bs_float;
    _bs_float.execute();
    _bs_float.verify();

    return 0;
}

