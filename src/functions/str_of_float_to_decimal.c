#include <stdio.h>
#include <string.h>
#include "../s21_decimal.h"

int str_of_float_to_decimal(char string[], s21_decimal * dec) {
    *dec = init(*dec);
    s21_decimal temp = {{0, 0, 0, 0}};
    s21_decimal dec_10 = {{10, 0, 0, 0}};
    size_t l = strlen(string);
    size_t exp = 0, k = 0;
    for (size_t i = 0; i < l; i ++) {
        long int c = (long int)string[l - 1 - i];
        if (c > 47 && c < 58) {
            temp = init(temp);
            temp.bits[0] = c - 48;
            for (size_t j = 1; j <= i - k; j ++) {
                s21_mul(temp, dec_10, &temp);
            }
            s21_add(temp, *dec, dec);
        }
        if (c == 46) {
            exp = i;
            k = 1;
        }
    }
    if (string[0] == 45) {
        set_bit(dec, 127);
    }
    set_exp(dec, exp);
return 1;
}
