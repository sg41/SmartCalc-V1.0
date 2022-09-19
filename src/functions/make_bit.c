#include "stdio.h"
#include "../s21_decimal.h"

// устанавливает значение bit в бит i
void make_bit(s21_decimal *dec, int i, int bit) {
    if (bit == 0 || bit == 1) {
        (bit) ? set_bit(dec, i) : drop_bit(dec, i);
    }
}
