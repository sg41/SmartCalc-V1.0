#include "stdio.h"
#include "../s21_decimal.h"

// устанавливает в 1 бит под номером i
void set_bit(s21_decimal *dec, int i) {
    if (i >= 0 && i < 128) {
        unsigned int mask = 0x00000001;
        mask = mask << i % 32;
        dec->bits[i/32] = dec->bits[i/32] | mask;
    }
}
