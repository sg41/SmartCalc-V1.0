#include "stdio.h"
#include "../s21_decimal.h"

// БОЛЬШЕ-РАВНО
int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2) {
    return !s21_is_less(dec1, dec2);
}
