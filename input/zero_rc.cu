#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main(int argc, char** argv)
{
   
    int q[20],i;
__global__ void _AFFINE_KERNEL_0(int* ,int ,int ,int ,int );


	#ifdef DATASET
		char* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));
		strcpy(outfile, readfile);
		strcat(outfile, ".data");
		FILE* fp;
		fp = fopen(outfile, "a");
	#endif

	#ifdef TIME
		struct timespec start_0, end_0, mid_start_0, mid_end_0;
		double runTime_0, pre_time_0, post_time_0, computeTime_0;
	#endif
	int _SZ_q_0 = 20;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_0);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_q_0;
	cudaMalloc((void**) &_DEV_q_0,sizeof(int) *_SZ_q_0);
	cudaMemcpy(_DEV_q_0,q,sizeof(int)*_SZ_q_0, cudaMemcpyHostToDevice);
	int _NUM_THREADS_0= 20;
	float _NUM_BLOCKS_0=1;
	int _NUM_TILE_0=1;
	dim3 _THREADS_0(512);
	dim3 _BLOCKS_0(1);
	if(_NUM_THREADS_0 < _NTHREAD)
	{
		_THREADS_0.x=_NUM_THREADS_0;
	}
	else {
		 _THREADS_0.x=_NTHREAD;
		_NUM_BLOCKS_0=(_NUM_THREADS_0 % _NTHREAD == 0)?(_NUM_THREADS_0/_NTHREAD):((_NUM_THREADS_0/_NTHREAD)+1);
		if(_NUM_BLOCKS_0<_NBLOCK)
			_BLOCKS_0.x=_NUM_BLOCKS_0;
		else {
			_BLOCKS_0.x=_NBLOCK;
			int temp_0=_NUM_BLOCKS_0;
			_NUM_TILE_0=(temp_0 % _NBLOCK == 0)?(_NUM_BLOCKS_0/_NBLOCK):((_NUM_BLOCKS_0/_NBLOCK)+1);
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_start_0);
	#endif

	int _CUDA_TILE_0;
	for(_CUDA_TILE_0=0;_CUDA_TILE_0<_NUM_TILE_0;_CUDA_TILE_0++)
	{
		_AFFINE_KERNEL_0<<<_BLOCKS_0,_THREADS_0>>>( _DEV_q_0, _SZ_q_0,0,18, _CUDA_TILE_0);
		cudaDeviceSynchronize();
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_0);
	#endif
	cudaMemcpy(q, _DEV_q_0,sizeof(int) *_SZ_q_0, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_q_0);

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &end_0);

		pre_time_0 = (double) ((((&mid_start_0)->tv_sec * 1000000000) + (&mid_start_0)->tv_nsec) - (((&start_0)->tv_sec * 1000000000) + (&start_0)->tv_nsec)) / 1000000000;
		post_time_0 = (double) ((((&end_0)->tv_sec * 1000000000) + (&end_0)->tv_nsec) - (((&mid_end_0)->tv_sec * 1000000000) + (&mid_end_0)->tv_nsec)) / 1000000000;
		computeTime_0 = (double) ((((&mid_end_0)->tv_sec * 1000000000) + (&mid_end_0)->tv_nsec) - (((&mid_start_0)->tv_sec * 1000000000) + (&mid_start_0)->tv_nsec)) / 1000000000;
		runTime_0 = (double) ((((&end_0)->tv_sec * 1000000000) + (&end_0)->tv_nsec) - (((&start_0)->tv_sec * 1000000000) + (&start_0)->tv_nsec)) / 1000000000;
	#endif

	#ifdef DATASET
		fprintf(fp,"%%d,%%d,%%d,%%d,%%d,%%.14f,%%.14f,%%.14f,%%.14f,%%d\n",N,_NTHREAD*_NBLOCK,_THREADS_0.x,_BLOCKS_0.x,data,pre_time_0,computeTime_0,post_time_0,runTime_0,_CUDA_TILE_0);
		fclose(fp);
		fclose(f);
	#else
	#ifdef TIME
		printf("Runtime:%%f\n",runTime_0);
	#endif
	#endif
   
__global__ void _AFFINE_KERNEL_1(int* ,int ,int ,int ,int ,int ,int );


	#ifdef DATASET
		char* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));
		strcpy(outfile, readfile);
		strcat(outfile, ".data");
		FILE* fp;
		fp = fopen(outfile, "a");
	#endif

	#ifdef TIME
		struct timespec start_1, end_1, mid_start_1, mid_end_1;
		double runTime_1, pre_time_1, post_time_1, computeTime_1;
	#endif
	int _SZ_q_1 = 20;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_1);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int*_DEV_q_1;
	cudaMalloc((void**) &_DEV_q_1,sizeof(int) *_SZ_q_1);
	cudaMemcpy(_DEV_q_1,q,sizeof(int) *_SZ_q_1, cudaMemcpyHostToDevice);
	int _NUM_THREADS_1= 20;
	float _NUM_BLOCKS_1=1;
	int _NUM_TILE_1=1;
	dim3 _THREADS_1(512);
	dim3 _BLOCKS_1(1);
	if(_NUM_THREADS_1 < _NTHREAD)
	{
		_THREADS_1.x=_NUM_THREADS_1;
	}
	else {
		 _THREADS_1.x=_NTHREAD;
		_NUM_BLOCKS_1=(_NUM_THREADS_1 % _NTHREAD == 0)?(_NUM_THREADS_1/_NTHREAD):((_NUM_THREADS_1/_NTHREAD)+1);
		if(_NUM_BLOCKS_1<_NBLOCK)
			_BLOCKS_1.x=_NUM_BLOCKS_1;
		else {
			_BLOCKS_1.x=_NBLOCK;
			int temp_1=_NUM_BLOCKS_1;
			_NUM_TILE_1=(temp_1 % _NBLOCK == 0)?(_NUM_BLOCKS_1/_NBLOCK):((_NUM_BLOCKS_1/_NBLOCK)+1);
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_start_1);
	#endif

	int _CUDA_TILE_1;
	for(i=0;i<18;i+=2)
	for(_CUDA_TILE_1=0;_CUDA_TILE_1<_NUM_TILE_1;_CUDA_TILE_1++)
	{		_AFFINE_KERNEL_1<<<_BLOCKS_1,_THREADS_1>>>( _DEV_q_1, _SZ_q_1,1,i,0,18,_CUDA_TILE_1);
		cudaDeviceSynchronize();
	}
	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_1);
	#endif
	cudaMemcpy(q, _DEV_q_1,sizeof(int) *_SZ_q_1, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_q_1);

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &end_1);
		pre_time_1 = (double) ((((&mid_start_1)->tv_sec * 1000000000) + (&mid_start_1)->tv_nsec) - (((&start_1)->tv_sec * 1000000000) + (&start_1)->tv_nsec)) / 1000000000;
		post_time_1 = (double) ((((&end_1)->tv_sec * 1000000000) + (&end_1)->tv_nsec) - (((&mid_end_1)->tv_sec * 1000000000) + (&mid_end_1)->tv_nsec)) / 1000000000;
		computeTime_1 = (double) ((((&mid_end_1)->tv_sec * 1000000000) + (&mid_end_1)->tv_nsec) - (((&mid_start_1)->tv_sec * 1000000000) + (&mid_start_1)->tv_nsec)) / 1000000000;
		runTime_1 = (double) ((((&end_1)->tv_sec * 1000000000) + (&end_1)->tv_nsec) - (((&start_1)->tv_sec * 1000000000) + (&start_1)->tv_nsec)) / 1000000000;
	#endif

	#ifdef DATASET
		fprintf(fp,"%%d,%%d,%%d,%%d,%%d,%%.14f,%%.14f,%%.14f,%%.14f,%%d\n",N,_NTHREAD*_NBLOCK,_THREADS_1.x,_BLOCKS_1.x,data,pre_time_1,computeTime_1,post_time_1,runTime_1,_CUDA_TILE_1);
		fclose(fp);
		fclose(f);
	#else
	#ifdef TIME
		printf("Runtime:%%f\n",runTime_1);
	#endif
	#endif
    
	
    return 0;
}




__global__ void _AFFINE_KERNEL_0(int* q,int  _SZ_q_0,int CUDA_L_i,int CUDA_U_i,int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
q[1+i] =(2 *(i + 1));
}}



__global__ void _AFFINE_KERNEL_1(int* q,int  _SZ_q_1,int phi_count, int CUDA_i,int CUDA_L_i,int CUDA_U_i,int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_i<=i)&&(i<(CUDA_i+2))&&(i<CUDA_U_i)){
q[19-i] = q[19-i-2];
}}

