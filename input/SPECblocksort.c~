#include<stdio.h>
#include<stdlib.h>
int main()
{
    int block[20],quadrant[20],i,j,k;
    for(i=0;i<20;i++)
    {
        block[i]=2*i;
        quadrant[i]=3*i;
    }
    // PARALLELIZE IN CUDA START
    for (i = 0; i < 20; i++) {
      block[15+i] = block[i];
      quadrant[15+i] = 0;
   }
    // PARALLELIZE IN CUDA END
}

