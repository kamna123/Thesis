#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{

    int x[20],y[20],i,z[10],a[100],j;
 
  //dep
for(i=5;i<=14;i=i+2)
    { 
      
      x[i]=x[i+2];
     // x[i]=y[2*i+1]+x[i*2]+z[i];
    // x[i+1] =  x[i+1]+2;
   
     } 
//dep
 for(i=1;i<=46;i=i+1)
    {
    y[i+10]=y[i+2];
      x[i+4]=y[i+2];
     y[i]=x[i+1];  
     } 
//no
 for(i=1; i<=101; i=i+1)
{
        x[2*i+3] = x[2*i] + 50;
}
//no
for( i=1;i<=100;i=i+1)
{
  x[2*i]=y[i];
  z[i]=x[4*i+1];
}
 // gcd:yes banerjee:no omega:no*/
/*  for(j=1;j<=10;j=j+1)
  {
        a[j]=a[j+10]+10;
      }
   
// gcd,omega: no
  //  banerjee: yes(need correction)
  for(j=1;j<=10;j=j+1)
     {  a[2*j]=a[4*j+3]+10;}
   
// gcd,banerjee,omega: yes
 for(j=1;j<=9;j=j+1)
     {  a[j]=a[10-j]+10;}
   
//gcd,banerjee,omega: yes
  for(j=1;j<=9;j=j+1)
     {  a[j]=a[j]+10;}*/
    
//  gcd,banerjee,omega: yes
  for(j=1;j<=9;j=j+1)
      { a[j]=a[10-j]+10;}
 
    
      return 0;   
    
}
