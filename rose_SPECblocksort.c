#include<stdio.h>
#include<stdlib.h>

int main()
{
  int block[20UL];
  int quadrant[20UL];
  int i;
  int j;
  int k;
  for (i = 0; i<=19; i=i+1) {
    block[1+i] = (2 * (i + 1));
    quadrant[1+i] = (3 * (i + 1));
  }
// PARALLELIZE IN CUDA START
  for (i = 0; i<=19; i=i+1) {
    block[15+1+i] = block[1+i];
    quadrant[15+1+i] = 0;
  }
  return 0;
// PARALLELIZE IN CUDA END
}
