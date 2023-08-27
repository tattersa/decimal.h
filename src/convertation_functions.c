#include "s21_decimal.h"
#define S21_MAX_UINT 4294967295

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  initialize_decimal(dst);
  if (src < 0) {
    set_sign(dst, 1);
    src = -src;
  }
  dst->bits[0] = src;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  *dst = 0;
  int sign = get_sign(src);
  int exp = get_scale(src);
  /* printf("%s%d\n", "exp:  ", exp); */
  s21_decimal src_buff;
  initialize_decimal(&src_buff);
  src_buff.bits[0] = src.bits[0];
  src_buff.bits[1] = src.bits[1];
  src_buff.bits[2] = src.bits[2];
  src_buff.bits[3] = src.bits[3];
  if ((exp > 0) && ((src.bits[1] != 0) || (src.bits[2] != 0))) {
    /* print_decimal(src_buff); */
    /* printf("\n"); */
    int k = 0;
    s21_decimal d_multiplier;
    initialize_decimal(&d_multiplier);
    d_multiplier.bits[0] = 10;
    while (((src_buff.bits[1] != 0) || (src_buff.bits[2] != 0))) {
      /* printf("%d\n", k); */
      s21_div_simple_no_rounding(src_buff, d_multiplier, &src_buff);
      /* print_decimal(src_buff); */
      /* printf("\n"); */
      exp--;
      s21_set_scale(exp, &src_buff);
      k++;
      if (exp < 0) {
        return ERROR;
      }
    }
    /* s21_decimal temp; */
    /* initialize_decimal(&temp); */
    /* temp.bits[0] = 1; */
    /* for (int i = 0; i < k; i++) { */
    /*     s21_mul(temp, d_multiplier, &temp); */
    /* } */
    /* s21_div_simple(src, temp, &src); */
    /* exp = get_scale(src); */
    /* s21_set_scale(exp - k, &src); */
  }

  if ((src_buff.bits[1] != 0) || (src_buff.bits[2] != 0)) {
    return ERROR;
  }

  /* print_decimal(src_buff); */
  /* printf("\n\n"); */
  unsigned int result = src_buff.bits[0];
  /* printf("%u\n", result); */

  exp = get_scale(src_buff);
  /* printf("%s%d\n", "exp:  ", exp); */
  result /= pow(10, exp);
  if (sign == 1) {
    result = -result;
  }
  *dst = (unsigned int)result;
  return OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  initialize_decimal(dst);
  int scale = get_exp_from_float(src);
  int mantissa_min_index = -get_mantissa_min_index(src);
  if (scale > 95) {
    return ERROR;
  }
  if (scale < -94) {
    return ERROR;
  }
  s21_decimal_extended d_buff_1;
  initialize_decimal_extended(&d_buff_1);
  int multiplier = 0;
  multiplier = scale + mantissa_min_index;
  s21_decimal_extended mantissa_buffer;
  initialize_decimal_extended(&mantissa_buffer);
  mantissa_buffer.bits[0] = 1;
  for (int i = 0; i < scale - multiplier; i++) {
    shift_left_decimal_extended(&mantissa_buffer);
  }
  unsigned int j = 8388608;
  unsigned int buff = *(unsigned int *)&src;
  for (int i = -1; i >= -23; i--) {
    j = j >> 1;
    if (!!(buff & j) == 1) {
      d_buff_1.bits[0] = 1;
      for (int k = 0; k < i + scale - multiplier; k++) {
        shift_left_decimal_extended(&d_buff_1);
      }
      s21_add_simple_extended(mantissa_buffer, d_buff_1, &mantissa_buffer);
      initialize_decimal_extended(&d_buff_1);
    }
  }
  initialize_decimal_extended(&d_buff_1);
  s21_decimal_extended d_buff_2;
  initialize_decimal_extended(&d_buff_2);
  s21_decimal result;
  initialize_decimal(&result);
  /////////////////////////////////////////////////
  if (multiplier >= 0) {
    for (int i = 0; i < multiplier; i++) {
      shift_left_decimal_extended(&mantissa_buffer);
    }
    result.bits[0] = mantissa_buffer.bits[0];
    result.bits[1] = mantissa_buffer.bits[1];
    result.bits[2] = mantissa_buffer.bits[2];
    result.bits[3] = mantissa_buffer.bits[3];
    *dst = result;  ///////////////////////
  } else {
    d_buff_2 = mantissa_buffer;
    initialize_decimal_extended(&d_buff_1);
    d_buff_1.bits[0] = 5;
    for (int i = 0; i < -multiplier; i++) {
      s21_mul_simple_extended(d_buff_1, d_buff_2, &d_buff_2);
    }
    initialize_decimal_extended(&d_buff_1);
    s21_decimal_extended d_buff_3;
    initialize_decimal_extended(&d_buff_3);
    d_buff_1.bits[0] = 10;
    d_buff_3.bits[0] = 1;
    for (int i = 0; i < -multiplier - 28; i++) {
      s21_mul_simple_extended(d_buff_1, d_buff_3, &d_buff_3);
    }
    if (-multiplier - 28 > 0) {
      s21_div_simple_extended(d_buff_2, d_buff_3, &d_buff_2);
    }
    result.bits[0] = d_buff_2.bits[0];
    result.bits[1] = d_buff_2.bits[1];
    result.bits[2] = d_buff_2.bits[2];
    result.bits[3] = d_buff_2.bits[3];
    if (multiplier < -28) {
      scale = 28;
    } else {
      scale = -multiplier;
    }
    s21_decimal temp;
    initialize_decimal(&temp);
    temp.bits[0] = 10;
    s21_set_scale(scale, &result);
  }
  if (src < 0) {
    set_sign(&result, 1);
  }
  *dst = result;
  return OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  *dst = 0;
  int sign = get_sign(src);
  int exp = get_scale(src);
  long double result = 0;
  for (int i = 0; i < 96; i++) {
    if (get_bit(src, i) == 1) {
      result += pow(2, i);
    }
  }
  result /= pow(10, exp);
  if (sign == 1) {
    result = -result;
  }
  *dst = (float)result;
  return 0;
}
