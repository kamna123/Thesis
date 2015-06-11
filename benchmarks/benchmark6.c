#include<stdio.h>
#include<stdlib.h>
int main()
{
    int block[20],quadrant[20],i,j,k;
    //for(i=1;i<=20;i=i+1)
    
    for (i = 1; i <= 20; i=i+1) 
    {
      block[15+i] = i;
      
   }
   
   for (i = 1; i <= 20; i=i+1) 
   {
      block[15+i] = block[i];
      
   }
    for ( i = 1; i <=10; i=i+1 )
  {
    //angle = 3.14 * ( double ) ( 10 - i ) /  ( 10 + 1 );
    block[i] = block[i]+3.14 / 10;
  }
}

