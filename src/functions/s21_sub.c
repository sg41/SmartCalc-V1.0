#include "stdio.h"
#include "../s21_decimal.h"

// разность
int s21_sub(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
    int err = 0;
    rescale(&dec1, &dec2);
    *result = init(*result);

    if (is_negative(dec1) == 0 && is_negative(dec2) == 1) {
        *result = simple_add(dec1, dec2);
    } else if (is_negative(dec1) == 0 && is_negative(dec2) == 0) {
        if (!simple_is_greater(dec2, dec1)) {
            *result = simple_sub(dec1, dec2);
        } else {
            *result = simple_sub(dec2, dec1);
            set_negative(result);
        }
    } else if (is_negative(dec1) == 1 && is_negative(dec2) == 0) {
        *result = simple_add(dec1, dec2);
        set_negative(result);
    } else {
        if (!simple_is_greater(dec1, dec2)) {
            *result = simple_sub(dec2, dec1);
            set_positive(result);
        } else {
            *result = simple_sub(dec1, dec2);
            set_negative(result);
        }
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
