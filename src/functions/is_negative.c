#include "stdio.h"
#include "../s21_decimal.h"

// возвращает 1 еслизак "-" и 0 если "+"
int is_negative(s21_decimal dec) {
    return get_bit(dec, 127);
}
