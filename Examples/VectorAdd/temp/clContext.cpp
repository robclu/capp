
#line 1 "aspects/clContext.cc"
#ifndef __ac_FIRST__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd__
#define __ac_FIRST__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd__
#define __ac_FIRST_FILE__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd_aspects_clContext_cc__
#endif // __ac_FIRST__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd__

#line 1 "aspects/clContext.cc"

#line 11 "clContext.acc"

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

#line 1 "aspects/clContext.cc"

#line 1 "aspects/clContext.cc"
/*
 * Member definitions for the clInstance class which is part of the clContext
 * aspect. The clInstance class will be put into any class that uses the
 * clContext aspect.
 *
 */


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


#line 121 "clContext.acc"
class VectorAdd;

#line 32 "aspects/clContext.ah"
class clContext
{
#line 127 "clContext.acc"
public:
  template <typename, int = 0> struct __CALL_clContext {};
  template <typename, int> friend struct __CALL_clContext;
private:
#line 33 "aspects/clContext.ah"

#line 134 "clContext.acc"
  friend class ::VectorAdd;

#line 33 "aspects/clContext.ah"

	public:
		// Class that holds any necessary OpenCL variables and 
		// calls any necessary OpenCL functions 
		class clInstance 
		{
#line 144 "clContext.acc"
public:
  template <typename, int = 0> struct __CALL__ZN9clContext10clInstanceE {};
  template <typename, int> friend struct __CALL__ZN9clContext10clInstanceE;
private:
#line 38 "aspects/clContext.ah"

#line 151 "clContext.acc"
  friend class ::clContext;
  friend class ::VectorAdd;

#line 38 "aspects/clContext.ah"

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
		
#line 81 "aspects/clContext.ah"


		// Pointcuts that run on contruction and setup OpenCL
		// Sets up both the OpenCL variables and the kernel
		
#line 85 "aspects/clContext.ah"
		

		// Pointcut to manage opencl variables (mostly mem) when the kernel is
		// executed
		
#line 90 "aspects/clContext.ah"


		// Insert the class clContext - all its variables and functions into the
		// classes defined bu programs
		
#line 94 "aspects/clContext.ah"


		// setupOpenCL(...) will be inserted into the classes defined by
		// programs() which are essentially calling their own setupOpenCL() fn's
		
#line 3 "aspects/clContext.ah"

public: 
#line 4 "aspects/clContext.ah"
 template<class JoinPoint> void __a0_around 
#line 98 "aspects/clContext.ah"
(JoinPoint *tjp) 
		{
#line 232 "clContext.acc"

  typedef typename JoinPoint::That __JP_That;
  typedef typename JoinPoint::Target __JP_Target;
  typedef typename JoinPoint::Result __JP_Result;

#line 99 "aspects/clContext.ah"

			This->setupOpenCL(This->deviceType, This->kernelSource);
			This->setupKernel(This->kernelSource, This->kernelName);
			tjp->proceed();
		}

		// Advice that will make the running of a kernel simple 
		
#line 3 "aspects/clContext.ah"

public: 
#line 4 "aspects/clContext.ah"
 template<class JoinPoint> void __a1_before 
#line 106 "aspects/clContext.ah"
(JoinPoint *tjp) 
		{
#line 255 "clContext.acc"

  typedef typename JoinPoint::That __JP_That;
  typedef typename JoinPoint::Target __JP_Target;
  typedef typename JoinPoint::Result __JP_Result;

#line 107 "aspects/clContext.ah"

			// Pass as arguments pointers to the runKernel() fn's arguments
			// i.e the inputs and outputs vectors which are modified, not
			// copied, so that the results are stored in the given outputs
			// vector
			This->manageClBuffers(tjp->template arg<0>(), tjp->template arg<1>());
		}
};

#endif	
			
#line 10 "aspects/clContext.cc"
#include <string>
#include <utility>
#include <iterator>
#include <fstream>

void clContext::clInstance::setupOpenCL(const string& deviceType, const string& kernelSource) 
{
	// Get the available OpenCL platforms 
	cl::Platform::get(&platforms);

	// Setup the context depending on the deviceType
	// NOTE: device type needs to be passed a string in the derived class
	//		 constructor. The lack of checking this is due to the inability to
	//		 get the constructor arguments for derived class in AspectC++.
	if (deviceType == "GPU") {
		cl_context_properties cps[3] = {
			CL_CONTEXT_PLATFORM,	
			(cl_context_properties)(platforms[0])(),
			0
		};
		context = cl::Context(CL_DEVICE_TYPE_GPU, cps);
	}
	else if (deviceType == "CPU") {
		cl_context_properties cps[3] = {
			CL_CONTEXT_PLATFORM, 
			(cl_context_properties)(platforms[0])(),
			0
		};
		context = cl::Context(CL_DEVICE_TYPE_CPU, cps);
	}
	else {
		// Use the default platform
		cl_context_properties cps[3] = {
			CL_CONTEXT_PLATFORM,
			(cl_context_properties)(platforms[0])(),
			0
		};
		context = cl::Context(CL_DEVICE_TYPE_DEFAULT, cps);
	}

	// Get the devices for the created context (and platform)
	devices = context.getInfo<CL_CONTEXT_DEVICES>();

	// If there is an available device create a command queue
	// Could add options displaying available devices and letting the user
	// choose the device to use 
	if (devices.size() > 0) {
		queue = cl::CommandQueue(context, devices[0]);
	}
}

void clContext::clInstance::setupKernel(const string& kernelSource, const string& kernelName)
{
	ifstream kSource(("kernels/" + kernelSource).c_str());

	// Convert the source to a string 
	string sourceString(istreambuf_iterator<char>(kSource), (istreambuf_iterator<char>()));

	// Create and OpenCL Source from the kernel source string 
	cl::Program::Sources clSource(1, make_pair(sourceString.c_str(), sourceString.length() + 1));

	// Create and OpenCL program from the source and the context
	program = cl::Program(context, clSource);
	program.build(devices);

	// Make the OpenCL kernel
	kernel = cl::Kernel(program, kernelName.c_str());
}

void clContext::clInstance::manageClBuffers(vector< vector<T> > * inputs, vector< vector<T> > * outputs)
{
	// Create buffers from each of the input vectors 
	for (size_t i = 0; i < inputs->size(); i++) {
		buffers.push_back(cl::Buffer(context, CL_MEM_READ_ONLY, (*inputs)[i].size() * sizeof(T)));
		// Create a buffer (copy from host to device mem) with a pointer to the first element in inputs[i]
		queue.enqueueWriteBuffer(buffers.back(), CL_TRUE, 0, (*inputs)[i].size() * sizeof(T), &((*inputs)[i][0]));
	}

	// Create the output buffer(s), these should all be initialised to 0 in host
	// code for safety
	for (size_t i = 0; i < outputs->size(); i++) {
		buffers.push_back(cl::Buffer(context, CL_MEM_WRITE_ONLY, (*outputs)[i].size() * sizeof(T)));
	}

	// Set the arguments for the kernel as the buffers 
	for (size_t i = 0; i < buffers.size(); i++) {
		kernel.setArg(i, buffers[i]);
	}

	// This should be set by the derived aspect or the implemented class
	cl::NDRange global((*inputs)[0].size());		// Number of elements to process
	cl::NDRange local(1);							

	// Place the kernel on the command queue
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);

	// Get the results back to the output vector
	for (size_t i = 0; i < outputs->size(); i++) {
		// Create a buffer for the results from the kernel
		T * results = new T[(*outputs)[i].size()];

		// Move the result from the device to the host
		queue.enqueueReadBuffer(buffers[inputs->size() + i], CL_TRUE, 0, (*outputs)[i].size() * sizeof(T), results);

		// Move the result from the temp buffer into the output vector
		(*outputs)[i] = vector<T>(results, results + (*outputs)[i].size());
		free(results);
	}
}

	


#line 387 "clContext.acc"

#ifdef __ac_FIRST_FILE__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd_aspects_clContext_cc__
#ifdef __ac_need__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd_aspects_clContext_ah__
#ifndef __ac_have__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd_aspects_clContext_ah__
#define __ac_have__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd_aspects_clContext_ah__
#include "aspects/clContext.ah"
#endif
#endif
#ifdef __ac_need__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd_aspects_VectorAdd_ah__
#ifndef __ac_have__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd_aspects_VectorAdd_ah__
#define __ac_have__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd_aspects_VectorAdd_ah__
#include "aspects/VectorAdd.ah"
#endif
#endif
#undef __ac_FIRST__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd__
#undef __ac_FIRST_FILE__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd_aspects_clContext_cc__
#endif // __ac_FIRST_FILE__home_joker_Programs_OpenCL_EasyCL_Examples_VectorAdd_aspects_clContext_cc__
