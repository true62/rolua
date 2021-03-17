#include <math.h>
#include <stdio.h>

// Some random bits we'll need
#define MINUSONODD(n) (n%2?-1:+1)
#define TWON(n) (2*(n))
#define NPLUSONE(n) ((n)+1)
#define TWONPLUSONE(n) NPLUSONE(TWON(n))
#define FACT(n) (tgamma(NPLUSONE(n)))

// The Euler series
//                           2^(2n) * (n!)^2      z^(2n+1)
// atan(z) = \sum_n=0^\infty --------------- * ---------------
//                               (2n+1)!       (1 + z^2)^(n+1)
#define TERMEULER(n,z) (pow(2,TWON(n))*                 \
            FACT(n)*FACT(n)*                \
            pow((z),TWONPLUSONE(n))/            \
            FACT(TWONPLUSONE(n)) /              \
            pow((1+z*z),NPLUSONE(n)) )

// The naive version
//                           (-1)^n * z^(2n+1)
// atan(z) = \sum_n=0^\infty -----------------
//                                2n + 1
#define TERMNAIVE(n,z) (MINUSONODD(n)*pow(z,TWONPLUSONE(n))/TWONPLUSONE(n))


// Define a set of bifruncations of the sum
#define N2TERMS(n,z,ALG)  (TERM##ALG(TWON(n),(z)) + TERM##ALG(TWONPLUSONE(n),(z)))
#define N4TERMS(n,z,ALG)  (N2TERMS(TWON(n),(z),ALG)+N2TERMS(TWONPLUSONE(n),(z),ALG))
#define N8TERMS(n,z,ALG)  (N4TERMS(TWON(n),(z),ALG)+N4TERMS(TWONPLUSONE(n),(z),ALG))
#define N16TERMS(n,z,ALG) (N8TERMS(TWON(n),(z),ALG)+N8TERMS(TWONPLUSONE(n),(z),ALG))
#define N32TERMS(n,z,ALG) (N16TERMS(TWON(n),(z),ALG)+N16TERMS(TWONPLUSONE(n),(z),ALG))

// Sum the fist 32*2+16 = 80 terms of a series...
#define PARTIALSUM(z,ALG) N32TERMS(0,(z),ALG)+N32TERMS(1,(z),ALG)+N16TERMS(4,(z),ALG)


int main(void){
  const double PI_TRAD = 4.0L * atan(1.0);
  const double PI_NAIVE = 4.0L * PARTIALSUM(0.999999L,NAIVE);
  const double PI_EULER = 4.0L * PARTIALSUM(0.999999L,EULER);
  printf("pi (math.h) = %10.8f\n",M_PI);
  printf("pi (trad.)  = %10.8f\n",PI_TRAD);
  printf("pi (NAIVE)  = %10.8f\n",PI_NAIVE);
  printf("pi (EULER)  = %10.8f\n",PI_EULER);
}
