#include "stdio.h"
#include "../s21_decimal.h"

// cдвигает вправо на 1 знак, не трогает степень
void rshift(s21_decimal *dec) {
    for (int i = 1; i < 96; i++) {
        make_bit(dec, i - 1, get_bit(*dec, i));
    }
    drop_bit(dec, 95);
}
