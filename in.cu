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
#define _NTHREAD 512
#define _NBLOCK 65535
#include<cuda.h>

__global__ void _AFFINE_KERNEL_0(int* ,int ,int ,int ,int );

	int _SZ_a_0 = 50;
	int *_DEV_a_0;
	cudaMalloc((void**) &_DEV_a_0,sizeof(int) *_SZ_a_0);
	cudaMemcpy(_DEV_a_0,a,sizeof(int)*_SZ_a_0, cudaMemcpyHostToDevice);
	int _NUM_THREADS_0= 50;
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
	int _CUDA_TILE_0;
	for(_CUDA_TILE_0=0;_CUDA_TILE_0<_NUM_TILE_0;_CUDA_TILE_0++)
	{
		_AFFINE_KERNEL_0<<<_BLOCKS_0,_THREADS_0>>>( _DEV_a_0, _SZ_a_0,0,19, _CUDA_TILE_0);
		cudaDeviceSynchronize();
	}
	cudaMemcpy(a, _DEV_a_0,sizeof(int) *_SZ_a_0, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_a_0);
#define _NTHREAD 512
#define _NBLOCK 65535
#include<cuda.h>

__global__ void _AFFINE_KERNEL_1(int* ,int ,int* ,int ,int* ,int ,int ,int ,int ,int ,int );

	int _SZ_a_1 = 50;
	int _SZ_b_1 = 300;
	int _SZ_z_1 = 10;
	int*_DEV_a_1;
	cudaMalloc((void**) &_DEV_a_1,sizeof(int) *_SZ_a_1);
	cudaMemcpy(_DEV_a_1,a,sizeof(int) *_SZ_a_1, cudaMemcpyHostToDevice);
	int*_DEV_b_1;
	cudaMalloc((void**) &_DEV_b_1,sizeof(int) *_SZ_b_1);
	cudaMemcpy(_DEV_b_1,b,sizeof(int) *_SZ_b_1, cudaMemcpyHostToDevice);
	int*_DEV_z_1;
	cudaMalloc((void**) &_DEV_z_1,sizeof(int) *_SZ_z_1);
	cudaMemcpy(_DEV_z_1,z,sizeof(int) *_SZ_z_1, cudaMemcpyHostToDevice);
	int _NUM_THREADS_1= 50;
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
	int _CUDA_TILE_1;
	for(i=0;i<=19;i+=1)
	for(_CUDA_TILE_1=0;_CUDA_TILE_1<_NUM_TILE_1;_CUDA_TILE_1++)
	{		_AFFINE_KERNEL_1<<<_BLOCKS_1,_THREADS_1>>>( _DEV_a_1, _SZ_a_1, _DEV_b_1, _SZ_b_1, _DEV_z_1, _SZ_z_1,1,i,0,19,_CUDA_TILE_1);
		cudaDeviceSynchronize();
	}	cudaMemcpy(a, _DEV_a_1,sizeof(int) *_SZ_a_1, cudaMemcpyDeviceToHost);
	cudaMemcpy(b, _DEV_b_1,sizeof(int) *_SZ_b_1, cudaMemcpyDeviceToHost);
	cudaMemcpy(z, _DEV_z_1,sizeof(int) *_SZ_z_1, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_a_1);
	cudaFree(_DEV_b_1);
	cudaFree(_DEV_z_1);


    return 0;
}




__global__ void _AFFINE_KERNEL_0(int* a,int  _SZ_a_0,int CUDA_L_i,int CUDA_U_i,int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
a[1+i] = 5;
}}



__global__ void _AFFINE_KERNEL_1(int* a,int  _SZ_a_1,int* b,int  _SZ_b_1,int* z,int  _SZ_z_1,int phi_count, int CUDA_i,int CUDA_L_i,int CUDA_U_i,int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_i<=i)&&(i<(CUDA_i+1))&&(i<=CUDA_U_i)){
a[5+1+i] = b[1+1+i];
b[2+1+i] =((a[1+i+2] + 2) + z[2+1+i]);
}}

