#include<stdio.h>
#include<stdlib.h>

int main()
{
  int x[20UL];
  int w[20UL];
  int i;
  int j;
  int k;
  for (i = 0; i<=19; i=i+1) {
    x[1+i] = (2 * i);
    w[1+i] = (2 * i);
  }
// PARALLELIZE IN CUDA START
  for (i = 0; i<=9; i=i+1) {
    x[1+i-1] = -x[20-1-i];
    w[1+i-1] = w[20-1-i];
  }
// PARALLELIZE IN CUDA END
  return 0;
}
