#include "stdio.h"
#include "../s21_decimal.h"

// инициализирует числом +0
s21_decimal init(s21_decimal dec) {
    for (int i = 0; i <= 3; i++) dec.bits[i] = 0x00000000;

    return dec;
}
