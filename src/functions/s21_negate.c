#include "stdio.h"
#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    *result = init(*result);

    if (is_negative(value)) {
        set_positive(&value);
    } else {
        set_negative(&value);
    }

    *result = value;

    return 0;
}
