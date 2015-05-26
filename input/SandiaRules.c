#include<stdio.h>
#include<stdlib.h>
int main()
{
    int x[20];
    int w[20],i,j,k;
    for(i=1;i<=20;i=i+1)
    {
        x[i]=2*i;
        w[i]=2*i;
    }
    // PARALLELIZE IN CUDA START
    for(i=1;i<=10;i=i+1)
    {
        x[i-1]=-x[20-i];
        w[i-1]=w[20-i];
    }
    // PARALLELIZE IN CUDA END
    
    return 0;
}

