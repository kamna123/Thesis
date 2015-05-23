
_global_ void sub(int &a,int &b,int &c)
{
}

_global_ void add(float &a,int &b,int &c)
{
}

void add(int a,int b,int c)
{
}

void sub(int i,int b,int c)
{
}

int main()
{
  int i;
  int j;
  int k;
//Added a comment
  i = 2;
  j = 3;
  k = 2;
  add(i,j,k);
  sub(i,j,k);
  int *crink_i;
  cudaMalloc((void**)& crink_i,size);
  cudaMemcpy(crink_i,&i,size,CudaMemcpyHostToDevice);
  int *crink_j;
  cudaMalloc((void**)& crink_j,size);
  cudaMemcpy(crink_j,&j,size,CudaMemcpyHostToDevice);
  int *crink_k;
  cudaMalloc((void**)& crink_k,size);
  cudaMemcpy(crink_k,&k,size,CudaMemcpyHostToDevice);
  add<<<1,1>>>(crink_i,crink_j,crink_k);
  cudaMemcpy(&k,crink_k,size,CudaMemcpyDeviceToHost);
  sub<<<1,1>>>(crink_i,crink_j,crink_k);
  cudaMemcpy(&k,crink_k,size,CudaMemcpyDeviceToHost);
  cudaFree(crink_i);
  cudaFree(crink_j);
  cudaFree(crink_k);
  return 0;
}
