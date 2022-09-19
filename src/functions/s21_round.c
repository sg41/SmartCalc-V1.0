#include "stdio.h"
#include "../s21_decimal.h"

// отбрасывает дробную часть
int s21_round(s21_decimal value, s21_decimal *result) {
    const s21_decimal dec_10 = {{10, 0, 0, 0}};
    const s21_decimal dec_1 = {{1, 0, 0, 0}};
    s21_decimal mod;
    *result = init(*result);

    while (get_exp(value)) {
        s21_mod(value, dec_10, &mod);
        set_exp(&value, get_exp(value) - 1);
        s21_div(value, dec_10, &value);
        if ( mod.bits[0] > 5 || (mod.bits[0] == 5 && value.bits[0] % 2) )
            value = simple_add(value, dec_1);
    }

    *result = value;

    return 0;
}
