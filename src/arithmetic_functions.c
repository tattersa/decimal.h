#include "s21_decimal.h"

/* int main() { */
/*     s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}}; */

/*     s21_decimal decimal_check = {{0x68DB9, 0x0, 0x0, 0x80000000}}; */

/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     print_decimal(decimal); */
/*     printf("\n"); */
/*     print_decimal(result); */
/*     printf("\n"); */
/*     print_decimal(decimal_check); */
/*     printf("\n"); */
/*     printf("%s%d\n", "my scale: ", get_scale(decimal)); */
/*     printf("%s%d\n", "orig:  : ", get_scale(decimal_check)); */

/*     return 0; */
/* } */

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initialize_decimal(result);
  int sign_a = get_sign(value_1);
  int sign_b = get_sign(value_2);
  int res = 0;
  s21_decimal d_a = value_1;
  s21_decimal d_b = value_2;
  degree_alignment(&d_a, &d_b);
  if (sign_a == sign_b) {
    /* printf("%d\n", 3); */
    res = s21_add_simple(d_a, d_b, result);
    set_sign(result, get_sign(d_a));
  } else if (sign_b > sign_a) {
    /* printf("%d\n", 2); */
    set_sign(&d_b, 0);
    res = s21_sub_simple(d_a, d_b, result);
  } else {
    /* printf("%d\n", 1); */
    set_sign(&d_a, 0);
    res = s21_sub_simple(d_b, d_a, result);
  }
  s21_set_scale(get_scale(d_a), result);

  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initialize_decimal(result);
  int res = 0;
  s21_decimal d_a;
  s21_decimal d_b;
  d_a = value_1;
  d_b = value_2;
  degree_alignment(&d_a, &d_b);
  int sign_a = get_sign(value_1);
  int sign_b = get_sign(value_2);
  if (sign_b > sign_a) {
    set_sign(&d_b, 0);
    res = s21_add_simple(d_a, d_b, result);
  } else if (sign_a > sign_b) {
    res = s21_add_simple(d_a, d_b, result);
    set_sign(result, 1);
  } else if (sign_a == 0) {
    res = s21_sub_simple(d_a, d_b, result);
  } else if (sign_a == 1) {
    res = s21_sub_simple(d_b, d_a, result);
  }
  s21_set_scale(get_scale(d_a), result);

  return res;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initialize_decimal(result);
  int sign_a = get_sign(value_1);
  int sign_b = get_sign(value_2);
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  int scale_a = get_scale(value_1);
  int scale_b = get_scale(value_2);
  s21_set_scale(0, &value_1);
  s21_set_scale(0, &value_2);
  s21_decimal_extended zero_ex;
  initialize_decimal_extended(&zero_ex);
  s21_decimal zero;
  initialize_decimal(&zero);
  if (s21_is_equal(value_2, zero)) {
    return DIVIDE_BY_ZERO;
  }
  if (s21_is_equal(value_1, zero)) {
    initialize_decimal(result);
    return OK;
  }

  int max_bit_a = 0;
  int max_bit_b = 0;
  for (int i = 0; i < 96; i++) {
    if (get_bit(value_1, i) == 1) {
      max_bit_a = i;
    }
    if (get_bit(value_2, i) == 1) {
      max_bit_b = i;
    }
  }
  int k = 0;
  int is_less = 0;
  if (s21_is_less_simple(value_2, value_1)) {
    k = max_bit_b;
    for (int i = 0; i < max_bit_a - max_bit_b; i++) {
      shift_left_decimal(&value_2);
    }
    if (s21_is_less(value_1, value_2)) {
      shift_right_decimal(&value_2);
      k++;
    }
  } else {
    is_less = 1;
    while (s21_is_less_simple(value_1, value_2)) {
      if (get_bit(value_1, 95) != 1) {
        shift_left_decimal(&value_1);
      } else {
        shift_right_decimal(&value_2);
      }
      k++;
    }
  }
  s21_decimal_extended d_buff_1;
  initialize_decimal_extended(&d_buff_1);
  s21_decimal_extended d_buff_2;
  initialize_decimal_extended(&d_buff_2);
  int param = 120 + k;
  while (k <= param) {
    if (s21_is_not_equal(value_1, zero)) {
      s21_sub_simple(value_1, value_2, &value_1);
      if (s21_is_not_equal_extended(d_buff_2, zero_ex)) {
        shift_left_decimal_extended(&d_buff_2);
        s21_set_bit_extended(&d_buff_2, 0, 1);
      } else {
        s21_set_bit_extended(&d_buff_2, 0, 1);
      }
      shift_left_decimal(&value_1);
      k++;
    }
    if (s21_is_equal(value_1, zero) && (k > max_bit_a)) {
      break;
    }
    while (s21_is_less(value_1, value_2) && (k <= param)) {
      if (get_bit(value_1, 95) != 1) {
        shift_left_decimal(&value_1);
        shift_left_decimal_extended(&d_buff_2);
      } else {
        shift_right_decimal(&value_2);
        shift_left_decimal_extended(&d_buff_2);
      }
      k++;
    }
  }
  int fractional_part_max_index = 0;
  if (is_less) {
    fractional_part_max_index = k - 1;
  } else {
    fractional_part_max_index = k - max_bit_a - 1;
  }

  /* printf("%d\n", fractional_part_max_index); */
  if (fractional_part_max_index + scale_a - scale_b < 200) {
    /* printf("%d\n", fractional_part_max_index + scale_a - scale_b); */
    /* printf("%d\n", fractional_part_max_index); */
    int scale = 0;
    if (fractional_part_max_index > 0) {
      s21_decimal_extended temp_ext;
      initialize_decimal_extended(&temp_ext);
      temp_ext = d_buff_2;
      d_buff_1.bits[0] = 5;
      for (int i = 0; i < fractional_part_max_index; i++) {
        s21_mul_simple_extended(d_buff_2, d_buff_1, &d_buff_2);
      }
      /* print_decimal_extended(d_buff_2); */
      /* printf("\n"); */
      initialize_decimal_extended(&d_buff_1);
      d_buff_1.bits[0] = 10;
      s21_decimal_extended d_buff_4;
      initialize_decimal_extended(&d_buff_4);
      int round = 0;
      int a = 0;
      while ((d_buff_2.bits[3] != 0) || (d_buff_2.bits[4] != 0) ||
             (d_buff_2.bits[5] != 0) || (d_buff_2.bits[6] != 0) ||
             (d_buff_2.bits[7] != 0) || (d_buff_2.bits[8] != 0) ||
             (d_buff_2.bits[9] != 0) || (d_buff_2.bits[10] != 0) ||
             (d_buff_2.bits[11] != 0) || (d_buff_2.bits[12] != 0) ||
             (d_buff_2.bits[13] != 0) || (d_buff_2.bits[14] != 0)) {
        round = 1;
        d_buff_4 = d_buff_2;
        s21_div_simple_extended(d_buff_2, d_buff_1, &d_buff_2);
        a++;
      }
      s21_decimal_extended d_buff_3;
      initialize_decimal_extended(&d_buff_3);
      s21_mul_simple_extended(d_buff_2, d_buff_1, &d_buff_3);
      s21_sub_simple_extended(d_buff_4, d_buff_3, &d_buff_3);
      scale = fractional_part_max_index - a + scale_a - scale_b;
      if (round == 1) {
        if (d_buff_3.bits[0] >= 5) {
          if ((d_buff_2.bits[0] == UINT_MAX) &&
              (d_buff_2.bits[1] == UINT_MAX) &&
              (d_buff_2.bits[2] == UINT_MAX) && (scale <= 0)) {
            if (sign_a == sign_b) {
              return PLUS_INFINITY;
            } else {
              return MINUS_INFINITY_OR_BELLOW_EPS;
            }
          }
          initialize_decimal_extended(&d_buff_3);
          d_buff_3.bits[0] = 1;
          s21_add_simple_extended(d_buff_2, d_buff_3, &d_buff_2);
        }
      }
    } else {
      scale = scale_a - scale_b;
    }
    s21_decimal_extended d_buff_3;
    initialize_decimal_extended(&d_buff_3);
    d_buff_3.bits[0] = 10;
    while (scale < 0) {
      if ((get_bit_extended(d_buff_2, 95) == 0) &&
          (get_bit_extended(d_buff_2, 94) == 0) &&
          (get_bit_extended(d_buff_2, 93) == 0) &&
          (get_bit_extended(d_buff_2, 92) == 0)) {
        s21_mul_simple_extended(d_buff_2, d_buff_3, &d_buff_2);
        scale++;
      } else {
        if (sign_a == sign_b) {
          return PLUS_INFINITY;
        } else {
          return MINUS_INFINITY_OR_BELLOW_EPS;
        }
      }
    }
    result->bits[0] = d_buff_2.bits[0];
    result->bits[1] = d_buff_2.bits[1];
    result->bits[2] = d_buff_2.bits[2];
    result->bits[3] = d_buff_2.bits[3];
    while (scale > 28) {
      s21_decimal temp;
      initialize_decimal(&temp);
      temp.bits[0] = 10;
      s21_div_simple(*result, temp, result);
      scale--;
    }
    s21_set_scale(scale, result);
    if (sign_a == sign_b) {
      set_sign(result, 0);
    } else {
      set_sign(result, 1);
    }
  } else {
    initialize_decimal(result);
  }
  return 0;
}

int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result) {
  initialize_decimal(result);
  int sign = 0;
  if (get_sign(a) == get_sign(b)) {
    sign = 0;
  } else {
    sign = 1;
  }
  int scale = get_scale(a) + get_scale(b);
  int res = 0;
  s21_decimal_extended result_ext;
  s21_decimal_extended a_ext;
  s21_decimal_extended b_ext;
  initialize_decimal_extended(&result_ext);
  initialize_decimal_extended(&a_ext);
  initialize_decimal_extended(&b_ext);
  a_ext.bits[0] = a.bits[0];
  a_ext.bits[1] = a.bits[1];
  a_ext.bits[2] = a.bits[2];
  b_ext.bits[0] = b.bits[0];
  b_ext.bits[1] = b.bits[1];
  b_ext.bits[2] = b.bits[2];
  for (int i = 0; i < 96; i++) {
    if (get_bit_extended(b_ext, i) == 1) {
      s21_add_simple_extended(result_ext, a_ext, &result_ext);
    }
    shift_left_decimal_extended(&a_ext);
  }
  s21_decimal_extended multiplier;
  initialize_decimal_extended(&multiplier);
  multiplier.bits[0] = 10;
  s21_decimal_extended temp;
  initialize_decimal_extended(&temp);
  s21_decimal_extended result_buff;
  initialize_decimal_extended(&result_buff);
  if ((result_ext.bits[3] != 0) || (result_ext.bits[4] != 0) ||
      (result_ext.bits[5] != 0) || (result_ext.bits[6] != 0) ||
      (result_ext.bits[7] != 0) || (result_ext.bits[8] != 0) ||
      (result_ext.bits[9] != 0) || (result_ext.bits[10] != 0) ||
      (result_ext.bits[11] != 0) || (result_ext.bits[12] != 0) ||
      (result_ext.bits[13] != 0) || (result_ext.bits[14] != 0)) {
    while ((result_ext.bits[3] != 0) || (result_ext.bits[4] != 0) ||
           (result_ext.bits[5] != 0) || (result_ext.bits[6] != 0) ||
           (result_ext.bits[7] != 0) || (result_ext.bits[8] != 0) ||
           (result_ext.bits[9] != 0) || (result_ext.bits[10] != 0) ||
           (result_ext.bits[11] != 0) || (result_ext.bits[12] != 0) ||
           (result_ext.bits[13] != 0) || (result_ext.bits[14] != 0)) {
      temp = result_ext;
      s21_div_simple_extended(result_ext, multiplier, &result_ext);
      scale--;
      if (scale < 0) {
        if (sign == 1) {
          res = MINUS_INFINITY_OR_BELLOW_EPS;
        } else {
          res = PLUS_INFINITY;
        }
      }
    }
    bank_rounding(&result_ext, &temp);
  }

  if (scale > 28) {
    while (scale > 28) {
      temp = result_ext;
      s21_div_simple_extended(result_ext, multiplier, &result_ext);
      scale--;
    }
    bank_rounding(&result_ext, &temp);
  }
  result->bits[0] = result_ext.bits[0];
  result->bits[1] = result_ext.bits[1];
  result->bits[2] = result_ext.bits[2];

  set_sign(result, sign);
  s21_set_scale(scale, result);
  return res;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initialize_decimal(result);
  if (s21_is_equal(value_2, *result)) {
    return DIVIDE_BY_ZERO;
  }
  s21_decimal_extended temp;
  initialize_decimal_extended(&temp);
  int sign_1 = get_sign(value_1);
  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  s21_decimal_extended value_1_buff;
  s21_decimal_extended value_2_buff;
  s21_decimal_extended multiplier;
  initialize_decimal_extended(&multiplier);
  initialize_decimal_extended(&value_1_buff);
  initialize_decimal_extended(&value_2_buff);
  value_1_buff.bits[0] = value_1.bits[0];
  value_1_buff.bits[1] = value_1.bits[1];
  value_1_buff.bits[2] = value_1.bits[2];

  value_2_buff.bits[0] = value_2.bits[0];
  value_2_buff.bits[1] = value_2.bits[1];
  value_2_buff.bits[2] = value_2.bits[2];
  multiplier.bits[0] = 10;
  while (scale_2 > scale_1) {
    s21_mul_simple_extended(value_1_buff, multiplier, &value_1_buff);
    scale_1++;
  }
  while (scale_1 > scale_2) {
    s21_mul_simple_extended(value_2_buff, multiplier, &value_2_buff);
    scale_2++;
  }
  s21_div_simple_extended(value_1_buff, value_2_buff, &temp);
  s21_mul_simple_extended(value_2_buff, temp, &temp);
  if (sign_1 == 0) {
    s21_sub_simple_extended(value_1_buff, temp, &temp);
  } else if (sign_1 == 1) {
    s21_sub_simple_extended(value_1_buff, temp, &temp);
    set_sign(result, 1);
  }
  result->bits[0] = temp.bits[0];
  result->bits[1] = temp.bits[1];
  result->bits[2] = temp.bits[2];

  s21_set_scale(scale_1, result);
  return OK;
}
