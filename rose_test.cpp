#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main()
{
    int x[20UL];
    int y[20UL];
    int i;
    int z[10UL];
// no dep
    for (i = 0; i <= 9; i = (i + 1))
    {
        x[(i*1+1)] = y[(i*1+1)];
        z[(i*1+1)] = x[(i*1+1) + 10];
// x[i]=y[2*i+1]+x[i*2]+z[i];
// x[i+1] =  x[i+1]+2;
    }
    return 0;
}
