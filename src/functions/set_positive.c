#include "stdio.h"
#include "../s21_decimal.h"

// устанавливает знак "+"
void set_positive(s21_decimal *dec) {
    drop_bit(dec, 127);
}
