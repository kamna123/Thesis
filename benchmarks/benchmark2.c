# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <time.h>
int main()
{
  int i;
int bvec[10];
 /*Purpose:

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
    to the input vector.*/
  for ( i = 1; i <=10; i=i+1 )
  {  
  bvec[i]=bvec[i+1];
  }
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

 int order,x[20],w[20];

  if ( order < 1 )
  {
    printf ( "\n" );
    printf ( "CHEBYSHEV1_COMPUTE - Fatal error!\n" );
    printf ( "  Illegal value of ORDER = %d\n", order );
    exit ( 1 );
  }

  for ( i = 1; i <=10; i=i+1 )
  {
    w[i] =w[i+1] +3.14 /10;
  }
  for ( i = 1; i <=10; i=i+1 )
  {
    x[i] =x[i+1]+10;
  }
  if ( ( 10 % 2 ) == 1 )
  {
    x[(order-1)/2] = 0.0;
  }
/* Purpose:

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


  if ( order < 1 )
  {
    printf ( "\n" );
    printf ( "CHEBYSHEV1_COMPUTE_POINTS - Fatal error!\n" );
    printf ( "  Illegal value of ORDER = %d\n", order );
    exit ( 1 );
  }

   for ( i = 1; i <=10; i=i+1 )
  {
    x[i] = x[i+1]+ 20;
  }
  if ( ( 10 % 2 ) == 1 )
  {
    x[(10-1)/2] = 0.0;
  }
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


 

  if ( order < 1 )
  {
    printf ( "\n" );
    printf ( "CHEBYSHEV1_COMPUTE_WEIGHTS - Fatal error!\n" );
    printf ( "  Illegal value of ORDER = %d\n", order );
    exit ( 1 );
  }

    for ( i = 1; i <=10; i=i+1 )
  {
    w[i] =w[i+1]+ 3.14 / ( double ) ( 10 );
  }

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
    x[i] =  x[i+1]+1;
  }

  if ( ( order % 2 ) == 1 )
  {
    x[(order-1)/2] = 0.0;
  }
/*******************************************************************************/
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
    x[(order-1)/2] = 0.0+pi;
  }
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
    w[i] = w[i+1]+3.14 / 10;
  }
return 0;
   }
   