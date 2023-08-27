#include "s21_decimal.h"

/* int main() { */

/* return 0; */
/* } */

int s21_div_simple(s21_decimal d_a, s21_decimal d_b, s21_decimal *result) {
  initialize_decimal(result);
  int sign_a = get_sign(d_a);
  int sign_b = get_sign(d_b);
  set_sign(&d_a, 0);
  set_sign(&d_b, 0);
  s21_decimal d_buff_1;
  initialize_decimal(&d_buff_1);
  d_buff_1.bits[0] = d_a.bits[0];
  d_buff_1.bits[1] = d_a.bits[1];
  d_buff_1.bits[2] = d_a.bits[2];
  d_buff_1.bits[3] = d_a.bits[3];
  /* printf("%s\n", "d_buff_1:    "); */
  /* print_decimal(d_buff_1); */
  /* printf("\n"); */
  initialize_decimal(result);
  s21_decimal zero;
  initialize_decimal(&zero);
  /* print_decimal(d_a); */
  /* printf("\n"); */
  int max_bit_a = 0;
  int max_bit_b = 0;
  for (int i = 0; i < 96; i++) {
    if (get_bit(d_a, i) == 1) {
      max_bit_a = i;
    }
    if (get_bit(d_b, i) == 1) {
      max_bit_b = i;
    }
  }
  int k = max_bit_b;
  for (int i = 0; i < max_bit_a - max_bit_b; i++) {
    shift_left_decimal(&d_b);
  }
  if (s21_is_less_simple(d_a, d_b)) {
    shift_right_decimal(&d_b);
    k++;
  }

  /* print_decimal(d_a); */
  /* printf("\n"); */
  while (k <= max_bit_a) {
    if (s21_is_not_equal(d_a, zero)) {
      s21_sub_simple(d_a, d_b, &d_a);
      /* print_decimal(d_a); */
      /* printf("\n"); */
      if (s21_is_not_equal(*result, zero)) {
        shift_left_decimal(result);
        s21_set_bit(result, 0, 1);
      } else {
        s21_set_bit(result, 0, 1);
      }
    }
    shift_left_decimal(&d_a);
    k++;

    while (s21_is_less_simple(d_a, d_b) && (k <= max_bit_a)) {
      if (get_bit(d_a, 95) != 1) {
        shift_left_decimal(&d_a);
        shift_left_decimal(result);
      } else {
        shift_right_decimal(&d_b);
        shift_left_decimal(result);
      }
      k++;
    }
  }
  s21_decimal d_buff_2;
  initialize_decimal(&d_buff_2);
  d_buff_2 = *result;
  s21_decimal temp;
  initialize_decimal(&temp);
  temp.bits[0] = 10;
  s21_mul_simple(d_buff_2, temp, &d_buff_2);

  /* printf("%s\n", "d_buff_2:    "); */
  /* print_decimal(d_buff_2); */
  /* printf("\n"); */
  s21_decimal tmp;
  initialize_decimal(&tmp);
  s21_sub_simple(d_buff_1, d_buff_2, &tmp);
  /* printf("%s\n", "remains:    "); */
  /* print_decimal(d_buff_1); */
  /* printf("\n"); */
  /* printf("%d\n", d_buff_1.bits[0]); */
  if (tmp.bits[0] > 5) {
    initialize_decimal(&d_buff_2);
    d_buff_2.bits[0] = 1;
    s21_add_simple(d_buff_2, *result, result);
  }
  if (tmp.bits[0] == 5) {
    s21_div_simple_no_rounding(d_buff_2, temp, &d_buff_2);
    s21_div_simple_no_rounding(d_buff_2, temp, &d_buff_2);
    s21_mul_simple(d_buff_2, temp, &d_buff_2);
    s21_mul_simple(d_buff_2, temp, &d_buff_2);
    s21_sub_simple(d_buff_1, d_buff_2, &d_buff_1);
    s21_sub_simple(d_buff_1, tmp, &d_buff_1);
    s21_div_simple_no_rounding(d_buff_1, temp, &d_buff_1);
    if (d_buff_1.bits[0] % 2 != 0) {
      initialize_decimal(&d_buff_2);
      d_buff_2.bits[0] = 1;
      s21_add_simple(d_buff_2, *result, result);
    }
    /* printf("%s\n", "d_buff_2:    "); */
    /* print_decimal(d_buff_2); */
    /* printf("\n"); */
    /* printf("%s\n", "remains:    "); */
    /* print_decimal(d_buff_1); */
    /* printf("\n"); */
  }
  if (sign_a != sign_b) {
    set_sign(result, 1);
  }
  return 0;
}

int s21_div_simple_no_rounding(s21_decimal d_a, s21_decimal d_b,
                               s21_decimal *result) {
  initialize_decimal(result);
  int sign_a = get_sign(d_a);
  int sign_b = get_sign(d_b);
  set_sign(&d_a, 0);
  set_sign(&d_b, 0);
  initialize_decimal(result);
  s21_decimal zero;
  initialize_decimal(&zero);
  int max_bit_a = 0;
  int max_bit_b = 0;
  for (int i = 0; i < 96; i++) {
    if (get_bit(d_a, i) == 1) {
      max_bit_a = i;
    }
    if (get_bit(d_b, i) == 1) {
      max_bit_b = i;
    }
  }
  int k = max_bit_b;
  for (int i = 0; i < max_bit_a - max_bit_b; i++) {
    shift_left_decimal(&d_b);
  }
  if (s21_is_less_simple(d_a, d_b)) {
    shift_right_decimal(&d_b);
    k++;
  }
  while (k <= max_bit_a) {
    if (s21_is_not_equal(d_a, zero)) {
      s21_sub_simple(d_a, d_b, &d_a);
      if (s21_is_not_equal(*result, zero)) {
        shift_left_decimal(result);
        s21_set_bit(result, 0, 1);
      } else {
        s21_set_bit(result, 0, 1);
      }
    }
    shift_left_decimal(&d_a);
    k++;

    while (s21_is_less_simple(d_a, d_b) && (k <= max_bit_a)) {
      if (get_bit(d_a, 95) != 1) {
        shift_left_decimal(&d_a);
        shift_left_decimal(result);
      } else {
        shift_right_decimal(&d_b);
        shift_left_decimal(result);
      }
      k++;
    }
  }

  if (sign_a != sign_b) {
    set_sign(result, 1);
  }
  return 0;
}

int s21_div_simple_extended(s21_decimal_extended d_a, s21_decimal_extended d_b,
                            s21_decimal_extended *result) {
  initialize_decimal_extended(result);
  s21_decimal_extended zero;
  initialize_decimal_extended(&zero);
  int max_bit_a = 0;
  int max_bit_b = 0;
  for (int i = 0; i < 640; i++) {
    if (get_bit_extended(d_a, i) == 1) {
      max_bit_a = i;
    }
    if (get_bit_extended(d_b, i) == 1) {
      max_bit_b = i;
    }
  }
  int k = max_bit_b;
  for (int i = 0; i < max_bit_a - max_bit_b; i++) {
    shift_left_decimal_extended(&d_b);
  }
  if (s21_is_less_simple_extended(
          d_a, d_b)) {  ///////////////////////////////////////////////////
    shift_right_decimal_extended(&d_b);
    k++;
  }
  s21_decimal_extended d_buff_1;
  initialize_decimal_extended(&d_buff_1);
  s21_decimal_extended d_buff_2;
  initialize_decimal_extended(&d_buff_2);
  while (k <= max_bit_a) {
    if (s21_is_not_equal_extended(
            d_a, zero)) {  ////////////////////////////////////////
      s21_sub_simple_extended(d_a, d_b, &d_a);
      if (s21_is_not_equal_extended(*result, zero)) {
        shift_left_decimal_extended(result);
        s21_set_bit_extended(result, 0, 1);
      } else {
        s21_set_bit_extended(result, 0, 1);
      }
    }
    shift_left_decimal_extended(&d_a);
    k++;

    while (s21_is_less_simple_extended(d_a, d_b) && (k <= max_bit_a)) {
      shift_left_decimal_extended(&d_a);
      k++;
      shift_left_decimal_extended(result);
    }
  }
  return 0;
}

int s21_mul_simple(s21_decimal a, s21_decimal b, s21_decimal *result) {
  initialize_decimal(result);
  for (int i = 0; i < 96; i++) {
    if (get_bit(b, i) == 1) {
      s21_add_simple(*result, a, result);
    }
    shift_left_decimal(&a);
  }
  /* s21_set_scale(s_a + s_b, result); */
  return 0;
}

int s21_mul_simple_extended(s21_decimal_extended a, s21_decimal_extended b,
                            s21_decimal_extended *result) {
  initialize_decimal_extended(result);
  for (int i = 0; i < 640; i++) {
    if (get_bit_extended(b, i) == 1) {
      s21_add_simple_extended(*result, a, result);
    }
    shift_left_decimal_extended(&a);
  }
  /* s21_set_scale(s_a + s_b, result); */
  return 0;
}

int s21_add_simple(s21_decimal a, s21_decimal b, s21_decimal *result) {
  initialize_decimal(result);
  int temp = 0;
  for (int i = 0; i < 96; i++) {
    int res;
    res = get_bit(a, i) + get_bit(b, i) + temp;
    if (res == 3) {
      s21_set_bit(result, i, 1);
      temp = 1;
    } else if (res == 2) {
      s21_set_bit(result, i, 0);
      temp = 1;
    } else {
      s21_set_bit(result, i, get_bit(a, i) + get_bit(b, i) + temp);
      temp = 0;
    }
    /* printf("%s%d%s%d\n", "i:   ", i, "temp:   ", temp); */
    if ((i == 95) && (temp != 0)) {
      initialize_decimal(result);
      if (get_sign(a) == 0) {
        return PLUS_INFINITY;
      } else {
        return MINUS_INFINITY_OR_BELLOW_EPS;
      }
    }
  }
  return OK;
}

int s21_add_simple_for_sub(s21_decimal a, s21_decimal b, s21_decimal *result) {
  initialize_decimal(result);
  int temp = 0;
  for (int i = 0; i < 96; i++) {
    int res;
    res = get_bit(a, i) + get_bit(b, i) + temp;
    if (res == 3) {
      s21_set_bit(result, i, 1);
      temp = 1;
    } else if (res == 2) {
      s21_set_bit(result, i, 0);
      temp = 1;
    } else {
      s21_set_bit(result, i, get_bit(a, i) + get_bit(b, i) + temp);
      temp = 0;
    }
  }
  return OK;
}

int s21_add_simple_extended(s21_decimal_extended a, s21_decimal_extended b,
                            s21_decimal_extended *result) {
  initialize_decimal_extended(result);
  int temp = 0;
  for (int i = 0; i < 640; i++) {
    int res;
    res = get_bit_extended(a, i) + get_bit_extended(b, i) + temp;
    if (res == 3) {
      s21_set_bit_extended(result, i, 1);
      temp = 1;
    } else if (res == 2) {
      s21_set_bit_extended(result, i, 0);
      temp = 1;
    } else {
      s21_set_bit_extended(
          result, i, get_bit_extended(a, i) + get_bit_extended(b, i) + temp);
      temp = 0;
    }
  }
  return 0;
}

int s21_sub_simple(s21_decimal a, s21_decimal b, s21_decimal *result) {
  initialize_decimal(result);
  s21_decimal buff;
  initialize_decimal(&buff);
  int sign = 0;
  if (s21_is_less_simple(a, b)) {
    buff = b;
    b = a;
    a = buff;
    sign = 1;
  }
  for (int i = 0; i < 3; i++) {
    b.bits[i] = ~(b.bits[i]);
  }
  s21_decimal tmp;
  initialize_decimal(&tmp);
  tmp.bits[0] = 1;
  s21_add_simple(tmp, b, &b);
  s21_add_simple_for_sub(a, b, result);
  set_sign(result, sign);
  return 0;
}

int s21_sub_simple_extended(s21_decimal_extended a, s21_decimal_extended b,
                            s21_decimal_extended *result) {
  initialize_decimal_extended(result);
  s21_decimal_extended buff;
  initialize_decimal_extended(&buff);
  for (int i = 0; i < 20; i++) {
    b.bits[i] = ~(b.bits[i]);
  }
  s21_decimal_extended temp;
  initialize_decimal_extended(&temp);
  temp.bits[0] = 1;
  s21_add_simple_extended(b, temp, &b);
  s21_add_simple_extended(a, b, result);
  return 0;
}

int s21_is_less_simple(s21_decimal a, s21_decimal b) {
  int result = 0;
  s21_decimal d_a = a;
  s21_decimal d_b = b;
  if (get_sign(d_a) > get_sign(d_b)) {
    result = 1;
  } else {
    for (int i = 95; i >= 0; i--) {
      if (get_bit(d_a, i) < get_bit(d_b, i)) {
        result = 1;
        break;
      }
      if (get_bit(d_a, i) > get_bit(d_b, i)) {
        result = 0;
        break;
      }
    }
  }
  return result;
}
