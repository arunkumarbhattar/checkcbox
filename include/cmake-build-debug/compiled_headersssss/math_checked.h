//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in math.h that                 //
// take pointer arguments.                                             //
//                                                                     //
// These are listed in the same order that they occur in the C11       //
// specification.                                                      //
/////////////////////////////////////////////////////////////////////////

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <math.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __MATH_CHECKED_H
#define __MATH_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

double frexp(double value, int *exp : itype(_TPtr<int>));
float frexpf(float value, int *exp : itype(_TPtr<int>));
long double frexpl(long double value, int *exp : itype(_TPtr<int>));

double modf(double value, double *iptr : itype(_TPtr<double>));
float modff(float value, float *iptr : itype(_TPtr<float>));
long double modfl(long double value,
                  long double *iptr : itype(_TPtr<long double>));

double remquo(double x, double y, int *quo : itype(_TPtr<int>));
float remquof(float x, float y, int *quo : itype(_TPtr<int>));
long double remquol(long double x, long double y, int *quo : itype(_TPtr<int>));

double nan(const char *t : itype(_TNt_array_ptr<const char>));
float nanf(const char *t : itype(_TNt_array_ptr<const char>));
long double nanl(const char *t : itype(_TNt_array_ptr<const char>));

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C
