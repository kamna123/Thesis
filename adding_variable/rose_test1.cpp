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
//dep
  for (i = 0; i <= (14-5)/2; i = (i + 1)) {
    x[(i*1+0)] = ((y[(2 * (i*1+0)) + 1] + x[(i*1+0) * 2]) + z[(i*1+0)]);
    x[(i*1+0) + 1] = (x[(i*1+0) + 1] + 2);
  }
//dep
  for (i = 0; i <= (45-0)/1; i = (i + 1)) {
    y[(i*1+0) + 10] = y[(i*1+0) + 2];
    x[(i*1+0) + 4] = y[(i*1+0) + 2];
    y[(i*1+0)] = x[(i*1+0) + 1];
  }
//no
  for (i = 0; i <= (100-0)/1; i = (i + 1)) {
    x[(2 * (i*1+0)) + 3] = (x[2 * (i*1+0)] + 50);
  }
//no
  for (i = 0; i <= (99-0)/1; i = (i + 1)) {
    x[2 * (i*1+0)] = y[(i*1+0)];
    z[(i*1+0)] = x[(4 * (i*1+0)) + 1];
  }
  return 0;
}
