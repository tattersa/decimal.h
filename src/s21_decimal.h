#ifndef _SRC_DECIMAL_LIBRARY_H_
#define SRC_DECIMAL_LIBRARY_H_
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum arithmetic_errors {
  PLUS_INFINITY = 1,
  MINUS_INFINITY_OR_BELLOW_EPS = 2,
  DIVIDE_BY_ZERO = 3
};

enum convertation_errors { OK = 0, ERROR = 1 };

enum comparison_outputs { FALSE = 0, TRUE = 1 };

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[20];
} s21_decimal_extended;

/* //Арифметические операторы */
int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result); // сложение
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result); // вычитание
int s21_mul(s21_decimal a, s21_decimal b,
            s21_decimal *result); // умножение
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result); // деление
int s21_mod(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result); // остаток от деления

/* // Операторы сравнения */
int s21_is_less(s21_decimal, s21_decimal);          // Меньше <
int s21_is_less_or_equal(s21_decimal, s21_decimal); // Меньше или равно <=
int s21_is_greater(s21_decimal, s21_decimal); // Больше >
int s21_is_greater_or_equal(s21_decimal, s21_decimal); // Больше или равно >=
int s21_is_equal(s21_decimal, s21_decimal);            // Равно ==
int s21_is_not_equal(s21_decimal, s21_decimal); // Не равно !=

/* // Преобразователи */
int s21_from_int_to_decimal(int src, s21_decimal *dst);     // Из int
int s21_from_float_to_decimal(float src, s21_decimal *dst); // Из float
int s21_from_decimal_to_int(s21_decimal src, int *dst);     // В int
int s21_from_decimal_to_float(s21_decimal src, float *dst); // В float

/* // Другие функции */
int s21_floor(s21_decimal src,
              s21_decimal *result); //  Округляет указанное Decimal число до
                                    //  ближайшего целого числа в сторону
                                    //  отрицательной бесконечности

int s21_round(
    s21_decimal src,
    s21_decimal *result); // Округляет Decimal до ближайшего целого числа

int s21_truncate(
    s21_decimal src,
    s21_decimal
        *result); // Возвращает целые цифры указанного Decimal числа;
                  //любые дробные цифры отбрасываются, включая конечные нули

int s21_negate(s21_decimal src,
               s21_decimal *result); // Возвращает результат умножения
                                     // указанного Decimal на -1

int s21_is_less_simple(s21_decimal a, s21_decimal b);
void degree_alignment(s21_decimal *d_a, s21_decimal *d_b);
void shift_right_decimal(s21_decimal *src);
int get_set_sign_from_float(float src, s21_decimal *dst);
int get_bit_long_long_int(const long long int src, int n);
void s21_set_scale(int src, s21_decimal *dst);
void from_long_long_int_to_decimal(long long int src, s21_decimal *dst);
int get_bit_int(const int src, int n);
void shift_left_decimal(s21_decimal *src);
int get_mantissa_min_index(float src);
int get_exp_from_float(float src);
void print_decimal(s21_decimal src);
void s21_set_bit(s21_decimal *src, int n, int sign_value);
int get_bit(s21_decimal src, int n);
void initialize_decimal(s21_decimal *src);
int get_scale(s21_decimal src);
int get_sign(s21_decimal src);
void set_sign(s21_decimal *src, int sign_value);
int s21_add_simple(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_sub_simple(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_div_simple(s21_decimal d_a, s21_decimal d_b, s21_decimal *result);
int s21_mul_simple(s21_decimal a, s21_decimal b, s21_decimal *result);
void shift_left_decimal_extended(s21_decimal_extended *src);
void s21_set_bit_extended(s21_decimal_extended *src, int n, int sign_value);
void initialize_decimal_extended(s21_decimal_extended *src);
void s21_set_bit_extended(s21_decimal_extended *src, int n, int sign_value);
int get_bit_extended(const s21_decimal_extended src, int n);
void print_decimal_extended(s21_decimal_extended src);
void shift_right_decimal_extended(s21_decimal_extended *src);
int s21_add_simple_extended(s21_decimal_extended a, s21_decimal_extended b,
                            s21_decimal_extended *result);
int s21_mul_simple_extended(s21_decimal_extended a, s21_decimal_extended b,
                            s21_decimal_extended *result);
int s21_div_simple_extended(s21_decimal_extended d_a, s21_decimal_extended d_b,
                            s21_decimal_extended *result);
int s21_is_less_simple_extended(s21_decimal_extended a, s21_decimal_extended b);
int s21_is_not_equal_extended(s21_decimal_extended a, s21_decimal_extended b);
int s21_sub_simple_extended(s21_decimal_extended a, s21_decimal_extended b,
                            s21_decimal_extended *result);
int s21_is_less_or_equal_simple(s21_decimal a, s21_decimal b);
int s21_add_simple_for_sub(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_div_simple_no_rounding(s21_decimal d_a, s21_decimal d_b,
                               s21_decimal *result);
int degree_alignment_mod(s21_decimal *d_a, s21_decimal *d_b);
void bank_rounding(s21_decimal_extended *result, s21_decimal_extended *temp);

#endif
