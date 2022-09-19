#include "stdio.h"
#include "../s21_decimal.h"

// cдвигает влево на 1 знак, не трогает степень
void lshift(s21_decimal *dec) {
    for (int i = 94; i >= 0; i--) {
        make_bit(dec, i + 1, get_bit(*dec, i));
    }
    drop_bit(dec, 0);
}
