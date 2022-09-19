#include "stdio.h"
#include "../s21_decimal.h"

// умножение
int s21_mul(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
    int err = 0;
    int overflow = 0;
    *result = init(*result);

    (is_negative(dec1) ^ is_negative(dec2)) ? set_negative(result) : set_positive(result);
    int exp = get_exp(dec1) + get_exp(dec2);
    if (exp > 28) {
        overflow = 1;
    } else {
        set_exp(result, exp);
    }

    for (int i = 0; i < 96; i++) {
        if (get_bit(dec1, i)) *result = simple_add(*result, dec2);
        lshift(&dec2);
        if (overflow) set_bit(&dec1, 126);
        if (get_bit(*result, 95)) overflow = 1;
    }

    if (get_bit(*result, 126)) {
        if (is_negative(*result)) {
            err = 2;
        } else {
            err = 1;
        }
    }

    return err;
}
