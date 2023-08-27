#include "s21_decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
  int result = 0;
  s21_decimal d_a = a;
  s21_decimal d_b = b;
  degree_alignment(&d_a, &d_b);
  int sign_a = get_sign(a);
  int sign_b = get_sign(b);
  if ((sign_a == sign_b) && (sign_a == 1)) {
    set_sign(&d_a, 0);
    set_sign(&d_b, 0);
    result = s21_is_greater(d_a, d_b);
  } else if (sign_a > sign_b) {
    if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
        (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
      result = FALSE;
    } else {
      result = TRUE;
    }
  } else if (sign_a < sign_b) {
    if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
        (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
      result = FALSE;
    } else {
      result = FALSE;
    }
  } else {
    for (int i = 95; i >= 0; i--) {
      if (get_bit(d_a, i) < get_bit(d_b, i)) {
        result = TRUE;
        break;
      }
      if (get_bit(d_a, i) > get_bit(d_b, i)) {
        result = FALSE;
        break;
      }
    }
  }
  return result;
}

int s21_is_less_simple_extended(s21_decimal_extended a,
                                s21_decimal_extended b) {
  int result = 0;
  s21_decimal_extended d_a = a;
  s21_decimal_extended d_b = b;
  for (int i = 639; i >= 0; i--) {
    if (get_bit_extended(d_a, i) < get_bit_extended(d_b, i)) {
      result = 1;
      break;
    }
    if (get_bit_extended(d_a, i) > get_bit_extended(d_b, i)) {
      result = 0;
      break;
    }
  }

  return result;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int result = 0;
  s21_decimal d_a = a;
  s21_decimal d_b = b;
  degree_alignment(&d_a, &d_b);
  int sign_a = get_sign(a);
  int sign_b = get_sign(b);

  if ((sign_a == sign_b) && (sign_a == 1)) {
    set_sign(&d_a, 0);
    set_sign(&d_b, 0);
    result = s21_is_less(d_a, d_b);
  } else if (sign_b > sign_a) {
    if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
        (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
      result = FALSE;
    } else {
      result = TRUE;
    }
  } else if (sign_b < sign_a) {
    if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
        (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
      result = FALSE;
    } else {
      result = FALSE;
    }
  } else {
    for (int i = 95; i >= 0; i--) {
      if (get_bit(d_b, i) < get_bit(d_a, i)) {
        result = TRUE;
        break;
      }
      if (get_bit(d_b, i) > get_bit(d_a, i)) {
        result = FALSE;
        break;
      }
    }
  }
  return result;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int result = 1;
  s21_decimal d_a = a;
  s21_decimal d_b = b;
  degree_alignment(&d_a, &d_b);
  if (get_sign(d_a) != get_sign(d_b)) {
    result = FALSE;
  } else {
    for (int i = 95; i >= 0; i--) {
      if (get_bit(d_a, i) != get_bit(d_b, i)) {
        result = FALSE;
        break;
      }
    }
  }
  if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
      (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
    result = TRUE;
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int result = 1;
  s21_decimal d_a = a;
  s21_decimal d_b = b;
  degree_alignment(&d_a, &d_b);
  int sign_a = get_sign(d_a);
  int sign_b = get_sign(d_b);

  if ((sign_a == sign_b) && (sign_a == 1)) {
    set_sign(&d_a, 0);
    set_sign(&d_b, 0);
    result = s21_is_greater_or_equal(d_a, d_b);
  } else if (sign_b > sign_a) {
    if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
        (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
      result = TRUE;
    } else {
      result = FALSE;
    }
  } else if (sign_b < sign_a) {
    result = TRUE;
  } else {
    for (int i = 95; i >= 0; i--) {
      if (get_bit(d_a, i) > get_bit(d_b, i)) {
        result = FALSE;
        break;
      }
      if (get_bit(d_a, i) < get_bit(d_b, i)) {
        result = TRUE;
        break;
      }
    }
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int result = 1;
  s21_decimal d_a = a;
  s21_decimal d_b = b;
  degree_alignment(&d_a, &d_b);

  int sign_a = get_sign(d_a);
  int sign_b = get_sign(d_b);

  if ((sign_a == sign_b) && (sign_a == 1)) {
    set_sign(&d_a, 0);
    set_sign(&d_b, 0);
    result = s21_is_less_or_equal(d_a, d_b);
  } else if (sign_a > sign_b) {
    if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
        (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
      result = TRUE;
    } else {
      result = FALSE;
    }
  } else if (sign_a < sign_b) {
    if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
        (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
      result = TRUE;
    } else {
      result = TRUE;
    }
  } else {
    for (int i = 95; i >= 0; i--) {
      if (get_bit(d_a, i) < get_bit(d_b, i)) {
        result = FALSE;
        break;
      }
      if (get_bit(d_a, i) > get_bit(d_b, i)) {
        result = TRUE;
        break;
      }
    }
  }
  return result;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  int result = 0;
  s21_decimal d_a = a;
  s21_decimal d_b = b;
  degree_alignment(&d_a, &d_b);
  if (get_sign(d_a) != get_sign(d_b)) {
    result = TRUE;
  } else {
    for (int i = 95; i >= 0; i--) {
      if (get_bit(d_a, i) != get_bit(d_b, i)) {
        result = TRUE;
        break;
      }
    }
  }
  if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
      (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
    result = FALSE;
  }
  return result;
}

int s21_is_not_equal_extended(s21_decimal_extended a, s21_decimal_extended b) {
  int result = 0;
  s21_decimal_extended d_a = a;
  s21_decimal_extended d_b = b;
  for (int i = 639; i >= 0; i--) {
    if (get_bit_extended(d_a, i) != get_bit_extended(d_b, i)) {
      result = 1;
      break;
    }
  }

  return result;
}
