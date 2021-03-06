# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
/******************************************************************************/
/*
  Purpose:

    BALL01_MONOMIAL_INTEGRAL returns monomial integrals in the unit ball.

  Discussion:

    The integration region is 

      X^2 + Y^2 + Z^2 <= 1.

    The monomial is F(X,Y,Z) = X^E(1) * Y^E(2) * Z^E(3).

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    02 January 2014

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Academic Press, 1984, page 263.

  Parameters:

    Input, int E[3], the exponents of X, Y and Z in the 
    monomial.  Each exponent must be nonnegative.

    Output, double BALL01_MONOMIAL_INTEGRAL, the integral.
*/
int main()
{
	 int i;
  double integral;
  const double u = 1.0;
  double s;
  int e[10];
  if ( e[0] < 0 || e[1] < 0 || e[2] < 0 )
  {
    fprintf ( stderr, "\n" );
    fprintf ( stderr, "BALL01_MONOMIAL_INTEGRAL - Fatal error!\n" );
    fprintf ( stderr, "  All exponents must be nonnegative.\n" );
    fprintf ( stderr, "  E[0] = %d\n", e[0] );
    fprintf ( stderr, "  E[1] = %d\n", e[1] );
    fprintf ( stderr, "  E[2] = %d\n", e[2] );
    exit ( 1 );
  }
for(i=1;i<=3;i=i+1)
  {e[i]=e[i+3];}
/*
  The surface integral is now adjusted to give the volume integral.
*/
  s = e[0] + e[1] + e[2] + 3;

  integral = integral * pow ( u, s  ) / ( double ) ( s );
  /******************************************************************************/
/*
  Purpose:

    BALL01_SAMPLE uniformly samples points from the unit ball.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    02 January 2014

  Author:

    John Burkardt

  Reference:

    Russell Cheng,
    Random Variate Generation,
    in Handbook of Simulation,
    edited by Jerry Banks,
    Wiley, 1998, pages 168.

    Reuven Rubinstein,
    Monte Carlo Optimization, Simulation, and Sensitivity 
    of Queueing Networks,
    Krieger, 1992,
    ISBN: 0894647644,
    LC: QA298.R79.

  Parameters:

    Input, int N, the number of points.

    Input/output, int *SEED, a seed for the random 
    number generator.

    Output, double X[3*N], the points.
*/


  int j;


int x[100];
  

    for ( i = 1; i <= 3; i=i+1 )
    {
      x[i+3] = x[i+4] / 10;
    }
  /*  ******************************************************************************/
/*  ******************************************************************************/
/*
  Purpose:

    BALL01_VOLUME returns the volume of the unit ball.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    02 January 2014

  Author:

    John Burkardt

  Parameters:

    Output, double BALL01_VOLUME, the volume of the unit ball.
*/

 
  const double r8_pi = 3.141592653589793;
  double volume;

  volume = 4.0 * r8_pi * pow ( u, 3 ) / 3.0;

 /******************************************************************************/
/*
  Purpose:

    MONOMIAL_VALUE evaluates a monomial.

  Discussion:

    This routine evaluates a monomial of the form

      product ( 1 <= i <= m ) x(i)^e(i)

    where the exponents are nonnegative integers.  Note that
    if the combination 0^0 is encountered, it should be treated
    as 1.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    08 May 2014

  Author:

    John Burkardt

  Parameters:

    Input, int M, the spatial dimension.

    Input, int N, the number of points at which the
    monomial is to be evaluated.

    Input, int E[M], the exponents.

    Input, double X[M*N], the point coordinates.

    Output, double MONOMIAL_VALUE[N], the value of the monomial.
*/

  double v[100];

  

  for ( i = 1; i<= 10; i=i+1 )
  {
    v[i] = v[i+2]+1.0;
  }
/******************************************************************************/
/*
  Purpose:

    R8_UNIFORM_01 returns a pseudorandom R8 scaled to [0,1].

  Discussion:

    This routine implements the recursion

      seed = 16807 * seed mod ( 2^31 - 1 )
      r8_uniform_01 = seed / ( 2^31 - 1 )

    The integer arithmetic never requires more than 32 bits,
    including a sign bit.

    If the initial seed is 12345, then the first three computations are

      Input     Output      R8_UNIFORM_01
      SEED      SEED

         12345   207482415  0.096616
     207482415  1790989824  0.833995
    1790989824  2035175616  0.947702

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    11 August 2004

  Author:

    John Burkardt

  Reference:

    Paul Bratley, Bennett Fox, Linus Schrage,
    A Guide to Simulation,
    Springer Verlag, pages 201-202, 1983.

    Pierre L'Ecuyer,
    Random Number Generation,
    in Handbook of Simulation
    edited by Jerry Banks,
    Wiley Interscience, page 95, 1998.

    Bennett Fox,
    Algorithm 647:
    Implementation and Relative Efficiency of Quasirandom
    Sequence Generators,
    ACM Transactions on Mathematical Software,
    Volume 12, Number 4, pages 362-376, 1986.

    P A Lewis, A S Goodman, J M Miller,
    A Pseudo-Random Number Generator for the System/360,
    IBM Systems Journal,
    Volume 8, pages 136-143, 1969.

  Parameters:

    Input/output, int *SEED, the "seed" value.  Normally, this
    value should not be 0.  On output, SEED has been updated.

    Output, double R8_UNIFORM_01, a new pseudorandom variate, strictly between
    0 and 1.
*/
    int* seed;
  int i4_huge = 2147483647;
  int k;


  k = *seed / 127773;

  *seed = 16807 * ( *seed - k * 127773 ) - k * 2836;

  if ( *seed < 0 )
  {
    *seed = *seed + i4_huge;
  }

  
  /******************************************************************************/
/*
  Purpose:

    R8MAT_NORMAL_01_NEW returns a unit pseudonormal R8MAT.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    03 October 2005

  Author:

    John Burkardt

  Reference:

    Paul Bratley, Bennett Fox, Linus Schrage,
    A Guide to Simulation,
    Springer Verlag, pages 201-202, 1983.

    Bennett Fox,
    Algorithm 647:
    Implementation and Relative Efficiency of Quasirandom
    Sequence Generators,
    ACM Transactions on Mathematical Software,
    Volume 12, Number 4, pages 362-376, 1986.

    Peter Lewis, Allen Goodman, James Miller,
    A Pseudo-Random Number Generator for the System/360,
    IBM Systems Journal,
    Volume 8, pages 136-143, 1969.

  Parameters:

    Input, int M, N, the number of rows and columns in the array.

    Input/output, int *SEED, the "seed" value, which should NOT be 0.
    On output, SEED has been updated.

    Output, double R8MAT_NORMAL_01_NEW[M*N], the array of pseudonormal values.
*/
/******************************************************************************/
/*
  Purpose:

    R8VEC_NORMAL_01_NEW returns a unit pseudonormal R8VEC.

  Discussion:

    The standard normal probability distribution function (PDF) has
    mean 0 and standard deviation 1.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    06 August 2013

  Author:

    John Burkardt

  Parameters:

    Input, int N, the number of values desired.

    Input/output, int *SEED, a seed for the random number generator.

    Output, double R8VEC_NORMAL_01_NEW[N], a sample of the standard normal PDF.

  Local parameters:

    Local, double R[N+1], is used to store some uniform random values.
    Its dimension is N+1, but really it is only needed to be the
    smallest even number greater than or equal to N.

    Local, int X_LO, X_HI, records the range of entries of
    X that we need to compute.
*/

  int n=10;
  int m;
  const double pi = 3.141592653589793;
 
  int x_hi;
  int x_lo;

  
/*
  Record the range of X we need to fill in.
*/
  x_lo = 1;
  x_hi = n;
/*
  If we need just one new value, do that here to avoid null arrays.
*/
  if ( x_hi - x_lo + 1 == 1 )
  {
    

    x[x_hi-1] = sqrt ( - 2.0  * 2.0 * pi );

   
  }
/*
  If we require an even number of values, that's easy.
*/
  else if ( ( x_hi - x_lo + 1 ) % 2 == 0 )
  {
    m = ( x_hi - x_lo + 1 ) / 2;

    

   
  }
/*
  If we require an odd number of values, we generate an even number,
  and handle the last pair specially, storing one in X(N).
*/
  else
  {
    x_hi = x_hi - 1;

    m = ( x_hi - x_lo + 1 ) / 2 + 1;

    i = 2*m - 2;

    x[x_lo+i-1] = sqrt ( - 2.0  *  2.0 * pi );
}

   /******************************************************************************/
/*
  Purpose:

    R8VEC_UNIFORM_01_NEW returns a unit pseudorandom R8VEC.

  Discussion:

    This routine implements the recursion

      seed = 16807 * seed mod ( 2^31 - 1 )
      unif = seed / ( 2^31 - 1 )

    The integer arithmetic never requires more than 32 bits,
    including a sign bit.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    19 August 2004

  Author:

    John Burkardt

  Reference:

    Paul Bratley, Bennett Fox, Linus Schrage,
    A Guide to Simulation,
    Second Edition,
    Springer, 1987,
    ISBN: 0387964673,
    LC: QA76.9.C65.B73.

    Bennett Fox,
    Algorithm 647:
    Implementation and Relative Efficiency of Quasirandom
    Sequence Generators,
    ACM Transactions on Mathematical Software,
    Volume 12, Number 4, December 1986, pages 362-376.

    Pierre L'Ecuyer,
    Random Number Generation,
    in Handbook of Simulation,
    edited by Jerry Banks,
    Wiley, 1998,
    ISBN: 0471134031,
    LC: T57.62.H37.

    Peter Lewis, Allen Goodman, James Miller,
    A Pseudo-Random Number Generator for the System/360,
    IBM Systems Journal,
    Volume 8, Number 2, 1969, pages 136-143.

  Parameters:

    Input, int N, the number of entries in the vector.

    Input/output, int *SEED, a seed for the random number generator.

    Output, double R8VEC_UNIFORM_01_NEW[N], the vector of pseudorandom values.
*/

  

  if ( *seed == 0 )
  {
    fprintf ( stderr, "\n" );
    fprintf ( stderr, "R8VEC_UNIFORM_01_NEW - Fatal error!\n" );
    fprintf ( stderr, "  Input value of SEED = 0.\n" );
    exit ( 1 );
  }

 
int r[100];
  for ( i = 1; i <= 10; i=i+1 )
  {

    r[i] =r[i+1]+ ( double ) ( 4) * 4.656612875E-10;
  }
/******************************************************************************/
/*
  Purpose:

    TIMESTAMP prints the current YMDHMS date as a time stamp.

  Example:

    31 May 2001 09:45:54 AM

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    24 September 2003

  Author:

    John Burkardt

  Parameters:

    None
*/
return 0;

 
  }
  
