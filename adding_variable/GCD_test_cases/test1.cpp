#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{

    int x[20],y[20],i,z[10];
 
  //dep
for(i=5;i<=14;i=i+2)
    { 
      
      x[i]=y[2*i+1]+x[i*2]+z[i];
     x[i+1] =  x[i+1]+2;
   
     } 
//dep
 for(i=0;i<46;i=i+1)
    {
    y[i+10]=y[i+2];
      x[i+4]=y[i+2];
     y[i]=x[i+1];  
     } 
//no
 for(i=0; i<=100; i=i+1)
{
        x[2*i+3] = x[2*i] + 50;
}
//no
for( i=0;i<100;i=i+1)
{
  x[2*i]=y[i];
  z[i]=x[4*i+1];
}
    return 0;
}
