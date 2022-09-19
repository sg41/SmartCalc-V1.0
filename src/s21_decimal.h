#ifndef SRC_S21_DECIMAL_H
#define SRC_S21_DECIMAL_H

typedef struct {
  unsigned int bits[4];
} s21_decimal;

#include "./functions/conversion.h"

s21_decimal init(s21_decimal dec); // инициализирует числом +0
void print_bin(s21_decimal dec); // печеатает dec в бинарной форме: bits[0-3], и value_type 
void set_bit(s21_decimal *dec, int i); // устанавливает в 1 бит под номером i
void drop_bit(s21_decimal *dec, int i); // сбрасывает в 0 бит под номером i
void make_bit(s21_decimal *dec, int i, int bit); // устанавливает значение bit в бит i
int get_bit(s21_decimal dec, int i); // возвращает бит под номером i
void set_negative(s21_decimal *dec); // устанавливает знак "-"
void set_positive(s21_decimal *dec); // устанавливает знак "+"
int is_negative(s21_decimal dec); // возвращает 1 еслизак "-" и 0 если "+"
void set_exp(s21_decimal *dec, unsigned int exp); // устанавливает степень экспоненты (0 - 28)
unsigned int get_exp(s21_decimal dec); // возвращает степень экспоненты
void lshift(s21_decimal *dec); // cдвигает влево на 1 знак, не трогает степень
void rshift(s21_decimal *dec); // cдвигает вправо на 1 знак, не трогает степень
s21_decimal simple_add(s21_decimal dec1, s21_decimal dec2); // суммирует без учета степени
s21_decimal simple_sub(s21_decimal dec1, s21_decimal dec2); // вычитает без учета степени
int simple_is_greater(s21_decimal dec1, s21_decimal dec2); // сравнивает без учета степени
void rescale(s21_decimal *dec1, s21_decimal *dec2);

int s21_mul(s21_decimal dec1, s21_decimal dec2, s21_decimal *result); // умножение
int s21_div(s21_decimal dec1, s21_decimal dec2, s21_decimal *result); // деление
int s21_add(s21_decimal dec1, s21_decimal dec2, s21_decimal *result); // сложение
int s21_sub(s21_decimal dec1, s21_decimal dec2, s21_decimal *result); // вычитание
int s21_mod(s21_decimal dec1, s21_decimal dec2, s21_decimal *result); // взятие остатка

int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_is_less(s21_decimal dec1, s21_decimal dec2); // МЕНЬШЕ
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2); // МЕНЬШЕ-РАВНО
int s21_is_greater(s21_decimal dec1, s21_decimal dec2); // БОЛЬШЕ
int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2); // БОЛЬШЕ-РАВНО
int s21_is_equal(s21_decimal dec1, s21_decimal dec2); // РАВНО
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2); // НЕ РАВНО
int str_of_float_to_decimal(char string[], s21_decimal * dec);

#endif  // SRC_S21_DECIMAL_H
