#ifndef HEADER_H
#define HEADER_H

/* Includes */
#include <math.h>
#include <string>
#include <assert.h>
#include <stdio.h>

#ifdef _MSC_VER // Compiling under Visual Studio
	#include <cstdlib>
	#include <ctime>
#else
	#include <stdlib.h>
#endif

/* Macros */ 
// #define LOG // do not remove (used for logging to console)
#define THREADS_PER_BLOCK 1024
#ifdef __CUDACC__
	#define CUDA_CALLABLE_MEMBER __host__ __device__
#else
	#define CUDA_CALLABLE_MEMBER
#endif

typedef int Index;

typedef Index CIdx;
typedef Index PIdx;

// Comparison function for sorting floats
int cmp(const void *v1, const void *v2);

int temp();

#endif
