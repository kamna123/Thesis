#include<stdio.h>
#include<stdlib.h>
int main()
{
    int block[20],quadrant[20],i,j,k;
    for(i=1;i<=20;i=i+1)
    {
        block[i]=2*(i+1);
        quadrant[i]=3*(i+1);
    }
    // PARALLELIZE IN CUDA START
    for (i = 1; i <= 20; i=i+1) {
      block[15+i] = block[i];
      quadrant[15+i] = 0;
   }
    // PARALLELIZE IN CUDA END
}

