#include "conversion.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

/**
 * @brief Конвертирует цисло из int в decimal
 * @param src Число типа int
 * @param dst указатель на decimal
 * @return Результат работы, где 0 - это SUCCESS, а 1 - это CONVERTING ERROR
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  char result = SUCCESS;
  if (dst) {
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
    // dst->value_type = 0;
    if (src < 0) {
      set_sign(dst, -1);
      src *= -1;
    }
    dst->bits[0] = src;
    // dst->value_type = s21_NORMAL_VALUE;
  } else {
    result = CONVERTING_ERROR;
  }
  return result;
}

/**
 * @brief Конвертирует цисло из decimal в int
 * @param src Число decimal
 * @param dst Указатель на int
 * @return Результат работы, где 0 - это SUCCESS, а 1 - это CONVERTING ERROR
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = CONVERTING_ERROR;
  // !if (src.value_type == s21_NORMAL_VALUE) {
  *dst = src.bits[0];
  *dst *= get_sign(src);
  *dst /= (int)pow(10, get_exp(src));
  result = SUCCESS;
  // !}
  return result;
}

// Возвращает знак числа и делает число положительным
int abs_copy_sign(long double *val) {
  int sign = copysignl(1, *val);
  if (sign < 0) *val = -*val;
  return sign;
}

// Округление до целого (не делает бухгалтерское округление)
long double s21_conversion_round(long double val) {
  long double q, iptr;
  int sign = 1;
  if (val < 0) {
    sign = -1;
    val = -val;
  } else {
  }
  q = modfl(val, &iptr);
  if (q > 0.5) iptr++;
  return iptr * sign;
}

// возвращает целое число равное дробной части float-числа
// длиной digits цифр
long double get_float_point(long double val, int digits) {
  long double iptr;
  // убираем знак - у дробной части его не должно быть
  abs_copy_sign(&val);
  val = modfl(val, &iptr);

  while (digits-- > 0) {
    val = val * 10;
  }
  // Округление
  iptr = s21_conversion_round(val);

  return (iptr);
}

//
double trim_trailing_zero(double *val) {
  long double iptr;
  int zero_count = 0;
  while (modfl(*val, &iptr) == 0 && iptr >= 1) {
    *val /= 10;
    zero_count++;
  }
  if (zero_count != 0) *val *= 10;
  return zero_count == 0 ? 0 : zero_count - 1;
}

int decimal_digits_count(long double val) {
  int count = 0;
  while (val >= 1) {
    val /= 10;
    count++;
  }
  return count;
}

// округляет чило с точностью digits знаков после запятой
long double s21_conversion_roundn(long double val, int digits) {
  long double iptr, d;
  int sign = abs_copy_sign(&val);
  modfl(val, &iptr);
  d = get_float_point(val, digits);
  if (d >= powl(10, digits)) {
    iptr++;
  } else {
    iptr += d / powl(10, digits);
  }
  return iptr * sign;
}

/**
 * @brief Делает перевод из float в децимал
 * @param src Значение float
 * @param dst Значение децимал
 * @return Результат работы, где 0 - это SUCCESS, а 1 - это CONVERTING ERROR
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
  // !dst->value_type = s21_NORMAL_VALUE;
  int result = CONVERTING_ERROR;  //, sign = abs_copy_sign((long double *)&src);
  floatint src_copy;
  src_copy.fl = src;
  int exp = src_copy.bits.exp - 127;
  int sign = src_copy.bits.sign;
  // src_copy.bits.sign = 0;

  if (dst && src != 0) {
    float temp = src_copy.fl;
    int off = 0;
    // for (; off < 28 && (int)temp / (1 << 22) == 0; temp *= 10, off++) {
    for (; off < 28 && abs((int)temp) < (1 << 22); temp *= 10, off++) {
    }
    temp = round(temp);
    if (off <= 28 && (exp > -96 && exp < 96)) {
      floatint mant;
      temp = (float)temp;
      // off -= trim_trailing_zero(&temp);
      for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {
      }
      mant.fl = temp;
      exp = mant.bits.exp - 127;
      dst->bits[exp / 32] |= 1 << exp % 32;
      for (int i = exp - 1, j = 22; j >= 0; i--, j--)
        if ((mant.ui & (1 << j)) != 0) dst->bits[i / 32] |= 1 << i % 32;
      set_exp(dst, off);
      set_sign(dst, sign == 0 ? +1 : -1);
      result = SUCCESS;
    }
  }
  return result;
}

/**
 * @brief Перевод из децимал в float
 * @param src Число децимал
 * @param dst указатель на float
 * @return Результат работы, где 0 - это SUCCESS, а 1 - это CONVERTING ERROR
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = CONVERTING_ERROR;
  // !if (src.value_type == s21_NORMAL_VALUE) {
  double temp = 0;
  for (int i = 0; i < 96; i++) {
    temp += (get_bit(src, i) * pow(2, i));
  }
  int exp = get_exp(src);
  *dst = temp / pow(10, exp);
  *dst *= get_sign(src);

  result = SUCCESS;
  //  !}
  return result;
}
/**
 * @brief Перевод из децимал в double
 * @param src Число децимал
 * @param dst указатель на double
 * @return Результат работы, где 0 - это SUCCESS, а 1 - это CONVERTING ERROR
 */
int s21_from_decimal_to_double(s21_decimal src, double *dst) {
  int result = CONVERTING_ERROR;
  // !if (src.value_type == s21_NORMAL_VALUE) {
  double temp = 0;
  for (int i = 0; i < 96; i++) {
    temp += (get_bit(src, i) * pow(2, i));
  }
  int exp = get_exp(src);
  *dst = temp / pow(10, exp);
  *dst *= get_sign(src);

  result = SUCCESS;
  //  !}
  return result;
}
