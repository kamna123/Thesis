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
/*for(i=0;i<20;i++)
    {
        x[i]=i;
        y[i]=2*i;
    }*/
// PARALLELIZE IN CUDA START
// for(j=0;j<4;j++)
  for (i = 0; i <= (14-5)/2; i = (i + 1)) {
    x[(i*2+5)] = ((y[(2 * (i*2+5)) + 1] + x[(i*2+5) * 2]) + z[(i*2+5)]);
    x[(i*2+5) + 1] = (x[(i*2+5) + 1] + 2);
// x[i*2] =  y[i+3]+x[2+i*3];
/*  z[i]= z[3+i*3+i*4]+x[2+i*3];
	     i = i +5;
       y[i]=x[i+1];*/
// y[2*i-3]=x[i];
//x[3*i-2]=y[i];
  }
/*for(i=0;i<46;i=i+1)
    {
    y[i+10]=y[i+2];
      x[i+4]=y[i+2];
     y[i]=x[i+1];  
     } 
 
   */
  return 0;
}
