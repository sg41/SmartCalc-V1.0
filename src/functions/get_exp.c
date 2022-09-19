#include "stdio.h"
#include "../s21_decimal.h"

// возвращает степень экспоненты
unsigned int get_exp(s21_decimal dec) {
    unsigned int mask = 0x00FF0000;
    dec.bits[3] = dec.bits[3] & mask;

    return dec.bits[3] >> 16;
}
