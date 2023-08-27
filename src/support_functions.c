#include "s21_decimal.h"

/* int main() { */

/*     s21_decimal value_1 =  {{2397809911, 86451412, 10, 0}}; */
/*     set_sign(&value_1, 1); */
/*     s21_decimal value_2 = {{193289, 0, 0, 0}}; */
/*     s21_set_scale(14, &value_2); */

/*     s21_decimal result; */
/*     initialize_decimal(&result); */
/*     s21_div(value_1, value_2, &result); */

/*     printf("\n"); */

/*     int scale_1 = get_scale(value_1); */
/*     int scale_2 = get_scale(value_2); */
/*     int scale_3 = get_scale(result); */
/*     /1* int scale_4 = get_scale(expected); *1/ */
/*     printf("%s%d\n", "scale_1:   ", scale_1); */
/*     printf("%s%d\n", "scale_2:   ", scale_2); */
/*     printf("%s%d\n", "scale_3:   ", scale_3); */
/*     /1* printf("%s%d\n", "scale_4:   ", scale_4); *1/ */

/*     print_decimal(value_1); */
/*     printf("\n"); */
/*     print_decimal(value_2); */
/*     printf("\n"); */

/*     print_decimal(result); */
/*     printf("\n"); */
/*     /1* print_decimal(expected); *1/ */
/*     /1* printf("\n"); *1/ */
/*     return 0; */
/* } */

int get_sign(s21_decimal src) {
  int result = get_bit(src, 127);
  return result;
}

void set_sign(s21_decimal *src, int sign_value) {
  s21_set_bit(src, 127, sign_value);
}

void s21_set_scale(int src, s21_decimal *dst) {
  for (int i = 112; i <= 119; i++) {
    if (get_bit_int(src, i - 112) == 1) {
      s21_set_bit(dst, i, 1);
    } else {
      s21_set_bit(dst, i, 0);
    }
  }
}

int get_scale(s21_decimal src) {
  int result = 0;
  for (int i = 112; i <= 119; i++) {
    if (get_bit(src, i) == 1) {
      result = (result | (1 << (i - 112)));
    } else {
      result = (result & ~(1 << (i - 112)));
    }
  }
  if (result > 28) {
    result = 28;
  }
  return result;
}

int get_bit(const s21_decimal src, int n) {
  int result = 0;
  if (((src.bits[n / 32] & (1 << (n % 32))) != 0)) {
    result = 1;
  }
  return result;
}

void s21_set_bit(s21_decimal *src, int n, int sign_value) {
  if (sign_value == 1) {
    src->bits[n / 32] = (src->bits[n / 32] | (1 << (n % 32)));
  } else {
    src->bits[n / 32] = (src->bits[n / 32] & ~(1 << (n % 32)));
  }
}

int get_exp_from_float(float src) {
  unsigned int buff = *(unsigned int *)&src;
  int scale = 0;
  int k = 0;
  for (unsigned int i = 8388608; i != 2147483648; i = i << 1) {
    if (!!(buff & i) == 1) {
      scale += pow(2, k);
    }
    k++;
  }
  scale = scale - 127;
  return scale;
}

int get_mantissa_min_index(float src) {
  int mantissa_min_index = 0;
  int k = 0;
  unsigned int buff = *(unsigned int *)&src;
  for (unsigned int i = 1; i != 8388608; i = i << 1) {
    if (!!(buff & i) == 1) {
      mantissa_min_index = 23 - k;
      break;
    }
    k++;
  }
  return mantissa_min_index;
}

void shift_left_decimal(s21_decimal *src) {
  /* Гниль............ */
  for (int i = 95; i >= 0; i--) {
    s21_set_bit(src, i + 1, get_bit(*src, i));
  }
  s21_set_bit(src, 0, 0);
}

void shift_right_decimal(s21_decimal *src) {
  /* Гниль............ */
  for (int i = 0; i <= 96; i++) {
    s21_set_bit(src, i, get_bit(*src, i + 1));
  }
  s21_set_bit(src, 96, 0);
}

void initialize_decimal(s21_decimal *src) {
  for (int i = 0; i < 128; i++) {
    s21_set_bit(src, i, 0);
  }
}

/* void print_decimal(s21_decimal src) { */
/*   for (int i = 0; i < 128; i++) { */
/*     if (i % 96 == 0) { */
/*       printf("\n"); */
/*     } */
/*     printf("%d", get_bit(src, i)); */
/*   } */
/* } */

int get_bit_int(const int src, int n) {
  int result = 0;
  if (((src & (1 << n)) != 0)) {
    result = 1;
  }
  return result;
}

void degree_alignment(s21_decimal *d_a, s21_decimal *d_b) {
  int scale_a = get_scale(*d_a);
  int scale_b = get_scale(*d_b);
  s21_set_scale(0, d_a);
  s21_set_scale(0, d_b);
  int sign_a = get_sign(*d_a);
  int sign_b = get_sign(*d_b);
  int multiplier = 10;
  s21_decimal d_multiplier;
  initialize_decimal(&d_multiplier);
  s21_from_int_to_decimal(multiplier, &d_multiplier);
  while (scale_a > scale_b) {
    if ((get_bit(*d_b, 95) == 0) && (get_bit(*d_b, 94) == 0) &&
        (get_bit(*d_b, 93) == 0) && (get_bit(*d_b, 92) == 0)) {
      s21_mul_simple(*d_b, d_multiplier, d_b);
      scale_b++;
    } else {
      s21_div_simple(*d_a, d_multiplier, d_a);
      scale_a--;
    }
  }
  while (scale_a < scale_b) {
    if ((get_bit(*d_a, 95) == 0) && (get_bit(*d_a, 94) == 0) &&
        (get_bit(*d_a, 93) == 0) && (get_bit(*d_a, 92) == 0)) {
      s21_mul_simple(*d_a, d_multiplier, d_a);
      scale_a++;
    } else {
      s21_div_simple(*d_b, d_multiplier, d_b);
      scale_b--;
    }
  }
  s21_set_scale(scale_a, d_a);
  s21_set_scale(scale_b, d_b);
  set_sign(d_a, sign_a);
  set_sign(d_b, sign_b);
}

void shift_left_decimal_extended(s21_decimal_extended *src) {
  /* Гниль............ */
  for (int i = 638; i >= 0; i--) {
    s21_set_bit_extended(src, i + 1, get_bit_extended(*src, i));
  }
  s21_set_bit_extended(src, 0, 0);
}

void s21_set_bit_extended(s21_decimal_extended *src, int n, int sign_value) {
  if (sign_value == 1) {
    src->bits[n / 32] = (src->bits[n / 32] | (1 << (n % 32)));
  } else {
    src->bits[n / 32] = (src->bits[n / 32] & ~(1 << (n % 32)));
  }
}

void initialize_decimal_extended(s21_decimal_extended *src) {
  for (int i = 0; i < 640; i++) {
    s21_set_bit_extended(src, i, 0);
  }
}

int get_bit_extended(const s21_decimal_extended src, int n) {
  int result = 0;
  if (((src.bits[n / 32] & (1 << (n % 32))) != 0)) {
    result = 1;
  }
  return result;
}

/* void print_decimal_extended(s21_decimal_extended src) { */
/*   for (int i = 0; i < 640; i++) { */
/*     if (i % 96 == 0) { */
/*       printf("\n"); */
/*     } */
/*     printf("%d", get_bit_extended(src, i)); */
/*   } */
/* } */

void shift_right_decimal_extended(s21_decimal_extended *src) {
  for (int i = 0; i < 639; i++) {
    s21_set_bit_extended(src, i, get_bit_extended(*src, i + 1));
  }
  s21_set_bit_extended(src, 639, 0);
}

void bank_rounding(s21_decimal_extended *result, s21_decimal_extended *temp) {
  s21_decimal_extended multiplier;
  initialize_decimal_extended(&multiplier);
  multiplier.bits[0] = 10;
  s21_decimal_extended result_buff;
  initialize_decimal_extended(&result_buff);

  s21_mul_simple_extended(*result, multiplier, &result_buff);
  s21_sub_simple_extended(*temp, result_buff, temp);
  initialize_decimal_extended(&result_buff);
  result_buff.bits[0] = 1;

  if (temp->bits[0] > 5) {
    s21_add_simple_extended(*result, result_buff, result);
  }
  if (temp->bits[0] == 5) {
    result_buff = *result;
    s21_div_simple_extended(result_buff, multiplier, &result_buff);
    s21_mul_simple_extended(result_buff, multiplier, &result_buff);
    s21_sub_simple_extended(*result, result_buff, temp);
    if (temp->bits[0] % 2 != 0) {
      initialize_decimal_extended(&result_buff);
      result_buff.bits[0] = 1;
      s21_add_simple_extended(*result, result_buff, result);
    }
  }
}
