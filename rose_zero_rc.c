#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(int argc,char **argv)
{
  int q[20UL];
  int i;
  for (i = 0; i<=19; i=i+1) {
    q[1+i] = (2 * (i + 1));
  }
  for (i = 0; i<18; i=i+1) {
    q[19-i] = q[19-i-2];
//y[2*i-3][3*j-5]=x[i][j];
//x[3*i-2][2*j-4]=y[i][j];
  }
  return 0;
}
