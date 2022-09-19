#include "stdio.h"
#include "../s21_decimal.h"

// возвращает бит под номером i
int get_bit(s21_decimal dec, int i) {
    unsigned int mask = 0x00000001;
    mask = mask << i % 32;
    dec.bits[i/32] = dec.bits[i/32] & mask;
    return !!dec.bits[i/32];
}
