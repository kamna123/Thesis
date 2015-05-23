#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{

    int x[20],y[20],i,z[10];
 
  // no dep
for(i=1;i<=10;i=i+1)
    { 
      
      x[i]=y[i];
      z[i]=x[i+10];
     // x[i]=y[2*i+1]+x[i*2]+z[i];
    // x[i+1] =  x[i+1]+2;
   
     } 
}
