#include "stdio.h"
#include "../s21_decimal.h"

// деление
int s21_div(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
    int err = 0;
    *result = init(*result);
    s21_decimal temp;
    for (int i = 0; i <= 3; i++) temp.bits[i] = 0;
    const s21_decimal dec_10 = {{10, 0, 0, 0}};
    int i = 95;

    // заменить на "равно"
    if (dec2.bits[0] == 0 && dec2.bits[1] == 0 && dec2.bits[2] == 0) err = 3;

    while (get_bit(dec1, i) == 0 && i >=0) i--;

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

    (is_negative(dec1) ^ is_negative(dec2)) ? set_negative(result) : set_positive(result);
    int exp = get_exp(dec1) - get_exp(dec2);
    while (exp < 0) {
        s21_mul(*result, dec_10, result);
        exp++;
    }
    set_exp(result, exp);

    return err;
}
