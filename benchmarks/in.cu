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
int main()
{
     int x[20],y[20],z[10],f[20];
   int i,a[50],k=5,j,b[300];
 
 
   //fasdf

int cd;
int jk;
int ty;
int kl;
 /* for(i=1;i<=20;i=i+1)
    {
     a[2+2*i]=5;
    }*/
__global__ void _AFFINE_KERNEL_0(int* ,int ,int* ,int ,int* ,int ,int ,int ,int );

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
	int _SZ_z_0 = 10;

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
	int *_DEV_z_0;
	cudaMalloc((void**) &_DEV_z_0,sizeof(int) *_SZ_z_0);
	cudaMemcpy(_DEV_z_0,z,sizeof(int) *_SZ_z_0, cudaMemcpyHostToDevice);
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

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_start_0);
	#endif

	int _CUDA_TILE_0;
	int ID_1_0=0, next_ID_1_0;
	while((ID_1_0<19))
	{
		next_ID_1_0 = MIN((((3)+(0)*ID_1_0)/(1)), (((2)+(1)*ID_1_0)/(1)));
	for(_CUDA_TILE_0=0;_CUDA_TILE_0<_NUM_TILE_0;_CUDA_TILE_0++)
	{
		_AFFINE_KERNEL_0<<<_BLOCKS_0,_THREADS_0>>>( _DEV_a_0, _SZ_a_0, _DEV_b_0, _SZ_b_0, _DEV_z_0, _SZ_z_0,ID_1_0, MIN(next_ID_1_0,19), _CUDA_TILE_0);
			cudaDeviceSynchronize();
		}
	for(_CUDA_TILE_0=0;_CUDA_TILE_0<_NUM_TILE_0;_CUDA_TILE_0++)
	{
		_AFFINE_KERNEL_0<<<_BLOCKS_0,_THREADS_0>>>( _DEV_a_0, _SZ_a_0, _DEV_b_0, _SZ_b_0, _DEV_z_0, _SZ_z_0,next_ID_1_0, 19, _CUDA_TILE_0);
			cudaDeviceSynchronize();
		}
		ID_1_0=next_ID_1_0;
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_0);
	#endif
	cudaMemcpy(a, _DEV_a_0,sizeof(int) *_SZ_a_0, cudaMemcpyDeviceToHost);
	cudaMemcpy(b, _DEV_b_0,sizeof(int) *_SZ_b_0, cudaMemcpyDeviceToHost);
	cudaMemcpy(z, _DEV_z_0,sizeof(int) *_SZ_z_0, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_a_0);
	cudaFree(_DEV_b_0);
	cudaFree(_DEV_z_0);

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


    return 0;
}




__global__ void _AFFINE_KERNEL_0(int* a,int  _SZ_a_0,int* b,int  _SZ_b_0,int* z,int  _SZ_z_0,int CUDA_L_i,int CUDA_U_i,int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
a[5+1+i] = b[1+1+i];
b[2+2+2*i] =((a[1+i+2] + 2) + z[2+1+i]);
}}

