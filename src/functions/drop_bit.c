#include "stdio.h"
#include "../s21_decimal.h"

// сбрасывает в 0 бит под номером i
void drop_bit(s21_decimal *dec, int i) {
    unsigned int mask = 0x00000001;
    if (i >= 0 && i < 128) {
        mask = mask << i % 32;
        mask = ~mask;
        dec->bits[i/32] = dec->bits[i/32] & mask;
    }
}
