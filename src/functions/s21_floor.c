#include "stdio.h"
#include "../s21_decimal.h"

// отбрасывает дробную часть
int s21_floor(s21_decimal value, s21_decimal *result) {
    const s21_decimal dec_1 = {{1, 0, 0, 0}};
    *result = init(*result);

    s21_truncate(value, result);

    if (is_negative(value) && get_exp(value)) *result = simple_add(*result, dec_1);

    return 0;
}
