#include "stdio.h"
#include "../s21_decimal.h"

// сравнивает без учета степени
int simple_is_greater(s21_decimal dec1, s21_decimal dec2) {
    int result = 0;

    for (int i = 95; i >= 0; i--) {
        if (get_bit(dec1, i) != get_bit(dec2, i)) {
            if (get_bit(dec1, i) > get_bit(dec2, i)) {
                result = 1;
            }
            break;
        }
    }

    return result;
}
