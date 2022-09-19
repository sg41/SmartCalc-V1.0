#include "stdio.h"
#include "../s21_decimal.h"

// взятие остатка
int s21_mod(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
    int err = 0;
    *result = init(*result);
    s21_decimal temp = {{0, 0, 0, 0}};
    int i = 95;

    if (dec2.bits[0] == 0 && dec2.bits[1] == 0 && dec2.bits[2] == 0) err = 3;

    while (get_bit(dec1, i) == 0 && i >= 0) i--;

    while (i >= 0) {
        lshift(&temp);
        lshift(result);
        make_bit(&temp, 0, get_bit(dec1, i));
        if (!simple_is_greater(dec2, temp)) {
            temp = simple_sub(temp, dec2);
            set_bit(result, 0);
        }
        i--;
    }

    *result = temp;

    if (is_negative(dec1)) {
        set_negative(result);
    } else {
        set_positive(result);
    }
    return err;
}
