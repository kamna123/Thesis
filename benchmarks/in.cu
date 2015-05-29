#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*cb gf*/
//int gcdf()
int main()
{
     int x[20],y[20],z[10],f[20];
   int i,a[50],k=5,j,b[300],pi=3.14,w[200];
 
 
   //fasdf
k=5;

__global__ void _AFFINE_KERNEL_0(int* ,int ,int* ,int ,int ,int ,int );

#define MIN(a,b) (((a)<(b))?(a):(b))
#include<cuda.h>

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
	int _SZ_a_0 = 50;
	int _SZ_b_0 = 300;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_0);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_a_0;
	cudaMalloc((void**) &_DEV_a_0,sizeof(int) *_SZ_a_0);
	cudaMemcpy(_DEV_a_0,a,sizeof(int) *_SZ_a_0, cudaMemcpyHostToDevice);
	int *_DEV_b_0;
	cudaMalloc((void**) &_DEV_b_0,sizeof(int) *_SZ_b_0);
	cudaMemcpy(_DEV_b_0,b,sizeof(int) *_SZ_b_0, cudaMemcpyHostToDevice);
	int _NUM_THREADS_0 = 50;
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
	int ID_1_0, ID_2_0, START[1];

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_start_0);
	#endif

	int _CUDA_TILE_0;
	int Phi_0[1]={0};
	int loopUpperLimits_0[1]={45};
	for(ID_1_0=1;ID_1_0<=45/0+1;ID_1_0++)
	{
		for(ID_2_0=0;ID_2_0<1;ID_2_0++)
		{
			if(Phi_0[ID_2_0]>=0)
				START[ID_2_0]=(ID_1_0-1)*Phi_0[ID_2_0];
			else
				START[ID_2_0]=loopUpperLimits_0[ID_2_0]+(ID_1_0-1)*Phi_0[ID_2_0];
		}
	for(_CUDA_TILE_0=0;_CUDA_TILE_0<_NUM_TILE_0;_CUDA_TILE_0++)
	{
		_AFFINE_KERNEL_0<<<_BLOCKS_0,_THREADS_0>>>( _DEV_a_0, _SZ_a_0, _DEV_b_0, _SZ_b_0,START[0], MIN(START[0]+0, 45), _CUDA_TILE_0);
			cudaDeviceSynchronize();
	}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_0);
	#endif
	cudaMemcpy(a, _DEV_a_0,sizeof(int) *_SZ_a_0, cudaMemcpyDeviceToHost);
	cudaMemcpy(b, _DEV_b_0,sizeof(int) *_SZ_b_0, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_a_0);
	cudaFree(_DEV_b_0);

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
  }



__global__ void _AFFINE_KERNEL_0(int* a,int  _SZ_a_0,int* b,int  _SZ_b_0,int CUDA_L_i,int CUDA_U_i,int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
a[1+i+10] = a[1+i+2];
b[1+i+1] = a[1+i];
a[1+i] = b[1+i+1];
}}


