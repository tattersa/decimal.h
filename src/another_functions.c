#include "s21_decimal.h"

/* int main() { */
/*     s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x190000}}; */

/*     print_decimal(decimal_check); */
/*     printf("\n"); */
/*     printf("%s%d\n", "orig: ", get_scale(decimal_check)); */
/*     float f = 2.28401628E-19; */
/*     s21_from_float_to_decimal(f, &decimal_check); */
/*     printf("\n"); */
/*     printf("\n"); */
/*     printf("%s%d\n", "orig: ", get_scale(decimal_check)); */

/*   /1* print_decimal(decimal); *1/ */
/*   /1* printf("\n\n"); *1/ */
/*   print_decimal(decimal_check); */
/*   /1* printf("\n%d\n", get_scale(result)); *1/ */

/*     return 0; */
/* } */

int s21_negate(s21_decimal src, s21_decimal *result) {
  initialize_decimal(result);
  *result = src;
  if (get_sign(src) == 0) {
    set_sign(result, 1);
  } else {
    set_sign(result, 0);
  }
  return 0;
}

int s21_truncate(s21_decimal src, s21_decimal *result) {
  initialize_decimal(result);
  s21_decimal src_buff;
  initialize_decimal(&src_buff);
  src_buff = src;
  int scale = get_scale(src_buff);
  s21_decimal temp;
  initialize_decimal(&temp);
  temp.bits[0] = 10;
  while (scale > 0) {
    s21_div_simple_no_rounding(src_buff, temp, &src_buff);
    scale--;
    s21_set_scale(scale, &src_buff);
  }
  *result = src_buff;

  return OK;
}

int s21_floor(s21_decimal src, s21_decimal *result) {
  initialize_decimal(result);
  int sign = get_sign(src);
  s21_truncate(src, result);
  if (sign == 1) {
    s21_decimal temp;
    initialize_decimal(&temp);
    s21_sub(src, *result, &temp);
    if (temp.bits[0] != 0) {
      initialize_decimal(&temp);
      temp.bits[0] = 1;
      s21_sub(*result, temp, result);
    }
  }
  return OK;
}

int s21_round(s21_decimal src, s21_decimal *result) {
  initialize_decimal(result);
  int sign = get_sign(src);
  s21_truncate(src, result);
  s21_decimal temp;
  initialize_decimal(&temp);
  s21_decimal d_buff_1;
  initialize_decimal(&d_buff_1);
  d_buff_1.bits[0] = 5;
  s21_set_scale(1, &d_buff_1);
  s21_sub(src, *result, &temp);
  /* print_decimal(temp); */
  /* printf("\n"); */
  s21_decimal zero;
  initialize_decimal(&zero);
  if (sign == 0) {
    if (s21_is_greater_or_equal(temp, d_buff_1) &&
        s21_is_not_equal(temp, zero)) {
      initialize_decimal(&temp);
      temp.bits[0] = 1;
      s21_add(*result, temp, result);
    }
  } else {
    set_sign(&d_buff_1, 1);
    if (s21_is_less_or_equal(temp, d_buff_1) && s21_is_not_equal(temp, zero)) {
      /* printf("%s\n", "aaaaaaa"); */
      initialize_decimal(&temp);
      temp.bits[0] = 1;
      s21_sub(*result, temp, result);
    }
  }
  return OK;
}
