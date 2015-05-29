#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int block[20],quadrant[20],i,j,k;
    //for(i=1;i<=20;i=i+1)
     i=1;
     while(i<=20)
    {
        block[i]=2*(i+1);
        quadrant[i]=3*(i+1);
         i++;
    }
    // PARALLELIZE IN CUDA START
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
	int _SZ_block_0 = 20;
	int _SZ_quadrant_0 = 20;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_0);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_block_0;
	cudaMalloc((void**) &_DEV_block_0,sizeof(int) *_SZ_block_0);
	cudaMemcpy(_DEV_block_0,block,sizeof(int) *_SZ_block_0, cudaMemcpyHostToDevice);
	int *_DEV_quadrant_0;
	cudaMalloc((void**) &_DEV_quadrant_0,sizeof(int) *_SZ_quadrant_0);
	cudaMemcpy(_DEV_quadrant_0,quadrant,sizeof(int) *_SZ_quadrant_0, cudaMemcpyHostToDevice);
	int _NUM_THREADS_0 = 20;
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
	int Phi_0[1]={15};
	int loopUpperLimits_0[1]={19};
	for(ID_1_0=1;ID_1_0<=19/15+1;ID_1_0++)
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
		_AFFINE_KERNEL_0<<<_BLOCKS_0,_THREADS_0>>>( _DEV_block_0, _SZ_block_0, _DEV_quadrant_0, _SZ_quadrant_0,START[0], MIN(START[0]+15, 19), _CUDA_TILE_0);
			cudaDeviceSynchronize();
	}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_0);
	#endif
	cudaMemcpy(block, _DEV_block_0,sizeof(int) *_SZ_block_0, cudaMemcpyDeviceToHost);
	cudaMemcpy(quadrant, _DEV_quadrant_0,sizeof(int) *_SZ_quadrant_0, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_block_0);
	cudaFree(_DEV_quadrant_0);

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
    // PARALLELIZE IN CUDA END
}




__global__ void _AFFINE_KERNEL_0(int* block,int  _SZ_block_0,int* quadrant,int  _SZ_quadrant_0,int CUDA_L_i,int CUDA_U_i,int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
block[15+1+i] = block[1+i];
quadrant[15+1+i] = 0;
}}


