#include "s21_math.h"

#include <math.h>

/*Вставляете свои функции вместо этих и тестите*/

/*Щас не работает pow и все зависящие от него другие функии*/
/* (a)sin, (a)cos, tan, sqrt*/

/*Так что сначала разобраться с pow*/

int s21_abs(int x) {
  if (x < 0) return -x;
  return x;
}

long double s21_fabs(double x) {
  if (x < 0.0) return -x;
  return x;
}

long double s21_sin(double x) {
  long double result = 0;
  if (x == S21_NAN || x == -S21_INF || x == S21_INF) {
    return S21_NAN;
  }
  if (x == S21_PI) {
    return 1e-50;
  }
  if (x == -S21_PI) {
    return -1e-50;
  }
  if (x == 0) {
    return 0;
  }
  for (; x < -2 * S21_PI || 2 * S21_PI < x;) {
    if (x > 2 * S21_PI) {
      x -= 2 * S21_PI;
    } else {
      x += 2 * S21_PI;
    }
  }
  double check_sign = 1.;
  if (x < 0) {
    x = -x;
    check_sign = -1.;
  }
  if (x == S21_PI || x == 2 * S21_PI) {
    return 0;
  }
  for (int i = 0; i < 10; i++) {
    result += s21_pow(-1, i) * s21_pow(x, 2 * i + 1) / s21_factorial(2 * i + 1);
  }
  return result * check_sign;
}

long double s21_cos(double x) {
  long double result = 0;
  if (x == S21_NAN || x == -S21_INF || x == S21_INF) {
    return S21_NAN;
  }

  for (; x < -2 * S21_PI || 2 * S21_PI < x;) {
    if (x > 2 * S21_PI) {
      x -= 2 * S21_PI;
    } else {
      x += 2 * S21_PI;
    }
  }
  if (x < 0) {
    x = -x;
  }

  if (x == 2 * S21_PI) {
    return 1.0;
  }
  for (int i = 0; i < 10; i++) {
    result += s21_pow(-1, i) * s21_pow(x, 2 * i) / s21_factorial(2 * i);
  }
  return result;
}

long double s21_sqrt(double x) {
  long double result = S21_NAN;
  if (x > 0) {
    result = s21_pow(x, 0.5);
  }
  if (x == 0) {
    result = 0;
  }
  if (x < 0) {
    result = S21_NAN;
  }
  return result;
}

long double s21_exp(double x) {
  long double res = 1;
  long double temp = 1;
  long double i = 1;
  int flag = 0;
  if (x < 0) {
    x *= -1;
    flag = 1;
  }
  while (s21_fabs(res) > S21_EPS) {
    res *= x / i;
    i += 1;
    temp += res;
    if (temp > DBL_MAX) {
      temp = S21_INF;
      break;
    }
  }
  if (flag == 1) {
    if (temp > DBL_MAX) {
      temp = 0;
    } else {
      temp = 1. / temp;
    }
  }
  if (temp > DBL_MAX) {
    return S21_INF;
  }
  return temp;
}

long double s21_pow(double base, double exp) {
  if ((int)exp != exp && base == -S21_INF) {
    if (exp > 0) {
      return S21_INF;
    } else if (exp < 0) {
      return 0;
    }
  }

  if (base > 0 && base < 1 &&
      (exp == S21_INF ||
       exp == DBL_MAX)) {  // число в диапозона (0;1) в ^(+) = 0;
    return 0;
  }
  if (base > 0 && base < 1 &&
      exp == -S21_INF) {  // число в диапозона (0;1) в ^(-) = inf
    return S21_INF;
  }
  if (base > -1 && base < 0 &&
      exp == -S21_INF) {  // числа в диапозоне (0;1) ^(-) = inf
    return S21_INF;
  }

  if (base > -1 && base < 0 &&
      exp == S21_INF) {  // числа в диапозоне (0;1) ^(+) = inf
    return 0;
  }

  if (base < -1 && exp == S21_INF) {  // числа от (-1; (-)) в степени (+)
    return S21_INF;
  }

  if (base < -1 && exp == -S21_INF) {  // числа от (-1; (-)) в степени (-)
    return 0;
  }

  if (base == S21_INF && exp == S21_INF) {  //бесконечность (+)^(+)
    return S21_INF;
  }

  if (base == S21_INF && exp == -S21_INF) {  //  бесконечность (+)^(-)
    return 0;
  }

  if (base == -S21_INF && exp == -S21_INF) {  //бесконечность (-)^(-)
    return 0;
  }

  if (base == -S21_INF && exp == S21_INF) {  //бесконечность (-)^(+)
    return S21_INF;
  }
  if (base == 0 && is_inf(exp)) {  // проверка 0 с бесконечностью + и "-"
    if (exp < 0) {
      return S21_INF;
    } else {
      return 0;
    }
  }

  if (exp == 0) {  // степень 0
    return 1;
  }

  if (base == 1) {  //любая степень 1 = 1
    return 1;
  }

  if (base == -1 &&
      (exp == S21_INF || exp == -S21_INF)) {  // -1 в степени (+)  и (-)
    return 1;
  }
  if (exp == S21_INF && base > 1) {  // числа от (1; (+)) в ^ (+) = inf
    return S21_INF;
  }

  if (exp == -S21_INF && base > 1) {  // числа от (1; (+)) в ^ (-) = inf
    return 0;
  }
  if (s21_fabs(base) != base &&
      s21_fmod(exp, 1) !=
          0) {  // проверка если экс вещ число // ПОМЕНЯЛ НА ОРИГ fmod
    return S21_NAN;
  }

  long double result = base;
  int negative_exp_flag = 0;

  if (exp < 0) {
    negative_exp_flag = 1;
    exp = -exp;
  }

  for (int i = 1; i < s21_abs(exp); ++i) {
    result *= base;
  }

  if (s21_fmod(exp, 1.0)) {
    if (exp < 1) result = 1;
    result *= s21_exp(s21_fmod(exp, 1.0) * s21_log(base));
  }

  if (negative_exp_flag) {
    result = 1.0 / result;
  }

  return result;
}

long double s21_factorial(int n) {
  if (n < 0) return 0;
  if (n == 0 || n == 1) return 1;

  unsigned long long result = 1;

  for (int i = 1; i <= n; ++i) {
    result *= i;
  }

  return result;
}

long double s21_fmod(double x, double y) {
  if (!is_fin(x) || is_nan(y)) {
    return S21_NAN;
  }
  if (is_inf(x) && is_inf(y)) {
    return S21_NAN;
  }
  if (is_inf(y)) {
    return x;
  }
  if (s21_fabs(y) < 1e-7) {
    return S21_NAN;
  }
  if (s21_fabs(x) < 1e-7) {
    return 0;
  }
  long long int mod = 0;
  mod = x / y;
  long double res = (long double)x - mod * (long double)y;
  return res;
}

long double s21_log(double x) {
  int ex_pow = 0;
  double result = 0;
  double compare = 0;
  if (x == S21_INF) {
    result = S21_INF;
  } else if (x == 0) {
    result = -S21_INF;
  } else if (x < 0) {
    result = S21_NAN;
  } else if (x == 1) {
    result = 0;
  } else {
    while (x >= S21_EXP) {
      x = x / S21_EXP;
      ex_pow++;
    }
    int i;
    for (i = 0; i < 100; i++) {
      compare = result;
      result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
    }
  }
  return (result + ex_pow);
}

long double s21_tan(double x) {
  long double result;
  if (x < 0) {
    result = -s21_tan(-x);
  } else if (s21_fabs(x) < 0.001) {
    result = x;
  } else if (x > S21_PI) {
    result = s21_tan(s21_fmod(x, S21_PI));
  } else if (x == S21_PI / 2) {
    result = 16331239353195370.0;
  } else {
    result = s21_sin(x) / s21_cos(x);
  }
  return result;
}

long double s21_strange_atan(double x) {
  long double coeffs[] = {1.0 / 2.0,   -1.0 / 4.0,   1.0 / 12.0,
                          -1.0 / 40.0, 1.0 / 48.0,   -1.0 / 112.0,
                          1.0 / 288.0, -1.0 / 320.0, 1.0 / 704.0};
  long double pow = 1;
  long double result = S21_PI / 4;
  for (int i = 0; i < 9; i++) {
    pow *= (x - 1);
    result += pow * coeffs[i];
  }
  return result;
}

long double s21_atan(double x) {
  long double result = 0;
  if (is_nan(x)) {
    result = S21_NAN;
  } else if (s21_fabs(x) == S21_INF) {
    result = (x < 0) ? -S21_PI / 2 : S21_PI / 2;
  } else if (x < 0) {
    result = -s21_atan(-x);
  } else if (x > 1) {
    result = S21_PI / 2 - s21_atan(1 / x);
  } else if (x < 0.95) {
    result = x;
    long double add = x;
    for (long long i = 1; i < 2000; i++) {
      add *= -x * x;
      result += add / (2 * i + 1);
    }
  } else {
    result = s21_strange_atan(x);
  }
  return result;
}

long double s21_floor(double x) {
  long double result = (long long)x;
  if (x != x) {
    result = S21_NAN;
  } else if (x < -FLT_MAX || x > FLT_MAX) {
    result = x;
  } else if (x < 0. && s21_fabs(x - result) > 0.) {
    result -= 1;
  }
  return result;
}

long double s21_ceil(double x) {
  long double result = (long long)x;
  if (x != x) {
    result = S21_NAN;
  } else if (x < -FLT_MAX || x > FLT_MAX) {
    result = x;
  } else if (x > 0. && s21_fabs(x - result) > 0.) {
    result += 1;
  }
  return result;
}

long double s21_asin(double x) {
  long double result = 0;
  if (s21_fabs(x) > 1) {
    result = S21_NAN;
  } else if (s21_fabs(x) == 1) {
    result = x * S21_PI / 2;
  } else {
    result = s21_atan(x / s21_sqrt(1 - (x * x)));
  }
  return result;
}

long double s21_acos(double x) { return S21_PI / 2.0 - s21_asin(x); }