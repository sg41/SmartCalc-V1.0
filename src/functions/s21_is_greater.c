#include "stdio.h"
#include "../s21_decimal.h"

// БОЛЬШЕ
int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
    int result = 0;
    s21_decimal dec_first = dec1;
    s21_decimal dec_second = dec2;
    rescale(&dec_first, &dec_second);
    if (get_bit(dec_first, 127) == get_bit(dec_second, 127)) {
        if (get_bit(dec_first, 127) == 0) {
            for (int i = 95; i >= 0; i--) {
                if (get_bit(dec_first, i) != get_bit(dec_second, i)) {
                    if (get_bit(dec_first, i) > get_bit(dec_second, i)) {
                        result = 1;
                    }
                    break;
                }
            }
        } else {
            drop_bit(&dec_first, 127);
            drop_bit(&dec_second, 127);
            result = s21_is_less(dec_first, dec_second);
        }
    } else {
        if (get_bit(dec_first, 127) < get_bit(dec_second, 127)) {
            result = 1;
        }
    }
    return result;
}
