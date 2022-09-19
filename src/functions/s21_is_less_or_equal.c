#include "stdio.h"
#include "../s21_decimal.h"

// МЕНЬШЕ-РАВНО
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
    return !s21_is_greater(dec1, dec2);
}
