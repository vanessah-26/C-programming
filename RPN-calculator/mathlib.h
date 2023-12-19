#ifndef __MATHLIB_H__
#define __MATHLIB_H__

#define EPSILON 1e-14
/*
 * Compute the absolute value of x.
 */
double Abs(double x);

/*
 * Compute the square root of x >= 0.
 */
double Sqrt(double x);

/*
 * Compute the sine of x.
 */
double Sin(double x);

/*
 * Compute the cosine of x.
 */
double Cos(double x);

/*
 * Compute the tangent of x.
 *
 * NOTE:
 * Tan(M_PI / 2) will not be undefined for two reasons:
 * (1) the IEEE 754 double precision standard cannot perfectly represent
 *     pi in binary; and
 * (2) the Taylor-Maclaurin series used to approximate Cos(pi/2) will not
 *     converge to 0.
 *  Therefore, it will instead to converge to a very, very small
 *  number resulting in a very, very large value of Tan(pi/2).
 */
double Tan(double x);

#endif
