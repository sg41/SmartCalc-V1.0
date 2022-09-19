#include "stdio.h"
#include "../s21_decimal.h"

// устанавливает знак "-"
void set_negative(s21_decimal *dec) {
    set_bit(dec, 127);
}
