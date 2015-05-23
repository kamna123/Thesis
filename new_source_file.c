#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _NTHREAD 512
#define _NBLOCK 65535
#include<cuda.h>

__global__ void _AFFINE_KERNEL(int* ,int ,int* ,int ,int* ,int ,int );

	int_SZ_a_1 = 50;
	int_SZ_b_1 = 300;
	int_SZ_z_1 = 10;
	int*_DEV_a;
	cudaMalloc((void**) &_DEV_a,sizeof(int)*_SZ_a_1);
	cudaMemcpy(_DEV_a,a,sizeof(int)*_SZ_a_1, cudaMemcpyHostToDevice);
	int*_DEV_b;
	cudaMalloc((void**) &_DEV_b,sizeof(int)*_SZ_b_1);
	cudaMemcpy(_DEV_b,b,sizeof(int)*_SZ_b_1, cudaMemcpyHostToDevice);
	int*_DEV_z;
	cudaMalloc((void**) &_DEV_z,sizeof(int)*_SZ_z_1);
	cudaMemcpy(_DEV_z,z,sizeof(int)*_SZ_z_1, cudaMemcpyHostToDevice);
	int _NUM_THREADS = 50;
	float _NUM_BLOCKS=1;
	int _NUM_TILE=1;
	dim3 _THREADS(512);
	dim3 _BLOCKS(1);
	if(_NUM_THREADS < _NTHREAD)
	{
		_THREADS.x=_NUM_THREADS;
	}
	else {
		 _THREADS.x=_NTHREAD;
		_NUM_BLOCKS=(_NUM_THREADS % _NTHREAD == 0)?(_NUM_THREADS/_NTHREAD):((_NUM_THREADS/_NTHREAD)+1);
		if(_NUM_BLOCKS<_NBLOCK)
			_BLOCKS.x=_NUM_BLOCKS;
		else {
			_BLOCKS.x=_NBLOCK;
			int temp=_NUM_BLOCKS;
			_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);
		}
	}
	int _CUDA_TILE;
for(i = 5stepsize)
