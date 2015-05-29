# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <time.h>

# include "sandia_rules.h"

/******************************************************************************/


/******************************************************************************/


void chebyshev1_compute ( int order, double x[], double w[] )


{
  int i;
  double pi = 3.141592653589793;

  
  for ( i = 1; i <=10; i=i+1 )
  {
    w[i] = pi / 10;
  }
  

  return;
}
void r8vec_copy ( int n, double a1[], double a2[] )

{
  int i;

  for ( i = 1; i <=10; i=i+1 )
  {
    a2[i] = a1[i];
  }
  return;
}