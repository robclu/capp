
#line 1 "src/BlackScholes.cpp"
#ifndef __ac_FIRST__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects__
#define __ac_FIRST__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects__
#define __ac_FIRST_FILE__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_src_BlackScholes_cpp__
#endif // __ac_FIRST__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects__

#line 1 "src/BlackScholes.cpp"

#line 11 "BlackScholes.acc"

#ifndef __ac_h_
#define __ac_h_
#ifdef __cplusplus
namespace AC {
  typedef const char* Type;
  enum JPType { CALL = 0x0004, EXECUTION = 0x0008, CONSTRUCTION = 0x0010, DESTRUCTION = 0x0020 };
  enum Protection { PROT_NONE, PROT_PRIVATE, PROT_PROTECTED, PROT_PUBLIC };
  enum Specifiers { SPEC_NONE = 0x0 , SPEC_STATIC = 0x1, SPEC_MUTABLE = 0x2, SPEC_VIRTUAL = 0x4 };
  struct Action {
    void **_args; void *_result; void *_target; void *_that; void *_fptr;
    void (*_wrapper)(Action &);
    inline void trigger () { _wrapper (*this); }
  };
  struct AnyResultBuffer {};
  template <typename T> struct ResultBuffer : public AnyResultBuffer {
    struct { char _array[sizeof (T)]; } _data;
    ~ResultBuffer () { ((T&)_data).T::~T(); }
    operator T& () const { return (T&)_data; }
  };
  template <typename T, typename N> struct TL {
    typedef T type; typedef N next; enum { ARGS = next::ARGS + 1 };
  };
  struct TLE { enum { ARGS = 0 }; };
  template <typename T> struct Referred { typedef T type; };
  template <typename T> struct Referred<T &> { typedef T type; };
  template <typename TL, int I> struct Arg {
    typedef typename Arg<typename TL::next, I - 1>::Type Type;
    typedef typename Referred<Type>::type ReferredType;
  };
  template <typename TL> struct Arg<TL, 0> {
    typedef typename TL::type Type;
    typedef typename Referred<Type>::type ReferredType;
  };
  template <typename T> int ttest(...);
  template <typename T> char ttest(typename T::__TI const volatile *);
  template<typename T> struct HasTypeInfo {
    enum { RET=((sizeof(ttest<T>(0))==1)?1:0) };
  };
  template<typename T, int HAVE = HasTypeInfo<T>::RET> struct TypeInfo {
    enum { AVAILABLE = 0 };
  };
  template<typename T> struct TypeInfo<T, 1> : T::__TI {
    enum { AVAILABLE = 1 };
	 };
  template<typename T> struct RT {};
  template<typename T> RT<T> rt_deduce (const T&) { return RT<T>(); }
  struct Cnv { template<typename T> operator RT<T>() const { return RT<T>(); }};
  #define __AC_TYPEOF(expr) (1?AC::Cnv():AC::rt_deduce(expr))
  template <class Aspect, int Index>
  struct CFlow {
    static int &instance () {
      static int counter = 0;
      return counter;
    }
    CFlow () { instance ()++; }
    ~CFlow () { instance ()--; }
    static bool active () { return instance () > 0; }
  };
}
inline void * operator new (unsigned long int, AC::AnyResultBuffer *p) { return p; }
inline void operator delete (void *, AC::AnyResultBuffer *) { } // for VC++
#endif // __cplusplus
#endif // __ac_h_

#line 1 "src/BlackScholes.cpp"

#line 1 "src/BlackScholes.cpp"

#line 81 "BlackScholes.acc"

#ifndef __ac_fwd_BlackScholesAspect__
#define __ac_fwd_BlackScholesAspect__
class BlackScholesAspect;
namespace AC {
  template <class JoinPoint>
  __attribute((always_inline)) inline void invoke_BlackScholesAspect_clContext_a0_around (JoinPoint *tjp);
  template <class JoinPoint>
  __attribute((always_inline)) inline void invoke_BlackScholesAspect_clContext_a1_before (JoinPoint *tjp);
}
#endif

#ifndef __ac_need__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_BlackScholesAspect_ah__
#define __ac_need__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_BlackScholesAspect_ah__
#endif

#line 1 "src/BlackScholes.cpp"
/* 
 * Class implementation for the vector addition example.
 */


#line 1 "src/BlackScholes.h"

#line 106 "BlackScholes.acc"

#ifndef __ac_fwd_BlackScholesAspect__
#define __ac_fwd_BlackScholesAspect__
class BlackScholesAspect;
namespace AC {
  template <class JoinPoint>
  __attribute((always_inline)) inline void invoke_BlackScholesAspect_clContext_a0_around (JoinPoint *tjp);
  template <class JoinPoint>
  __attribute((always_inline)) inline void invoke_BlackScholesAspect_clContext_a1_before (JoinPoint *tjp);
}
#endif

#ifndef __ac_need__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_BlackScholesAspect_ah__
#define __ac_need__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_BlackScholesAspect_ah__
#endif

#line 1 "src/BlackScholes.h"
/* 
 * Class that can run OpenCL kernels in C++ using the aspect clContext
 * which gets rid of the OpenCL setup overhead.
 *
 * This class will specifically do vector addition 
 * in the form:
 *				C = A + B;
 *
 */

#ifndef BLACK_SCHOLES_CPP_INCLUDED
#define BLACK_SCHOLES_CPP_INCLUDED

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#undef CL_VERSION_1_2
#endif

#include <vector>
#include <string>

using namespace std;


#line 150 "BlackScholes.acc"
class clContext;
class BlackScholesAspect;

#line 26 "src/BlackScholes.h"

#line 156 "BlackScholes.acc"

#ifndef __ac_guard__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_clContext_ah__
#define __ac_guard__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_clContext_ah__

#line 1 "aspects/clContext.ah"
/*
 * Abstract aspect that defines how a parallel aspect will be implemented.
 * This allows for more specific aspects to be derived from it that do not 
 * have to deal with the setup of the parallel context but rather just define
 * where to setup the parallel context.
 *
 * All member funciton implementations for the class clInstance are in
 * clInstance.cc
 *
 */

#ifndef __CL_CONTEXT__ASPECT__
#define __CL_CONTEXT__ASPECT__

#include <vector>
#include <time.h>
#include <iostream>

// Windows 
#if defined(__WIN64) || defined(__WIN32)
	#include <windows.h>
#endif

// Make sure we are using version 1.1
// otherwise NVIDIA GPU's wont work
#ifdef __APPLE__
	#include <OpenCL/opencl.hpp>
#else
	#include <CL/cl.hpp>
	#undef   CL_VERSION_1_2
#endif

#define This	tjp->that()		// Pointer to context on which advice acts
#define T		float			// Type of data the kernel will operate on

using namespace std;


#line 200 "BlackScholes.acc"
class BlackScholesAspect;

#line 38 "aspects/clContext.ah"
class clContext
{
#line 206 "BlackScholes.acc"
public:
  template <typename, int = 0> struct __CALL_clContext {};
  template <typename, int> friend struct __CALL_clContext;
private:
#line 39 "aspects/clContext.ah"

#line 213 "BlackScholes.acc"
  friend class ::BlackScholesAspect;

#line 39 "aspects/clContext.ah"

	public:
		// Class that holds any necessary OpenCL variables and 
		// calls any necessary OpenCL functions 
		class clInstance 
		{
#line 223 "BlackScholes.acc"
public:
  template <typename, int = 0> struct __CALL__ZN9clContext10clInstanceE {};
  template <typename, int> friend struct __CALL__ZN9clContext10clInstanceE;
private:
#line 44 "aspects/clContext.ah"

#line 230 "BlackScholes.acc"
  friend class ::clContext;
  friend class ::BlackScholesAspect;

#line 44 "aspects/clContext.ah"

			public: 
				timespec start;					// Time point for start
				timespec end;					// Time point for end
			public:
				// OpenCL context
				cl::Context context;

				// OpenCL available platforms
				vector<cl::Platform> platforms;

				// Devices available for the chosen platform 
				vector<cl::Device> devices;

				// OpenCl command queue 
				cl::CommandQueue queue;

				// OpenCL kernel that will be executed on the device
				cl::Kernel kernel;

				// OpenCL program 
				cl::Program program;

				// OpenCL buffers that are used to move data between the host
				// memory and the device memory when the kernel is executed
				vector<cl::Buffer> buffers;

				// All instances must have a run kernel function
				virtual void runKernel(vector< vector<T> >& inputs,
									   vector< vector<T> >& outputs) = 0;
				
				timespec GetRunTime();

			private:
				// Sets up the necessary OpenCL variables using the device type
				// and the kernel source file
				void setupOpenCL(const string& devType, const string& kSource);

				// Sets up the OpenCL kernel
				void setupKernel(const string& kSource, const string& kName);

				// Manages data buffers on kernel execution
				void manageClBuffers(vector< vector<T> > * inputs,
								   vector< vector<T> > * outputs);
		};

		// Virtual pointcuts which must be set to the cpp classes that will need
		// the pointcuts advice (which is defined below)
		
#line 92 "aspects/clContext.ah"


		// Pointcuts that run on contruction and setup OpenCL
		// Sets up both the OpenCL variables and the kernel
		
#line 96 "aspects/clContext.ah"
		

		// Pointcut to manage opencl variables (mostly mem) when the kernel is
		// executed
		
#line 101 "aspects/clContext.ah"
 

		// Insert the class clContext - all its variables and functions into the
		// classes defined bu programs
		
#line 105 "aspects/clContext.ah"


		// setupOpenCL(...) will be inserted into the classes defined by
		// programs() which are essentially calling their own setupOpenCL() fn's
		
#line 3 "aspects/clContext.ah"

public: 
#line 4 "aspects/clContext.ah"
 template<class JoinPoint> void __a0_around 
#line 109 "aspects/clContext.ah"
(JoinPoint *tjp) 
		{
#line 316 "BlackScholes.acc"

  typedef typename JoinPoint::That __JP_That;
  typedef typename JoinPoint::Target __JP_Target;
  typedef typename JoinPoint::Result __JP_Result;

#line 110 "aspects/clContext.ah"

			This->setupOpenCL(This->deviceType, This->kernelSource);
			This->setupKernel(This->kernelSource, This->kernelName);
			tjp->proceed();
		}

		// Advice that will make the running of a kernel simple 
		
#line 3 "aspects/clContext.ah"

public: 
#line 4 "aspects/clContext.ah"
 template<class JoinPoint> void __a1_before 
#line 117 "aspects/clContext.ah"
(JoinPoint *tjp) 
		{
#line 339 "BlackScholes.acc"

  typedef typename JoinPoint::That __JP_That;
  typedef typename JoinPoint::Target __JP_Target;
  typedef typename JoinPoint::Result __JP_Result;

#line 118 "aspects/clContext.ah"

			// Pass as arguments pointers to the runKernel() fn's arguments
			// i.e the inputs and outputs vectors which are modified, not
			// copied, so that the results are stored in the given outputs
			// vector
			This->manageClBuffers(tjp->template arg<0>(), tjp->template arg<1>());
		}
};

#endif	
			
#line 7 "src/BlackScholes.h"
#endif

#line 26 "src/BlackScholes.h"
class BlackScholes 
: public clContext::clInstance
#line 27 "src/BlackScholes.h"
{
#line 365 "BlackScholes.acc"
public:
  template <typename, int = 0> struct __CALL_BlackScholes {};
  template <typename, int> friend struct __CALL_BlackScholes;
private:
#line 27 "src/BlackScholes.h"

#line 372 "BlackScholes.acc"
  friend class ::clContext;
  friend class ::BlackScholesAspect;

#line 27 "src/BlackScholes.h"

	public:
		// Sets parameters that OpenCL will need to setup the environment
		
#line 381 "BlackScholes.acc"


template <typename TResult, typename TThat, typename TTarget, typename TArgs> struct TJP__ZN12BlackScholesC1EKN3stdE12basic_stringIcEKN3stdE12basic_stringIcEKN3stdE12basic_stringIcE_0 {
  typedef TJP__ZN12BlackScholesC1EKN3stdE12basic_stringIcEKN3stdE12basic_stringIcEKN3stdE12basic_stringIcE_0 __TJP;
  typedef TResult Result;
  typedef TThat   That;
  typedef TTarget Target;
  enum { ARGS = TArgs::ARGS };
  template <int I> struct Arg : AC::Arg<TArgs, I> {};
  static const int JPID = 0;
  static const AC::JPType JPTYPE = (AC::JPType)16;
  struct Res {
    typedef void Type;
    typedef void ReferredType;
  };

  void *_args[ARGS];
  Result *_result;
  That *_that;

  inline void *arg (int n) {return _args[n];}
  template <int I> typename Arg<I>::ReferredType *arg () {
    return (typename Arg<I>::ReferredType*)arg (I);
  }
  inline Result *result() {return (Result*)_result;}
  inline That *that() {return (That*)_that;}

  void proceed () {
    __TJP::that ()->__exec_old_C1(*(typename __TJP::template Arg<0>::ReferredType*)__TJP::arg(0), *(typename __TJP::template Arg<1>::ReferredType*)__TJP::arg(1), *(typename __TJP::template Arg<2>::ReferredType*)__TJP::arg(2));
  }
};


#line 30 "src/BlackScholes.h"
BlackScholes(const string dfloat,
					      const string kSource,
						  const string kName) 
			: deviceType(dfloat), kernelSource(kSource), kernelName(kName) 
#line 420 "BlackScholes.acc"
{
  typedef TJP__ZN12BlackScholesC1EKN3stdE12basic_stringIcEKN3stdE12basic_stringIcEKN3stdE12basic_stringIcE_0< void, ::BlackScholes , ::BlackScholes ,  AC::TL< ::std::string , AC::TL< ::std::string , AC::TL< ::std::string , AC::TLE > > > > __TJP;
    __TJP tjp;
  tjp._args[0] = (void*)&dfloat;
  tjp._args[1] = (void*)&kSource;
  tjp._args[2] = (void*)&kName;
  tjp._result = 0;
  tjp._that =  (__TJP::That*)this;
  AC::invoke_BlackScholesAspect_clContext_a0_around<__TJP> (&tjp);
  
}
__attribute__((always_inline)) inline void __exec_old_C1(const ::std::string ,const ::std::string ,const ::std::string )
#line 33 "src/BlackScholes.h"
{}

		// Function to run the kernel, which must be in this form as defined by
		// the clContext aspect (specifically in the clInstance class)
		
#line 439 "BlackScholes.acc"
public: __attribute__((always_inline)) inline void __exec_old_runKernel(::std::vector<std::vector<float> > &inputs,::std::vector<std::vector<float> > &outputs);

#line 37 "src/BlackScholes.h"
void runKernel(vector< vector<float> > &inputs,
					   vector< vector<float> > &outputs);

		// Function to print the results 
		void PrintResults();

		// Get the type of device
		string getDeviceType() const { return deviceType; }

		// Get the kernel name 
		string getKernelName() const { return kernelName; }

	private:
		// Device type (CPU or GPU)
		const string deviceType;

		// The name of the kernel source file
		const string kernelSource;

		// The name of the kernel
		const string kernelName;

		// Data to process
		vector< vector<float> > in;			// Input data
		vector< vector<float> > out;			// Output data

#line 469 "BlackScholes.acc"

template <typename TResult, typename TThat, typename TTarget, typename TArgs> struct TJP__ZN12BlackScholesC1ERK12BlackScholes_0 {
  typedef TJP__ZN12BlackScholesC1ERK12BlackScholes_0 __TJP;
  typedef TResult Result;
  typedef TThat   That;
  typedef TTarget Target;
  enum { ARGS = TArgs::ARGS };
  template <int I> struct Arg : AC::Arg<TArgs, I> {};
  static const int JPID = 36;
  static const AC::JPType JPTYPE = (AC::JPType)16;
  struct Res {
    typedef void Type;
    typedef void ReferredType;
  };

  void *_args[ARGS];
  Result *_result;
  That *_that;

  inline void *arg (int n) {return _args[n];}
  template <int I> typename Arg<I>::ReferredType *arg () {
    return (typename Arg<I>::ReferredType*)arg (I);
  }
  inline Result *result() {return (Result*)_result;}
  inline That *that() {return (That*)_that;}

  void proceed () {
  }
};


#line 62 "src/BlackScholes.h"

#line 503 "BlackScholes.acc"

public:
inline BlackScholes (const BlackScholes &arg0) : clContext::clInstance (arg0), deviceType (arg0.deviceType), kernelSource (arg0.kernelSource), kernelName (arg0.kernelName), in (arg0.in), out (arg0.out) {
  typedef TJP__ZN12BlackScholesC1ERK12BlackScholes_0< void, ::BlackScholes , ::BlackScholes ,  AC::TL< const ::BlackScholes &, AC::TLE > > __TJP;
  __TJP tjp;
  tjp._args[0] = (void*)&arg0;
  tjp._result = 0;
  tjp._that =  (__TJP::That*)this;
  AC::invoke_BlackScholesAspect_clContext_a0_around<__TJP> (&tjp);

}

#line 62 "src/BlackScholes.h"
};

#endif

#line 6 "src/BlackScholes.cpp"
#include <iostream>
#include <cstring>


#line 526 "BlackScholes.acc"


template <typename TResult, typename TThat, typename TTarget, typename TArgs> struct TJP__ZN12BlackScholes9runKernelERN3stdE6vectorIN3stdE6vectorIfEERN3stdE6vectorIN3stdE6vectorIfEE_0 {
  typedef TJP__ZN12BlackScholes9runKernelERN3stdE6vectorIN3stdE6vectorIfEERN3stdE6vectorIN3stdE6vectorIfEE_0 __TJP;
  typedef TResult Result;
  typedef TThat   That;
  typedef TTarget Target;
  enum { ARGS = TArgs::ARGS };
  template <int I> struct Arg : AC::Arg<TArgs, I> {};
  static const int JPID = 25;
  static const AC::JPType JPTYPE = (AC::JPType)8;
  struct Res {
    typedef TResult Type;
    typedef TResult ReferredType;
  };

  void *_args[ARGS];
  That *_that;

  inline void *arg (int n) {return _args[n];}
  template <int I> typename Arg<I>::ReferredType *arg () {
    return (typename Arg<I>::ReferredType*)arg (I);
  }
  inline That *that() {return (That*)_that;}

};


#line 9 "src/BlackScholes.cpp"
void BlackScholes::runKernel(std::vector< std::vector<float> > &inputs,	
								  std::vector< std::vector<float> > &outputs) 

#line 559 "BlackScholes.acc"
{
  typedef TJP__ZN12BlackScholes9runKernelERN3stdE6vectorIN3stdE6vectorIfEERN3stdE6vectorIN3stdE6vectorIfEE_0< void, ::BlackScholes , ::BlackScholes ,  AC::TL< ::std::vector<std::vector<float> > &, AC::TL< ::std::vector<std::vector<float> > &, AC::TLE > > > __TJP;
    __TJP tjp;
  tjp._args[0] = (void*)&inputs;
  tjp._args[1] = (void*)&outputs;
  tjp._that =  (__TJP::That*)this;
  AC::invoke_BlackScholesAspect_clContext_a1_before<__TJP> (&tjp);
    this->__exec_old_runKernel(inputs, outputs);
  
}
__attribute__((always_inline)) inline void BlackScholes::__exec_old_runKernel(::std::vector<std::vector<float> > &inputs,::std::vector<std::vector<float> > &outputs)
#line 11 "src/BlackScholes.cpp"
{
	// Copy the given data to the class data elements. 
	//in = inputs;

	// Copy the results to the class 
	//out = outputs;
}


void BlackScholes::PrintResults() {

	std::cout << std::endl 
			  << "Displaying the results : " 
			  << std::endl  << std::endl;

	/* Then the outputs */
	for (int i = 0; i < out.size(); i++) {
		for (int j = 0; j < out[i].size(); j++) {
			std::cout << out[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

#line 596 "BlackScholes.acc"

#ifdef __ac_FIRST_FILE__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_src_BlackScholes_cpp__
#ifdef __ac_need__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_clContext_ah__
#ifndef __ac_have__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_clContext_ah__
#define __ac_have__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_clContext_ah__
#include "aspects/clContext.ah"
#endif
#endif
#ifdef __ac_need__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_BlackScholesAspect_ah__
#ifndef __ac_have__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_BlackScholesAspect_ah__
#define __ac_have__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_aspects_BlackScholesAspect_ah__

#line 1 "aspects/BlackScholesAspect.ah"
/*
 * Aspect that is used to setup the OpenCl
 * components of a parallel class. This essentially 
 * abstracts the OpenCL setup away from the class and 
 * allows it to behave like normal x86 code.
 * */

#ifndef BLACK_SCHOLES_ASPECT__
#define BLACK_SCHOLES_ASPECT__


#line 1 "aspects/BlackScholesAspect.ah"

#line 623 "BlackScholes.acc"
class clContext;

#line 13 "aspects/BlackScholesAspect.ah"
class BlackScholesAspect : public clContext
{
#line 629 "BlackScholes.acc"
public:
  template <typename, int = 0> struct __CALL_BlackScholesAspect {};
  template <typename, int> friend struct __CALL_BlackScholesAspect;
private:
#line 14 "aspects/BlackScholesAspect.ah"

#line 636 "BlackScholes.acc"

public:
  static BlackScholesAspect *aspectof () {
    static BlackScholesAspect __instance;
    return &__instance;
  }
  static BlackScholesAspect *aspectOf () {
    return aspectof ();
  }
private:

#line 14 "aspects/BlackScholesAspect.ah"

#line 650 "BlackScholes.acc"
  friend class ::clContext;

#line 14 "aspects/BlackScholesAspect.ah"

	public:
			
		// OpenCL program name on which to apply aspect
		
#line 18 "aspects/BlackScholesAspect.ah"
	
};
#line 662 "BlackScholes.acc"

namespace AC {
  template <class JoinPoint>
  __attribute((always_inline)) inline void invoke_BlackScholesAspect_clContext_a0_around (JoinPoint *tjp) {
    ((::clContext*)::BlackScholesAspect::aspectof())->__a0_around (tjp);
  }
  template <class JoinPoint>
  __attribute((always_inline)) inline void invoke_BlackScholesAspect_clContext_a1_before (JoinPoint *tjp) {
    ((::clContext*)::BlackScholesAspect::aspectof())->__a1_before (tjp);
  }
} 

#line 19 "aspects/BlackScholesAspect.ah"


#endif

#line 13 "src/BlackScholes.cpp"
#endif
#endif
#undef __ac_FIRST__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects__
#undef __ac_FIRST_FILE__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_src_BlackScholes_cpp__
#endif // __ac_FIRST_FILE__home_joker_Programs_OpenCl_EasyCL_Examples_BlackScholes_BlackScholesParallelWitsAspects_src_BlackScholes_cpp__
