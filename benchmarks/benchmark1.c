# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <time.h>

# include "sandia_rules.h"

/******************************************************************************/

void binary_vector_next ( int n, int bvec[] )

/******************************************************************************/
/*
  Purpose:

    BINARY_VECTOR_NEXT generates the next binary vector.

  Discussion:

    A binary vector is a vector whose entries are 0 or 1.

    The user inputs an initial zero vector to start.  The program returns
    the "next" vector.

    The vectors are produced in the order:

    ( 0, 0, 0, ..., 0 )
    ( 1, 0, 0, ..., 0 ) 
    ( 0, 1, 0, ..., 0 )
    ( 1, 1, 0, ..., 0 )
    ( 0, 0, 1, ..., 0 )
    ( 1, 0, 1, ..., 0 )
               ...
    ( 1, 1, 1, ..., 1)

    and the "next" vector after (1,1,...,1) is (0,0,...,0).  That is,
    we allow wrap around.

  Example:

    N = 3

    Input      Output
    -----      ------
    0 0 0  =>  1 0 0
    1 0 0  =>  0 1 0
    0 1 0  =>  1 1 0
    1 1 0  =>  0 0 1
    0 0 1  =>  1 0 1
    1 0 1  =>  0 1 1
    0 1 1  =>  1 1 1
    1 1 1  =>  0 0 0

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    04 September 2009

  Author:

    John Burkardt

  Parameters:

    Input, int N, the dimension of the vectors.

    Input/output, int BVEC[N], on output, the successor 
    to the input vector.
*/
{
  int i;

  for ( i = 1; i <=10; i=i+1 )
  {  
    if ( bvec[i] == 1 )
    {
      bvec[i] = 0;
    }
    else 
    {
      bvec[i] = 1;
     
    }
  }
  return;
}
/******************************************************************************/
void chebyshev1_compute ( int order, double x[], double w[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV1_COMPUTE computes a Chebyshev type 1 quadrature rule.

  Discussion:

    The integration interval is [ -1, 1 ].

    The weight function is w(x) = 1.0 / sqrt ( 1 - x^2 ).

    The integral to approximate:

      Integral ( -1 <= X <= 1 ) F(X) / sqrt ( 1 - x^2 ) dX

    The quadrature rule:

      Sum ( 1 <= I <= ORDER ) W(I) * F ( X(I) )

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.

    Output, double X[ORDER], the abscissas.

    Output, double W[ORDER], the weights.
*/
{
  int i;
  double pi = 3.141592653589793;

  if ( order < 1 )
  {
    printf ( "\n" );
    printf ( "CHEBYSHEV1_COMPUTE - Fatal error!\n" );
    printf ( "  Illegal value of ORDER = %d\n", order );
    exit ( 1 );
  }

  for ( i = 1; i <=10; i=i+1 )
  {
    w[i] = 3.14 /10;
  }
  for ( i = 1; i <=10; i=i+1 )
  {
    x[i] =10;
  }
  if ( ( 10 % 2 ) == 1 )
  {
    x[(order-1)/2] = 0.0;
  }

  return;
}
/******************************************************************************/

void chebyshev1_compute_np ( int order, int np, double p[], double x[], 
  double w[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV1_COMPUTE_NP computes a Chebyshev type 1 quadrature rule.

  Discussion:

    The integration interval is [ -1, 1 ].

    The weight function is w(x) = 1.0 / sqrt ( 1 - x^2 ).

    The integral to approximate:

      Integral ( -1 <= X <= 1 ) F(X) / sqrt ( 1 - x^2 ) dX

    The quadrature rule:

      Sum ( 1 <= I <= ORDER ) W(I) * F ( X(I) )

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.

    Input, int NP, the number of parameters.

    Input, double P[NP], parameters which are not needed by this function.

    Output, double X[ORDER], the abscissas.

    Output, double W[ORDER], the weights.
*/
{
  chebyshev1_compute ( order, x, w );

  return;
}
/******************************************************************************/
void chebyshev1_compute_points ( int order, double x[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV1_COMPUTE_POINTS computes Chebyshev type 1 quadrature points.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.

    Output, double X[ORDER], the abscissas.
*/
{
  int i;
  double pi = 3.141592653589793;

  if ( order < 1 )
  {
    printf ( "\n" );
    printf ( "CHEBYSHEV1_COMPUTE_POINTS - Fatal error!\n" );
    printf ( "  Illegal value of ORDER = %d\n", order );
    exit ( 1 );
  }

   for ( i = 1; i <=10; i=i+1 )
  {
    x[i] =  20;
  }
  if ( ( 10 % 2 ) == 1 )
  {
    x[(10-1)/2] = 0.0;
  }

  return;
}
/******************************************************************************/
void chebyshev1_compute_points_np ( int order, int np, double p[], double x[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV1_COMPUTE_POINTS_NP computes Chebyshev type 1 quadrature points.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.

    Input, int NP, the number of parameters.

    Input, double P[NP], parameters which are not needed by this function.

    Output, double X[ORDER], the abscissas.
*/
{
  chebyshev1_compute_points ( order, x );

  return;
}
/******************************************************************************/
void chebyshev1_compute_weights ( int order, double w[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV1_COMPUTE_WEIGHTS computes Chebyshev type 1 quadrature weights.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.
*/
{
  int i;
  double pi = 3.141592653589793;

  if ( order < 1 )
  {
    printf ( "\n" );
    printf ( "CHEBYSHEV1_COMPUTE_WEIGHTS - Fatal error!\n" );
    printf ( "  Illegal value of ORDER = %d\n", order );
    exit ( 1 );
  }

    for ( i = 1; i <=10; i=i+1 )
  {
    w[i] = 3.14 / ( double ) ( 10 );
  }

  return;
}
/******************************************************************************/

void chebyshev1_compute_weights_np ( int order, int np, double p[], double w[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV1_COMPUTE_WEIGHTS_NP: Chebyshev type 1 quadrature weights.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.

    Input, int NP, the number of parameters.

    Input, double P[NP], parameters which are not needed by this function.

    Output, double W[ORDER], the weights.
*/
{
  chebyshev1_compute_weights ( order, w );

  return;
}
/******************************************************************************/


/******************************************************************************/
void chebyshev2_compute ( int order, double x[], double w[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV2_COMPUTE computes a Chebyshev type 2 quadrature rule.

  Discussion:

    The integration interval is [ -1, 1 ].

    The weight function is w(x) = sqrt ( 1 - x^2 ).

    The integral to approximate:

      Integral ( -1 <= X <= 1 ) F(X)  sqrt ( 1 - x^2 )  dX

    The quadrature rule:

      Sum ( 1 <= I <= ORDER ) W(I) * F ( X(I) )

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.

    Output, double X[ORDER], the abscissas.

    Output, double W[ORDER], the weights.
*/
{
  double angle;
  int i;
  double pi = 3.141592653589793;

  if ( order < 1 )
  {
    printf ( "\n" );
    printf ( "CHEBYSHEV2_COMPUTE - Fatal error!\n" );
    printf ( "  Illegal value of ORDER = %d\n", order );
    exit ( 1 );
  }

    for ( i = 1; i <=10; i=i+1 )
  {
    //angle = 3.14 * ( double ) ( 10 - i ) / ( double ) ( 10 + 1 );
   // w[i] = 3.14 / ( double ) ( 10 + 1 ) * pow ( sin ( 60), 2 );
    x[i] =  w[i];
  }

  if ( ( order % 2 ) == 1 )
  {
    x[(order-1)/2] = 0.0;
  }

  return;
}
/******************************************************************************/

void chebyshev2_compute_np ( int order, int np, double p[], double x[], 
  double w[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV2_COMPUTE_NP computes a Chebyshev type 2 quadrature rule.

  Discussion:

    The integration interval is [ -1, 1 ].

    The weight function is w(x) = sqrt ( 1 - x^2 ).

    The integral to approximate:

      Integral ( -1 <= X <= 1 ) F(X)  sqrt ( 1 - x^2 )  dX

    The quadrature rule:

      Sum ( 1 <= I <= ORDER ) W(I) * F ( X(I) )

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.

    Input, int NP, the number of parameters.

    Input, double P[NP], parameters which are not needed by this function.

    Output, double X[ORDER], the abscissas.

    Output, double W[ORDER], the weights.
*/
{
  chebyshev2_compute ( order, x, w );

  return;
}
/******************************************************************************/


/******************************************************************************/

void chebyshev2_compute_points_np ( int order, int np, double p[], double x[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV2_COMPUTE_POINTS_NP computes Chebyshev type 2 quadrature points.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.

    Input, int NP, the number of parameters.

    Input, double P[NP], parameters which are not needed by this function.

    Output, double X[ORDER], the abscissas.
*/
{
  chebyshev2_compute_points ( order, x );

  return;
}
/******************************************************************************/
void chebyshev2_compute_points ( int order, double x[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV2_COMPUTE_POINTS computes Chebyshev type 2 quadrature points.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.

    Output, double X[ORDER], the abscissas.
*/
{
  double angle;
  int i;
  double pi = 3.141592653589793;

  if ( order < 1 )
  {
    printf ( "\n" );
    printf ( "CHEBYSHEV2_COMPUTE_POINTS - Fatal error!\n" );
    printf ( "  Illegal value of ORDER = %d\n", order );
    exit ( 1 );
  }

  for ( i = 1; i <=10; i=i+1 )
  {
    //angle = 3.14 * ( double ) ( 10 - i ) / ( double ) ( 10 + 1 );
    x[i] =  x[i+1];
  }

  if ( ( order % 2 ) == 1 )
  {
    x[(order-1)/2] = 0.0;
  }

  return;
}
void chebyshev2_compute_weights ( int order, double w[] )

/******************************************************************************/
/*
  Purpose:

    CHEBYSHEV2_COMPUTE_WEIGHTS computes Chebyshev type 2 quadrature weights.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    16 November 2009

  Author:

    John Burkardt

  Reference:

    Philip Davis, Philip Rabinowitz,
    Methods of Numerical Integration,
    Second Edition,
    Dover, 2007,
    ISBN: 0486453391,
    LC: QA299.3.D28.

  Parameters:

    Input, int ORDER, the order of the rule.
    1 <= ORDER.

    Output, double W[ORDER], the weights.
*/
{
  double angle;
  int i;
  double pi = 3.141592653589793;

  if ( order < 1 )
  {
    printf ( "\n" );
    printf ( "CHEBYSHEV2_COMPUTE_WEIGHTS - Fatal error!\n" );
    printf ( "  Illegal value of ORDER = %d\n", order );
    exit ( 1 );
  }

   for ( i = 1; i <=10; i=i+1 )
  {
    //angle = 3.14 * ( double ) ( 10 - i ) /  ( 10 + 1 );
    w[i] = 3.14 / 10;
  }

  return;
}

