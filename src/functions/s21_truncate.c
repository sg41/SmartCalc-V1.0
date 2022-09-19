#include "stdio.h"
#include "../s21_decimal.h"

// отбрасывает дробную часть
int s21_truncate(s21_decimal value, s21_decimal *result) {
    const s21_decimal dec_10 = {{10, 0, 0, 0}};
    *result = init(*result);

    while (get_exp(value)) {
        set_exp(&value, get_exp(value) - 1);
        s21_div(value, dec_10, &value);
    }

    *result = value;

    return 0;
}
