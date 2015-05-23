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
  int a[100UL];
  int j;
//dep
  for (i = 0; i<=4; i=i+1) {
    x[5+2*i] = x[5+2*i+2];
// x[i]=y[2*i+1]+x[i*2]+z[i];
// x[i+1] =  x[i+1]+2;
  }
//dep
  for (i = 0; i<=45; i=i+1) {
    y[1+i+10] = y[1+i+2];
    x[1+i+4] = y[1+i+2];
    y[1+i] = x[1+i+1];
  }
//no
  for (i = 0; i<=100; i=i+1) {
    x[2+2*i+3] = (x[2+2*i] + 50);
  }
//no
  for (i = 0; i<=99; i=i+1) {
    x[2+2*i] = y[1+i];
    z[1+i] = x[4+4*i+1];
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
  for (j = 0; j<=8; j=j+1) {
    a[1+j] = (a[10-1-j] + 10);
  }
  return 0;
}
