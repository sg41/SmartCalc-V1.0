#include "stdio.h"
#include "../s21_decimal.h"

// РАВНО
int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
    int result = 1;
    s21_decimal dec_first = dec1;
    s21_decimal dec_second = dec2;
    s21_decimal dec_result;
    for (int i = 0; i <= 3; i++) dec_result.bits[i] = 0;
    s21_decimal dec_0 = init(dec_result);
    s21_sub(dec_first, dec_second, &dec_result);
    for (int i = 95; i >= 0; i--) {
        if (get_bit(dec_result, i) != get_bit(dec_0, i)) {
            result = 0;
            break;
        }
    }
    return result;
}
