#include "../s21_decimal.h"
#include "stdio.h"

/**
 * @brief Возвращает знак числа децимал
 * @param dec число децимал
 * @return +1 = '+', -1 = '-'
 */
int get_sign(s21_decimal dec) {
  int sign;
  if (get_bit(dec, 127) == 1) {
    sign = -1;
  } else {
    sign = 1;
  }
  return sign;
}
