#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
//int x[5000],z[10],f[20];
  int i;
  int a[500UL];
  int y[20UL];
  int j;
  int k;
//fasdf
  for (i = 1; i <= 20; i = (i + 1)) {
    a[i + 4] = (a[i + 4] + 10);
    y[i] = a[i + 6];
  }
  return 0;
}
