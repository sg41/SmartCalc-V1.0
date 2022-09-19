#include "stdio.h"
#include "../s21_decimal.h"

// устанавливает степень экспоненты (0 - 28)
void set_exp(s21_decimal *dec, unsigned int exp) {
    unsigned int mask = 0x80000000;

    if (exp <= 28) {
        dec->bits[3] = dec->bits[3] & mask;
        mask = exp << 16;
        dec->bits[3] = dec->bits[3] | mask;
    }
}
