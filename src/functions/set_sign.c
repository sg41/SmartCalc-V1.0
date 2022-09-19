#include "../s21_decimal.h"
#include "stdio.h"

/**
 * @brief Установить знак числа децимал
 * @param dec указатель на число децимал
 * @param sign знак (+1 = '+', -1 = '-')
 */
void set_sign(s21_decimal *dec, int sign) {
  if (sign < 0) {
    set_bit(dec, 127);
  } else {
    drop_bit(dec, 127);
  }
}
