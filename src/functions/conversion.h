#ifndef SRC_FUNCTIONS_S21_CONVERSION_H
#define SRC_FUNCTIONS_S21_CONVERSION_H
#include <float.h>
#include <limits.h>

#include "../s21_decimal.h"

#define SUCCESS 0
#define CONVERTING_ERROR 1
#define SIGN 0x80000000
#define EPSILON 0.0001  // Лучшей точности для флоат достичь пока не могу
#define FLOAT_EQ(x, v) (((v - EPSILON) < x) && (x < (v + EPSILON)))

typedef struct {
  unsigned mantissa : 23;
  unsigned exp : 8;
  unsigned sign : 1;
} floatbits;

typedef union {
  floatbits bits;
  int ui;
  float fl;
} floatint;

typedef struct {
  unsigned long mantissa : 52;
  unsigned exp : 11;
  unsigned sign : 1;
} doublebits;

typedef union {
  doublebits bits;
  long ui;
  double fl;
} doublelong;

void set_sign(s21_decimal *dec, int sign);
int get_sign(s21_decimal dec);
void set_bit_value(s21_decimal *dec, int i, int v);
int abs_copy_sign(long double *val);
long double s21_conversion_round(long double val);
long double get_float_point(long double val, int digits);
double trim_trailing_zero(double *val);
int decimal_digits_count(long double val);
long double s21_conversion_roundn(long double val, int digits);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_double(s21_decimal src, double *dst);

#endif  // SRC_FUNCTIONS_S21_CONVERSION_H
