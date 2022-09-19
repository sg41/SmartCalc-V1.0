#include "stdio.h"
#include "../s21_decimal.h"

// приводит к одной степени
void rescale(s21_decimal *dec1, s21_decimal *dec2) {
    s21_decimal *big_exp;
    s21_decimal *small_exp;
    s21_decimal dec_10 = {{10, 0, 0, 0}};

    if (get_exp(*dec1) > get_exp(*dec2)) {
        big_exp = dec1;
        small_exp = dec2;
    } else {
        big_exp = dec2;
        small_exp = dec1;
    }

    while (get_bit(*big_exp, 95) == 0
    && get_exp(*big_exp) != get_exp(*small_exp)
    && get_exp(*small_exp) <= 28) {
        s21_mul(*small_exp, dec_10, small_exp);
        set_exp(small_exp, get_exp(*small_exp) + 1);
    }

    while (get_exp(*big_exp) != get_exp(*small_exp)) {
        s21_div(*big_exp, dec_10, big_exp);
        set_exp(big_exp, get_exp(*big_exp) - 1);
    }
}
