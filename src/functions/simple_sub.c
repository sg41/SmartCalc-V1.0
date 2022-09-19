#include "stdio.h"
#include "../s21_decimal.h"

// вычитает без учета степени
s21_decimal simple_sub(s21_decimal dec1, s21_decimal dec2) {
    int overflow = 0;
    // int temp = 0;

    for (int i = 0; i < 96; i++) {
        int temp = get_bit(dec1, i) - get_bit(dec2, i) - overflow;
        overflow = (temp < 0) ? 1 : 0;
        (temp % 2) ? set_bit(&dec1, i) : drop_bit(&dec1, i);
    }

    return dec1;
}
