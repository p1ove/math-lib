#ifndef S21_MATH_H
#define S21_MATH_H

#include <ctype.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#define ACCURACY 500
#define EPSILON 1e-06

#define S21_PI 3.14159265358979323846264338327950288
#define S21_EXP 2.7182818284590452353602874713526624
#define S21_EPS 1e-6

#define S21_INF 1.0 / 0.0
#define S21_NAN 0.f / 0.f

//Макросы, использующие встроенные функции компилятора GCC
#define is_fin(x) \
  __builtin_isfinite(x)  //Макрос для проверки, является ли значение x конечным
                         //(не является бесконечностью или NaN)
#define is_nan(x)  \
  __builtin_isnan( \
      x)  //Макрос для проверки, является ли значение x NaN (Not a Number).
#define is_inf(x) \
  __builtin_isinf(x)  //Макрос для проверки, является ли значение x
                      //бесконечностью (положительной или отрицательной).

int s21_abs(int x);
long double s21_fabs(double x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_sqrt(double x);
long double s21_exp(double x);
long double s21_pow(double base, double exp);
long double s21_factorial(int n);
long double s21_log(double x);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_atan(double x);
long double s21_strange_atan(double x);
long double s21_tan(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_fmod(double x, double y);

#endif  // S21_MATH_H
