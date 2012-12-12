/*

GPU Implementation of K-Means Algorithm

*/

#ifdef _MSC_VER // Compiling under Visual Studio
#include <Windows.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#endif

// this code is for GPU kernel
#include <time.h>
#include "KMeansGPU.h"

using namespace KMG;

// GPU FUNCTION
__global__ void gpu(
	float *icdMat,
	int *ridMat,
	float *centers,
	float *points,
	int *label,
	int k,
	int dim)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	int oldCnt = label[idx];
	float oldDist = 0;
	int i, j, curCnt, newCnt = oldCnt;
	float curDist, newDist;
	for(i = 0; i < dim; i++)
	{
		oldDist += (points[(idx * dim)+i] - centers[(oldCnt * dim)+i]) * (points[(idx * dim)+i] - centers[(oldCnt * dim)+i]);
	}
	oldDist = sqrt(oldDist);
	newDist = oldDist;

	for(j=0; j < k; j++){
		curCnt = ridMat[oldCnt*k+j];
		if(icdMat[oldCnt * k + curCnt] <= (2 * oldDist)){
			curDist = 0;
			for(i = 0; i < dim; i++)
			{
				curDist += (points[(idx * dim) + i] - centers[(curCnt * dim)+i]) * (points[(idx * dim)+i] - centers[(curCnt * dim)+i]);
			}
			curDist = sqrt(curDist);
			if(curDist < newDist){
				newDist = curDist;
				newCnt = curCnt;
			}
		} else {
			j=k;
		}
	}
	label[idx]=newCnt;
}

// FUNCTION CALLED BY MAIN
int gpu_kernel(KMeansGPU& kmeansGpu){
	const int dim = kmeansGpu.data.getDim();
	Centers& curr = kmeansGpu.curr;
	// k= number of clusters
	const int k = curr.nCenters;
	// int *d_k;
	// INTER CENTROID DISTANCES
	float* icdMat = curr.distMat; // this pointer is for CPU
	float *h_icdMat;
	float* d_icdMat; // this pointer is for GPU

	// RANKED INDEX MATRIX
	const int* ridMat = curr.ridMat;
	const int* h_ridMat;
	int* d_ridMat; // this pointer is for GPU
	
	Point * centers = curr.centers; // this centers is for CPU
	float *d_centers; // this centers is for GPU
	Point * points = kmeansGpu.data.getPoints();
	float *d_points; // this is for GPU
	const int N = kmeansGpu.data.getNPoints(); 

	float * h_centers = new float[kmeansGpu.nCenters * dim];
	float *h_points;	
	float total_entropy ;
	int* label = kmeansGpu.clusterIdx; // curr status of label in CPU this need to be updated after an iteration in GPU
	int *d_label;
	float calculate_entropy(float *, int *, float *, int , int );
	// getchar();
#ifdef _MSC_VER // Compiling under Visual Studio
	unsigned long startTime_, diffInMilliSec;
	startTime_ = GetTickCount();
#else
	struct timespec t_start, t_end;
	double elapsedTime;
	clock_gettime(CLOCK_REALTIME, &t_start);
#endif
	h_points = (float *)malloc(N*dim*sizeof(float));
	/* Allocate Memory on device */
	if ( cudaSuccess != cudaMalloc((void **)&d_icdMat, k*k*sizeof(float))) {printf( "Error!\n" ); exit(EXIT_FAILURE);}
	if ( cudaSuccess != cudaMalloc((void **)&d_ridMat, k*k*sizeof(int))) {printf( "Error!\n" ); exit(EXIT_FAILURE);}
	if ( cudaSuccess != cudaMalloc((void **)&d_centers, k*dim*sizeof(float))) {printf( "Error!\n" ); exit(EXIT_FAILURE);}
	if ( cudaSuccess != cudaMalloc((void **)&d_points, N*dim*sizeof(float))) {printf( "Error!\n" ); exit(EXIT_FAILURE);}
	if ( cudaSuccess != cudaMalloc((void **)&d_label, N*sizeof(int))) {printf( "Error!\n" ); exit(EXIT_FAILURE);}

#ifdef _MSC_VER // Compiling under Visual Studio
	diffInMilliSec = GetTickCount() - startTime_;
	printf("Time taken for memory allocation on CUDA device : %10lu millisec\n", diffInMilliSec);
#else
	clock_gettime(CLOCK_REALTIME, &t_end);
	elapsedTime = (t_end.tv_sec - t_start.tv_sec)*1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec)/1000000.0;
	printf("time elapsed New Method (Memory Allocation) %1f msec\n", elapsedTime);
#endif

	int i,j;
	int nStages = kmeansGpu.nStages, iteration;
	curr.updateDistMat();
	curr.updateRidMat();

	printf("Number of Centers: %d Dimension: %d\n",k,dim);
#ifdef LOG
	for(i=0;i<N;i++){
		printf("--- label[%d] %d   ---\n",i,label[i]);
	}	
#endif
	for(i=0;i<k;i++){
		for(j=0;j<dim;j++){
			h_centers[i * dim + j] = centers[i].x[j];
			// printf("--- h_centers[%d][%d]= %f   ---\n",i,j,h_centers[i][j]);
		}
	}
	for(i=0;i<N;i++){
		for(j=0;j<dim;j++){
			h_points[i*dim+j] = points[i].x[j];
			// printf("--- h_points[%d][%d]= %f    ---\n",i,j,h_points[i][j]);
		}
	}
	h_ridMat = ridMat;
	h_icdMat = icdMat;
	
	// printf("size of int=%d  size of float %d\n", sizeof(int), sizeof(float));
#ifdef _MSC_VER // Compiling under Visual Studio
	startTime_ = GetTickCount();
#else
	clock_gettime(CLOCK_REALTIME, &t_start);
#endif
	cudaMemcpy(d_points, (float *)h_points , N * dim * sizeof(float) , cudaMemcpyHostToDevice);

#ifdef _MSC_VER // Not compiling under Visual Studio	
	diffInMilliSec = GetTickCount() - startTime_;
	printf("Time taken for memory copy on CUDA device : %10lu millisec\n", diffInMilliSec);

	startTime_ = GetTickCount();
#else
	clock_gettime(CLOCK_REALTIME, &t_end);
	elapsedTime = (t_end.tv_sec - t_start.tv_sec)*1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec)/1000000.0;
	printf("time elapsed New Method (MemCpy outside for loop) %1f msec\n", elapsedTime);
	clock_gettime(CLOCK_REALTIME, &t_start);
#endif	

	/* This assertion ensures that the data set is in order. */
	assert (N % THREADS_PER_BLOCK == 0);
	
	for(iteration = 0 ; iteration < nStages ; iteration++) { 
		printf( "Stage %2d starting..", iteration + 1);

		/* Memory copy from HOST to GPU */
		cudaMemcpy(d_icdMat, (float *)h_icdMat, k*k*sizeof(float) , cudaMemcpyHostToDevice);
		cudaMemcpy(d_ridMat, (int *)h_ridMat, k*k*sizeof(int) , cudaMemcpyHostToDevice);
		cudaMemcpy(d_label, label , N*sizeof(int) , cudaMemcpyHostToDevice);
		cudaMemcpy(d_centers, (float *)h_centers ,k*dim*sizeof(float) , cudaMemcpyHostToDevice);

		/* Main Computation call on GPU */
		gpu<<<N/THREADS_PER_BLOCK,THREADS_PER_BLOCK>>> (d_icdMat, d_ridMat, d_centers, d_points, d_label, k, dim);

		/* Memory copy from GPU to HOST */
		cudaMemcpy(label, d_label, N*sizeof(int), cudaMemcpyDeviceToHost);

		/* Update centers from the new assignments */
		// for(int q = 0; q < N; q++, printf("%3d ", label[q]));printf("\n");

		curr.resetPerIteration();
		curr.processLabel(label, kmeansGpu.data);

		curr.updateCenters(true, h_centers);	
		curr.updateDistMat();
		curr.updateRidMat();

		// curr.print();
		printf( " done.\n");
	}
#ifdef _MSC_VER // Compiling under Visual Studio
	diffInMilliSec = GetTickCount() - startTime_;
	printf("Time taken for total computation on CUDA device : %10lu millisec\n", diffInMilliSec);
#else
	clock_gettime(CLOCK_REALTIME, &t_end);
	elapsedTime = (t_end.tv_sec - t_start.tv_sec)*1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec)/1000000.0;
	printf("time elapsed New Method (iteration: after the loop) %1f msec\n", elapsedTime);
#endif

#ifdef LOG
	printf("Printing label[i]s\n");
	for(i=0;i<N;i++){
		printf(" %6d",label[i]);
	}
#endif
	
	cudaFree(d_points); cudaFree(d_centers);
	cudaFree(d_icdMat); cudaFree(d_ridMat); cudaFree(d_label);
	
	total_entropy = calculate_entropy(h_centers, label, h_points, N, dim);
	printf("\n total entropy of the system = %f\n", total_entropy);
	if(!h_centers) delete [] h_centers;
	return 0;
}

float calculate_entropy(float *h_centers, int *label, float *h_points, int N, int dim){
	int i,j,center_idx;
	float total=0;
	for(i=0;i<N;i++){
		center_idx = label[i];
		for(j=0;j<dim;j++){
	total += ((h_centers[center_idx*dim+j]-h_points[i*dim+j])*(h_centers[center_idx*dim+j]-h_points[i*dim+j]));
		}
	}
	return sqrt(total)/N;
}
