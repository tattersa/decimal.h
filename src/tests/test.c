#include <check.h>
#include <limits.h>

#include "../s21_decimal.h"
#define S21_TRUE 1
#define S21_FALSE 0
#define U_MAX_INT 4294967295 // 0b11111111111111111111111111111111
#define S21_MAX_UINT 4294967295
#define MAX_INT 2147483647 // 0b01111111111111111111111111111111
#define CONVERTERS_S21_TRUE 0
#define CONVERTERS_S21_FALSE 1
#define EXPONENT_MINUS_1 2147549184  // 0b10000000000000010000000000000000
#define EXPONENT_PLUS_1 65536        // 0b00000000000000010000000000000000
#define EXPONENT_PLUS_2 196608       // 0b00000000000000110000000000000000
#define EXPONENT_MINUS_28 2149318656 // 0b10000000000111000000000000000000
#define EXPONENT_PLUS_28 1835008     // 0b00000000000111000000000000000000
#define MINUS 2147483648             // 0b10000000000000000000000000000000

#define ASSERT_DECIMAL_EQ                                                      \
  for (size_t i = 0; i < 4; i++) {                                             \
    ck_assert_msg(result.bits[i] == expected.bits[i], "[%zu] %u != %u", i,     \
                  result.bits[i], expected.bits[i]);                           \
  }

START_TEST(test_s21_add_1) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(1899999, &test_value_1);
  s21_from_int_to_decimal(100001, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 2000000);
}
END_TEST

START_TEST(test_s21_add_2) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(199421, &test_value_1);
  s21_from_int_to_decimal(-4433, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 199421 + (-4433));
}
END_TEST

START_TEST(test_s21_add_3) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  float result_int;
  s21_from_float_to_decimal(-199421, &test_value_1);
  s21_from_float_to_decimal(4433, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_int);
  ck_assert_float_eq(result_int, -199421 + 4433);
}
END_TEST

START_TEST(test_s21_add_4) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  float result_int;
  s21_from_float_to_decimal(-199421, &test_value_1);
  s21_from_float_to_decimal(-4433, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_int);
  ck_assert_float_eq(result_int, -199421 + (-4433));
}
END_TEST

START_TEST(test_s21_add_5) {
  s21_decimal test_value_1 = {{10000, 3, 10, 0}};
  s21_decimal test_value_2 = {{5000, 2, 500, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 10000 + 5000);
  ck_assert_uint_eq(result_dec.bits[1], 3 + 2);
  ck_assert_uint_eq(result_dec.bits[2], 10 + 500);
}
END_TEST

START_TEST(test_s21_add_6) {
  s21_decimal test_value_1 = {{4294967295, 10, 10, 0}};
  s21_decimal test_value_2 = {{1, 2, 20, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 0);
  ck_assert_uint_eq(result_dec.bits[1], 13);
  ck_assert_uint_eq(result_dec.bits[2], 30);
}
END_TEST

START_TEST(test_s21_add_7) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal test_value_2 = {{1, 1, 1, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result = s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_add_9) {
  s21_decimal test_value_1 = {{123, 0, 0, 262144}};
  s21_decimal test_value_2 = {{37, 0, 0, 196608}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 493);
  ck_assert_uint_eq(result_dec.bits[3], 262144);
}
END_TEST

START_TEST(test_s21_add_11) {
  s21_decimal src1, src2, result;
  float a = -1234;
  float b = 1.234;
  float res_origin = a + b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_12) {
  s21_decimal src1, src2, result;
  float a = -1234;
  float b = -1.234;
  float res_origin = a + b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_13) {
  s21_decimal src1, src2, result;
  float a = -1234;
  float b = -221.234;
  float res_origin = a + b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_14) {
  s21_decimal src1, src2, result;
  float a = -9403;
  float b = 0.00234;
  float res_origin = a + b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_15) {
  s21_decimal src1, src2, result;
  float a = -940.3;
  float b = 0.000234;
  float res_origin = a + b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_16) {
  s21_decimal src1, src2, result;
  float a = -0.9403;
  float b = 0.000234;
  float res_origin = a + b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_17) {
  s21_decimal src1, src2, result;
  float a = -0.9403;
  float b = 2.0234;
  float res_origin = a + b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_18) {
  s21_decimal src1, src2, result;
  float a = -0.9403;
  float b = -112.0234;
  float res_origin = a + b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_19) {
  s21_decimal src1, src2, result;
  float a = -0.94e03;
  float b = -112.0234;
  float res_origin = a + b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_20) {
  s21_decimal src1, src2, result;
  float a = -0.94e03;
  float b = -112.0e2;
  float res_origin = a + b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_21) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0x1C0000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xF;
  src1.bits[0] = 0x67E4FEEF;
  src2.bits[3] = 0x1C0000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xFF;
  src2.bits[0] = 0x67E4FFFF;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x1C0000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x10E;
  result_origin.bits[0] = 0xCFC9FEEE;
  s21_add(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_add_22) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0x30000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xFF;
  src1.bits[0] = 0x67E4F;
  src2.bits[3] = 0x60000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xEA;
  src2.bits[0] = 0x67E4F;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x60000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x3E502;
  result_origin.bits[0] = 0x1963E2E7;
  s21_add(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_add_23) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967290, 0}};
  s21_decimal test_value_2 = {{100, 0, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 0);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_24) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967290, 0}};
  s21_decimal test_value_2 = {{5, 1, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 42949672);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_25) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967290, 0}};
  s21_decimal test_value_2 = {{5, 0, 1, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 4123168603);
  ck_assert_int_eq(result_dec.bits[1], 42949672);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_26) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967290, 0}};
  s21_decimal test_value_2 = {{165, 0, 1, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 4123168605);
  ck_assert_int_eq(result_dec.bits[1], 42949672);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(add_1) {
  s21_decimal value_1 = {{55555, 0, 0, 0}};
  s21_decimal value_2 = {{66666, 0, 0, 262144}};
  s21_decimal result;
  s21_decimal expected = {{555616666, 0, 0, 262144}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(add_2) {
  s21_decimal value_1 = {{5555, 0, 0, 2147483648}};
  s21_decimal value_2 = {{333333333, 0, 0, 327680}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{222166667, 0, 0, 2147811328}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(add_3) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 327680}};
  s21_decimal value_2 = {{UINT_MAX, 100, 0, 2148139008}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4294867297, 99898, 0, 655360}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(add_4) {
  s21_decimal value_1 = {{UINT_MAX, 613566756, 0, 2147811328}};
  s21_decimal value_2 = {{UINT_MAX, 214748364, 0, 2147745792}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4294967285, 2761050406, 0, 2147811328}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(add_5) {
  s21_decimal value_1 = {{346456, 53345, 0, 2147942400}};
  s21_decimal value_2 = {{567567, 3456567, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{567220544, 3456513655, 0, 458752}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(add_6) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, 2147483647, 1638400}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, 0, 2148466688}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4153960755, 858993458, 785251635, 2149056512}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}

START_TEST(add_7) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 1638400}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 2148466688}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{2701727008, 2450292888, UINT_MAX, 2148466688}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}

START_TEST(add_8) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX}};
  s21_decimal value_2 = {{54, 0, 0, 0}};
  set_sign(&value_2, 1);
  s21_set_scale(2, &value_2);
  s21_decimal result = {{0}};
  s21_decimal expected = {{4294967295, UINT_MAX, UINT_MAX}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}

START_TEST(add_9) {
  s21_decimal value_1 = {{4294967294, UINT_MAX, UINT_MAX, 0}};
  s21_decimal value_2 = {{15, 0, 0, 65536}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(add_10) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 2147483648}};
  s21_decimal value_2 = {{1, 0, 0, 2147483648}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 2147483648}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(add_11) {
  s21_decimal value_1 = {{98564, 1247856, 98541, 2147483648}};
  s21_decimal value_2 = {{875, 651214965, 831764, 131072}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{9855525, 3768537931, 9022335, 2147614720}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(add_12) {
  s21_decimal value_1 = {{124, 0, 2014589674, 458752}};
  s21_decimal value_2 = {{875, 651214965, 831764, 131072}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{172673693, 1558211807, 851910048, 327680}};
  int status = s21_add(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(add_test_1) {
  int num1 = 42;
  int num2 = 30;
  int sum_int = 72;
  s21_decimal a, b;
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
  ck_assert_int_eq(s21_add(a, b, &res_dec), 0);
}
END_TEST

START_TEST(add_test_2) {
  int num1 = 1000;
  int num2 = 2000;
  int sum_int = 3000;
  s21_decimal a, b;
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(add_test_3) {
  int num1 = 0;
  int num2 = 0;
  int sum_int = 0;
  s21_decimal a, b;
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(add_test_4) {
  int num1 = -15;
  int num2 = 5;
  int sum_int = -10;
  s21_decimal a, b;
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(add_test_5) {
  int num1 = 11115;
  int num2 = 5;
  int sum_int = 11120;
  s21_decimal a, b;
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(add_test_6) {
  int num1 = -1;
  int num2 = -10;
  int sum_int = -11;
  s21_decimal a, b;
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(add_test_7) {
  s21_decimal src1, src2;
  int a = -1234;
  int b = 234;
  int res_origin = -1000;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(add_test_8) {
  s21_decimal src1, src2;
  int a = -9403;
  int b = 234;
  int res_origin = -9169;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(add_test_9) {
  s21_decimal src1, src2;
  int a = 9403;
  int b = 202;
  int res_origin = 9605;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(add_test_10) {
  s21_decimal src1, src2;
  int a = 450;
  int b = -50;
  int res_origin = 400;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(add_test_11) {
  s21_decimal src1, src2;
  float num1 = 7.25;
  float num2 = 9.5;
  float res_origin = 16.75;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_12) {
  s21_decimal src1, src2;
  int num1 = -1234;
  float num2 = 1.234;
  float res_origin = -1232.766;
  s21_from_int_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_13) {
  s21_decimal src1, src2;
  int num1 = -1234;
  float num2 = -1.234;
  float res_origin = -1235.234;
  s21_from_int_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_14) {
  s21_decimal src1, src2;
  float num1 = -94;
  float num2 = 0.00234;
  float res_origin = num1 + num2;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_15) {
  s21_decimal src1, src2;
  float num1 = -940.3;
  float num2 = 0.000234;
  float res_origin = -940.299766;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_16) {
  s21_decimal src1, src2;
  float num1 = -0.9403;
  float num2 = 0.000234;
  float res_origin = -0.940066;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_17) {
  s21_decimal src1, src2;
  float num1 = -0.9403;
  float num2 = 2.0234;
  float res_origin = num1 + num2;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_18) {
  s21_decimal src1, src2;
  float num1 = -0.9403;
  float num2 = -112.0234;
  float res_origin = -112.9637;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_19) {
  s21_decimal src1, src2;
  float num1 = -0.94e03;
  float num2 = -112.0234;
  float res_origin = -1052.0234;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_20) {
  s21_decimal src1, src2;
  float num1 = -0.94e03;
  float num2 = -112.0e2;
  float res_origin = -12140;
  s21_from_float_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_21) {
  s21_decimal dec1, dec2;
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = 100099;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_add(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_test_22) {
  s21_decimal dec1, dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  int res = -100099;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_add(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_test_23) {
  s21_decimal dec1, dec2;
  int tmp1 = 2147483647;
  int tmp2 = -2147483647;
  int res_s21 = 0;
  int res = 0;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_add(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_test_24) {
  s21_decimal dec1, dec2;
  dec1.bits[3] = 0x300000;
  dec1.bits[2] = 0;
  dec1.bits[1] = 0xF;
  dec1.bits[0] = 0x67E4FEEF;

  dec2.bits[3] = 0x300000;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0xFF;
  dec2.bits[0] = 0x67E4FFFF;

  s21_decimal res;
  res.bits[3] = 1835008;
  res.bits[2] = 0;
  res.bits[1] = 0x10E;
  res.bits[0] = 0xCFC9FEEE;
  s21_decimal res1;

  s21_add(dec1, dec2, &res1);
  ck_assert_int_eq(res.bits[3], res1.bits[3]);
  ck_assert_int_eq(res.bits[2], res1.bits[2]);
  ck_assert_int_eq(res.bits[1], res1.bits[1]);
  ck_assert_int_eq(res.bits[0], res1.bits[0]);
}
END_TEST

START_TEST(add_test_25) {
  s21_decimal dec1, dec2;
  int tmp1 = -2147483647;
  int tmp2 = 2147483647;
  int res_s21 = 0;
  int res = 0;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_add(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_test_26) {
  s21_decimal dec1 = {{U_MAX_INT, U_MAX_INT, U_MAX_INT, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal res1;
  int ret_s21 = s21_add(dec1, dec2, &res1);
  ck_assert_int_eq(1, ret_s21);
}
END_TEST

START_TEST(add_test_27) {
  float tmp2 = pow(2, 31);
  s21_decimal dec1 = {{U_MAX_INT, U_MAX_INT, U_MAX_INT, tmp2}};
  s21_decimal dec2 = {{1, 0, 0, tmp2}};
  s21_decimal res1;
  int ret_s21 = s21_add(dec1, dec2, &res1);
  ck_assert_int_eq(2, ret_s21);
}
END_TEST

START_TEST(add_test_28) {
  float float_a = -10758.218750;
  float float_b = 6268.843750;

  float float_res = float_a + float_b;

  s21_decimal expected = {0};
  s21_from_float_to_decimal(float_res, &expected);

  s21_decimal dec_a = {0};
  s21_from_float_to_decimal(float_a, &dec_a);
  s21_decimal dec_b = {0};
  s21_from_float_to_decimal(float_b, &dec_b);

  s21_decimal result = {0};
  int code = s21_add(dec_a, dec_b, &result);

  float got_float = 0;
  s21_from_decimal_to_float(result, &got_float);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, float_res, 1e-06);
}

START_TEST(add_test_29) {
  s21_decimal src1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal src2 = {0};
  float a = 0.01448;
  s21_from_float_to_decimal(a, &src2);
  s21_decimal res_dec = {0};
  s21_add(src1, src2, &res_dec);
  ck_assert_int_eq(s21_add(src1, src2, &res_dec), 0);
}
END_TEST

START_TEST(add_test_30) {
  s21_decimal src1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(MAX_INT)}};
  s21_decimal src2 = {0};
  float a = -0.01448;
  s21_from_float_to_decimal(a, &src2);
  s21_decimal res_dec = {0};
  s21_add(src1, src2, &res_dec);
  ck_assert_int_eq(s21_add(src1, src2, &res_dec), 0);
}
END_TEST

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_2) {
  s21_decimal val1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_3) {
  s21_decimal val1 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {0};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_11) {
  s21_decimal val1 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_12) {
  s21_decimal val1 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_13) {
  s21_decimal val1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(thalassa_add_16) {
  s21_decimal val1 = {{4, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_test_decimal_add_0) {
  s21_decimal c = {{5, 0, 0, 0}};
  s21_decimal d = {{5, 0, 0, 0}};
  s21_decimal etalon = {{10, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(add, 0);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_1) {
  s21_decimal c = {{100, 0, 0, 0}};
  s21_decimal d = {{100, 0, 0, 0}};
  s21_decimal etalon = {{100, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_add(c, d, p_res);
  ;
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(add, 0);
  ck_assert_int_eq(equal, S21_FALSE);
}
END_TEST

START_TEST(s21_test_decimal_add_2) {
  s21_decimal c = {{2147483647, 0, 0, 0}};
  s21_decimal d = {{2147483647, 0, 0, 0}};
  s21_decimal etalon = {{4294967294, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal *p_result = &result;

  int add = s21_add(c, d, p_result);
  ck_assert_int_eq(add, 0);
  ;
  int equal = s21_is_equal(result, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_3) {
  s21_decimal c = {{1000, 0, 0, 0}};
  s21_decimal d = {{1000, 0, 0, 0}};
  s21_decimal etalon = {{2000, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal *p_result = &result;

  int add = s21_add(c, d, p_result);
  ck_assert_int_eq(add, 0);
  ;
  int equal = s21_is_equal(result, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_4) {
  s21_decimal c = {{1000, 0, 0, ~(MAX_INT)}};
  s21_decimal d = {{1000, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal *p_result = &result;

  int add = s21_add(c, d, p_result);
  ck_assert_int_eq(add, 0);
  ;
  int equal = s21_is_equal(result, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_5) {
  s21_decimal c = {{1, 0, 0, ~(MAX_INT)}};
  s21_decimal d = {{1, 0, 0, ~(MAX_INT)}};
  s21_decimal etalon = {{2, 0, 0, ~(MAX_INT)}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal *p_result = &result;

  int add = s21_add(c, d, p_result);
  ck_assert_int_eq(add, 0);
  ;
  int equal = s21_is_equal(*p_result, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_6) {
  s21_decimal c = {{0, 0, 0, 0}};
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_7) {
  s21_decimal c = {{1, 0, 0, 0}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{2, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_8) {
  s21_decimal c = {{1000, 0, 0, 0}};
  s21_decimal d = {{1000, 0, 0, 0}};
  s21_decimal etalon = {{2000, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_8_1) {
  s21_decimal c = {{MAX_INT, 0, 0, 0}};
  s21_decimal d = {{MAX_INT, 0, 0, 0}};
  s21_decimal etalon = {{4294967294, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_9) {
  s21_decimal c = {{MAX_INT, 0, 0, 0}};
  s21_decimal d = {{MAX_INT, 0, 0, 0}};
  s21_decimal etalon = {{UINT32_MAX - 1, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_10) {
  s21_decimal c = {{UINT32_MAX, 0, 0, 0}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{0, 1, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[3], etalon.bits[3]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[0], etalon.bits[0]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_11) {
  s21_decimal c = {{0, S21_MAX_UINT - 1, 0, 0}};
  s21_decimal d = {{0, 1, 0, 0}};
  s21_decimal etalon = {{0, S21_MAX_UINT, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_12) {
  s21_decimal c = {{0, 0, S21_MAX_UINT - 1, 0}};
  s21_decimal d = {{0, 0, 1, 0}};
  s21_decimal etalon = {{0, 0, S21_MAX_UINT, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_13) {
  s21_decimal c = {{0, 0, 0, ~(MAX_INT)}};
  s21_decimal d = {{0, 0, 0, ~(MAX_INT)}};
  s21_decimal etalon = {{0, 0, 0, ~(MAX_INT)}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_14) {
  s21_decimal c = {{1, 0, 0, ~(MAX_INT)}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_15) {
  s21_decimal c = {{1, 0, 0, ~(MAX_INT)}};
  s21_decimal d = {{1, 0, 0, ~(MAX_INT)}};
  s21_decimal etalon = {{2, 0, 0, ~(MAX_INT)}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[3], etalon.bits[3]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[0], etalon.bits[0]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_16) {
  s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal etalon = {{11, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_17) {
  s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{21, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_18) {
  s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{121, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_19) {
  s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_2}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{1111, 0, 0, EXPONENT_PLUS_2}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_20) {
  s21_decimal c = {0};
  c.bits[0] = 0b11111111111111111111111111111110;
  c.bits[1] = 0b00000000000000000000000000000000;
  c.bits[2] = 0b00000000000000000000000000000000;
  c.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {0};
  etalon.bits[0] = 0b11111111111111111111111111111111;
  etalon.bits[1] = 0b00000000000000000000000000000000;
  etalon.bits[2] = 0b00000000000000000000000000000000;
  etalon.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_21) {
  s21_decimal c = {{UINT32_MAX - 1, UINT32_MAX, 0, 0}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{UINT32_MAX, UINT32_MAX, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_25) {
  s21_decimal c = {{0b00000000000000000001100101111001, 0, 0, 0}};
  s21_decimal d = {{0b00000000000000010010000110001001, 0, 0, 0}};
  s21_decimal etalon = {{0b00000000000000010011101100000010, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_26) {
  s21_decimal c = {{0b10001001111001111111111111111111,
                    0b10001010110001110010001100000100, 0, 0}};
  s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  s21_decimal etalon = {{0b10001001111010000000000000000000,
                         0b10001010110001110010001100000100, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_27) {
  s21_decimal c = {{S21_MAX_UINT, S21_MAX_UINT, 0, 0}};
  s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 1, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_28) {
  s21_decimal c = {
      {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
  s21_decimal d = {{0b00000011010000001001011100101110, 0, 0, 0}};
  s21_decimal etalon = {
      {0b01110001001010101101101011101101, 0b00101110001111001110000111111000,
       0b10110000001111101110111101101101, 0b10000000000011100000000000000000}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_29) {
  s21_decimal c = {
      {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
  s21_decimal d = {
      {0b01001000000110110001111110011000, 0b11111011111111011000100101101101,
       0b00000000000001000110110101110111, 0b10000000000110000000000000000000}};
  s21_decimal etalon = {
      {0b10110110001010011011010111011011, 0b11111001111010100000110001111111,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);
  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_30) {
  s21_decimal src1, src2, origin;
  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b01001110111001000011100101110110;
  origin.bits[1] = 0b01001011001101011010000111011001;
  origin.bits[2] = 0b00011001101110010111010010111111;
  origin.bits[3] = 0b00000000000011110000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal *p_res = &result;
  int add = s21_add(src1, src2, p_res);
  ck_assert_int_eq(add, 0);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);

  int equal = s21_is_equal(result, origin);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_0) {
  s21_decimal c = {{0, 0, 0, 0}};
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_1) {
  s21_decimal c = {{1, 0, 0, 0}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{2, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_2) {
  s21_decimal c = {{1000, 0, 0, 0}};
  s21_decimal d = {{1000, 0, 0, 0}};
  s21_decimal etalon = {{2000, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_3) {
  s21_decimal c = {{MAX_INT, 0, 0, 0}};
  s21_decimal d = {{MAX_INT, 0, 0, 0}};
  s21_decimal etalon = {{4294967294, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_4) {
  s21_decimal c = {{MAX_INT, 0, 0, 0}};
  s21_decimal d = {{MAX_INT, 0, 0, 0}};
  s21_decimal etalon = {{UINT32_MAX - 1, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_5) {
  s21_decimal c = {{S21_MAX_UINT, 0, 0, 0}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{0, 1, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[3], etalon.bits[3]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[0], etalon.bits[0]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_6) {
  s21_decimal c = {{0, S21_MAX_UINT - 1, 0, 0}};
  s21_decimal d = {{0, 1, 0, 0}};
  s21_decimal etalon = {{0, S21_MAX_UINT, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_7) {
  s21_decimal c = {{0, 0, S21_MAX_UINT - 1, 0}};
  s21_decimal d = {{0, 0, 1, 0}};
  s21_decimal etalon = {{0, 0, S21_MAX_UINT, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_8) {
  s21_decimal c = {{0, 0, 0, ~(MAX_INT)}};
  s21_decimal d = {{0, 0, 0, ~(MAX_INT)}};
  s21_decimal etalon = {{0, 0, 0, ~(MAX_INT)}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_9) {
  s21_decimal c = {{1, 0, 0, ~(MAX_INT)}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_10) {
  s21_decimal c = {{1, 0, 0, ~(MAX_INT)}};
  s21_decimal d = {{1, 0, 0, ~(MAX_INT)}};
  s21_decimal etalon = {{2, 0, 0, ~(MAX_INT)}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_11) {
  s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal etalon = {{11, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_12) {
  s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{21, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_13) {
  s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_1}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{121, 0, 0, EXPONENT_PLUS_1}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_14) {
  s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_2}};
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal etalon = {{1111, 0, 0, EXPONENT_PLUS_2}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);
  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_20) {
  s21_decimal c = {{0b00000000000000000001100101111001, 0, 0, 0}};
  s21_decimal d = {{0b00000000000000010010000110001001, 0, 0, 0}};
  s21_decimal etalon = {{0b00000000000000010011101100000010, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_21) {
  s21_decimal c = {{0b10001001111001111111111111111111,
                    0b10001010110001110010001100000100, 0, 0}};
  s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  s21_decimal etalon = {{0b10001001111010000000000000000000,
                         0b10001010110001110010001100000100, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_22) {
  s21_decimal c = {{S21_MAX_UINT, S21_MAX_UINT, 0, 0}};
  s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 1, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;

  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_23) {
  s21_decimal c = {
      {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
  s21_decimal d = {{0b00000011010000001001011100101110, 0, 0, 0}};
  s21_decimal etalon = {
      {0b01110001001010101101101011101101, 0b00101110001111001110000111111000,
       0b10110000001111101110111101101101, 0b10000000000011100000000000000000}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_add(c, d, p_res);
  ck_assert_int_eq(add, 0);
  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_add_max_31) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
}
END_TEST

START_TEST(s21_add_max_32) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 1);
}
END_TEST

START_TEST(s21_add_max_33) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 1);
}
END_TEST

START_TEST(s21_add_max_34) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111111;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_add(src1, src2, &s21_res);
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(s21_add_max_35) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111111;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_add(src1, src2, &s21_res);
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(s21_add_max_36) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111110;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_add(src1, src2, &s21_res);
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(add_test_37) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b00000000000000000000001111111111;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000001111111111;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000100000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b00000000000000000010101111110101;
  original_res.bits[1] = 0b00000000000000000000000000000000;
  original_res.bits[2] = 0b00000000000000000000000000000000;
  original_res.bits[3] = 0b00000000000000100000000000000000;
  s21_decimal s21_res = {0};
  s21_add(src1, src2, &s21_res);
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(test_s21_sub_1) {
  s21_decimal src1, src2, result;
  int a = 9403;
  int b = 202;
  int res_origin = 9201;
  int res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_int(result, &res_our);
  ck_assert_int_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_2) {
  s21_decimal src1, src2, result;
  int a = 9403;
  float b = 202.098;
  float res_origin = 9200.902;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_3) {
  s21_decimal src1, src2, result;
  float a = -9403;
  float b = 202.098;
  float res_origin = a - b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_4) {
  s21_decimal src1, src2, result;
  float a = 9403.0;
  float b = 202.09e8;
  float res_origin = -20208990597;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_5) {
  s21_decimal src1, src2, result;
  float a = 9403.0e2;
  float b = 202.09e8;
  float res_origin = -20208059700;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_6) {
  s21_decimal src1, src2, result;
  float a = -9403.0e2;
  int b = -202;
  float res_origin = a - b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_7) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000000000110011011110000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00000000000001000101000111010110;
  s21_decimal result_origin;
  result_origin.bits[3] = 0b00000000000000110000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00000000001000111110001111101010;
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_sub_8) {
  s21_decimal test_value_1 = {{1, 10, 0, 0}};
  s21_decimal test_value_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4);
  ck_assert_uint_eq(result_dec.bits[2], 0);
}
END_TEST

START_TEST(test_s21_sub_9) {
  s21_decimal test_value_1 = {{1, 4, 5, 0}};
  s21_decimal test_value_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967294);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(test_s21_sub_10) {
  s21_decimal test_value_1 = {{1, 0, 5, 0}};
  s21_decimal test_value_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967290);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(sub_1) {
  s21_decimal value_1 = {{55555, 0, 0, 0}};
  s21_decimal value_2 = {{66666, 0, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{555483334, 0, 0, 262144}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 2147614720}};
  s21_decimal value_2 = {{23465246, 0, 0, 2147549184}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4060314835, 0, 0, 2147614720}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}};
  s21_decimal value_2 = {{UINT_MAX, 100, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 100, 0, 2147483648}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal value_1 = {{UINT_MAX, 4563654, 0, 2148139008}};
  s21_decimal value_2 = {{23465246, 364563, 0, 2148270080}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4271501950, 456000936, 0, 2148270080}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(sub_5) {
  s21_decimal value_1 = {{UINT_MAX, 345634, 0, 2147876864}};
  s21_decimal value_2 = {{23465246, 45634, 0, 327680}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{234652459, 801975, 0, 2147876864}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(sub_6) {
  s21_decimal value_1 = {{UINT_MAX, 345634, 0, 393216}};
  s21_decimal value_2 = {{23465246, 45634, 0, 2147811328}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{234652459, 801975, 0, 393216}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(sub_7) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, 2147483647, 1638400}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, 0, 983040}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4153960755, 858993458, 785251635, 2149056512}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}

START_TEST(sub_8) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal value_2 = {{4294967294, UINT_MAX, UINT_MAX, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}

START_TEST(sub_9) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 1835008}};
  s21_decimal value_2 = {{4294967294, UINT_MAX, UINT_MAX, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4294967286, UINT_MAX, UINT_MAX, 2147483648}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(sub_10) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX}};
  s21_decimal value_2 = {{54, 0, 0, 0}};
  s21_set_scale(2, &value_2);
  s21_decimal result = {{0}};
  s21_decimal expected = {{4294967295, UINT_MAX, UINT_MAX}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}

START_TEST(sub_11) {
  s21_decimal value_1 = {{2294791350, 10215304, 0, 0}};
  set_sign(&value_1, 1);
  s21_set_scale(2, &value_1);
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_sign(&value_2, 1);
  s21_decimal result = {{0}};
  s21_decimal expected = {{4100220690, 4294865142, 4294967295}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}

START_TEST(sub_12) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 2147483648}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result;
  initialize_decimal(&result);
  s21_decimal expected = {{0, 0, 0, 2147483648}};
  int status = s21_sub(value_1, value_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 2);
}
END_TEST

//////////////////////////////////////////////////////////////
START_TEST(sub_test_1) {
  int num1 = -10;
  int num2 = -10;
  int dif_int = 0;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, dif_int);
}
END_TEST

START_TEST(sub_test_2) {
  int num1 = 10;
  int num2 = 20;
  int dif_int = -10;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, dif_int);
}
END_TEST

START_TEST(sub_test_3) {
  int num1 = -10;
  int num2 = 20;
  int dif_int = -30;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, dif_int);
}
END_TEST

START_TEST(sub_test_4) {
  int num1 = 9403;
  int num2 = 202;
  int dif_int = 9201;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, dif_int);
}
END_TEST

START_TEST(sub_test_5) {
  int num1 = 100;
  int num2 = -200;
  int dif_int = 300;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, dif_int);
}
END_TEST

START_TEST(sub_test_6) {
  int num1 = 100;
  int num2 = -10;
  int dif_int = 110;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, dif_int);
}
END_TEST

START_TEST(sub_test_7) {
  int num1 = -900;
  int num2 = -100;
  int dif_int = -800;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, dif_int);
}
END_TEST

START_TEST(sub_test_8) {
  int num1 = 900;
  int num2 = 100;
  int dif_int = 800;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, dif_int);
}
END_TEST

START_TEST(sub_test_9) {
  int num1 = 900;
  int num2 = -100;
  int dif_int = 1000;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, dif_int);
}
END_TEST

START_TEST(sub_test_10) {
  int num1 = -900;
  int num2 = 100;
  int dif_int = -1000;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, dif_int);
}
END_TEST

START_TEST(sub_test_11) {
  int num1 = 123;
  float num2 = 12.5;
  float origin_float = 110.5;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, origin_float);
}
END_TEST

START_TEST(sub_test_12) {
  int num1 = -123;
  float num2 = 12.5;
  float dif_float = num1 - num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_13) {
  float num1 = 12.9;
  float num2 = 12.5;
  float original_res = num1 - num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float our_res = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &our_res);
  ck_assert_float_eq(our_res, original_res);
}
END_TEST

START_TEST(sub_test_14) {
  int num1 = 9403;
  float num2 = 202.098;
  float dif_float = 9200.902;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_15) {
  int num1 = -9403;
  float num2 = 202.098;
  float dif_float = num1 - num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_16) {
  float num1 = 9403.0;
  float num2 = 202.09e8;
  float dif_float = num1 - num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_17) {
  float num1 = 9403.0e2;
  float num2 = 202.09e8;
  float dif_float = num1 - num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_18) {
  float num1 = -9403.0e2;
  int num2 = -202;
  float dif_float = num1 - num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_19) {
  float num1 = -94;
  float num2 = -202;
  float dif_float = num1 - num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_20) {
  float num1 = -1.0 / 0.0;
  int num2 = 202;
  double dif_float = 0 - num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_21) {
  float num1 = 1.0 / 0.0;
  int num2 = 20;
  double dif_float = 0 - num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_sub(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(s21_sub_inf_27) {
  float tmp = pow(2, 31);
  s21_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal dec2 = {{1, 0, 0, tmp}};
  s21_decimal res1;
  int ret_s21 = s21_sub(dec1, dec2, &res1);
  ck_assert_int_eq(1, ret_s21);
}
END_TEST

START_TEST(s21_sub_neg_inf_28) {
  float tmp = pow(2, 31);
  s21_decimal dec1 = {{4294967295, 4294967295, 4294967295, tmp}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal res1;
  int ret_s21 = s21_sub(dec1, dec2, &res1);
  ck_assert_int_eq(2, ret_s21);
}
END_TEST

START_TEST(s21_sub_max_30) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111111;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_sub(src1, src2, &s21_res);
  ck_assert_int_eq(s21_sub(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(s21_sub_max_31) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111111;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_sub(src1, src2, &s21_res);
  ck_assert_int_eq(s21_sub(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(s21_sub_max_32) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111110;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_sub(src1, src2, &s21_res);
  ck_assert_int_eq(s21_sub(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(s21_sub_max_33) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_sub(src1, src2, &s21_res), 2);
}
END_TEST

START_TEST(s21_sub_max_34) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_sub(src1, src2, &s21_res), 2);
}
END_TEST

START_TEST(s21_sub_max_35) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_sub(src1, src2, &s21_res), 2);
}
END_TEST

START_TEST(s21_subTest1) {
  // 863
  s21_decimal src1, src2, origin;
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest2) {
  // 889
  s21_decimal src1, src2, origin;
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest3) {
  // 915
  s21_decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest4) {
  // 941
  s21_decimal src1, src2, origin;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest5) {
  // 967
  s21_decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest6) {
  // 993
  s21_decimal src1, src2, origin;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest7) {
  // 1019
  s21_decimal src1, src2, origin;
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000010000100000010000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest8) {
  // 1045
  s21_decimal src1, src2, origin;
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000101110100011001110100010111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest9) {
  // 1071
  s21_decimal src1, src2, origin;
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 95;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 5;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest10) {
  // 1097
  s21_decimal src1, src2, origin;
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000001011001000011001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest11) {
  // 1123
  s21_decimal src1, src2, origin;
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11111101101100110001110000110000;
  origin.bits[1] = 0b00000000000000000000000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest12) {
  // 1149
  s21_decimal src1, src2, origin;
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b01001100110100101000000111000010;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest13) {
  // 1175
  s21_decimal src1, src2, origin;
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b10001001111001111111111111111110;
  origin.bits[1] = 0b10001010110001110010001100000100;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest14) {
  // 1201
  s21_decimal src1, src2, origin;
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11111111111111111111111111111110;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest15) {
  // 1227
  s21_decimal src1, src2, origin;
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;

  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11000000100010111000101000100010;
  origin.bits[1] = 0b11111111111111111111111111111101;
  origin.bits[2] = 0b00000000000000000000000000001001;
  origin.bits[3] = 0b00000000000000010000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest16) {
  // 1253
  s21_decimal src1, src2, origin;
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;

  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b10010100100110011101101011101101;
  origin.bits[1] = 0b11000101100100110110100101100010;
  origin.bits[2] = 0b10110000001111101111000110111100;
  origin.bits[3] = 0b10000000000011100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest17) {
  // 1279
  s21_decimal src1, src2, origin;
  // src1 = -545454512454545.35265454545645;
  // src2 = -5.352654545456454545645464;

  // -545454512454545.35265454545645 exp 14
  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;

  // -5.352654545456454545645464 exp 24
  src2.bits[0] = 0b01001000000110110001111110011000;
  src2.bits[1] = 0b11111011111111011000100101101101;
  src2.bits[2] = 0b00000000000001000110110101110111;
  src2.bits[3] = 0b10000000000110000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  // -54545451245453999999999999999 exp 14
  s21_sub(src1, src2, &result);

  // -54545451245453999999999999999 exp 14
  origin.bits[0] = 0b01001111100110101111111111111111;
  origin.bits[1] = 0b11111001111001100011111011011011;
  origin.bits[2] = 0b10110000001111101111000010010100;
  origin.bits[3] = 0b10000000000011100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest18) {
  // 1305
  s21_decimal src1, src2, origin;
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b01001110111001000011100101110110;
  origin.bits[1] = 0b01001011001101011010000111011001;
  origin.bits[2] = 0b00011001101110010111010010111111;
  origin.bits[3] = 0b00000000000011110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest19) {
  // 1331
  s21_decimal src1, src2, origin;
  // src1 = 12345677.987654345678987654346;
  // 12345677.987654345678987654346
  // src2 = 87654323456.9876545678987653;
  // 87654323456.9876545678987653
  // printf("\ns21_subTest19 s21_subTest19 s21_subTest19\n\n");

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);
  // 87641977779.00000022221977764 exp 17

  origin.bits[0] = 0b10010010000001100111100010100101;
  origin.bits[1] = 0b10001011011010100100100011011111;
  origin.bits[2] = 0b00011100010100011001001100010001;
  origin.bits[3] = 0b10000000000100010000000000000000;
  // print_2(&src1);
  // print_2(&src2);
  // print_2(&result);
  // print_2(&origin);
  // 87641977779.00000022221977765 exp 17
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest20) {
  // 1357
  s21_decimal src1, src2, origin;
  // src1 = -12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11010010000011011110010110111111;
  origin.bits[1] = 0b10100111010011100111001000100001;
  origin.bits[2] = 0b00011100010100111001110111101101;
  origin.bits[3] = 0b10000000000100010000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest21) {
  // 1383
  s21_decimal src1, src2, origin;
  // src1 = 12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11010010000011011110010110111111;
  origin.bits[1] = 0b10100111010011100111001000100001;
  origin.bits[2] = 0b00011100010100111001110111101101;
  origin.bits[3] = 0b00000000000100010000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest22) {
  // 1409
  s21_decimal src1, src2, origin;
  // src1 = -12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b10010010000001100111100010100101;
  origin.bits[1] = 0b10001011011010100100100011011111;
  origin.bits[2] = 0b00011100010100011001001100010001;
  origin.bits[3] = 0b00000000000100010000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest23) {
  // 1435
  s21_decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest24) {
  // 1461
  s21_decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest25) {
  // 1487
  s21_decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest26) {
  // 1513
  s21_decimal src1, src2, origin;
  // src1 = 792281625142643375935439503;
  // src2 = -1;

  src1.bits[0] = 0b00101000111101011100001010001111;
  src1.bits[1] = 0b11110101110000101000111101011100;
  src1.bits[2] = 0b00000010100011110101110000101000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00101000111101011100001010010000;
  origin.bits[1] = 0b11110101110000101000111101011100;
  origin.bits[2] = 0b00000010100011110101110000101000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest27) {
  // 1539
  s21_decimal src1, src2, origin;
  // src1 = 7922816251427554395;
  // src2 = 65645646;

  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b01011011000111100101100000001101;
  origin.bits[1] = 0b01101101111100110111111101100111;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest28) {
  // 1565
  s21_decimal src1, src2, origin;
  // src1 = 665464545;
  // src2 = 8798232189789785;

  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11101000101010001011011101111000;
  origin.bits[1] = 0b00000000000111110100000111110001;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest29) {
  // 1591
  s21_decimal src1, src2, origin;
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;

  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;

  src2.bits[0] = 0b11010100101011100011110110001010;
  src2.bits[1] = 0b01110100000101000010011110100011;
  src2.bits[2] = 0b00000000000010000100000101000100;
  src2.bits[3] = 0b00000000000110000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00001110111111111010100000101010;
  origin.bits[1] = 0b00101001110101100000001000110100;
  origin.bits[2] = 0b00000000000001011111000010100001;
  origin.bits[3] = 0b10000000000110000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest30) {
  // 1617
  s21_decimal src1, src2, origin;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;

  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11010010100100100111101010001100;
  origin.bits[1] = 0b10011110100111100111000100000100;
  origin.bits[2] = 0b00011111101010011000000100111000;
  origin.bits[3] = 0b10000000000011000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest31) {
  // 1643
  s21_decimal src1, src2, origin;
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;

  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;

  src2.bits[0] = 0b00010111001001010100110000000010;
  src2.bits[1] = 0b00000000111101010001010110011011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b01011010101111100101111101110011;
  origin.bits[1] = 0b00101101001111010011000001101000;
  origin.bits[2] = 0b00000100101010001101010101010111;
  origin.bits[3] = 0b10000000000111000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest32) {
  // 1669
  s21_decimal src1, src2, origin;
  // src1 = -0.77545545454546589781;
  // src2 = 87894515154546456456;

  src1.bits[0] = 0b10101100001010000001100001010101;
  src1.bits[1] = 0b00110100001010010001111010111100;
  src1.bits[2] = 0b00000000000000000000000000000100;
  src1.bits[3] = 0b10000000000101000000000000000000;

  src2.bits[0] = 0b00010011111011011111011110001000;
  src2.bits[1] = 0b11000011110010000000101111011001;
  src2.bits[2] = 0b00000000000000000000000000000100;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b10111000010101011100100001001010;
  origin.bits[1] = 0b01100110100011011000001100010111;
  origin.bits[2] = 0b00011100011001100111011011000001;
  origin.bits[3] = 0b10000000000010000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest33) {
  // 1695
  s21_decimal src1, src2, origin;
  // src1 = -7922816251426433759354395033;
  // src2 = 1;

  src1.bits[0] = 0b10011001100110011001100110011001;
  src1.bits[1] = 0b10011001100110011001100110011001;
  src1.bits[2] = 0b00011001100110011001100110011001;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b10011001100110011001100110011010;
  origin.bits[1] = 0b10011001100110011001100110011001;
  origin.bits[2] = 0b00011001100110011001100110011001;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_test_decimal_sub_simple_0) {
  s21_decimal c = {{10, 0, 0, 0}};
  s21_decimal d = {{5, 0, 0, 0}};
  s21_decimal etalon = {{5, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_sub(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_sub_simple_1) {
  s21_decimal c = {{100, 0, 0, 0}};
  s21_decimal d = {{5, 0, 0, 0}};
  s21_decimal etalon = {{5, 0, 0, 0}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_sub(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_FALSE);
}
END_TEST

START_TEST(s21_test_decimal_sub_simple_2) {
  s21_decimal c = {{INT_MAX, 0, 0, 0}};
  s21_decimal d = {{5, 0, 0, 0}};
  s21_decimal etalon = {{2147483642, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_sub(c, d, p_res);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_sub_simple_3) {
  s21_decimal c = {{INT_MAX, INT_MAX, 0, 0}};
  s21_decimal d = {{5, 0, 0, 0}};
  s21_decimal etalon = {{INT_MAX - 5, INT_MAX, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_sub(c, d, p_res);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}

START_TEST(s21_test_decimal_sub_simple_7) {
  s21_decimal c = {{1, 0, 0, 0}};
  s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
  s21_decimal etalon = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_sub(c, d, p_res);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_sub_simple_8) {
  s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
  s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
  s21_decimal etalon = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_sub(c, d, p_res);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_sub_simple_10) {
  s21_decimal c = {{100, 0, 0, 0}};
  s21_decimal d = {{100, 0, 0, ~(INT_MAX)}};
  s21_decimal etalon = {{200, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_sub(c, d, p_res);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_decimal_sub_simple_11) {
  s21_decimal c = {{100, 0, 0, ~(INT_MAX)}};
  s21_decimal d = {{100, 0, 0, ~(INT_MAX)}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal *p_res = &res;
  int add = s21_sub(c, d, p_res);
  ck_assert_int_eq(add, 0);
}
END_TEST

START_TEST(s21_sub_int_22) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = -99899;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(s21_sub_int_23) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  int res = 99899;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(s21_sub_int_24) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -2147483647;
  int tmp2 = -2147483647;
  int res_s21 = 0;
  int res = 0;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(s21_sub_int_25) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -214748347;
  int tmp2 = 217483647;
  int res_s21 = 0;
  int res = -214748347 - 217483647;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(s21_sub_int_26) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 214748347;
  int tmp2 = -217483647;
  int res_s21 = 0;
  int res = 214748347 - -217483647;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(test_s21_mul_1) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 189940600;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_2) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0e2;
  float b = 9403.0e2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 884164090000;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_3) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403;
  float b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 1899406;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_4) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -65536;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_5) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 32768;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1073741824;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_6) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float res_our_dec = 0.0;
  float res_origin = 4294967296;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_7) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_mul_8) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

/* START_TEST(test_s21_mul_9) { */
/*     s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 131072}}; */
/*     s21_decimal src2 = {{0, 0, 0, 0}}; */
/*     s21_decimal result = {{0, 0, 0, 0}}; */
/*     s21_from_float_to_decimal(1.01, &src2); */
/*     s21_set_scale(3, &src1); */
/*     s21_mul(src1, src2, &result); */
/*     ck_assert_int_eq(result.bits[0], 927712902); */
/*     ck_assert_int_eq(result.bits[1], 3848290697); */
/*     ck_assert_int_eq(result.bits[2], 433791696); */
/* } */
/* END_TEST */

START_TEST(test_s21_mul_10) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  float n1 = -5.6e-15;
  float n2 = 1.5e-15;
  s21_from_float_to_decimal(n1, &val1);
  s21_from_float_to_decimal(n2, &val2);
  /* int r = s21_mul(val1, val2, &res); */
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(s21_div_box_1_3_0_0) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(0, &a);
  s21_set_scale(0, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{89478485, 347537611, 180700362, 1835008}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

// 1 / 3(0 - 1)
START_TEST(s21_div_box_1_3_0_1) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(0, &a);
  s21_set_scale(1, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{894784853, 3475376110, 1807003620, 1835008}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

// 1 / 3 (1-0)
START_TEST(s21_div_box_1_3_1_0) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(1, &a);
  s21_set_scale(0, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{1297438037, 893747220, 18070036, 1835008}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

// 1 / 3 (1-1)
START_TEST(s21_div_box_1_3_1_1) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(1, &a);
  s21_set_scale(1, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{89478485, 347537611, 180700362, 1835008}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

// 1 / 3 (10-10)
START_TEST(s21_div_box_1_3_10_10) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(10, &a);
  s21_set_scale(10, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{89478485, 347537611, 180700362, 1835008}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

// 1 / 3 (28-28)
START_TEST(s21_div_box_1_3_28_28) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(28, &a);
  s21_set_scale(28, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{89478485, 347537611, 180700362, 1835008}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

// 1 / 3 (28-0)
START_TEST(s21_div_box_1_3_28_0) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(28, &a);
  s21_set_scale(0, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{0, 0, 0, 0}};
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
}
END_TEST

// 1 / 3 (0-28)
START_TEST(s21_div_box_1_3_0_28) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(0, &a);
  s21_set_scale(28, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{894784853, 3475376110, 1807003620, 65536}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

// 1 / 3 (5-15)
START_TEST(s21_div_box_1_3_5_15) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(5, &a);
  s21_set_scale(15, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{894784853, 3475376110, 1807003620, 1245184}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

// 1 / 3 (15-5)
START_TEST(s21_div_box_1_3_15_5) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(15, &a);
  s21_set_scale(5, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{2367771989, 77610214, 0, 1835008}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

// 1 / 3 (5-0)
START_TEST(s21_div_box_1_3_5_0) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(5, &a);
  s21_set_scale(0, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{4241839445, 15551256, 1807, 1835008}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

// 1 / 3 (0-5)
START_TEST(s21_div_box_1_3_0_5) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(0, &a);
  s21_set_scale(5, &b);
  s21_decimal result = {0};
  int ex_code = s21_div(a, b, &result);
  s21_decimal expected = {{894784853, 3475376110, 1807003620, 1572864}};

  ASSERT_DECIMAL_EQ
  ck_assert_int_eq(0, ex_code);
}
END_TEST

START_TEST(div_test_1) {
  int num1 = 100;
  int num2 = 50;
  int res_origin = 2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_2) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -16384;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_3) {
  int num1 = 2;
  int num2 = 2;
  int res_origin = 1;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_4) {
  int num1 = 0;
  int num2 = 5;
  int res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_5) {
  s21_decimal dec1, dec2, result;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);

  dec1.bits[3] = 0;
  dec1.bits[2] = 1568954488;
  dec1.bits[1] = 1568954488;
  dec1.bits[0] = 1568954488;

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 0;

  diff = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(diff, 3);
}
END_TEST

START_TEST(div_test_6) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 1568954488;
  dec1.bits[1] = 1568954488;
  dec1.bits[0] = 1568954488;

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 1;

  orig.bits[3] = 0;
  orig.bits[2] = 1568954488;
  orig.bits[1] = 1568954488;
  orig.bits[0] = 1568954488;

  s21_div(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(div_test_7) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 0;
  dec1.bits[1] = 1568954488;
  dec1.bits[0] = 1568954488;

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 1;
  s21_set_scale(2, &dec2);

  orig.bits[3] = 0;
  orig.bits[2] = 36;
  orig.bits[1] = 2276626180;
  orig.bits[0] = 2276626144;

  s21_div(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(div_test_8) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);
  // 4949341991908698119347372159
  dec1.bits[3] = 0;
  dec1.bits[2] = 0b1111111111011111111111101111;
  dec1.bits[1] = 0b111100000000000000;
  dec1.bits[0] = 0b0000000000000001111111;
  // 31
  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 0b000000011111;
  s21_set_scale(2, &dec2);
  // 15965619328737735868862490835.4838709677419355
  orig.bits[3] = 0;
  orig.bits[2] = 0b00110011100101100111001101100110;
  orig.bits[1] = 0b00010000100100000011100111001110;
  orig.bits[0] = 0b01110011100111001110100011010011;

  s21_div(dec1, dec2, &result);

  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(test_s21_div_1) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  float a = 25;
  float b = 5;
  float c = 0;
  s21_from_decimal_to_float(result, &c);
  ck_assert_float_eq(c, a / b);
}
END_TEST

START_TEST(test_s21_div_2) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_div(src1, src2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(test_s21_div_3) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);

  s21_decimal result_expected;
  initialize_decimal(&result_expected);
  result_expected.bits[0] = 2147483648;
  float a = 0;
  float b = 0;
  s21_from_decimal_to_float(result, &a);
  s21_from_decimal_to_float(result_expected, &b);

  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(test_s21_div_4) {
  s21_decimal src1 = {{1000, 0, 0, 65536}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  s21_decimal result_expected;
  initialize_decimal(&result_expected);
  result_expected.bits[0] = 50;
  float a = 0;
  float b = 0;
  s21_from_decimal_to_float(result, &a);
  s21_from_decimal_to_float(result_expected, &b);

  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(test_s21_div_5) {
  s21_decimal src1 = {{1000, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);

  s21_decimal result_expected;
  initialize_decimal(&result_expected);
  result_expected.bits[0] = 2000;
  float a = 0;
  float b = 0;
  s21_from_decimal_to_float(result, &a);
  s21_from_decimal_to_float(result_expected, &b);

  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(div_1) {
  s21_decimal value_1 = {{895412, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 3);
}
END_TEST

START_TEST(div_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{75, 0, 0, 0}};
  s21_decimal result;
  initialize_decimal(&result);
  s21_decimal expected = {{0, 0, 0, 0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_3) {
  s21_decimal value_1 = {{225, 0, 0, 0}};
  s21_set_scale(2, &value_1);
  s21_decimal value_2 = {{15, 0, 0, 0}};
  set_sign(&value_2, 1);
  s21_set_scale(1, &value_2);
  s21_decimal expected = {{15, 0, 0, 0}};
  set_sign(&expected, 1);
  s21_set_scale(1, &expected);
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_4) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};
  s21_decimal expected = {{178956971, 695075222, 361400724, 0}};
  s21_set_scale(28, &expected);
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_5) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_set_scale(28, &value_1);
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_6) {
  s21_decimal value_1 = {{20, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_set_scale(5, &value_2);
  s21_decimal expected = {{400000, 0, 0, 0}};
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_7) {
  s21_decimal value_1 = {{592211859, 1035921593, 0, 0}};
  s21_set_scale(6, &value_1);
  s21_decimal value_2 = {{43764, 0, 0, 0}};
  s21_decimal expected = {{926677031, 1324446808, 551124877, 0}};
  s21_set_scale(20, &expected);
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_8) {
  s21_decimal value_1 = {{279772309, 218, 0, 0}};
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{2984756849, 242550, 0, 0}};
  s21_set_scale(16, &value_2);
  s21_decimal expected = {{4258462862, 1733906937, 487375841, 0}};
  set_sign(&expected, 1);
  s21_set_scale(15, &expected);
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_9) {
  s21_decimal value_1 = {{2243774991, 741267166, 0, 0}};
  set_sign(&value_1, 1);
  s21_set_scale(19, &value_1);
  s21_decimal value_2 = {{2243774991, 741267166, 0, 0}};
  set_sign(&value_2, 1);
  s21_set_scale(19, &value_2);
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_10) {
  s21_decimal value_1 = {{1392783818, 22080446, 0, 0}};
  set_sign(&value_1, 1);
  s21_set_scale(8, &value_1);
  s21_decimal value_2 = {{2313682944, 2328306436, 0, 0}};
  s21_decimal expected = {{1392783818, 22080446, 0, 0}};
  set_sign(&expected, 1);
  s21_set_scale(27, &expected);
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_11) {
  s21_decimal value_1 = {{2397809911, 86451412, 10, 0}};
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{193289, 0, 0, 0}};
  s21_set_scale(14, &value_2);
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(div_12) {
  s21_decimal value_1 = {{2833012231, 1194835434, 39, 0}};
  s21_decimal value_2 = {{193289, 0, 0, 0}};
  s21_set_scale(17, &value_2);
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(div_13) {
  s21_decimal value_1 = {{3815433103, 2843293561, 408, 0}};
  s21_set_scale(14, &value_1);
  s21_decimal value_2 = {{134934984, 0, 0, 0}};
  s21_set_scale(5, &value_2);
  s21_decimal expected = {{2535589114, 2456994201, 302858453, 0}};
  s21_set_scale(23, &expected);
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_14) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_scale(28, &value_1);
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_set_scale(1, &value_2);
  s21_decimal expected = {{858993459, 858993459, 858993459, 0}};
  s21_set_scale(27, &expected);
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_15) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_scale(1, &value_1);
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_set_scale(2, &value_2);
  s21_decimal result;
  initialize_decimal(&result);
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_mod_1) {
  s21_decimal src1 = {{1, 0, 0, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_mod_2) {
  s21_decimal src1 = {{1, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mod(src1, src2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(test_s21_mod_3) {
  s21_decimal src1 = {{1010, 0, 0, 65536}};
  s21_decimal src2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_mod(src1, src2, &result);
  s21_decimal origin = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_is_equal(origin, result), 1);
}
END_TEST

START_TEST(test_s21_mod_4) {
  s21_decimal src1 = {{101, 0, 0, 0}};
  s21_decimal src2 = {{100, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_mod(src1, src2, &result);
  s21_decimal origin = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_is_equal(origin, result), 1);
}
END_TEST
START_TEST(compare_01) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_02) {
  s21_decimal a = {{123, 123, 123, 0}};
  s21_decimal b = {{123, 123, 123, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_03) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_04) {
  s21_decimal a = {{4294967295, 4294967295, 0, 1835008}};
  s21_decimal b = {{4294967295, 4294967294, 0, 1835008}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_05) {
  s21_decimal a = {{4294967295, 4294967295, 4294967295, 65536}};
  s21_decimal b = {{4294967295, 4294967295, 4294967295, 196608}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_06) {
  s21_decimal a = {{4294967295, 4294967295, 4294967295, 65536}};
  s21_decimal b = {{4294967295, 4294967295, 4294967295, 196608}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_07) {
  s21_decimal a = {{2576980377, 4278124286, 4294967295, -2147483648}};
  s21_decimal b = {{2576980377, 4278124286, 4294967278, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_08) {
  s21_decimal a = {{12345600, 0, 0, 196608}};
  s21_decimal b = {{123456, 0, 0, 65536}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_09) {
  s21_decimal a = {{12345678, 0, 0, 0}};
  s21_decimal b = {{123456781, 0, 0, 65536}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_10) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_11) {
  s21_decimal a = {{12345, 0, 0, 262144}};  //  1.2345
  s21_decimal b = {{12, 0, 0, 2147549184}}; // -1.2
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_12) {
  s21_decimal a = {{12345, 0, 0, 2147745792}}; // -1.2345
  s21_decimal b = {{12, 0, 0, 65536}};         //  1.2
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_13) {
  s21_decimal a = {{12345, 0, 0, 262144}}; //  1.2345
  s21_decimal b = {{12, 0, 0, 65536}};     //  1.2
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_14) {
  s21_decimal a = {{12345, 0, 0, 2147745792}}; // -1.2345
  s21_decimal b = {{12, 0, 0, 2147549184}};    // -1.2
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_15) {
  s21_decimal a = {{120000, 0, 0, 262144}}; //  12.0000
  s21_decimal b = {{12, 0, 0, 0}};          //  12
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_16) {
  s21_decimal a = {{120000, 0, 0, 262144}}; //  12.0000
  s21_decimal b = {{12, 0, 0, 2147483648}}; //  -12
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  /* ck_assert_int_eq(s21_is_greater_noscale(a, b), 1); */
}
END_TEST

START_TEST(compare_17) {
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal a = {{0, 0, 0, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_less_1) {
  s21_decimal test_value_1 = {{10, 0, 0, 0}};
  s21_decimal test_value_2 = {{15, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2),
                   1); // 10 < 15 = True
}
END_TEST

START_TEST(test_s21_is_less_2) {
  s21_decimal test_value_1 = {{6739, 0, 0, 0}};
  s21_decimal test_value_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2),
                   1); // 6739 < 19993 = True
}
END_TEST

START_TEST(test_s21_is_less_3) {
  s21_decimal test_value_1 = {{19993, 0, 0, 0}};
  s21_decimal test_value_2 = {{6739, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2),
                   0); // 19993 < 6739 = False
}
END_TEST

START_TEST(test_s21_is_less_4) {
  s21_decimal test_value_1 = {{19993, 0, 0, 0}};
  s21_decimal test_value_2 = {{6739, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2),
                   0); // 19993 < -6739 = False
}
END_TEST

START_TEST(test_s21_is_less_5) {
  s21_decimal test_value_1 = {{19993, 0, 0, 0}};
  s21_decimal test_value_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2),
                   0); // 19993 < 19993 = False
}
END_TEST

START_TEST(test_s21_is_less_6) {
  s21_decimal test_value_1 = {{19993, 0, 0, 0}};
  s21_decimal test_value_2 = {{19993, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2),
                   0); // 19993 < 199,93 = False
}
END_TEST

START_TEST(test_s21_is_less_7) {
  s21_decimal test_value_1 = {{0, 1, 0, 0}};
  s21_decimal test_value_2 = {{
      19993,
      0,
      0,
  }};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2),
                   0); // 4294967295 < 19993 = False
}
END_TEST

START_TEST(test_s21_is_less_8) {
  s21_decimal test_value_1 = {{19993, 1, 0, 2147483648}};
  s21_decimal test_value_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2),
                   1); // -19993 < 19993 = True
}
END_TEST

START_TEST(test_s21_is_less_or_equal_1) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2),
                   1); // 0 <= 0 = True
}
END_TEST

START_TEST(test_s21_is_less_or_equal_2) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2),
                   1); // 5000 <= 5001 = True
}
END_TEST

START_TEST(test_s21_is_less_or_equal_3) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2),
                   0); // 5000 <= -5000 = False
}
END_TEST

START_TEST(test_s21_is_less_or_equal_4) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2),
                   0); // 5000 <= 50 = False
}
END_TEST

START_TEST(test_s21_is_less_or_equal_5) {
  s21_decimal test_value_1 = {{0, 1, 0, 0}};
  s21_decimal test_value_2 = {{0, 1, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2),
                   1); // 4294967295 <= 4294967295 = True
}
END_TEST

START_TEST(test_s21_is_greater_1) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1); // 1.2345 > 1.2 = True
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0); // 1.2 > 1.2345 = False
}
END_TEST

START_TEST(test_s21_is_greater_2) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(-1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0); // -1.2345 > -1.2 = False
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 1); // -1.2 > -1.2345 = True
}
END_TEST

START_TEST(test_s21_is_greater_3) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1); // 1.2345 > -1.2 = True
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0); // -1.2 > 1.2345 = False
}
END_TEST

START_TEST(test_s21_is_greater_4) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(0.0, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0); // 0.0 > 0.0 = False
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_1) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2),
                   1); // 0 >= 0 = True
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_2) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2),
                   0); // 5000 >= 5001 = False
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_3) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2),
                   1); // 5000 >= 50 = True
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_4) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2),
                   1); // 5000 >= -5000 = True
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_5) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2),
                   1); // 5000 >= 5000 = True
}
END_TEST

START_TEST(test_s21_is_equal_1) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2),
                   1); // 0 == 0 = True
}
END_TEST

START_TEST(test_s21_is_equal_2) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2),
                   0); // 5000 == 5001 = False
}
END_TEST

START_TEST(test_s21_is_equal_3) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2),
                   0); // 5000 == -5000 = False
}
END_TEST

START_TEST(test_s21_is_equal_4) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2),
                   0); // 5000 == 50 = False
}
END_TEST

START_TEST(test_s21_is_equal_5) {
  s21_decimal test_value_1 = {{5000, 1, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 2, 0}};
  ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2),
                   0); // number1 == number2 = False
}
END_TEST

START_TEST(test_s21_is_not_equal_1) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2),
                   0); // 0 != 0 = False
}
END_TEST

START_TEST(test_s21_is_not_equal_2) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2),
                   1); // 5000 != 5001 = True
}
END_TEST

START_TEST(test_s21_is_not_equal_3) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2),
                   1); // 5000 != -5000 = True
}
END_TEST

START_TEST(test_s21_is_not_equal_4) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2),
                   1); // 5000 != 50 = True
}
END_TEST

START_TEST(test_s21_is_not_equal_5) {
  s21_decimal test_value_1 = {{5000, 1, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 2, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2),
                   1); // number1 != number2 = True
}
END_TEST

START_TEST(not_equal_1) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(not_equal_2) {
  float num1 = 1.39;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(not_equal_3) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(not_equal_4) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(not_equal_5) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(not_equal_6) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(s21_not_equal_7) {
  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b10000000000000010000000000000000}}; // -1.2;
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);

  s21_decimal dec3 = {
      {120000, 0, 0, 0b00000000000001000000000000000000}}; //  12.0000
  s21_decimal dec4 = {{12, 0, 0, 0b00000000000000000000000000000000}}; //
  ck_assert_int_eq(s21_is_not_equal(dec3, dec4), 0);

  s21_decimal dec5 = {{0, 0, 0, 0b00000000000000000000000000000000}};  //  0
  s21_decimal dec6 = {{00, 0, 0, 0b00000000000000010000000000000000}}; //
  ck_assert_int_eq(s21_is_not_equal(dec5, dec6), 0);

  s21_decimal dec7 = {{0, 0, 0, 0b00000000000000000000000000000000}}; //   0
  s21_decimal dec8 = {{0, 0, 0, 0b10000000000000000000000000000000}}; //  -0;
  ck_assert_int_eq(s21_is_not_equal(dec7, dec8), 0);
}
END_TEST
START_TEST(less_1) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_2) {
  float num1 = 1.39;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_3) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_4) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_5) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_6) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_7) {
  float num1 = -34534534.232446543232446543;
  float num2 = -3.232323233232323233;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(s21_less_8) {
  s21_decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
  s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}}; // -1.2
  ck_assert_int_eq(s21_is_less(dec5, dec6), 0);
  ck_assert_int_eq(s21_is_less(dec6, dec5), 1);

  s21_decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}}; // -1.2345
  s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}}; //  1.2;
  ck_assert_int_eq(s21_is_less(dec7, dec8), 1);
  ck_assert_int_eq(s21_is_less(dec8, dec7), 0);

  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}}; //  1.2;
  ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
  ck_assert_int_eq(s21_is_less(dec2, dec1), 1);

  s21_decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}}; // -1.2345
  s21_decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}}; //  -1.2;
  ck_assert_int_eq(s21_is_less(dec3, dec4), 1);
  ck_assert_int_eq(s21_is_less(dec4, dec3), 0);

  s21_decimal dec9 = {{12345, 0, 0, 0}};
  s21_decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(dec9, dec10), 0);
  ck_assert_int_eq(s21_is_less(dec10, dec9), 0);

  s21_decimal dec11 = {{0, 0, 0, 0}};
  s21_decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(dec11, dec12), 0);
  ck_assert_int_eq(s21_is_less(dec12, dec11), 0);
}
END_TEST

// less or equal

START_TEST(less_or_equal_1) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_2) {
  float num1 = 1.39;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_3) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_or_equal_4) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_5) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_6) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_7) {
  float num1 = -3453434.232446543232446543;
  float num2 = -3.232323233232323233;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_8) {
  float num1 = -34534553434.232446543232446543;
  float num2 = 34534553434.232446543232446543;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_9) {
  float num1 = 1.78;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_or_equal_10) {
  float num1 = -3453453452.0;
  float num2 = -34.0;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_11) {
  float num1 = 104235454634.34534534;
  float num2 = 1042354546.34534534;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_or_equal_12) {
  float num1 = 1042354546.34534534;
  float num2 = 104235454634.345345;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_13) {
  float num1 = 1042.5667777;
  float num2 = 1042.345345;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_or_equal_14) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_15) {
  float num1 = 1.39;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_16) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_or_equal_17) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_18) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_19) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(less_or_equal_20) {
  int num1 = 10;
  int num2 = 3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_or_equal_21) {
  float num1 = 104232346.34534534;
  float num2 = 3.3453453234;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(less_or_equal_22) {
  float num1 = -3.34534534;
  float num2 = 3.34534534;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(s21_less_or_equal_23) {
  s21_decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
  s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}}; // -1.2;
  ck_assert_int_eq(s21_is_less_or_equal(dec5, dec6), 0);
  ck_assert_int_eq(s21_is_less_or_equal(dec6, dec5), 1);

  s21_decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}}; // -1.2345
  s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}}; //  1.2;
  ck_assert_int_eq(s21_is_less_or_equal(dec7, dec8), 1);
  ck_assert_int_eq(s21_is_less_or_equal(dec8, dec7), 0);

  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}}; //  1.2;
  ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2), 0);
  ck_assert_int_eq(s21_is_less_or_equal(dec2, dec1), 1);

  s21_decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}}; // -1.2345
  s21_decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}}; //  -1.2;
  ck_assert_int_eq(s21_is_less_or_equal(dec3, dec4), 1);
  ck_assert_int_eq(s21_is_less_or_equal(dec4, dec3), 0);

  s21_decimal dec9 = {{12345, 0, 0, 0}};
  s21_decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(dec9, dec10), 1);
  ck_assert_int_eq(s21_is_less_or_equal(dec10, dec9), 1);

  s21_decimal dec11 = {{0, 0, 0, 0}};
  s21_decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(dec11, dec12), 1);
  ck_assert_int_eq(s21_is_less_or_equal(dec12, dec11), 1);
}
END_TEST

START_TEST(s21_test_is_less_or_equal_1) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b),
                   S21_TRUE); // Возвращаемое значение : 0 - FALSE   1 - TRUE
}
END_TEST

START_TEST(s21_test_is_less_or_equal_2) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{U_MAX_INT, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

START_TEST(s21_test_is_less_or_equal_2i) {
  s21_decimal a = {{U_MAX_INT, 0, 0, 0}};
  s21_decimal b = {{U_MAX_INT, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

START_TEST(s21_test_is_less_or_equal_3) {
  s21_decimal a = {{U_MAX_INT - 1, 0, 0, 0}};
  s21_decimal b = {{U_MAX_INT, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

START_TEST(s21_test_is_less_or_equal_4) {
  s21_decimal a = {{U_MAX_INT, 0, 0, 0}};
  s21_decimal b = {{U_MAX_INT, 1, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

START_TEST(s21_test_is_less_or_equal_41) {
  s21_decimal a = {{U_MAX_INT, 1, 0, 0}};
  s21_decimal b = {{U_MAX_INT, 1, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

START_TEST(s21_test_is_less_or_equal_5) {
  s21_decimal a = {{U_MAX_INT, U_MAX_INT - 1, 0, 0}};
  s21_decimal b = {{U_MAX_INT, U_MAX_INT, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

// START_TEST(s21_test_is_less_or_equal_51) {
//     s21_decimal a = {{U_MAX_INT, U_MAX_INT, 0, 0}};
//     s21_decimal b = {{U_MAX_INT, U_MAX_INT, 0, 0}};
//     ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
// }
END_TEST

START_TEST(s21_test_is_less_or_equal_6) {
  s21_decimal a = {{U_MAX_INT, U_MAX_INT, U_MAX_INT, 0}};
  s21_decimal b = {{U_MAX_INT, U_MAX_INT, U_MAX_INT, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

START_TEST(s21_test_is_less_or_equal_7) {
  s21_decimal a = {{U_MAX_INT, U_MAX_INT, U_MAX_INT - 1, 0}};
  s21_decimal b = {{U_MAX_INT, U_MAX_INT, U_MAX_INT, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

START_TEST(s21_test_is_less_or_equal_8) {
  s21_decimal a = {{0, U_MAX_INT, U_MAX_INT, 0}};
  s21_decimal b = {{0, U_MAX_INT, U_MAX_INT, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

START_TEST(s21_test_is_less_or_equal_9) {
  s21_decimal a = {{0, 0, U_MAX_INT, 0}};
  s21_decimal b = {{0, 0, U_MAX_INT, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

START_TEST(s21_test_is_less_or_equal_10) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, U_MAX_INT, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), S21_TRUE);
}
END_TEST

START_TEST(s21_is_less_or_equalTest1) {
  // 3172
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest2) {
  // 3190
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest3) {
  // 3208
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest4) {
  // 3226
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest5) {
  // 3244
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest6) {
  // 3262
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest7) {
  // 3280
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest8) {
  // 3298
  s21_decimal src1, src2;
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest9) {
  // 3316
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest10) {
  // 3334
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest11) {
  // 3352
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest12) {
  // 3370
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest13) {
  // 3388
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest14) {
  // 3406
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest15) {
  // 3424
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest16) {
  // 3442
  s21_decimal src1, src2;
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest18) {
  // 3478
  s21_decimal src1, src2;
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest19) {
  // 3496
  s21_decimal src1, src2;
  // src1 = 12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest20) {
  // 3514
  s21_decimal src1, src2;
  // src1 = -12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest21) {
  // 3532
  s21_decimal src1, src2;
  // src1 = 12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest22) {
  // 3550
  s21_decimal src1, src2;
  // src1 = -12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest23) {
  // 3568
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest24) {
  // 3586
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest25) {
  // 3604
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest26) {
  // 3622
  s21_decimal src1, src2;
  // src1 = 79228162514264337593543950335;
  // src2 = -1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest27) {
  // 3640
  s21_decimal src1, src2;
  // src1 = 7922816251427554395;
  // src2 = 65645646;

  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest28) {
  // 3658
  s21_decimal src1, src2;
  // src1 = 665464545;
  // src2 = 8798232189789785;

  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest29) {
  // 3676
  s21_decimal src1, src2;
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;

  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  src2.bits[0] = 0b11010100101011100011110110001010;
  src2.bits[1] = 0b01110100000101000010011110100011;
  src2.bits[2] = 0b00000000000010000100000101000100;
  src2.bits[3] = 0b00000000000110000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest30) {
  // 3694
  s21_decimal src1, src2;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] =
      0b00011111101010011000000110101101; // 111111010100110000001101011011000101101010010000001010101100101010100010000000011110110001100
  src1.bits[3] =
      0b10000000000011000000000000000000; // -9798956154578676.797564534156

  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] =
      0b00000000000001111010100110101011; // 111101010011010101101100101111100100100110110101100
  src2.bits[2] = 0b00000000000000000000000000000000; // -2156878451.854764
  src2.bits[3] = 0b10000000000001100000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest31) {
  // 3712
  s21_decimal src1, src2;
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;

  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;
  src2.bits[0] = 0b00010111001001010100110000000010;
  src2.bits[1] = 0b00000000111101010001010110011011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest32) {
  // 3730
  s21_decimal src1, src2;
  // src1 = -0.77545545454546589781;
  // src2 = 87894515154546456456;

  src1.bits[0] = 0b10101100001010000001100001010101;
  src1.bits[1] = 0b00110100001010010001111010111100;
  src1.bits[2] = 0b00000000000000000000000000000100;
  src1.bits[3] = 0b10000000000101000000000000000000;
  src2.bits[0] = 0b00010011111011011111011110001000;
  src2.bits[1] = 0b11000011110010000000101111011001;
  src2.bits[2] = 0b00000000000000000000000000000100;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest33) {
  // 3748
  s21_decimal src1, src2;
  // src1 = -79228162514264337593543950335;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest34) {
  // 3766
  s21_decimal src1, src2;
  // src1 = 32323465788987654;
  // src2 = 67543278.89765424354657687;

  src1.bits[0] = 0b01011000010000110001100100000110;
  src1.bits[1] = 0b00000000011100101101011000000101;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b10111110000100011000010110010111;
  src2.bits[1] = 0b11011001001111010001001011000110;
  src2.bits[2] = 0b00000000000001011001011001001000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest35) {
  // 3784
  s21_decimal src1, src2;
  // src1 = -784515454.7989898652154545652;
  // src2 = -579895323215489956.67897455465;

  src1.bits[0] = 0b10110001001110110100010111110100;
  src1.bits[1] = 0b00111000100000111010110010000001;
  src1.bits[2] = 0b00011001010110010101110000011000;
  src1.bits[3] = 0b10000000000100110000000000000000;
  src2.bits[0] = 0b11100110001001011001001101101001;
  src2.bits[1] = 0b00111000110110101110001010110100;
  src2.bits[2] = 0b10111011010111111101000100011110;
  src2.bits[3] = 0b10000000000010110000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equalTest36) {
  // 3802
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = -37986322154988653.784354545765;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b01001111101101000110000001100101;
  src2.bits[1] = 0b01000010001101101011011001100001;
  src2.bits[2] = 0b01111010101111011000110010011010;
  src2.bits[3] = 0b10000000000011000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

// greater

START_TEST(greater_1) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_2) {
  float num1 = 1.39;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_3) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(greater_4) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_5) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_6) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_7) {
  int num1 = -3;
  int num2 = 3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_8) {
  float num1 = -3.232446546;
  float num2 = -3.2;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_9) {
  float num1 = -345.232446546;
  float num2 = -3.2;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_10) {
  float num1 = -3.232323233232323233;
  float num2 = -34545124.232446543232446543;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_11) {
  s21_decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
  s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}}; //  -1.2;
  ck_assert_int_eq(s21_is_greater(dec5, dec6), 1);
  ck_assert_int_eq(s21_is_greater(dec6, dec5), 0);

  s21_decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}}; // -1.2345
  s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}}; //  1.2;
  ck_assert_int_eq(s21_is_greater(dec7, dec8), 0);
  ck_assert_int_eq(s21_is_greater(dec8, dec7), 1);

  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}}; //  1.2
  ck_assert_int_eq(s21_is_greater(dec1, dec2), 1);
  ck_assert_int_eq(s21_is_greater(dec2, dec1), 0);

  s21_decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}}; // -1.2345
  s21_decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}}; //   -1.2
  ck_assert_int_eq(s21_is_greater(dec3, dec4), 0);
  ck_assert_int_eq(s21_is_greater(dec4, dec3), 1);
}
END_TEST

START_TEST(greater_12) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b),
                   S21_TRUE); // Возвращаемое значение : 0 - FALSE   1 - TRUE
}
END_TEST

START_TEST(greater_13) {
  s21_decimal a = {{S21_MAX_UINT, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_TRUE);
}
END_TEST

START_TEST(greater_14) {
  s21_decimal a = {{S21_MAX_UINT, 0, 0, 0}};
  s21_decimal b = {{S21_MAX_UINT - 1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_TRUE);
}
END_TEST

START_TEST(greater_15) {
  s21_decimal a = {{S21_MAX_UINT, 0, 0, 0}};
  s21_decimal b = {{S21_MAX_UINT, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_FALSE);
}
END_TEST

START_TEST(greater_16) {
  s21_decimal a = {{S21_MAX_UINT, 0, 0, 0}};
  s21_decimal b = {{S21_MAX_UINT, 1, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_FALSE);
}
END_TEST

START_TEST(greater_17) {
  s21_decimal a = {{S21_MAX_UINT, 1, 0, 0}};
  s21_decimal b = {{S21_MAX_UINT, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_TRUE);
}
END_TEST

START_TEST(greater_18) {
  s21_decimal a = {{S21_MAX_UINT, S21_MAX_UINT, 0, 0}};
  s21_decimal b = {{S21_MAX_UINT, S21_MAX_UINT - 1, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_TRUE);
}
END_TEST

START_TEST(greater_19) {
  s21_decimal a = {{S21_MAX_UINT, S21_MAX_UINT, 0, 0}};
  s21_decimal b = {{S21_MAX_UINT, S21_MAX_UINT, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_FALSE);
}
END_TEST

START_TEST(greater_20) {
  s21_decimal a = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal b = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT - 1, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_TRUE);
}
END_TEST

START_TEST(greater_21) {
  s21_decimal a = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT - 1, 0}};
  s21_decimal b = {{S21_MAX_UINT, S21_MAX_UINT, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_TRUE);
}
END_TEST

START_TEST(greater_22) {
  s21_decimal a = {{0, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal b = {{0, S21_MAX_UINT, S21_MAX_UINT - 1, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_TRUE);
}
END_TEST

START_TEST(greater_23) {
  s21_decimal a = {{0, 0, S21_MAX_UINT, 0}};
  s21_decimal b = {{0, 0, S21_MAX_UINT - 1, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_TRUE);
}
END_TEST

START_TEST(greater_24) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, S21_MAX_UINT, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), S21_FALSE);
}
END_TEST

START_TEST(greater_25) {
  // 3820
  s21_decimal src1, src2;
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_26) {
  // 3838
  s21_decimal src1, src2;
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_27) {
  // 3856
  s21_decimal src1, src2;
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_28) {
  // 3874
  s21_decimal src1, src2;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_29) {
  // 3892
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_30) {
  // 3910
  s21_decimal src1, src2;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_31) {
  // 3928
  s21_decimal src1, src2;
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_32) {
  // 3946
  s21_decimal src1, src2;
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_33) {
  // 3964
  s21_decimal src1, src2;
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_34) {
  // 3982
  s21_decimal src1, src2;
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_35) {
  // 4000
  s21_decimal src1, src2;
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_36) {
  // 4018
  s21_decimal src1, src2;
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_37) {
  // 4036
  s21_decimal src1, src2;
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_38) {
  // 4054
  s21_decimal src1, src2;
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_39) {
  // 4072
  s21_decimal src1, src2;
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_40) {
  // 4090
  s21_decimal src1, src2;
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_41) {
  // 4108
  s21_decimal src1, src2;
  // src1 = -545454512454545.35265454545645;
  // src2 = -5.352654545456454545645464;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  src2.bits[0] = 0b01001000000110110001111110011000;
  src2.bits[1] = 0b11111011111111011000100101101101;
  src2.bits[2] = 0b00000000000001000110110101110111;
  src2.bits[3] = 0b10000000000110000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_42) {
  // 4126
  s21_decimal src1, src2;
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_43) {
  // 4144
  s21_decimal src1, src2;
  // src1 = 12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_44) {
  // 4162
  s21_decimal src1, src2;
  // src1 = -12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_45) {
  // 4180
  s21_decimal src1, src2;
  // src1 = 12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_46) {
  // 4198
  s21_decimal src1, src2;
  // src1 = -12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_47) {
  // 4216
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_48) {
  // 4234
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_49) {
  // 4252
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_50) {
  // 4270
  s21_decimal src1, src2;
  // src1 = 79228162514264337593543950335;
  // src2 = -1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_51) {
  // 4288
  s21_decimal src1, src2;
  // src1 = 7922816251427554395;
  // src2 = 65645646;

  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_52) {
  // 4306
  s21_decimal src1, src2;
  // src1 = 665464545;
  // src2 = 8798232189789785;

  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_53) {
  // 4324
  s21_decimal src1, src2;
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;

  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  src2.bits[0] = 0b11010100101011100011110110001010;
  src2.bits[1] = 0b01110100000101000010011110100011;
  src2.bits[2] = 0b00000000000010000100000101000100;
  src2.bits[3] = 0b00000000000110000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_54) {
  // 4342
  s21_decimal src1, src2;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;
  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_55) {
  // 4360
  s21_decimal src1, src2;
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;

  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;
  src2.bits[0] = 0b00010111001001010100110000000010;
  src2.bits[1] = 0b00000000111101010001010110011011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_56) {
  // 4378
  s21_decimal src1, src2;
  // src1 = -0.77545545454546589781;
  // src2 = 87894515154546456456;

  src1.bits[0] = 0b10101100001010000001100001010101;
  src1.bits[1] = 0b00110100001010010001111010111100;
  src1.bits[2] = 0b00000000000000000000000000000100;
  src1.bits[3] = 0b10000000000101000000000000000000;
  src2.bits[0] = 0b00010011111011011111011110001000;
  src2.bits[1] = 0b11000011110010000000101111011001;
  src2.bits[2] = 0b00000000000000000000000000000100;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_57) {
  // 4396
  s21_decimal src1, src2;
  // src1 = -79228162514264337593543950335;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_58) {
  // 4414
  s21_decimal src1, src2;
  // src1 = 32323465788987654;
  // src2 = 67543278.89765424354657687;

  src1.bits[0] = 0b01011000010000110001100100000110;
  src1.bits[1] = 0b00000000011100101101011000000101;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b10111110000100011000010110010111;
  src2.bits[1] = 0b11011001001111010001001011000110;
  src2.bits[2] = 0b00000000000001011001011001001000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_59) {
  // 4432
  s21_decimal src1, src2;
  // src1 = -784515454.7989898652154545652;
  // src2 = -579895323215489956.67897455465;

  src1.bits[0] = 0b10110001001110110100010111110100;
  src1.bits[1] = 0b00111000100000111010110010000001;
  src1.bits[2] = 0b00011001010110010101110000011000;
  src1.bits[3] = 0b10000000000100110000000000000000;
  src2.bits[0] = 0b11100110001001011001001101101001;
  src2.bits[1] = 0b00111000110110101110001010110100;
  src2.bits[2] = 0b10111011010111111101000100011110;
  src2.bits[3] = 0b10000000000010110000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_60) {
  // 4450
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = -37986322154988653.784354545765;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b01001111101101000110000001100101;
  src2.bits[1] = 0b01000010001101101011011001100001;
  src2.bits[2] = 0b01111010101111011000110010011010;
  src2.bits[3] = 0b10000000000011000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

// greater or equal

START_TEST(greater_or_equal_1) {
  float num1 = 1.375323;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_or_equal_2) {
  int num1 = 2;
  int num2 = 1;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(greater_or_equal_3) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(greater_or_equal_4) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(greater_or_equal_5) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_or_equal_6) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(greater_or_equal_7) {
  int num1 = 10;
  int num2 = 3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(greater_or_equal_8) {
  float num1 = 10423546.34534534;
  float num2 = 3.34534534;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(greater_or_equal_9) {
  float num1 = -3.34534534;
  float num2 = 3.34534534;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_or_equal_10) {
  float num1 = 1042634.34534534;
  float num2 = 10424546.34534534;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_or_equal_11) {
  float num1 = 10426.34534534;
  float num2 = 104234.345345;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(greater_or_equal_12) {
  float num1 = 1042.5667777;
  float num2 = 1042.345345;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(greater_or_equal_13) {
  s21_decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
  s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}}; //
  ck_assert_int_eq(s21_is_greater_or_equal(dec5, dec6), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec6, dec5), 0);

  s21_decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}}; // -1.2345
  s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec7, dec8), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(dec8, dec7), 1);

  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec2, dec1), 0);

  s21_decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}}; // -1.2345
  s21_decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}}; //

  ck_assert_int_eq(s21_is_greater_or_equal(dec3, dec4), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(dec4, dec3), 1);

  s21_decimal dec9 = {{12345, 0, 0, 0}};
  s21_decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec9, dec10), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec10, dec9), 1);

  s21_decimal dec11 = {{0, 0, 0, 0}};
  s21_decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec11, dec12), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec12, dec11), 1);
}
END_TEST

START_TEST(equal_1) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(equal_2) {
  float num1 = 1.39;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(equal_3) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(equal_4) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(equal_5) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(equal_6) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(equal_7) {
  float num1 = 7.0000003;
  float num2 = 1.1;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(equal_8) {
  float num1 = 7.9e+28;
  float num2 = 1.342;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(equal_9) {
  float num1 = 7.9e+25;
  float num2 = 1.342;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(equal_10) {
  float num1 = NAN;
  float num2 = 2.3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, FALSE);
}
END_TEST

START_TEST(s21_equal_null_12) {
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(0, &dec1);
  s21_from_int_to_decimal(0, &dec2);
  dec1.bits[3] = 0;
  ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(s21_is_equalTest1) {
  // 5116
  s21_decimal src1, src2;
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest2) {
  // 5134
  s21_decimal src1, src2;
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest3) {
  // 5152
  s21_decimal src1, src2;
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest4) {
  // 5170
  s21_decimal src1, src2;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest5) {
  // 5188
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest6) {
  // 5206
  s21_decimal src1, src2;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest7) {
  // 5224
  s21_decimal src1, src2;
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest8) {
  // 5242
  s21_decimal src1, src2;
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest9) {
  // 5260
  s21_decimal src1, src2;
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest10) {
  // 5278
  s21_decimal src1, src2;
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest11) {
  // 5296
  s21_decimal src1, src2;
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest12) {
  // 5314
  s21_decimal src1, src2;
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest13) {
  // 5332
  s21_decimal src1, src2;
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest14) {
  // 5350
  s21_decimal src1, src2;
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest15) {
  // 5368
  s21_decimal src1, src2;
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;

  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest16) {
  // 5386
  s21_decimal src1, src2;
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;

  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest17) {
  // 5404
  s21_decimal src1, src2;
  // src1 = -545454512454545.35265454545645;
  // src2 = -5.352654545456454545645464;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;

  src2.bits[0] = 0b01001000000110110001111110011000;
  src2.bits[1] = 0b11111011111111011000100101101101;
  src2.bits[2] = 0b00000000000001000110110101110111;
  src2.bits[3] = 0b10000000000110000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest18) {
  // 5422
  s21_decimal src1, src2;
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest19) {
  // 5440
  s21_decimal src1, src2;
  // src1 = 12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest20) {
  // 5458
  s21_decimal src1, src2;
  // src1 = -12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest21) {
  // 5476
  s21_decimal src1, src2;
  // src1 = 12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest22) {
  // 5494
  s21_decimal src1, src2;
  // src1 = -12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest23) {
  // 5512
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest24) {
  // 5530
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest25) {
  // 5548
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest26) {
  // 5566
  s21_decimal src1, src2;
  // src1 = 79228162514264337593543950335;
  // src2 = -1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest27) {
  // 5584
  s21_decimal src1, src2;
  // src1 = 7922816251427554395;
  // src2 = 65645646;

  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest28) {
  // 5602
  s21_decimal src1, src2;
  // src1 = 665464545;
  // src2 = 8798232189789785;

  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest29) {
  // 5620
  s21_decimal src1, src2;
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;

  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;

  src2.bits[0] = 0b11010100101011100011110110001010;
  src2.bits[1] = 0b01110100000101000010011110100011;
  src2.bits[2] = 0b00000000000010000100000101000100;
  src2.bits[3] = 0b00000000000110000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest30) {
  // 5638
  s21_decimal src1, src2;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;

  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest31) {
  // 5656
  s21_decimal src1, src2;
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;

  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;

  src2.bits[0] = 0b00010111001001010100110000000010;
  src2.bits[1] = 0b00000000111101010001010110011011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest32) {
  // 5674
  s21_decimal src1, src2;
  // src1 = -0.77545545454546589781;
  // src2 = 87894515154546456456;

  src1.bits[0] = 0b10101100001010000001100001010101;
  src1.bits[1] = 0b00110100001010010001111010111100;
  src1.bits[2] = 0b00000000000000000000000000000100;
  src1.bits[3] = 0b10000000000101000000000000000000;

  src2.bits[0] = 0b00010011111011011111011110001000;
  src2.bits[1] = 0b11000011110010000000101111011001;
  src2.bits[2] = 0b00000000000000000000000000000100;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest33) {
  // 5692
  s21_decimal src1, src2;
  // src1 = -79228162514264337593543950335;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest34) {
  // 5710
  s21_decimal src1, src2;
  // src1 = 32323465788987654;
  // src2 = 67543278.89765424354657687;

  src1.bits[0] = 0b01011000010000110001100100000110;
  src1.bits[1] = 0b00000000011100101101011000000101;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b10111110000100011000010110010111;
  src2.bits[1] = 0b11011001001111010001001011000110;
  src2.bits[2] = 0b00000000000001011001011001001000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest35) {
  // 5728
  s21_decimal src1, src2;
  // src1 = -784515454.7989898652154545652;
  // src2 = -579895323215489956.67897455465;

  src1.bits[0] = 0b10110001001110110100010111110100;
  src1.bits[1] = 0b00111000100000111010110010000001;
  src1.bits[2] = 0b00011001010110010101110000011000;
  src1.bits[3] = 0b10000000000100110000000000000000;

  src2.bits[0] = 0b11100110001001011001001101101001;
  src2.bits[1] = 0b00111000110110101110001010110100;
  src2.bits[2] = 0b10111011010111111101000100011110;
  src2.bits[3] = 0b10000000000010110000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equalTest36) {
  // 5746
  s21_decimal src1, src2;
  // src1 = 0;
  // src2 = -37986322154988653.784354545765;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b01001111101101000110000001100101;
  src2.bits[1] = 0b01000010001101101011011001100001;
  src2.bits[2] = 0b01111010101111011000110010011010;
  src2.bits[3] = 0b10000000000011000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal1) {
  s21_decimal result;
  s21_from_int_to_decimal(0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal2) {
  s21_decimal result;
  s21_from_int_to_decimal(-128, &result);
  ck_assert_int_eq(result.bits[0], 128);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_3) {
  s21_decimal result;
  s21_from_int_to_decimal(5000, &result);
  ck_assert_int_eq(result.bits[0], 5000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_4) {
  s21_decimal result;
  s21_from_int_to_decimal(-2147483648, &result);
  ck_assert_int_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_5) {
  s21_decimal result;
  s21_from_int_to_decimal(2147483647, &result);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(int_to_dec_1) {
  int src = INT_MIN;
  s21_decimal expected = {{INT_MIN, 0, 0, 0}};
  set_sign(&expected, 1);
  s21_decimal result;
  int status = s21_from_int_to_decimal(src, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(int_to_dec_2) {
  int src = INT_MAX;
  s21_decimal expected = {{INT_MAX, 0, 0, 0}};
  s21_decimal result;
  int status = s21_from_int_to_decimal(src, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(int_to_dec_3) {
  int src = 0;
  s21_decimal expected = {{0}};
  s21_decimal result;
  int status = s21_from_int_to_decimal(src, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(int_to_dec_4) {
  int src = 1234567;
  s21_decimal expected = {{1234567, 0, 0, 0}};
  s21_decimal result;
  int status = s21_from_int_to_decimal(src, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(int_to_dec_5) {
  int src = -98765;
  s21_decimal expected = {{98765, 0, 0, 0}};
  set_sign(&expected, 1);
  s21_decimal result;
  int status = s21_from_int_to_decimal(src, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal1) {
  s21_decimal result;
  s21_from_float_to_decimal(0.03, &result);
  float a = 0.03;
  float b = 0;
  s21_from_decimal_to_float(result, &b);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal2) {
  s21_decimal result;
  s21_from_float_to_decimal(127.1234, &result);
  float a = 127.1234;
  float b = 0;
  s21_from_decimal_to_float(result, &b);
  ck_assert_float_eq(a, b);
}
END_TEST
//////////////////////////////////////////////////////////// 1e-4 это печально
START_TEST(test_s21_form_float_to_decimal_3) {
  s21_decimal result;
  s21_from_float_to_decimal(-128.023, &result);
  float a = -128.023;
  float b = 0;
  s21_from_decimal_to_float(result, &b);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_4) {
  s21_decimal result;
  s21_from_float_to_decimal(22.14836E+03, &result);
  float a = 22.14836E+03;
  float b = 0;
  s21_from_decimal_to_float(result, &b);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_5) {
  s21_decimal result;
  s21_from_float_to_decimal(1.02E+09, &result);
  float a = 1.02E+09;
  float b = 0;
  s21_from_decimal_to_float(result, &b);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_6) {
  s21_decimal result;
  s21_from_float_to_decimal(-333.2222, &result);
  float a = -333.2222;
  float b = 0;
  s21_from_decimal_to_float(result, &b);
  float eps = 1e-6;
  ck_assert_float_eq_tol(a, b, eps);
}
END_TEST

START_TEST(float_1) {
  s21_decimal dec;
  s21_from_float_to_decimal(-0.478965218, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -0.478965218, 1e-06);
}
END_TEST

START_TEST(float_2) {
  s21_decimal dec;
  s21_from_float_to_decimal(0.8541465951, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 0.8541465951, 1e-06);
}
END_TEST

START_TEST(float_3) {
  s21_decimal dec;
  s21_from_float_to_decimal(1.4896752254, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 1.4896752254, 1e-05);
}
END_TEST

START_TEST(float_4) {
  s21_decimal dec;
  s21_from_float_to_decimal(-1.89651472, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -1.89651472, 1e-05);
}
END_TEST

START_TEST(float_5) {
  s21_decimal dec;
  s21_from_float_to_decimal(-10.000584145, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -10.000584145, 1e-04);
}
END_TEST

START_TEST(float_6) {
  s21_decimal dec;
  s21_from_float_to_decimal(87.185547514, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 87.185547514, 1e-04);
}
END_TEST

START_TEST(float_7) {
  s21_decimal dec;
  s21_from_float_to_decimal(954.6547892, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 954.6547892, 1e-03);
}
END_TEST

START_TEST(float_8) {
  s21_decimal dec;
  s21_from_float_to_decimal(-547.6587123, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -547.6587123, 1e-03);
}
END_TEST

START_TEST(float_9) {
  s21_decimal dec;
  s21_from_float_to_decimal(-1547.6587123, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -1547.6587123, 1e-02);
}
END_TEST

START_TEST(float_10) {
  s21_decimal dec;
  s21_from_float_to_decimal(6874.98541, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 6874.98541, 1e-02);
}
END_TEST

START_TEST(float_11) {
  s21_decimal dec;
  s21_from_float_to_decimal(-86874.98541, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -86874.98541, 1e-01);
}
END_TEST

START_TEST(float_12) {
  s21_decimal dec;
  s21_from_float_to_decimal(-686874.98541, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -686874.98541, 1);
}
END_TEST

START_TEST(float_13) {
  s21_decimal dec;
  s21_from_float_to_decimal(-686874.98541, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -686874.98541, 1);
}
END_TEST

START_TEST(float_14) {
  s21_decimal dec;
  s21_from_float_to_decimal(4.189654154e18, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 4.189654154e18, 1e+12);
}
END_TEST

START_TEST(float_15) {
  s21_decimal dec;
  int a = s21_from_float_to_decimal(4e30, &dec);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(float_16) {
  s21_decimal dec;
  s21_from_float_to_decimal(5.6584159654e25, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 5.6584159654e25, 1e+19);
}
END_TEST

START_TEST(float_17) {
  s21_decimal dec;
  int a = s21_from_float_to_decimal(4e-30, &dec);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(test_s21_decimal_to_int_1) {
  int number = 0;
  s21_decimal src = {{2147483647, 0, 0, 0}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 2147483647);
}
END_TEST

START_TEST(test_s21_decimal_to_int_2) {
  int number = 0;
  s21_decimal src = {{0, 0, 0, 0}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
}
END_TEST

START_TEST(test_s21_decimal_to_int_3) {
  int number = 0;
  s21_decimal src = {{5000, 0, 0, 2147483648}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -5000);
}
END_TEST

START_TEST(test_s21_decimal_to_int_4) {
  int number = 0;
  s21_decimal src = {{2147483648, 0, 0, 2147483648}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -2147483648);
}
END_TEST

START_TEST(dec_to_int_1) {
  int expected = INT_MAX, result;
  s21_decimal src = {{INT_MAX, 0, 0, 0}};
  int status = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(status, 0);
}

START_TEST(dec_to_int_2) {
  int expected = INT_MIN, result;
  s21_decimal src = {{INT_MIN, 0, 0, 0}};
  set_sign(&src, 1);
  int status = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(status, 0);
}

/* START_TEST(dec_to_int_3) { */
/*     int result = 0; */
/*     s21_decimal src = {{INT_MIN, 0, 0, 0}}; */
/*     int status = s21_from_decimal_to_int(src, &result); */
/*     ck_assert_int_eq(status, 1); */
/* } */

START_TEST(dec_to_int_4) {
  s21_decimal dec;
  int result = 0;
  int number = 0;
  dec.bits[0] = 2147483647;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;
  result = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, 2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(dec_to_int_5) {
  s21_decimal dec;
  int result = 0;
  int number = 0;
  dec.bits[0] = 133141;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;
  result = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, 133141);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(dec_to_int_6) {
  s21_decimal dec;
  int result = 0;
  int number = 0;
  dec.bits[0] = 2147483648;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;
  set_sign(&dec, 1);
  result = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, -2147483648);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(dec_to_int_7) {
  s21_decimal dec;
  int result = 0, number = 0;
  dec.bits[0] = 123451234;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 2147483648;
  result = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, -123451234);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(dec_to_int_8) {
  s21_decimal dec;
  int result = 0, number = 0;
  dec.bits[0] = 18;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 2147483648;
  result = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(dec_to_int_9) {
  s21_decimal dec;
  int result = 0, number = 0;
  dec.bits[0] = 1714336475;
  dec.bits[1] = 602887423;
  dec.bits[2] = 48737584;
  dec.bits[3] = 2148401152;
  result = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_decimal_to_float_1) {
  float number = 0.0;
  s21_decimal src = {{18122, 0, 0, 2147680256}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
}
END_TEST

START_TEST(test_s21_decimal_to_float_2) {
  float number = 0.0;
  s21_decimal src = {{1812, 0, 0, 2147483648}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
}
END_TEST

START_TEST(test_s21_decimal_to_float_3) {
  float number = 0.0;
  s21_decimal src = {{23450987, 0, 0, 2147745792}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
}
END_TEST

START_TEST(test_s21_decimal_to_float_4) {
  float number = 0.0;
  s21_decimal src = {{4294967295, 4294967295, 0, 0}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
}
END_TEST

START_TEST(test_s21_floor_1) {
  s21_decimal value_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal value_1 = {{679988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal value_1 = {{679988, 0, 0, 2147745796}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 68);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_floor_4) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 131072}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 687194767);
  ck_assert_float_eq(result.bits[1], 4123168604);
  ck_assert_float_eq(result.bits[2], 42949672);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_5) {
  s21_decimal value_1 = {{5, 1, 0, 131072}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 42949673);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_6) {
  s21_decimal value_1 = {{4294967295, 0, 1, 131072}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4166118277);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_7) {
  s21_decimal value_1 = {{115, 0, 1, 2147483648}};
  s21_set_scale(2, &value_1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4123168606);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_floor_8) {
  s21_decimal value_1 = {{5, 0, 1, 0}};
  s21_set_scale(2, &value_1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4123168604);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_floor_1) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111011;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000000000000000010100101;
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000010000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10010011111111111111110001010010; // 2483027.026
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000110000000000000000; // 3
  s21_decimal result;
  result.bits[0] = 0b00000000001001011110001101010011;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10010011111111111111110001010011;
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000000110000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000001001011110001101010100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal dec1;

  dec1.bits[0] = 0b00001111111111111111111111111111;
  dec1.bits[1] = 0b00111110001001010000001001100001;
  dec1.bits[2] = 0b00100000010011111100111001011110;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b10100111011000111111111111111111;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_6) {
  s21_decimal dec1;

  dec1.bits[0] = 0b00001111111111111111111111111111;
  dec1.bits[1] = 0b00111110001001010000001001100001;
  dec1.bits[2] = 0b00100000010011111100111001011110;
  dec1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_7) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10111101001001111000010001010010;
  dec1.bits[1] = 0b00000000000000000000000000011100;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000010010000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_8) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111011;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_9) {
  s21_decimal dec1;

  dec1.bits[0] = 0b01010101001110101110101110110001;
  dec1.bits[1] = 0b00001101101101001101101001011111;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000100100000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_10) {
  s21_decimal dec1;

  dec1.bits[0] = 0b01010101001110101110101110110001;
  dec1.bits[1] = 0b00001101101101001101101001011111;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000100100000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_11) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10010111011100111001111111111111;
  dec1.bits[1] = 0b00111100000010000011000110001101;
  dec1.bits[2] = 0b00000000000000000000000000000001;
  dec1.bits[3] = 0b00000000000001110000000000000000;
  s21_decimal result;
  s21_floor(dec1, &result);
  s21_decimal result_origin;
  result_origin.bits[3] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0b00000000000000000000001000010010;
  result_origin.bits[0] = 0b00110110101101101000110000111111;
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floor_01) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  float num = 0.0;
  s21_from_decimal_to_float(dec1, &num);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111011;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_02) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000000000000000010100101;
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  float num = 0.0;
  s21_from_decimal_to_float(dec1, &num);
  // printf("%f", num);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000010000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floorTest1) {
  // 7130
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = 2;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest2) {
  // 7151
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest3) {
  // 7172
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = -3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest4) {
  // 7193
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest5) {
  // 7214
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = -1.2;

  src1.bits[0] = 0b00000000000000000000000000001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest6) {
  // 7235
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = -545454512454545.35265454545645;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  origin.bits[0] = 0b10000110011101001011101110010010;
  origin.bits[1] = 0b00000000000000011111000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest7) {
  // 7256
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = -5.492654545456454545645464;

  src1.bits[0] = 0b00000111100110110001111110011000;
  src1.bits[1] = 0b01100110010010001001000110100011;
  src1.bits[2] = 0b00000000000001001000101100011101;
  src1.bits[3] = 0b10000000000110000000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest8) {
  // 7277
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = 7961327845421.879754123131254;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  origin.bits[0] = 0b10100100000111100100000000101101;
  origin.bits[1] = 0b00000000000000000000011100111101;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest9) {
  // 7298
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = -12345677.187654345678987654346;

  src1.bits[0] = 0b01111000100010101111010011001010;
  src1.bits[1] = 0b01100010000010101110010010000111;
  src1.bits[2] = 0b00100111111001000001101011010101;
  src1.bits[3] = 0b10000000000101010000000000000000;

  origin.bits[0] = 0b00000000101111000110000101001110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest10) {
  // 7319
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = 2.1986531268974139743;

  src1.bits[0] = 0b00010010001110001101100101011111;
  src1.bits[1] = 0b00110001000111111101100110110011;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest11) {
  // 7340
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = 1;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_round_1) {
  s21_decimal value_1 = {{5, 0, 1, 0}};
  s21_set_scale(2, &value_1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4123168604);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_2) {
  s21_decimal value_1 = {{5, 1, 1, 0}};
  s21_set_scale(2, &value_1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4166118277);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_3) {
  s21_decimal value_1 = {{155, 1, 1, 0}};
  s21_set_scale(2, &value_1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4166118279);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_4) {
  s21_decimal value_1 = {{155, 1, 1, 2147483648}};
  s21_set_scale(2, &value_1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4166118279);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_round_5) {
  s21_decimal value_1 = {{0, 1, 0, 0}};
  s21_set_scale(1, &value_1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 429496730);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_round_1) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000000000000000010100101; // -16.5
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000000010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000010001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal dec1;
  dec1.bits[0] = 0b11111111111111111111111111111111; // 18014398509481.983
  dec1.bits[1] = 0b00000000001111111111111111111111;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000110000000000000000;
  s21_decimal result;

  result.bits[0] = 0b01001101110100101111000110101001; // 18014398509481
  result.bits[1] = 0b00000000000000000001000001100010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000011110111001001110100; // -10123.40
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000000110000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000001111110100; // -1012
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10000000000000000000001111110100; // 112590205.4327284
  dec1.bits[1] = 0b00000000000001000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000110101101011111110101111101; // 112590205
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10000000000000000000001111110100; // 2147484660
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result;
  result.bits[0] = 0b10000000000000000000001111110100; // 2147484660
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_7) {
  s21_decimal dec1;

  dec1.bits[0] = 0b01100011000011111111111111111111;
  dec1.bits[1] = 0b01101011110001110101111000101101;
  dec1.bits[2] = 0b00000000000000000000000000000101;
  dec1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b01010100000010111110010000000000;
  result.bits[1] = 0b00000000000000000000000000000010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal dec1;

  dec1.bits[0] = 0b01010101001110101110101110110001;
  dec1.bits[1] = 0b00001101101101001101101001011111;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000100100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_9) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_10) {
  s21_decimal dec1;

  dec1.bits[0] = 0b11001101110001110111110001000000;
  dec1.bits[1] = 0b00111110001001010000001001100000;
  dec1.bits[2] = 0b00100000010011111100111001011110;
  dec1.bits[3] = 0b10000000000001000000000000000000;
  s21_decimal result;
  result.bits[0] = 0b10100000111111100100111000000100;
  result.bits[1] = 0b00011011110011101100110011101101;
  result.bits[2] = 0b00000000000000001101001111000010;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_11) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10100000111111100100111000000100;
  dec1.bits[1] = 0b00011011110011101100110011101101;
  dec1.bits[2] = 0b00000000000000001101001111000010;
  dec1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b10100000111111100100111000000100;
  result.bits[1] = 0b00011011110011101100110011101101;
  result.bits[2] = 0b00000000000000001101001111000010;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_12) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10010111011100111001111111111111;
  dec1.bits[1] = 0b00111100000010000011000110001101;
  dec1.bits[2] = 0b00000000000000000000000000000001;
  dec1.bits[3] = 0b00000000000001110000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b00110110101101101000110001000000;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_13) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10010111011100111001111111111111;
  dec1.bits[1] = 0b00111100000010000011000110001101;
  dec1.bits[2] = 0b00000000000000000000000000000001;
  dec1.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b00110110101101101000110001000000;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_roundTest1) {
  // 8053
  s21_decimal src1, origin;
  // src1 = 2;

  src1.bits[0] = 2;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 2;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest2) {
  // 8074
  s21_decimal src1, origin;
  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest3) {
  // 8095
  s21_decimal src1, origin;
  // src1 = -3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest4) {
  // 8116
  s21_decimal src1, origin;
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest5) {
  // 8137
  s21_decimal src1, origin;
  // src1 = -9878798789;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b01001100110100101000000111000101;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest6) {
  // 8158
  s21_decimal src1, origin;
  // src1 = -545454512454545.35265;

  src1.bits[0] = 0b11011110101101001010101001100001;
  src1.bits[1] = 0b11110100111110000101111011101001;
  src1.bits[2] = 0b00000000000000000000000000000010;
  src1.bits[3] = 0b10000000000001010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b10000110011101001011101110010001;
  origin.bits[1] = 0b00000000000000011111000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

/* START_TEST(s21_roundTest7) { */
/*   // 8179 */
/*   s21_decimal src1, origin; */
/*   // src1 = -5.492654545456454545645464; */

/*   src1.bits[0] = 0b00000111100110110001111110011000; */
/*   src1.bits[1] = 0b01100110010010001001000110100011; */
/*   src1.bits[2] = 0b00000000000001001000101100011101; */
/*   src1.bits[3] = 0b10000000000110000000000000000000; */
/*   s21_decimal result = {{0, 0, 0, 0}}; */
/*   s21_round(src1, &result); */
/*   origin.bits[0] = 0b00000000000000000000000000000110; */
/*   origin.bits[1] = 0b00000000000000000000000000000000; */
/*   origin.bits[2] = 0b00000000000000000000000000000000; */
/*   origin.bits[3] = 0b10000000000000000000000000000000; */
/*   ck_assert_int_eq(origin.bits[3], result.bits[3]); */
/*   ck_assert_int_eq(origin.bits[2], result.bits[2]); */
/*   ck_assert_int_eq(origin.bits[1], result.bits[1]); */
/*   ck_assert_int_eq(origin.bits[0], result.bits[0]); */
/* } */
/* END_TEST */

START_TEST(s21_roundTest8) {
  // 8200
  s21_decimal src1, origin;
  // src1 = 7961327845421.879754123131254;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b10100100000111100100000000101110;
  origin.bits[1] = 0b00000000000000000000011100111101;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest9) {
  // 8221
  s21_decimal src1, origin;
  // src1 = -12345677.187654345678987654346;

  src1.bits[0] = 0b01111000100010101111010011001010;
  src1.bits[1] = 0b01100010000010101110010010000111;
  src1.bits[2] = 0b00100111111001000001101011010101;
  src1.bits[3] = 0b10000000000101010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000101111000110000101001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest10) {
  // 8242
  s21_decimal src1, origin;
  // src1 = 2.5986531268974139743;

  src1.bits[0] = 0b10101111110010001101100101011111;
  src1.bits[1] = 0b01101000101000101011010010000001;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest11) {
  // 8263
  s21_decimal src1, origin;
  // src1 = 1;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest12) {
  // 8284
  s21_decimal src1, origin;
  // src1 = 1.1;

  src1.bits[0] = 0b00000000000000000000000000001011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest13) {
  // 8305
  s21_decimal src1, origin;
  // src1 = -1.1;

  src1.bits[0] = 0b00000000000000000000000000001011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest14) {
  // 8326
  s21_decimal src1, origin;
  // src1 = 24.56;

  src1.bits[0] = 0b00000000000000000000100110011000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000100000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000011001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_roundTest15) {
  // 8347
  s21_decimal src1, origin;
  // src1 = -2.124;

  src1.bits[0] = 0b00000000000000000000100001001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000110000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_negate_1) {
  s21_decimal value_1 = {{155, 1, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal value_1 = {{155, 1, 1, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_negate_1) {
  int a = 15;
  int res_a = 0;
  s21_decimal src;
  s21_decimal res;
  s21_from_int_to_decimal(a, &src);
  s21_negate(src, &res);
  s21_from_decimal_to_int(res, &res_a);
  ck_assert_int_eq(-15, res_a);
}
END_TEST

START_TEST(s21_negate_2) {
  float a = 10.12345;
  float res_a = 0;
  s21_decimal src;
  s21_decimal res;
  s21_from_float_to_decimal(a, &src);
  s21_negate(src, &res);
  s21_from_decimal_to_float(res, &res_a);
  ck_assert_float_eq(-10.12345, res_a);
}
END_TEST

START_TEST(s21_negate_3) {
  float a = 10.1234e5;
  float res_a = 0;
  s21_decimal src;
  s21_decimal res;
  s21_from_float_to_decimal(a, &src);
  s21_negate(src, &res);
  s21_from_decimal_to_float(res, &res_a);
  ck_assert_float_eq(-10.1234e5, res_a);
}
END_TEST

START_TEST(s21_negate_4) {
  float a = -10.1234e5;
  float res_a = 0;
  s21_decimal src;
  s21_decimal res;
  s21_from_float_to_decimal(a, &src);
  s21_negate(src, &res);
  s21_from_decimal_to_float(res, &res_a);
  ck_assert_float_eq(10.1234e5, res_a);
}
END_TEST

START_TEST(s21_negate_5) {
  int a = -15;
  int res_a = 0;
  s21_decimal src;
  s21_decimal res;
  s21_from_int_to_decimal(a, &src);
  s21_negate(src, &res);
  s21_from_decimal_to_int(res, &res_a);
  ck_assert_int_eq(15, res_a);
}
END_TEST

START_TEST(s21_test_negate_0) {
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal etalon = {{0, 0, 0, ~(MAX_INT)}};
  int negate = s21_negate(b, &etalon);
  ck_assert_int_eq(negate, 0);
}
END_TEST

START_TEST(s21_test_negate_1) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal etalon = {{1, 0, 0, ~(MAX_INT)}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  int add = s21_negate(a, ptr_b);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_negate_2) {
  s21_decimal a = {{1, 0, 0, ~(MAX_INT)}};
  s21_decimal etalon = {{1, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  int add = s21_negate(a, ptr_b);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_negate_3) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal etalon = {{100, 0, 0, ~(MAX_INT)}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  int add = s21_negate(a, ptr_b);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_negate_4) {
  s21_decimal a = {{100, 0, 0, ~(MAX_INT)}};
  s21_decimal etalon = {{100, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  int add = s21_negate(a, ptr_b);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_negate_5) {
  s21_decimal a = {{S21_MAX_UINT, 0, 0, 0}};
  s21_decimal etalon = {{S21_MAX_UINT, 0, 0, ~(MAX_INT)}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  int add = s21_negate(a, ptr_b);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_negate_6) {
  s21_decimal a = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal etalon = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  int add = s21_negate(a, ptr_b);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(s21_test_negate_7) {
  s21_decimal a = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal etalon = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(MAX_INT)}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  int add = s21_negate(a, ptr_b);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_negate_8) {
  s21_decimal a = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(MAX_INT)}};
  s21_decimal etalon = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  int add = s21_negate(a, ptr_b);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(negate_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_negate(val, &res));
}
END_TEST

START_TEST(negate_1) {
  s21_decimal val = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_negate(val, &res));
}
END_TEST

START_TEST(negate_2) {
  s21_decimal val = {{0, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_negate(val, &res));
}
END_TEST

START_TEST(negate_3) {
  s21_decimal val = {0};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_negate(val, &res));
}
END_TEST

START_TEST(test_s21_truncate_1) {
  s21_decimal value_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(value_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(-2744406, &value_1);
  s21_set_scale(4, &value_1);
  s21_truncate(value_1, &result);
  ck_assert_float_eq(result.bits[0], 274);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_trun_1) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000000000000000011010011; // 21.1
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000010101;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_truncate(dec1, &res1);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_trun_2) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000000000000000010100101;
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000010000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_trun_3) {
  s21_decimal dec1;
  dec1.bits[0] =
      0b11111111111111111111111111111111; // 7922816251426433759354395033.5
  dec1.bits[1] = 0b11111111111111111111111111111111;
  dec1.bits[2] = 0b11111111111111111111111111111111;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b10011001100110011001100110011001;
  result.bits[1] = 0b10011001100110011001100110011001;
  result.bits[2] = 0b00011001100110011001100110011001;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_truncate(dec1, &res1);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_trun_4) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10000000000000000000000010100101; // 214.7483813
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000001110000000000000000;
  float num = 0.0;
  s21_from_decimal_to_float(dec1, &num);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000011010110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_truncate(dec1, &res1);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_1) {
  s21_decimal dec1;

  dec1.bits[3] = 0x000A0000;
  dec1.bits[2] = 0x0;
  dec1.bits[1] = 0xFFFFFFFF;
  dec1.bits[0] = 0xFFFFFFFF;
  s21_decimal result;
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  s21_decimal res1;
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal dec1;

  dec1.bits[3] = 0b10000000000011000000000000000000;
  dec1.bits[2] = 0x0;
  dec1.bits[1] = 0xFFFFFFFF;
  dec1.bits[0] = 0xFFFFFFFF;
  s21_decimal result;
  result.bits[3] = 0b10000000000000000000000000000000;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x1197998;
  s21_decimal res1;
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_3) {
  s21_decimal dec1;

  dec1.bits[3] = 0x80000000;
  dec1.bits[2] = 0x0;
  dec1.bits[1] = 0xFFFFFFFF;
  dec1.bits[0] = 0xFFFFFFFF;
  s21_decimal result;
  result.bits[3] = 0x80000000;
  result.bits[2] = 0x0;
  result.bits[1] = 0xFFFFFFFF;
  result.bits[0] = 0xFFFFFFFF;
  s21_decimal res1;
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_4) {
  s21_decimal dec1;

  dec1.bits[0] = 0b00000000000000000000000001101101;
  dec1.bits[1] = 0b00000000000011000110010101011011;
  dec1.bits[2] = 0b00000000000000000011000000111001;
  dec1.bits[3] = 0b00000000000011100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_5) {
  s21_decimal dec1;

  dec1.bits[0] = 0b11011110101001001000000010110110;
  dec1.bits[1] = 0b01011111101001011101111110100000;
  dec1.bits[2] = 0b00011111111010011010111101100000;
  dec1.bits[3] = 0b00000000000010010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00110100101011011100000100111110;
  result.bits[1] = 0b10001001000100001000011110111001;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_6) {
  s21_decimal dec1;

  dec1.bits[3] = 0x80090000;
  dec1.bits[2] = 0;
  dec1.bits[1] = 0xFFFFEA34;
  dec1.bits[0] = 0xFF837E4F;
  s21_decimal result;
  s21_truncate(dec1, &result);
  s21_decimal res1;

  res1.bits[3] = 0x80000000;
  res1.bits[2] = 0;
  res1.bits[1] = 0x4;
  res1.bits[0] = 0x4B829C70;
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncate_7) {
  s21_decimal dec1;

  dec1.bits[0] = 0b11010000101000110011000001101101;
  dec1.bits[1] = 0b00011111100110100110101101011000;
  dec1.bits[2] = 0;
  dec1.bits[3] = 0b00000000000010010000000000000000;
  s21_decimal result;
  s21_truncate(dec1, &result);
  s21_decimal result_origin;
  result_origin.bits[3] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b10000111101111000001011000011110;
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncate_8) {
  s21_decimal dec1;

  dec1.bits[0] = 0b01111000101001111011110011000110;
  dec1.bits[1] = 0b10011111111111001111101010000100;
  dec1.bits[2] = 0b00011111111010011010111101101101;
  dec1.bits[3] = 0b00000000000111000000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncateTest1) {
  // 6766
  s21_decimal src1, origin;
  // src1 = 2;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest2) {
  // 6787
  s21_decimal src1, origin;
  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest3) {
  // 6808
  s21_decimal src1, origin;
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest4) {
  // 6829
  s21_decimal src1, origin;
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest5) {
  // 6850
  s21_decimal src1, origin;
  // src1 = -9878798789;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b01001100110100101000000111000101;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest6) {
  // 6871
  s21_decimal src1, origin;
  // src1 = -545454512454545.35265454545645;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b10000110011101001011101110010001;
  origin.bits[1] = 0b00000000000000011111000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest7) {
  // 6892
  s21_decimal src1, origin;
  // src1 = -5.492654545456454545645464;

  src1.bits[0] = 0b00000111100110110001111110011000;
  src1.bits[1] = 0b01100110010010001001000110100011;
  src1.bits[2] = 0b00000000000001001000101100011101;
  src1.bits[3] = 0b10000000000110000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest8) {
  // 6913
  s21_decimal src1, origin;
  // src1 = 7961327845421.879754123131254;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b10100100000111100100000000101101;
  origin.bits[1] = 0b00000000000000000000011100111101;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest9) {
  // 6934
  s21_decimal src1, origin;
  // src1 = -12345677.187654345678987654346;

  src1.bits[0] = 0b01111000100010101111010011001010;
  src1.bits[1] = 0b01100010000010101110010010000111;
  src1.bits[2] = 0b00100111111001000001101011010101;
  src1.bits[3] = 0b10000000000101010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000101111000110000101001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest10) {
  // 6955
  s21_decimal src1, origin;
  // src1 = 2.5086531268974139743;

  src1.bits[0] = 0b01100101111011101101100101011111;
  src1.bits[1] = 0b01011100001001010100001101000110;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest11) {
  // 6976
  s21_decimal src1, origin;
  // src1 = 1;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = MAX_INT;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_float_eq(number, 2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = 133141;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 133141);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  s21_decimal src;
  int result = 0, number = 0;
  long int c = 2147483648;
  src.bits[0] = 123451234;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -123451234);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_5) {
  s21_decimal src;
  int result = 0, number = 0;
  long int c = 2147483648;
  src.bits[0] = 18;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c; // 2147483648
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_6) {
  s21_decimal src;
  int result = 0, number = 0;
  long int c = 4294967295;
  src.bits[0] = c;
  src.bits[1] = c;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
  ck_assert_int_eq(result, 1);
}
END_TEST

int check, result, code;

START_TEST(s21_test_from_decimal_to_int_0) {
  s21_decimal a = {{100, 0, 0, 0}};
  check = 100;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_1) {
  s21_decimal a = {{MAX_INT, 0, 0, 0}};
  check = MAX_INT;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_3) {
  s21_decimal a = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  check = 0;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_4) {
  s21_decimal a = {{MAX_INT, MAX_INT, MAX_INT, MAX_INT}};
  check = 0;
  int result;
  s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, 3);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_6) {
  s21_decimal a = {{S21_MAX_UINT, S21_MAX_UINT, 0, 0}};
  check = 0;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST
START_TEST(s21_test_from_decimal_to_int_7) {
  s21_decimal a = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  check = 0;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_8) {
  s21_decimal a = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT}};
  check = 0;
  int result;
  s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, -7);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_9) {
  s21_decimal a = {{MAX_INT, 0, 0, MINUS}};
  check = -MAX_INT;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_10) {
  s21_decimal a = {{MAX_INT, 0, 0, MINUS}};
  check = -MAX_INT;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_11) {
  s21_decimal a = {{MAX_INT, 0, 0, EXPONENT_PLUS_1}};
  check = 214748364; // (int)(MAX_INT / 10^1)
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_12) {
  s21_decimal a = {{MAX_INT, 0, 0, EXPONENT_MINUS_28}};
  check = 0; // (int)(MAX_INT / 10^28)
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_14) {
  s21_decimal a = {{MAX_INT, 0, 0, EXPONENT_PLUS_28}};
  check = 0; // (int)(MAX_INT / 10^28)
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_15) {
  s21_decimal a;
  a.bits[0] = 0b10000000000000000000000000000000;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b00000000000000000000000000000001;
  check = -2147483648;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_16) {
  s21_decimal a;
  a.bits[0] = 0b00000000000000000000000000000001;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b00000000000000000000000000000000;
  check = 1;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_17) {
  s21_decimal a;
  a.bits[0] = 0b10000000000000000000000000000001;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b00000000000000000000000000000000;
  check = -2147483647;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest1) {
  // 6556
  s21_decimal src1;
  // src1 = 2;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest2) {
  // 6570
  s21_decimal src1;
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest3) {
  // 6584
  s21_decimal src1;
  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 3);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest4) {
  // 6598
  s21_decimal src1;
  // src1 = 4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 4);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest5) {
  // 6612
  s21_decimal src1;
  // src1 = -4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -4);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest6) {
  // 6626
  s21_decimal src1;
  int code = 0;
  // src1 = -5454.3526545;

  src1.bits[0] = 0b10110011000011000010101010010001;
  src1.bits[1] = 0b00000000000000000000000000001100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000001110000000000000000;
  int result;
  //   print_2(&src1);
  //   int *res = &result;
  code = s21_from_decimal_to_int(src1, &result);
  ck_assert_int_eq(result, -5454);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest7) {
  // 6640
  s21_decimal src1;
  // src1 = -5.492654545456454545645464;

  src1.bits[0] = 0b00000111100110110001111110011000;
  src1.bits[1] = 0b01100110010010001001000110100011;
  src1.bits[2] = 0b00000000000001001000101100011101;
  src1.bits[3] = 0b10000000000110000000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -5);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest8) {
  // 6654
  s21_decimal src1;
  // src1 = 796132784.879754;

  src1.bits[0] = 0b00011011110101100011100010001010;
  src1.bits[1] = 0b00000000000000101101010000010100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 796132784);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest9) {
  // 6668
  s21_decimal src1;
  // src1 = -12345677.187654345678987654346;

  src1.bits[0] = 0b01111000100010101111010011001010;
  src1.bits[1] = 0b01100010000010101110010010000111;
  src1.bits[2] = 0b00100111111001000001101011010101;
  src1.bits[3] = 0b10000000000101010000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -12345677);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest10) {
  // 6682
  s21_decimal src1;
  // src1 = 2.5086531268974139743;

  src1.bits[0] = 0b01100101111011101101100101011111;
  src1.bits[1] = 0b01011100001001010100001101000110;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest11) {
  // 6696
  s21_decimal src1;
  // src1 = 1;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest12) {
  // 6710
  s21_decimal src1;
  // src1 = 1.25;

  src1.bits[0] = 0b00000000000000000000000001111101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000100000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest13) {
  // 6724
  s21_decimal src1;
  // src1 = -1.25;

  src1.bits[0] = 0b00000000000000000000000001111101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest14) {
  // 6738
  s21_decimal src1;
  // src1 = -12.25;

  src1.bits[0] = 0b00000000000000000000010011001001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -12);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest15) {
  // 6752
  s21_decimal src1;
  // src1 = -3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -3);
}
END_TEST

// int to decimal

START_TEST(s21_from_int_to_decimal1) {
  s21_decimal val;
  initialize_decimal(&val);

  s21_from_int_to_decimal(0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_int_to_decimal(-128, &val);
  ck_assert_int_eq(val.bits[0], 128);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);

  s21_from_int_to_decimal(127, &val);
  ck_assert_int_eq(val.bits[0], 127);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_int_to_decimal(-2147483648, &val);
  ck_assert_int_eq(val.bits[0], 2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);

  s21_from_int_to_decimal(2147483647, &val);
  ck_assert_int_eq(val.bits[0], 2147483647);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

int a, add, equal;

START_TEST(s21_test_from_int_to_decimal_0) {
  a = 100;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{100, 0, 0, 0}};
  ck_assert_int_eq(add, CONVERTERS_S21_TRUE);
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal1) {
  a = 100;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{1000, 0, 0, 0}};
  ck_assert_int_eq(add, CONVERTERS_S21_TRUE);
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_FALSE);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal2) {
  a = INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{INT_MAX, 0, 0, 0}};
  ck_assert_int_eq(add, CONVERTERS_S21_TRUE);
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_3) {
  a = -INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{INT_MAX, 0, 0, 0}};
  ck_assert_int_eq(add, CONVERTERS_S21_TRUE);
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_FALSE);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_4) {
  a = -INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{INT_MAX, 0, 0, ~(INT_MAX)}};
  ck_assert_int_eq(add, CONVERTERS_S21_TRUE);
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_5) {
  a = 0; // ERROR of NAN
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;
  add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{INT_MAX, 0, 0, ~(INT_MAX)}};
  ck_assert_int_eq(add, CONVERTERS_S21_TRUE);
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_FALSE);
}
END_TEST

START_TEST(from_int_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest1) {
  // 6412
  int src1 = 1;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest2) {
  // 6428
  int src1 = -1;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest3) {
  // 6444
  int src1 = 0;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest4) {
  // 6460
  int src1 = 0;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest5) {
  // 6476
  int src1 = -987879878;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00111010111000011101100111000110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest6) {
  // 6492
  int src1 = -2147483646;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b01111111111111111111111111111110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest7) {
  // 6508
  int src1 = 2147483646;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b01111111111111111111111111111110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest8) {
  // 6524
  int src1 = 796132784;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00101111011101000000010110110000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest9) {
  // 6540
  int src1 = -12345677;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);
  origin.bits[0] = 0b00000000101111000110000101001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

// from float to decimal

START_TEST(s21_from_float_to_decimal1) {
  s21_decimal val;
  float fl1 = 3;
  float fl2 = 127.1234;
  float fl1_res = 0;
  float fl2_res = 0;
  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);
  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST

START_TEST(s21_from_float_to_decimal2) {
  s21_decimal val;
  float fl1 = -128.023;
  float fl2 = 12345.37643764;
  float fl1_res = 0;
  float fl2_res = 0;
  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);
  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST
START_TEST(s21_from_float_to_decimal_3) {
  s21_decimal val;
  float num = -2.1474836E+09;
  s21_from_float_to_decimal(num, &val);
  ck_assert_int_eq(val.bits[0], 2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  s21_decimal val;
  float fl1 = 22.14836E+03;
  float fl2 = -2.1474836E+09;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);

  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  s21_decimal val;
  s21_from_float_to_decimal(1.02E+09, &val);
  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  s21_decimal val;
  float fl1 = -333.2222;
  float fl2 = -2.1474836E+20;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);

  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST

START_TEST(s21_from_float_to_decimal_7) {
  s21_decimal val;
  float a = 1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_8) {
  s21_decimal val;
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal10) {
  s21_decimal val;
  float a = 1e-30;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal11) {
  s21_decimal dec;
  float tmp = 0;
  float tmp1 = 0.03;
  s21_from_float_to_decimal(tmp1, &dec);
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, tmp1, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal12) {
  s21_decimal dec;
  s21_from_float_to_decimal(-128.023, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -128.023, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal13) {
  s21_decimal dec;
  s21_from_float_to_decimal(-2.1474836E+09, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -2.1474836E+09, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal14) {
  s21_decimal dec;
  s21_from_float_to_decimal(22.14836E+03, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 22.14836E+03, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal15) {
  s21_decimal dec;
  s21_from_float_to_decimal(1.02E+08, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 1.02E+08, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal16) {
  s21_decimal dec;
  s21_from_float_to_decimal(-333.2222, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -333.2222, 1e-06);
}
END_TEST

START_TEST(s21_from_float_to_decimal17) {
  s21_decimal dec;
  float a = 1.0 / 0.0;
  int ret = s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal18) {
  s21_decimal dec;
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

// from decimal to float

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  long int c = 2147680256;
  src.bits[0] = 18122;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;

  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  long int c = 2147483648;
  src.bits[0] = 1812;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 0XFFFFFF;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 16777215);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  long int c = 2147745792;
  src.bits[0] = 23450987;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_5) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  long int c = 4294967295;
  src.bits[0] = c;
  src.bits[1] = c;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_7) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  long int c = 2147483648;
  dec.bits[0] = 1812;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = c;
  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, -1812);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_8) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;

  dec.bits[0] = 0XFFFFFF;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;
  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, 16777215);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_9) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  long int c = 2147745792;
  dec.bits[0] = 23450987;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = c;
  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_10) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  long int c = 4294967295;
  dec.bits[0] = c;
  dec.bits[1] = c;
  dec.bits[2] = 0;
  dec.bits[3] = 0;
  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_floatTest1) {
  // 6997
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = 2546.5;

  src1.bits[0] = 0b00000000000000000110001101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", 2546.5);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(s21_from_decimal_to_floatTest2) {
  // 7016
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = -0.46453;

  src1.bits[0] = 0b00000000000000001011010101110101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000001010000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", -0.46453);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(s21_from_decimal_to_floatTest3) {
  // 7035
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", 3.5);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(s21_from_decimal_to_floatTest4) {
  // 7054
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = 4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", 4.5);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(s21_from_decimal_to_floatTest5) {
  // 7073
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = -4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", -4.5);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(s21_from_decimal_to_floatTest6) {
  // 7092
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = -5.49265;

  src1.bits[0] = 0b00000000000010000110000110010001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000001010000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", -5.49265);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(s21_from_decimal_to_floatTest7) {
  // 7111
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = 2.5086531268974139743;

  src1.bits[0] = 0b01100101111011101101100101011111;
  src1.bits[1] = 0b01011100001001010100001101000110;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", 2.50865312689741);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(mul_test_1) {
  int num1 = -10;
  int num2 = -10;
  int prod_int = 100;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_2) {
  int num1 = 10;
  int num2 = 20;
  int prod_int = 200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_3) {
  int num1 = -10;
  int num2 = 20;
  int prod_int = -200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_4) {
  int num1 = 9403;
  int num2 = 202;
  int res_origin = 1899406;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_5) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -65536;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_6) {
  int num1 = -32768;
  int num2 = 32768;
  int res_origin = -1073741824;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_7) {
  float num1 = 9403.0e2;
  int num2 = 202;
  float res_origin = 189940600;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(mul_test_8) {
  float num1 = 9403.0e2;
  float num2 = 9403.0e2;
  float res_origin = 884164090000;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(mod_test_1) {
  int num1 = 3;
  int num2 = 2;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_2) {
  int num1 = -98765;
  int num2 = 1234;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_3) {
  int num1 = 30198;
  int num2 = 20210;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_4) {
  int num1 = -98765;
  int num2 = -1234;
  int res_origin = num1 % num2;
  // printf("%f", fmod(-98765, -1234));
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_5) {
  int num1 = 98765;
  int num2 = 127234;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_6) {
  int num1 = 342576;
  int num2 = 1542134;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_7) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 0;
  dec1.bits[1] = 0;
  dec1.bits[0] = 1568954488;
  s21_set_scale(0, &dec1);

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 54484454;
  s21_set_scale(4, &dec2);

  orig.bits[3] = 0;
  orig.bits[2] = 0;
  orig.bits[1] = 0;
  orig.bits[0] = 38052798;
  s21_set_scale(4, &orig);

  s21_mod(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(mod_test_8) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 1568954488;
  dec1.bits[1] = 1568954488;
  dec1.bits[0] = 1568954488;
  s21_set_scale(5, &dec1);

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 54484454;
  dec2.bits[0] = 54484454;
  s21_set_scale(0, &dec2);

  orig.bits[3] = 0;
  orig.bits[2] = 846;
  orig.bits[1] = 1282492878;
  orig.bits[0] = 2851446520;
  s21_set_scale(5, &orig);

  s21_mod(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(mod_test_9) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 1568954488;
  dec1.bits[1] = 1568954488;
  dec1.bits[0] = 1568954488;
  s21_set_scale(5, &dec1);

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 54484454;
  dec2.bits[0] = 54484454;
  s21_set_scale(5, &dec2);

  orig.bits[3] = 0;
  orig.bits[2] = 0;
  orig.bits[1] = 3444746;
  orig.bits[0] = 1572399234;
  s21_set_scale(5, &orig);

  s21_mod(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(mod_test_10) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 1568954488;
  dec1.bits[1] = 1568954488;
  dec1.bits[0] = 1568954488;
  s21_set_scale(10, &dec1);

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 54484454;
  dec2.bits[0] = 54484454;
  s21_set_scale(5, &dec2);

  orig.bits[3] = 0;
  orig.bits[2] = 846;
  orig.bits[1] = 1282492878;
  orig.bits[0] = 2851446520;
  s21_set_scale(10, &orig);

  s21_mod(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(mod_test_11) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 1568954488;
  dec1.bits[1] = 1568954488;
  dec1.bits[0] = 1568954488;
  s21_set_scale(10, &dec1);

  dec2.bits[3] = 0;
  dec2.bits[2] = 88;
  dec2.bits[1] = 54484454;
  dec2.bits[0] = 54484454;
  s21_set_scale(20, &dec2);

  orig.bits[3] = 0;
  orig.bits[2] = 50;
  orig.bits[1] = 1220244763;
  orig.bits[0] = 722611462;
  s21_set_scale(20, &orig);

  s21_mod(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(mod_test_12) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 0b11100010001011101010010010010011;
  dec1.bits[1] = 0b10110011000000110001000010100111;
  dec1.bits[0] = 0b01110000000000000000000000000000;
  s21_set_scale(0, &dec1);

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 1;
  s21_set_scale(3, &dec2);
  orig.bits[3] = 0;
  orig.bits[2] = 0;
  orig.bits[1] = 0;
  orig.bits[0] = 0;
  s21_set_scale(3, &orig);

  s21_mod(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(mod_test_13) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 21474836;
  dec1.bits[1] = 21474847;
  dec1.bits[0] = 223335554;
  s21_set_scale(0, &dec1);
  set_sign(&dec1, 1);

  dec2.bits[3] = 0;
  dec2.bits[2] = 2147483645;
  dec2.bits[1] = 2147483647;
  dec2.bits[0] = 2147483647;
  s21_set_scale(2, &dec2);

  orig.bits[3] = 0;
  orig.bits[2] = 21474836;
  orig.bits[1] = 21474847;
  orig.bits[0] = 223335554;
  s21_set_scale(0, &orig);
  set_sign(&orig, 1);

  s21_mod(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(mod_test_14) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 21474836;
  dec1.bits[1] = 21474847;
  dec1.bits[0] = 223335554;

  dec2.bits[3] = 0;
  dec2.bits[2] = 21474836;
  dec2.bits[1] = 21474847;
  dec2.bits[0] = 223335554;

  orig.bits[3] = 0;
  orig.bits[2] = 0;
  orig.bits[1] = 0;
  orig.bits[0] = 0;

  s21_mod(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, S21_TRUE);
}
END_TEST

START_TEST(mod_test_15) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 21474836;
  dec1.bits[1] = 21474847;
  dec1.bits[0] = 223335554;
  s21_set_scale(1, &dec1);
  set_sign(&dec1, 1);

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 0;
  s21_set_scale(0, &dec2);

  diff = s21_mod(dec1, dec2, &result);
  ck_assert_int_eq(diff, 3);
}
END_TEST

START_TEST(test_round_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

/* START_TEST(test_round_ok3) { */
/*     // 7922816251426433759354395033.5 */
/*     s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}}; */
/*     // 7922816251426433759354395034 */
/*     s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
 */

/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */
/* } */

/* START_TEST(test_round_ok4) { */
/*     // -7922816251426433759354395033.5 */
/*     s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
 */
/*     // -7922816251426433759354395034 */
/*     s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999,
 * 0x80000000}}; */

/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */
/* } */

START_TEST(test_round_ok5) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok6) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  // -792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok7) {
  // 79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  // 79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok8) {
  // -79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  // -79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok9) {
  // 7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
  // 7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok10) {
  // -7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
  // -7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok11) {
  // 792281625142643375935439.50335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
  // 792281625142643375935440
  s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

/* START_TEST(test_round_ok12) { */
/*     // -792281625142643375935439.50335 */
/*     s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
 */
/*     // -792281625142643375935440 */
/*     s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5,
 * 0x80000000}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

/* START_TEST(test_round_ok13) { */
/*     // 79228162514264337593543.950335 */
/*     s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}}; */
/*     // 79228162514264337593544 */
/*     s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x0}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

/* START_TEST(test_round_ok14) { */
/*     // -79228162514264337593543.950335 */
/*     s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
 */
/*     // -79228162514264337593544 */
/*     s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6,
 * 0x80000000}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

START_TEST(test_round_ok15) {
  // 7922816251426433759354.3950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
  // 7922816251426433759354
  s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok16) {
  // -7922816251426433759354.3950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
  // -7922816251426433759354
  s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok17) {
  // 792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
  // 792281625142643375935
  s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok18) {
  // -792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
  // -792281625142643375935
  s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok19) {
  // 79228162514264337593.543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
  // 79228162514264337594
  s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

/* START_TEST(test_round_ok20) { */
/*     // -79228162514264337593.543950335 */
/*     s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
 */
/*     // -79228162514264337594 */
/*     s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x80000000}};
 */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

START_TEST(test_round_ok21) {
  // 7922816251426433759.3543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
  // 7922816251426433759
  s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok22) {
  // -7922816251426433759.3543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
  // -7922816251426433759
  s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok23) {
  // 792281625142643375.93543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
  // 792281625142643376
  s21_decimal decimal_check = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok24) {
  // -792281625142643375.93543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
  // -792281625142643376
  s21_decimal decimal_check = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok25) {
  // 79228162514264337.593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
  // 79228162514264338
  s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok26) {
  // -79228162514264337.593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
  // -79228162514264338
  s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok27) {
  // 7922816251426433.7593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
  // 7922816251426434
  s21_decimal decimal_check = {{0x68497682, 0x1C25C2, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok28) {
  // -7922816251426433.7593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
  // -7922816251426434
  s21_decimal decimal_check = {{0x68497682, 0x1C25C2, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok29) {
  // 792281625142643.37593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // 792281625142643
  s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok30) {
  // -792281625142643.37593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // -792281625142643
  s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok31) {
  // 79228162514264.337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
  // 79228162514264
  s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok32) {
  // -79228162514264.337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
  // -79228162514264
  s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok33) {
  // 7922816251426.4337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
  // 7922816251426
  s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok34) {
  // -7922816251426.4337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
  // -7922816251426
  s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok35) {
  // 792281625142.64337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
  // 792281625143
  s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok36) {
  // -792281625142.64337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
  // -792281625143
  s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok37) {
  // 79228162514.264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
  // 79228162514
  s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok38) {
  // -79228162514.264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
  // -79228162514
  s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok39) {
  // 7922816251.4264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
  // 7922816251
  s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok40) {
  // -7922816251.4264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
  // -7922816251
  s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok41) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  // 792281625
  s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok42) {
  // -792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
  // -792281625
  s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

/* START_TEST(test_round_ok43) { */
/*     // 79228162.514264337593543950335 */
/*     s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
 */
/*     // 79228163 */
/*     s21_decimal decimal_check = {{0x4B8ED03, 0x0, 0x0, 0x0}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

/* START_TEST(test_round_ok44) { */
/*     // -79228162.514264337593543950335 */
/*     s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
 */
/*     // -79228163 */
/*     s21_decimal decimal_check = {{0x4B8ED03, 0x0, 0x0, 0x80000000}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

START_TEST(test_round_ok45) {
  // 7922816.2514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
  // 7922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok46) {
  // -7922816.2514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
  // -7922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok47) {
  // 792281.62514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
  // 792282
  s21_decimal decimal_check = {{0xC16DA, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok48) {
  // -792281.62514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
  // -792282
  s21_decimal decimal_check = {{0xC16DA, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok49) {
  // 79228.162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
  // 79228
  s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok50) {
  // -79228.162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
  // -79228
  s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok51) {
  // 7922.8162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
  // 7923
  s21_decimal decimal_check = {{0x1EF3, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok52) {
  // -7922.8162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
  // -7923
  s21_decimal decimal_check = {{0x1EF3, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok53) {
  // 792.28162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
  // 792
  s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok54) {
  // -792.28162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
  // -792
  s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok55) {
  // 79.228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
  // 79
  s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok56) {
  // -79.228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
  // -79
  s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok57) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 8
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok58) {
  // -7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -8
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok59) {
  // 79228162514264337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok60) {
  // -79228162514264337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal_check = {
      {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok61) {
  // 7922816251426433759354395033.4
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok62) {
  // -7922816251426433759354395033.4
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395033
  s21_decimal decimal_check = {
      {0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok63) {
  // 792281625142643375935439503.34
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok64) {
  // -792281625142643375935439503.34
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  // -792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok65) {
  // 79228162514264337593543950.334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  // 79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok66) {
  // -79228162514264337593543950.334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  // -79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok67) {
  // 7922816251426433759354395.0334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
  // 7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok68) {
  // -7922816251426433759354395.0334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
  // -7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok69) {
  // 792281625142643375935439.50334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
  // 792281625142643375935440
  s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

/* START_TEST(test_round_ok70) { */
/*     // -792281625142643375935439.50334 */
/*     s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
 */
/*     // -792281625142643375935440 */
/*     s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5,
 * 0x80000000}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

/* START_TEST(test_round_ok71) { */
/*     // 79228162514264337593543.950334 */
/*     s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}}; */
/*     // 79228162514264337593544 */
/*     s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x0}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

/* START_TEST(test_round_ok72) { */
/*     // -79228162514264337593543.950334 */
/*     s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
 */
/*     // -79228162514264337593544 */
/*     s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6,
 * 0x80000000}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

START_TEST(test_round_ok73) {
  // 7922816251426433759354.3950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
  // 7922816251426433759354
  s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok74) {
  // -7922816251426433759354.3950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
  // -7922816251426433759354
  s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok75) {
  // 792281625142643375935.43950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
  // 792281625142643375935
  s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok76) {
  // -792281625142643375935.43950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
  // -792281625142643375935
  s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok77) {
  // 79228162514264337593.543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
  // 79228162514264337594
  s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

/* START_TEST(test_round_ok78) { */
/*     // -79228162514264337593.543950334 */
/*     s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
 */
/*     // -79228162514264337594 */
/*     s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x80000000}};
 */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

START_TEST(test_round_ok79) {
  // 7922816251426433759.3543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
  // 7922816251426433759
  s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok80) {
  // -7922816251426433759.3543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
  // -7922816251426433759
  s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok81) {
  // 792281625142643375.93543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
  // 792281625142643376
  s21_decimal decimal_check = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok82) {
  // -792281625142643375.93543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
  // -792281625142643376
  s21_decimal decimal_check = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok83) {
  // 79228162514264337.593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
  // 79228162514264338
  s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok84) {
  // -79228162514264337.593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
  // -79228162514264338
  s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok85) {
  // 7922816251426433.7593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
  // 7922816251426434
  s21_decimal decimal_check = {{0x68497682, 0x1C25C2, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok86) {
  // -7922816251426433.7593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
  // -7922816251426434
  s21_decimal decimal_check = {{0x68497682, 0x1C25C2, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok87) {
  // 792281625142643.37593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // 792281625142643
  s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok88) {
  // -792281625142643.37593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // -792281625142643
  s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok89) {
  // 79228162514264.337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
  // 79228162514264
  s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok90) {
  // -79228162514264.337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
  // -79228162514264
  s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok91) {
  // 7922816251426.4337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
  // 7922816251426
  s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok92) {
  // -7922816251426.4337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
  // -7922816251426
  s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok93) {
  // 792281625142.64337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
  // 792281625143
  s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok94) {
  // -792281625142.64337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
  // -792281625143
  s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok95) {
  // 79228162514.264337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
  // 79228162514
  s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok96) {
  // -79228162514.264337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
  // -79228162514
  s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok97) {
  // 7922816251.4264337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
  // 7922816251
  s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok98) {
  // -7922816251.4264337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
  // -7922816251
  s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok99) {
  // 792281625.14264337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  // 792281625
  s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok100) {
  // -792281625.14264337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
  // -792281625
  s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_mul1) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul2) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul3) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul4) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul5) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul6) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul7) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul8) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul9) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow

  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul10) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul11) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul12) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul13) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul14) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul15) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul16) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul17) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 52818775009509558395695964249
  s21_decimal decimal_check = {{0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul18) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -52818775009509558395695964249
  s21_decimal decimal_check = {
      {0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul19) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul20) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul21) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 13204693752377389598923991722
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul22) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -13204693752377389598923991722
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul23) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 13204693752377389598923991720
  s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul24) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -13204693752377389598923991720
  s21_decimal decimal_check = {
      {0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul25) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 13204693752377389598923991725
  s21_decimal decimal_check = {{0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul26) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -13204693752377389598923991725
  s21_decimal decimal_check = {
      {0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul27) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 26409387504754779197847983448
  s21_decimal decimal_check = {{0x55555558, 0x55555555, 0x55555555, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul28) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -26409387504754779197847983448
  s21_decimal decimal_check = {
      {0x55555558, 0x55555555, 0x55555555, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul29) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul30) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul31) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 26409387504754779197847983442
  s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x55555555, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul32) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -26409387504754779197847983442
  s21_decimal decimal_check = {
      {0x55555552, 0x55555555, 0x55555555, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul33) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul34) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul35) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul36) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul37) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 20923672451288935879452631411
  s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul38) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -20923672451288935879452631411
  s21_decimal decimal_check = {
      {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul39) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul40) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul41) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // 66023468761886.947994619958612
  s21_decimal decimal_check = {{0x55555554, 0x55555555, 0xD5555555, 0xF0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul42) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -66023468761886.947994619958612
  s21_decimal decimal_check = {
      {0x55555554, 0x55555555, 0xD5555555, 0x800F0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul43) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // 13204693752377.389598923991722
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0xF0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul44) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // -13204693752377.389598923991722
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x800F0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul45) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul46) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul47) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul48) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul49) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 2.6409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul50) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -2.6409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul51) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 26.409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x1B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul52) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -26.409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x801B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul53) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul54) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul55) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul56) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul57) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul58) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul59) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul60) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul61) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul62) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul63) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul64) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul65) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul66) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul67) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul68) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul69) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul70) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul71) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul72) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul73) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul74) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul75) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -52818775009509558395695964249
  s21_decimal decimal_check = {
      {0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul76) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 52818775009509558395695964249
  s21_decimal decimal_check = {{0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul77) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul78) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul79) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -13204693752377389598923991722
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul80) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 13204693752377389598923991722
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul81) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -13204693752377389598923991720
  s21_decimal decimal_check = {
      {0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul82) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 13204693752377389598923991720
  s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul83) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -13204693752377389598923991725
  s21_decimal decimal_check = {
      {0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul84) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 13204693752377389598923991725
  s21_decimal decimal_check = {{0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul85) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -26409387504754779197847983448
  s21_decimal decimal_check = {
      {0x55555558, 0x55555555, 0x55555555, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul86) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 26409387504754779197847983448
  s21_decimal decimal_check = {{0x55555558, 0x55555555, 0x55555555, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul87) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul88) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul89) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -26409387504754779197847983442
  s21_decimal decimal_check = {
      {0x55555552, 0x55555555, 0x55555555, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul90) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 26409387504754779197847983442
  s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x55555555, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul91) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul92) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul93) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul94) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul95) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -20923672451288935879452631411
  s21_decimal decimal_check = {
      {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul96) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 20923672451288935879452631411
  s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul97) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul98) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul99) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // -66023468761886.947994619958612
  s21_decimal decimal_check = {
      {0x55555554, 0x55555555, 0xD5555555, 0x800F0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul100) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // 66023468761886.947994619958612
  s21_decimal decimal_check = {{0x55555554, 0x55555555, 0xD5555555, 0xF0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2000) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -7.922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x801B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2001) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // 63.382530011411470074835160268
  s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCCC, 0x1B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2002) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -63.382530011411470074835160268
  s21_decimal decimal_check = {
      {0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCCC, 0x801B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2003) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 7.9228162514264337593543950327
  s21_decimal decimal_check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2004) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -7.9228162514264337593543950327
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2005) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul2006) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul2007) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 62.771017353866807638357894230
  s21_decimal decimal_check = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, 0x1B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2008) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -62.771017353866807638357894230
  s21_decimal decimal_check = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, 0x801B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2009) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 6.2771017353866807638357894234
  s21_decimal decimal_check = {{0x96EE45A, 0x359A3B3E, 0xCAD2F7F5, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2010) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -6.2771017353866807638357894234
  s21_decimal decimal_check = {{0x96EE45A, 0x359A3B3E, 0xCAD2F7F5, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2011) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // 6277101735386680.7638357894230
  s21_decimal decimal_check = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, 0xD0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2012) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // -6277101735386680.7638357894230
  s21_decimal decimal_check = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, 0x800D0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2013) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // 0.0000000000000198070406285661
  s21_decimal decimal_check = {{0xDC35095D, 0xB424, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2014) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -0.0000000000000198070406285661
  s21_decimal decimal_check = {{0xDC35095D, 0xB424, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2015) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // 0.0000000000000039614081257132
  s21_decimal decimal_check = {{0x5F3DCEAC, 0x2407, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2016) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // -0.0000000000000039614081257132
  s21_decimal decimal_check = {{0x5F3DCEAC, 0x2407, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2017) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2018) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2019) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2020) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2021) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2022) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2023) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000079
  s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2024) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000000079
  s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2025) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // 3172574647370199.8576965422111
  s21_decimal decimal_check = {{0x97DE8C1F, 0x868DD8E0, 0x6682EC22, 0xD0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2026) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // -3172574647370199.8576965422111
  s21_decimal decimal_check = {
      {0x97DE8C1F, 0x868DD8E0, 0x6682EC22, 0x800D0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2027) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // -455376068323281495570.77766605
  s21_decimal decimal_check = {
      {0x1B9271CD, 0xDEBB5DB9, 0x9323D354, 0x80080000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2028) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // 455376068323281495570.77766605
  s21_decimal decimal_check = {{0x1B9271CD, 0xDEBB5DB9, 0x9323D354, 0x80000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2029) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // -55901.969927234268947708082476
  s21_decimal decimal_check = {
      {0x2DC7792C, 0x10FB6E4E, 0xB4A10696, 0x80180000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2030) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // 55901.969927234268947708082476
  s21_decimal decimal_check = {{0x2DC7792C, 0x10FB6E4E, 0xB4A10696, 0x180000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2031) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul2032) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul2033) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul2034) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul2035) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -48716721244363430604.148555673
  s21_decimal decimal_check = {
      {0xD4B7BF99, 0x79B8EBC2, 0x9D6986FE, 0x80090000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2036) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 48716721244363430604.148555673
  s21_decimal decimal_check = {{0xD4B7BF99, 0x79B8EBC2, 0x9D6986FE, 0x90000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2037) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -48716721233020685042.758212308
  s21_decimal decimal_check = {
      {0xF8685AD4, 0xDC4F64C4, 0x9D6986FD, 0x80090000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2038) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // 48716721233020685042.758212308
  s21_decimal decimal_check = {{0xF8685AD4, 0xDC4F64C4, 0x9D6986FD, 0x90000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2039) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // -11342745561.390343364970342328
  s21_decimal decimal_check = {
      {0xA940E7B8, 0xFB0123D2, 0x24A67FCC, 0x80120000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2040) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 11342745561.390343364970342328
  s21_decimal decimal_check = {{0xA940E7B8, 0xFB0123D2, 0x24A67FCC, 0x120000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2041) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // -209236724.51288935879452631410
  s21_decimal decimal_check = {
      {0xADCFA172, 0x67336914, 0x439BA7FC, 0x80140000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2042) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // 209236724.51288935879452631410
  s21_decimal decimal_check = {{0xADCFA172, 0x67336914, 0x439BA7FC, 0x140000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2043) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // -209236724.46417263756150562906
  s21_decimal decimal_check = {
      {0x8A37E05A, 0x2397C118, 0x439BA7FC, 0x80140000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2044) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 209236724.46417263756150562906
  s21_decimal decimal_check = {{0x8A37E05A, 0x2397C118, 0x439BA7FC, 0x140000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2045) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -209236720.51380999118065508859
  s21_decimal decimal_check = {
      {0x3BF421FB, 0xB95D0366, 0x439BA7E6, 0x80140000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2046) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 209236720.51380999118065508859
  s21_decimal decimal_check = {{0x3BF421FB, 0xB95D0366, 0x439BA7E6, 0x140000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2047) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -15.845632502852867518708789275
  s21_decimal decimal_check = {
      {0x3333301B, 0x33333333, 0x33333333, 0x801B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2048) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 15.845632502852867518708789275
  s21_decimal decimal_check = {{0x3333301B, 0x33333333, 0x33333333, 0x1B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2049) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2050) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2051) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -3.9614081257132168796771975168
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2052) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2053) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -3.9614081257132168796771975160
  s21_decimal decimal_check = {
      {0xFFFFFFF8, 0xFFFFFFFF, 0x7FFFFFFF, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2054) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 3.9614081257132168796771975160
  s21_decimal decimal_check = {{0xFFFFFFF8, 0xFFFFFFFF, 0x7FFFFFFF, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2055) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -3.9614081257132168796771975175
  s21_decimal decimal_check = {{0x7, 0x0, 0x80000000, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2056) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 3.9614081257132168796771975175
  s21_decimal decimal_check = {{0x7, 0x0, 0x80000000, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2057) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -7.922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x801B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2058) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 7.922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x1B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2059) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -63.382530011411470074835160268
  s21_decimal decimal_check = {
      {0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCCC, 0x801B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2060) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 63.382530011411470074835160268
  s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCCC, 0x1B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2061) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -7.9228162514264337593543950327
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2062) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 7.9228162514264337593543950327
  s21_decimal decimal_check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2063) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul2064) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul2065) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -62.771017353866807638357894230
  s21_decimal decimal_check = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, 0x801B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2066) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 62.771017353866807638357894230
  s21_decimal decimal_check = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, 0x1B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2067) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -6.2771017353866807638357894234
  s21_decimal decimal_check = {{0x96EE45A, 0x359A3B3E, 0xCAD2F7F5, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2068) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 6.2771017353866807638357894234
  s21_decimal decimal_check = {{0x96EE45A, 0x359A3B3E, 0xCAD2F7F5, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2069) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // -6277101735386680.7638357894230
  s21_decimal decimal_check = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, 0x800D0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2070) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // 6277101735386680.7638357894230
  s21_decimal decimal_check = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, 0xD0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2071) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // -0.0000000000000198070406285661
  s21_decimal decimal_check = {{0xDC35095D, 0xB424, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2072) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // 0.0000000000000198070406285661
  s21_decimal decimal_check = {{0xDC35095D, 0xB424, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2073) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // -0.0000000000000039614081257132
  s21_decimal decimal_check = {{0x5F3DCEAC, 0x2407, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2074) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // 0.0000000000000039614081257132
  s21_decimal decimal_check = {{0x5F3DCEAC, 0x2407, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2075) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2076) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2077) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2078) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2079) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2080) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2081) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000079
  s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2082) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 0.0000000000000000000000000079
  s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2083) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // -3172574647370199.8576965422111
  s21_decimal decimal_check = {
      {0x97DE8C1F, 0x868DD8E0, 0x6682EC22, 0x800D0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2084) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // 3172574647370199.8576965422111
  s21_decimal decimal_check = {{0x97DE8C1F, 0x868DD8E0, 0x6682EC22, 0xD0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2085) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // 455376068323281495570.77766605
  s21_decimal decimal_check = {{0x1B9271CD, 0xDEBB5DB9, 0x9323D354, 0x80000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2086) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // -455376068323281495570.77766605
  s21_decimal decimal_check = {
      {0x1B9271CD, 0xDEBB5DB9, 0x9323D354, 0x80080000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2087) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // 55901.969927234268947708082476
  s21_decimal decimal_check = {{0x2DC7792C, 0x10FB6E4E, 0xB4A10696, 0x180000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2088) {
  // -7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // -55901.969927234268947708082476
  s21_decimal decimal_check = {
      {0x2DC7792C, 0x10FB6E4E, 0xB4A10696, 0x80180000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2089) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 20923672451288935879452631411
  s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2090) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -20923672451288935879452631411
  s21_decimal decimal_check = {
      {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2091) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 20923672446417263756150562907
  s21_decimal decimal_check = {{0x8A37E05B, 0x2397C118, 0x439BA7FC, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2092) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -20923672446417263756150562907
  s21_decimal decimal_check = {
      {0x8A37E05B, 0x2397C118, 0x439BA7FC, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2093) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 4871672124436343060.4148555676
  s21_decimal decimal_check = {{0xD4B7BF9C, 0x79B8EBC2, 0x9D6986FE, 0xA0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2094) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -4871672124436343060.4148555676
  s21_decimal decimal_check = {
      {0xD4B7BF9C, 0x79B8EBC2, 0x9D6986FE, 0x800A0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2095) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 4871672123302068504.2758212311
  s21_decimal decimal_check = {{0xF8685AD7, 0xDC4F64C4, 0x9D6986FD, 0xA0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2096) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // -4871672123302068504.2758212311
  s21_decimal decimal_check = {
      {0xF8685AD7, 0xDC4F64C4, 0x9D6986FD, 0x800A0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

/* START_TEST(test_mul2097) { */
/*     // 0.7922816251426433759354395034 */
/*     s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
 */
/*     // 1431655765 */
/*     s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}}; */
/*     // 1134274556.1390343364970342329 */
/*     s21_decimal decimal_check = {{0xA940E7B9, 0xFB0123D2, 0x24A67FCC,
 * 0x130000}}; */
/*     s21_decimal result; */
/*     s21_mul(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_mul2098) { */
/*     // 0.7922816251426433759354395034 */
/*     s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
 */
/*     // -1431655765 */
/*     s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}}; */
/*     // -1134274556.1390343364970342329 */
/*     s21_decimal decimal_check = {{0xA940E7B9, 0xFB0123D2, 0x24A67FCC,
 * 0x80130000}}; */
/*     s21_decimal result; */
/*     s21_mul(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_mul2099) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // 20923672.451288935879452631411
  s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x150000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul2100) {
  // 0.7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // -20923672.451288935879452631411
  s21_decimal decimal_check = {
      {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80150000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1000) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 52818774.997211729016086241369
  s21_decimal decimal_check = {{0xAAAAA059, 0x0, 0xAAAAAAAA, 0x150000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1001) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -52818773.999999999999999997359
  s21_decimal decimal_check = {
      {0xA9BFF5AF, 0xF0E83FEA, 0xAAAAAA73, 0x80150000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1002) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 52818773.999999999999999997359
  s21_decimal decimal_check = {{0xA9BFF5AF, 0xF0E83FEA, 0xAAAAAA73, 0x150000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1003) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -3.9999999999999999999999996000
  s21_decimal decimal_check = {
      {0x3FFFF060, 0xF8940984, 0x813F3978, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1004) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 3.9999999999999999999999996000
  s21_decimal decimal_check = {{0x3FFFF060, 0xF8940984, 0x813F3978, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1005) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal_check = {
      {0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1006) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal_check = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1007) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0.9999999999999999999999999500
  s21_decimal decimal_check = {{0xFFFFE0C, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1008) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 0.9999999999999999999999999500
  s21_decimal decimal_check = {{0xFFFFE0C, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1009) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -0.9999999999999999999999999498
  s21_decimal decimal_check = {{0xFFFFE0A, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1010) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0.9999999999999999999999999498
  s21_decimal decimal_check = {{0xFFFFE0A, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1011) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -0.9999999999999999999999999502
  s21_decimal decimal_check = {{0xFFFFE0E, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1012) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0.9999999999999999999999999502
  s21_decimal decimal_check = {{0xFFFFE0E, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1013) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -1.9999999999999999999999999002
  s21_decimal decimal_check = {
      {0x1FFFFC1A, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1014) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 1.9999999999999999999999999002
  s21_decimal decimal_check = {{0x1FFFFC1A, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1015) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -15.999999999999999999999999200
  s21_decimal decimal_check = {
      {0x7FFFFCE0, 0xFD0803CE, 0x33B2E3C9, 0x801B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1016) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 15.999999999999999999999999200
  s21_decimal decimal_check = {{0x7FFFFCE0, 0xFD0803CE, 0x33B2E3C9, 0x1B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1017) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -1.9999999999999999999999998998
  s21_decimal decimal_check = {
      {0x1FFFFC16, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1018) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 1.9999999999999999999999998998
  s21_decimal decimal_check = {{0x1FFFFC16, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1019) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 2);
}

START_TEST(test_mul1020) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_mul(decimal1, decimal2, &result), 1);
}

START_TEST(test_mul1021) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -15.845632502852867518708789275
  s21_decimal decimal_check = {
      {0x3333301B, 0x33333333, 0x33333333, 0x801B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1022) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 15.845632502852867518708789275
  s21_decimal decimal_check = {{0x3333301B, 0x33333333, 0x33333333, 0x1B0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1023) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -1.5845632502852867518708789276
  s21_decimal decimal_check = {
      {0x3333301C, 0x33333333, 0x33333333, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1024) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 1.5845632502852867518708789276
  s21_decimal decimal_check = {{0x3333301C, 0x33333333, 0x33333333, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1025) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // -1584563250285286.7518708789275
  s21_decimal decimal_check = {
      {0x3333301B, 0x33333333, 0x33333333, 0x800D0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1026) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // 1584563250285286.7518708789275
  s21_decimal decimal_check = {{0x3333301B, 0x33333333, 0x33333333, 0xD0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1027) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // -0.0000000000000050000000000000
  s21_decimal decimal_check = {{0x883D2000, 0x2D79, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1028) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // 0.0000000000000050000000000000
  s21_decimal decimal_check = {{0x883D2000, 0x2D79, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1029) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // -0.0000000000000010000000000000
  s21_decimal decimal_check = {{0x4E72A000, 0x918, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1030) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // 0.0000000000000010000000000000
  s21_decimal decimal_check = {{0x4E72A000, 0x918, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1031) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1032) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1033) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1034) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1035) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000002
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1036) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 0.0000000000000000000000000002
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1037) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000020
  s21_decimal decimal_check = {{0x14, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1038) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 0.0000000000000000000000000020
  s21_decimal decimal_check = {{0x14, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1039) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // -800870434625820.2177254820354
  s21_decimal decimal_check = {
      {0xDCA98A02, 0x8CE489CB, 0x19E0A51C, 0x800D0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1040) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // 800870434625820.2177254820354
  s21_decimal decimal_check = {{0xDCA98A02, 0x8CE489CB, 0x19E0A51C, 0xD0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1041) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // 114953080791516531253.48487852
  s21_decimal decimal_check = {{0x90D572AC, 0xA3EBFD4F, 0x2524B22B, 0x80000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1042) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // -114953080791516531253.48487852
  s21_decimal decimal_check = {
      {0x90D572AC, 0xA3EBFD4F, 0x2524B22B, 0x80080000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1043) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // 14111.641152139457551613630632
  s21_decimal decimal_check = {{0xD22D18A8, 0xB969E962, 0x2D98E03F, 0x180000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1044) {
  // -1.9999999999999999999999999000
  s21_decimal decimal1 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // -14111.641152139457551613630632
  s21_decimal decimal_check = {
      {0xD22D18A8, 0xB969E962, 0x2D98E03F, 0x80180000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1045) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1046) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1047) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1048) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1049) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 6148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1050) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1051) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 6148914689804861440
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1052) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1053) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 1431655765
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1054) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -1431655765
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1055) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // 26409387.504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1056) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // -26409387.504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1057) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // 26409387.498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1058) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -26409387.498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1059) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 26409387
  s21_decimal decimal_check = {{0x192F9AB, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1060) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -26409387
  s21_decimal decimal_check = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1061) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal_check = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1062) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal_check = {
      {0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1063) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1064) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1065) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x10000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1066) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -0.5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80010000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1067) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal_check = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1068) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal_check = {
      {0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1069) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal_check = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1070) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal_check = {
      {0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1071) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal_check = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1072) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal_check = {
      {0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1073) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // 8
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1074) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -8
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1075) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal_check = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1076) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal_check = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1077) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1078) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1079) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1080) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1081) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1082) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -0.7922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1083) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // 792281625142643.37593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1084) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // -792281625142643.37593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1085) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // 0.0000000000000025
  s21_decimal decimal_check = {{0x19, 0x0, 0x0, 0x100000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1086) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -0.0000000000000025
  s21_decimal decimal_check = {{0x19, 0x0, 0x0, 0x80100000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1087) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // 0.0000000000000005
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x100000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1088) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // -0.0000000000000005
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80100000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1089) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1090) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1091) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1092) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1093) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1094) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1095) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1096) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1097) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // 400435217312910.10886274103770
  s21_decimal decimal_check = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1098) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // -400435217312910.10886274103770
  s21_decimal decimal_check = {
      {0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1099) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // -57476540395758265626.742442133
  s21_decimal decimal_check = {
      {0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_mul1100) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // 57476540395758265626.742442133
  s21_decimal decimal_check = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  s21_decimal result;
  s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div_manual1) {
  // 1.2640938749860586450804312205
  s21_decimal decimal1 = {{0x1888888D, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 0.6320469374930293225402156102
  s21_decimal check = {{0x8C444446, 0x5F128130, 0x146C2B73, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual2) {
  // 2
  s21_decimal decimal1 = {{0x2, 0x0, 0x0, 0x0}};
  // 1.2640938749860586450804312205
  s21_decimal decimal2 = {{0x1888888D, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // 1.5821609767882606564463392905
  s21_decimal check = {{0x8B80B889, 0x20B8279E, 0x331F5430, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual3) {
  // 1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 12.640938749860586450805
  s21_decimal decimal2 = {{0x2EB3EF75, 0x4444026F, 0x2AD, 0x150000}};
  // 113255494.17884722765619814067
  s21_decimal check = {{0x6D7C5EB3, 0x2C521AF0, 0x24984660, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual4) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 500
  s21_decimal decimal2 = {{0x1F4, 0x0, 0x0, 0x0}};
  // 0.002
  s21_decimal check = {{0x2, 0x0, 0x0, 0x30000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 10000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual6) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -3
  s21_decimal check = {{0x3, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual8) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 156064767525876035022225408
  s21_decimal decimal2 = {{0x0, 0x0, 0x811800, 0x0}};
  // -169.22068909868474138626644073
  s21_decimal check = {{0x8C085869, 0xC05E68BD, 0x36AD9B79, 0x801A0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual9) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -429496729.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
  // 61489146926681729710
  s21_decimal check = {{0xAAAAAAAE, 0x55555558, 0x3, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual10) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual11) {
  // 1.2640938749860586450804312207
  s21_decimal decimal1 = {{0x1888888F, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // 2.0000000000000000000000000000
  s21_decimal decimal2 = {{0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 0.6320469374930293225402156104
  s21_decimal check = {{0x8C444448, 0x5F128130, 0x146C2B73, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual12) {
  // 3.6336660283201536
  s21_decimal decimal1 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 36336660283201536000000000000
  s21_decimal check = {{0x89800000, 0xFEE8FB1C, 0x7568FB1C, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual13) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(check, result), 1);
}

START_TEST(test_div_manual14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div_manual15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  // overflow
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div_manual16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div_manual17) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div_manual18) {
  // 0.0000000074505801528346182749
  s21_decimal decimal1 = {{0xCAD4845D, 0x9F9C7BD, 0x4, 0x1C0000}};
  // 1152921504606846976
  s21_decimal decimal2 = {{0x0, 0x10000000, 0x0, 0x0}};
  // 0.0000000000000000000000000065
  s21_decimal decimal_check = {{0x41, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div_manual19) {
  // 0.0000000000000000000542101054
  s21_decimal decimal1 = {{0x204FCE3E, 0x0, 0x0, 0x1C0000}};
  // 8388608
  s21_decimal decimal2 = {{0x800000, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000065
  s21_decimal decimal_check = {{0x41, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div_manual20) {
  // 8388608
  s21_decimal decimal1 = {{0x800000, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000542101054
  s21_decimal decimal2 = {{0x204FCE3E, 0x0, 0x0, 0x1C0000}};
  // 154742514114351823414827745.38
  s21_decimal decimal_check = {{0x6306800A, 0xE4ABBB05, 0x32000031, 0x20000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div_manual21) {
  // 0.0000000000000000000020971522
  s21_decimal decimal1 = {{0x1400002, 0x0, 0x0, 0x1C0000}};
  // 8388608
  s21_decimal decimal2 = {{0x800000, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000003
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div_manual22) {
  // 8388608
  s21_decimal decimal1 = {{0x800000, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000020971522
  s21_decimal decimal2 = {{0x1400002, 0x0, 0x0, 0x1C0000}};
  // 3999999618530309817284601470.5
  s21_decimal decimal_check = {{0x695280F1, 0x2D062C6F, 0x813F38AA, 0x10000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div_manual23) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div_manual24) {
  // 79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div_manual25) {
  // -79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div_manual26) {
  // 79228162514264337593543950319
  s21_decimal decimal1 = {{0xFFFFFFEF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div_manual27) {
  // 79228162514264337593543950319
  s21_decimal decimal1 = {{0xFFFFFFEF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // 1.9999999999999999998915797827
  s21_decimal decimal_check = {{0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // -1.9999999999999999998915797827
  s21_decimal decimal_check = {
      {0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div12) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 20000000000000000000000000000
  s21_decimal decimal_check = {{0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // -20000000000000000000000000000
  s21_decimal decimal_check = {
      {0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // 18446744069414584321
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // -18446744069414584321
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // 1.0000000002328306436538696289
  s21_decimal decimal_check = {{0x4E250261, 0x5E74D0BF, 0x204FCE5E, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div18) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -1.0000000002328306436538696289
  s21_decimal decimal_check = {
      {0x4E250261, 0x5E74D0BF, 0x204FCE5E, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // 18446744073709551616
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div20) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // -18446744073709551616
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // 36893488147419103232
  s21_decimal decimal_check = {{0x0, 0x0, 0x2, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div22) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // -36893488147419103232
  s21_decimal decimal_check = {{0x0, 0x0, 0x2, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // 9223372037928517632.125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x30000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div24) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // -9223372037928517632.125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x80030000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // 15845632502852867518708790067
  s21_decimal decimal_check = {{0x33333333, 0x33333333, 0x33333333, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div26) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // -15845632502852867518708790067
  s21_decimal decimal_check = {
      {0x33333333, 0x33333333, 0x33333333, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 39614081257132168796771975168
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div28) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // -39614081257132168796771975168
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 39614081257132168796771977148
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div30) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -39614081257132168796771977148
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 39614081257132168796771975169
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div32) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -39614081257132168796771975169
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950327
  s21_decimal decimal_check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div34) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -79228162514264337593543950327
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
}

START_TEST(test_div36) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
}

START_TEST(test_div37) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
}

START_TEST(test_div38) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
}

START_TEST(test_div39) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // overflow
}

START_TEST(test_div40) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // overflow
}

START_TEST(test_div41) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
}

START_TEST(test_div42) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // overflow
}

START_TEST(test_div43) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 10000000000000000000000000000
  s21_decimal decimal_check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div44) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -10000000000000000000000000000
  s21_decimal decimal_check = {
      {0x10000000, 0x3E250261, 0x204FCE5E, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div45) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
  // 1320469375237738959892399172.1
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x10000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div46) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // -1320469375237738959892399172.1
  s21_decimal decimal_check = {
      {0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x80010000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div47) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // overflow
}

START_TEST(test_div48) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // overflow
}

START_TEST(test_div49) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // overflow
}

START_TEST(test_div50) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // overflow
}

START_TEST(test_div51) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // overflow
}

START_TEST(test_div52) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // overflow
}

START_TEST(test_div53) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
  // 1999999999534338.7126922607422
  s21_decimal decimal_check = {{0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0xD0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div54) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
  // -1999999999534338.7126922607422
  s21_decimal decimal_check = {
      {0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0x800D0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div55) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // 1844674407370955161600000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x5F5E100, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div56) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // -1844674407370955161600000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x5F5E100, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div57) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // 368934881474191032320000
  s21_decimal decimal_check = {{0x0, 0x0, 0x4E20, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div58) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // -368934881474191032320000
  s21_decimal decimal_check = {{0x0, 0x0, 0x4E20, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div59) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // 1844674407800451891300000000
  s21_decimal decimal_check = {{0x5F5E100, 0x5F5E100, 0x5F5E100, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div60) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // -1844674407800451891300000000
  s21_decimal decimal_check = {{0x5F5E100, 0x5F5E100, 0x5F5E100, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div61) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // overflow
}

START_TEST(test_div62) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // overflow
}

/* START_TEST(test_div63) { */
/*     // 79228162514264337593543950335 */
/*     s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}}; */
/*     // 1.431655765 */
/*     s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}}; */
/*     // 55340232234013556739000000000 */
/*     s21_decimal decimal_check = {{0xB2D05E00, 0xB2D05E00, 0xB2D05E00, 0x0}};
 */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div64) { */
/*     // 79228162514264337593543950335 */
/*     s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}}; */
/*     // -1.431655765 */
/*     s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}}; */
/*     // -55340232234013556739000000000 */
/*     s21_decimal decimal_check = {{0xB2D05E00, 0xB2D05E00, 0xB2D05E00,
 * 0x80000000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_div65) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // 9364712231340627836019760.833
  s21_decimal decimal_check = {{0x9ACD5EC1, 0x4BCA35AA, 0x1E424EF3, 0x30000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div66) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // -9364712231340627836019760.833
  s21_decimal decimal_check = {
      {0x9ACD5EC1, 0x4BCA35AA, 0x1E424EF3, 0x80030000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div67) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // 9903520314283042199192993792
  s21_decimal decimal_check = {{0x0, 0x0, 0x20000000, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div68) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // -9903520314283042199192993792
  s21_decimal decimal_check = {{0x0, 0x0, 0x20000000, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div69) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // 79149013500763574019524425909
  s21_decimal decimal_check = {{0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div70) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // -79149013500763574019524425909
  s21_decimal decimal_check = {
      {0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div71) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div72) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div73) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div74) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div75) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div76) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div77) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div78) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

/* START_TEST(test_div79) { */
/*     // 79228162514264337593543950335 */
/*     s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}}; */
/*     // -1429062841781896312709593009.2 */
/*     s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46,
 * 0x80010000}}; */
/*     // -55.440642775005513864255183391 */
/*     s21_decimal decimal_check = {{0x2D411A1F, 0x85E406F, 0xB3236CC3,
 * 0x801B0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div80) { */
/*     // 79228162514264337593543950335 */
/*     s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}}; */
/*     // 1429062841781896312709593009.2 */
/*     s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
 */
/*     // 55.440642775005513864255183391 */
/*     s21_decimal decimal_check = {{0x2D411A1F, 0x85E406F, 0xB3236CC3,
 * 0x1B0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_div81) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // 21669104637638919604.083853925
  s21_decimal decimal_check = {{0x63478A65, 0x327B2965, 0x46044364, 0x90000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div82) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -21669104637638919604.083853925
  s21_decimal decimal_check = {
      {0x63478A65, 0x327B2965, 0x46044364, 0x80090000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div83) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 126429998059967356684.63712959
  s21_decimal decimal_check = {{0xFF91BABF, 0xD1DCAEAC, 0x28DA0B58, 0x80000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div84) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -126429998059967356684.63712959
  s21_decimal decimal_check = {
      {0xFF91BABF, 0xD1DCAEAC, 0x28DA0B58, 0x80080000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div85) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div86) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div87) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div88) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div89) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div90) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div91) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div92) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div93) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // -1.9999999999999999998915797827
  s21_decimal decimal_check = {
      {0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div94) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // 1.9999999999999999998915797827
  s21_decimal decimal_check = {{0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div95) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div96) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div97) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // -20000000000000000000000000000
  s21_decimal decimal_check = {
      {0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div98) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // 20000000000000000000000000000
  s21_decimal decimal_check = {{0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div99) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // -18446744069414584321
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div100) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // 18446744069414584321
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3000) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3001) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3002) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3003) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // -0.0000000000000000000000000006
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3004) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // 0.0000000000000000000000000006
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3005) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3006) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3007) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3008) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3009) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3010) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3011) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3012) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3013) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3014) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3015) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero

  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div3016) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero

  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div3017) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div3018) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div3019) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3020) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3021) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3022) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3023) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3024) {
  // -0.0000000000000000000000000008
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3025) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3026) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3027) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3028) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

/* START_TEST(test_div3029) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // 79228162514264337593543950334 */
/*     s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}}; */
/*     // 0 */
/*     s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div3030) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // -79228162514264337593543950334 */
/*     s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
 * 0x80000000}}; */
/*     // -0 */
/*     s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_div3031) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3032) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3033) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3034) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3035) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3036) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3037) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3038) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3039) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3040) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3041) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3042) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3043) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3044) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3045) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3046) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3047) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3048) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3049) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3050) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3051) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3052) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

/* START_TEST(test_div3053) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // 1.9999999999999999999999999000 */
/*     s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
 */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div3054) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // -1.9999999999999999999999999000 */
/*     s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC,
 * 0x801C0000}}; */
/*     // -0.0000000000000000000000000001 */
/*     s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div3055) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // 1.9999999999999999999999999999 */
/*     s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
 */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div3056) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // -1.9999999999999999999999999999 */
/*     s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC,
 * 0x801C0000}}; */
/*     // -0.0000000000000000000000000001 */
/*     s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div3057) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // 1.0000000000000000000000000001 */
/*     s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
 */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div3058) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // -1.0000000000000000000000000001 */
/*     s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E,
 * 0x801C0000}}; */
/*     // -0.0000000000000000000000000001 */
/*     s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_div3059) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // 0.125
  s21_decimal decimal_check = {{0x7D, 0x0, 0x0, 0x30000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3060) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // -0.125
  s21_decimal decimal_check = {{0x7D, 0x0, 0x0, 0x80030000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3061) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3062) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3063) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x10000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3064) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80010000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

/* START_TEST(test_div3065) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // 0.9999999999999999999999999999 */
/*     s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
 */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div3066) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // -0.9999999999999999999999999999 */
/*     s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
 */
/*     // -0.0000000000000000000000000001 */
/*     s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_div3067) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3068) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3069) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3070) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3071) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.0000000000000000000000000002
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3072) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -0.0000000000000000000000000002
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3073) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // 0.0000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x190000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3074) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // -0.0000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80190000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3075) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // 0.0000000000000000000000000053
  s21_decimal decimal_check = {{0x35, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3076) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // -0.0000000000000000000000000053
  s21_decimal decimal_check = {{0x35, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

/* START_TEST(test_div3077) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // 39614081266355.540835774234624 */
/*     s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
 */
/*     // 0 */
/*     s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div3078) { */
/*     // 0.0000000000000000000000000001 */
/*     s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}}; */
/*     // -39614081266355.540835774234624 */
/*     s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000,
 * 0x800F0000}}; */
/*     // -0 */
/*     s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_div3079) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3080) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3081) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3082) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3083) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3084) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3085) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3086) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3087) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3088) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3089) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3090) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3091) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3092) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3093) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3094) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3095) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3096) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3097) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3098) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div3099) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div3100) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div1500) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // 79228162495817593524129366015
  s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1501) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // -7922816249581759352412936601.5
  s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80010000}};
}

START_TEST(test_div1502) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // 7922816249581759352412936601.5
  s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1503) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div1504) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div1505) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div1506) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div1507) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // 55.440642762097233325371836019
  s21_decimal decimal_check = {{0xD8064673, 0x553AD3AC, 0xB3236CC2, 0x1B0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1508) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // -55.440642762097233325371836019
  s21_decimal decimal_check = {
      {0xD8064673, 0x553AD3AC, 0xB3236CC2, 0x801B0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1509) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // -21669104632593688025.07401738
  s21_decimal decimal_check = {{0x8BE1AA0A, 0x97A57D66, 0x7006D23, 0x80080000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1510) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 21669104632593688025.07401738
  s21_decimal decimal_check = {{0x8BE1AA0A, 0x97A57D66, 0x7006D23, 0x80000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1511) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -126429998030530578866.03122539
  s21_decimal decimal_check = {
      {0x568F176B, 0xA902A354, 0x28DA0B58, 0x80080000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1512) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 126429998030530578866.03122539
  s21_decimal decimal_check = {{0x568F176B, 0xA902A354, 0x28DA0B58, 0x80000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1513) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000542101086
  s21_decimal decimal_check = {{0x204FCE5E, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1514) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000542101086
  s21_decimal decimal_check = {{0x204FCE5E, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1515) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.0000000000000000005421010862
  s21_decimal decimal_check = {{0x431E0FAE, 0x1, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1516) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.0000000000000000005421010862
  s21_decimal decimal_check = {{0x431E0FAE, 0x1, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1517) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000542101086
  s21_decimal decimal_check = {{0x204FCE5E, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1518) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000542101086
  s21_decimal decimal_check = {{0x204FCE5E, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1519) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000000001626303259
  s21_decimal decimal_check = {{0x60EF6B1B, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1520) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.0000000000000000001626303259
  s21_decimal decimal_check = {{0x60EF6B1B, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1521) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // 0.0000000000000000001084202172
  s21_decimal decimal_check = {{0x409F9CBC, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1522) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // -0.0000000000000000001084202172
  s21_decimal decimal_check = {{0x409F9CBC, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1523) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 0.0000000000000000001084202172
  s21_decimal decimal_check = {{0x409F9CBC, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1524) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // -0.0000000000000000001084202172
  s21_decimal decimal_check = {{0x409F9CBC, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1525) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 1084202172.4855044340074528009
  s21_decimal decimal_check = {{0x5149BD09, 0x6940B791, 0x23084F67, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1526) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // -1084202172.4855044340074528009
  s21_decimal decimal_check = {
      {0x5149BD09, 0x6940B791, 0x23084F67, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1527) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // 0.9999999997671693564003404797
  s21_decimal decimal_check = {{0xF22ACBFD, 0x1DD53402, 0x204FCE5E, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1528) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // -0.9999999997671693564003404797
  s21_decimal decimal_check = {
      {0xF22ACBFD, 0x1DD53402, 0x204FCE5E, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1529) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000542101086
  s21_decimal decimal_check = {{0x204FCE5E, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1530) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000542101086
  s21_decimal decimal_check = {{0x204FCE5E, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1531) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1532) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1533) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1534) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1535) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // 0.5000000000582076609202436708
  s21_decimal decimal_check = {{0x1B933A64, 0x272674C8, 0x1027E72F, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1536) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // -0.5000000000582076609202436708
  s21_decimal decimal_check = {
      {0x1B933A64, 0x272674C8, 0x1027E72F, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1537) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // 858993459.2
  s21_decimal decimal_check = {{0x0, 0x2, 0x0, 0x10000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1538) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // -858993459.2
  s21_decimal decimal_check = {{0x0, 0x2, 0x0, 0x80010000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1539) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 2147483648
  s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1540) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // -2147483648
  s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1541) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 2147483648.0000000000000001074
  s21_decimal decimal_check = {{0x432, 0x44F40000, 0x45639182, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1542) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -2147483648.0000000000000001074
  s21_decimal decimal_check = {{0x432, 0x44F40000, 0x45639182, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1543) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 2147483648.0000000000000000001
  s21_decimal decimal_check = {{0x1, 0x44F40000, 0x45639182, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1544) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -2147483648.0000000000000000001
  s21_decimal decimal_check = {{0x1, 0x44F40000, 0x45639182, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1545) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 4294967295.9999999999999999996
  s21_decimal decimal_check = {{0xFFFFFFFC, 0x89E7FFFF, 0x8AC72304, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1546) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -4294967295.9999999999999999996
  s21_decimal decimal_check = {
      {0xFFFFFFFC, 0x89E7FFFF, 0x8AC72304, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1547) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div1548) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div1549) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div1550) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div1551) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div1552) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div1553) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 4294967296.0000000000000000004
  s21_decimal decimal_check = {{0x4, 0x89E80000, 0x8AC72304, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1554) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -4294967296.0000000000000000004
  s21_decimal decimal_check = {{0x4, 0x89E80000, 0x8AC72304, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

/* START_TEST(test_div1555) { */
/*     // 4294967296 */
/*     s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}}; */
/*     // 7.9228162514264337593543950335 */
/*     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
 */
/*     // 542101086.24275221700372640044 */
/*     s21_decimal decimal_check = {{0x9670B12C, 0xE4395D6, 0xAF298D05,
 * 0x140000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div1556) { */
/*     // 4294967296 */
/*     s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}}; */
/*     // -7.9228162514264337593543950335 */
/*     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
 * 0x801C0000}}; */
/*     // -542101086.24275221700372640044 */
/*     s21_decimal decimal_check = {{0x9670B12C, 0xE4395D6, 0xAF298D05,
 * 0x80140000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div1557) { */
/*     // 4294967296 */
/*     s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}}; */
/*     // 60.000000000000000000000000005 */
/*     s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
 */
/*     // 71582788.266666666666666666661 */
/*     s21_decimal decimal_check = {{0xAAAAAAA5, 0x9082AAAA, 0xE74BE507,
 * 0x150000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div1558) { */
/*     // 4294967296 */
/*     s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}}; */
/*     // -60.000000000000000000000000005 */
/*     s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635,
 * 0x801B0000}}; */
/*     // -71582788.266666666666666666661 */
/*     s21_decimal decimal_check = {{0xAAAAAAA5, 0x9082AAAA, 0xE74BE507,
 * 0x80150000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_div1559) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 8589934592
  s21_decimal decimal_check = {{0x0, 0x2, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1560) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -8589934592
  s21_decimal decimal_check = {{0x0, 0x2, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1561) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // 4294967296000
  s21_decimal decimal_check = {{0x0, 0x3E8, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1562) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // -4294967296000
  s21_decimal decimal_check = {{0x0, 0x3E8, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1563) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // 226050910315.78947368421052632
  s21_decimal decimal_check = {{0x435E50D8, 0x48950D79, 0x490A7E38, 0x110000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1564) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // -226050910315.78947368421052632
  s21_decimal decimal_check = {
      {0x435E50D8, 0x48950D79, 0x490A7E38, 0x80110000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1565) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
  // 0.0001084202172233068944336729
  s21_decimal decimal_check = {{0xF68A759, 0xB7AFE0AD, 0xE596, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1566) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
  // -0.0001084202172233068944336729
  s21_decimal decimal_check = {{0xF68A759, 0xB7AFE0AD, 0xE596, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1567) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // 100000000
  s21_decimal decimal_check = {{0x5F5E100, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1568) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // -100000000
  s21_decimal decimal_check = {{0x5F5E100, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1569) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // 20000
  s21_decimal decimal_check = {{0x4E20, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1570) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // -20000
  s21_decimal decimal_check = {{0x4E20, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1571) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // 100000000.02328306437080797375
  s21_decimal decimal_check = {{0x6E74D0BF, 0x5E74D0BF, 0x204FCE5E, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1572) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // -100000000.02328306437080797375
  s21_decimal decimal_check = {
      {0x6E74D0BF, 0x5E74D0BF, 0x204FCE5E, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1573) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // 4295396835.6835683568356835684
  s21_decimal decimal_check = {{0x199A4164, 0x77BE0268, 0x8ACAB09A, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1574) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // -4295396835.6835683568356835684
  s21_decimal decimal_check = {
      {0x199A4164, 0x77BE0268, 0x8ACAB09A, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1575) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // 3000000000.6984919311242392126
  s21_decimal decimal_check = {{0x4B5E723E, 0x1B5E723E, 0x60EF6B1B, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1576) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // -3000000000.6984919311242392126
  s21_decimal decimal_check = {
      {0x4B5E723E, 0x1B5E723E, 0x60EF6B1B, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1577) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // 507662.0672960542241587993222
  s21_decimal decimal_check = {{0x439C1A86, 0x201C529F, 0x1067483E, 0x160000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1578) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // -507662.0672960542241587993222
  s21_decimal decimal_check = {
      {0x439C1A86, 0x201C529F, 0x1067483E, 0x80160000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1579) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // 536870912
  s21_decimal decimal_check = {{0x20000000, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1580) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // -536870912
  s21_decimal decimal_check = {{0x20000000, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1581) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // 4290676619.3806193806193806194
  s21_decimal decimal_check = {{0xFD714B72, 0x15262B79, 0x8AA3A528, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1582) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // -4290676619.3806193806193806194
  s21_decimal decimal_check = {
      {0xFD714B72, 0x15262B79, 0x8AA3A528, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1583) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // 4294967296
  s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1584) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -4294967296
  s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1585) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // 429496729.6
  s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x10000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1586) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -429496729.6
  s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80010000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1587) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div1588) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div1589) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div1590) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div1591) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // -0.000000000000000003005443267
  s21_decimal decimal_check = {{0xB3236CC3, 0x0, 0x0, 0x801B0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1592) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // 0.000000000000000003005443267
  s21_decimal decimal_check = {{0xB3236CC3, 0x0, 0x0, 0x1B0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1593) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // 1.1746845161971917984513124388
  s21_decimal decimal_check = {{0x27BBE824, 0x39191E73, 0x25F4C338, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1594) {
  // 4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -1.1746845161971917984513124388
  s21_decimal decimal_check = {
      {0x27BBE824, 0x39191E73, 0x25F4C338, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

/* START_TEST(test_div1595) { */
/*     // 4294967296 */
/*     s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}}; */
/*     // 626656361.06935169033698303587 */
/*     s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
 */
/*     // 6.8537839281977359508125051049 */
/*     s21_decimal decimal_check = {{0xFC8E8A9, 0x595F449F, 0xDD752C00,
 * 0x1C0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div1596) { */
/*     // 4294967296 */
/*     s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x0}}; */
/*     // -626656361.06935169033698303587 */
/*     s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C,
 * 0x80140000}}; */
/*     // -6.8537839281977359508125051049 */
/*     s21_decimal decimal_check = {{0xFC8E8A9, 0x595F449F, 0xDD752C00,
 * 0x801C0000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_div1597) {
  // -4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000542101086
  s21_decimal decimal_check = {{0x204FCE5E, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1598) {
  // -4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000542101086
  s21_decimal decimal_check = {{0x204FCE5E, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1599) {
  // -4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.0000000000000000005421010862
  s21_decimal decimal_check = {{0x431E0FAE, 0x1, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div1600) {
  // -4294967296
  s21_decimal decimal1 = {{0x0, 0x1, 0x0, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.0000000000000000005421010862
  s21_decimal decimal_check = {{0x431E0FAE, 0x1, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6800) {
  // 3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // 0.0000000000000000025585110092
  s21_decimal decimal_check = {{0xF4FDCC4C, 0x5, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6801) {
  // 3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6802) {
  // 3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6803) {
  // 3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 5.8345741632702390863554084715
  s21_decimal decimal_check = {{0x89EFF6B, 0xAC35A812, 0xBC86775F, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6804) {
  // 3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -5.8345741632702390863554084715
  s21_decimal decimal_check = {{0x89EFF6B, 0xAC35A812, 0xBC86775F, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6805) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000461486534
  s21_decimal decimal_check = {{0x1B81B9C6, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6806) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000461486534
  s21_decimal decimal_check = {{0x1B81B9C6, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6807) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.0000000000000000004614865343
  s21_decimal decimal_check = {{0x131141BF, 0x1, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6808) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.0000000000000000004614865343
  s21_decimal decimal_check = {{0x131141BF, 0x1, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6809) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000461486534
  s21_decimal decimal_check = {{0x1B81B9C6, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6810) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000461486534
  s21_decimal decimal_check = {{0x1B81B9C6, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6811) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000000001384459603
  s21_decimal decimal_check = {{0x52852D53, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6812) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.0000000000000000001384459603
  s21_decimal decimal_check = {{0x52852D53, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6817) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // -922973068.5438793292982834954
  s21_decimal decimal_check = {{0xBDE4D70A, 0x7CB1FD5, 0x1DD2A77F, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6818) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // 922973068.5438793292982834954
  s21_decimal decimal_check = {{0xBDE4D70A, 0x7CB1FD5, 0x1DD2A77F, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6819) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // -0.8512923989195593323454179836
  s21_decimal decimal_check = {
      {0xFD20A9FC, 0x2A1C1CB7, 0x1B81B9C6, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6820) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // 0.8512923989195593323454179836
  s21_decimal decimal_check = {{0xFD20A9FC, 0x2A1C1CB7, 0x1B81B9C6, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6821) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000461486534
  s21_decimal decimal_check = {{0x1B81B9C6, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6822) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000461486534
  s21_decimal decimal_check = {{0x1B81B9C6, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6823) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.8512923991177662895235057332
  s21_decimal decimal_check = {
      {0x273CC6B4, 0x459DD67E, 0x1B81B9C6, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6824) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // 0.8512923991177662895235057332
  s21_decimal decimal_check = {{0x273CC6B4, 0x459DD67E, 0x1B81B9C6, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6825) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // -1.7025847982355325790470114664
  s21_decimal decimal_check = {
      {0x4E798D68, 0x8B3BACFC, 0x3703738C, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6826) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // 1.7025847982355325790470114664
  s21_decimal decimal_check = {{0x4E798D68, 0x8B3BACFC, 0x3703738C, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6827) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // -0.425646199608434884073580549
  s21_decimal decimal_check = {{0xDDA56805, 0xB75E55C4, 0x1601616, 0x801B0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6828) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // 0.425646199608434884073580549
  s21_decimal decimal_check = {{0xDDA56805, 0xB75E55C4, 0x1601616, 0x1B0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6829) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // -731254602.70883709321494490946
  s21_decimal decimal_check = {
      {0x78596F42, 0x7C17235E, 0xEC47F688, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6830) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // 731254602.70883709321494490946
  s21_decimal decimal_check = {{0x78596F42, 0x7C17235E, 0xEC47F688, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

/* START_TEST(test_div6831) { */
/*     // -3656273013.5441854660747245473 */
/*     s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44,
 * 0x80130000}}; */
/*     // 2 */
/*     s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}}; */
/*     // -1828136506.7720927330373622736 */
/*     s21_decimal decimal_check = {{0x9E165BD0, 0x1F05C8D7, 0x3B11FDA2,
 * 0x80130000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div6832) { */
/*     // -3656273013.5441854660747245473 */
/*     s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44,
 * 0x80130000}}; */
/*     // -2 */
/*     s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}}; */
/*     // 1828136506.7720927330373622736 */
/*     s21_decimal decimal_check = {{0x9E165BD0, 0x1F05C8D7, 0x3B11FDA2,
 * 0x130000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */
/* } */

START_TEST(test_div6833) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -1828136506.7720927330373623651
  s21_decimal decimal_check = {
      {0x9E165F63, 0x1F05C8D7, 0x3B11FDA2, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6834) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 1828136506.7720927330373623651
  s21_decimal decimal_check = {{0x9E165F63, 0x1F05C8D7, 0x3B11FDA2, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6835) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -1828136506.7720927330373622737
  s21_decimal decimal_check = {
      {0x9E165BD1, 0x1F05C8D7, 0x3B11FDA2, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6836) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 1828136506.7720927330373622737
  s21_decimal decimal_check = {{0x9E165BD1, 0x1F05C8D7, 0x3B11FDA2, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6837) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -3656273013.5441854660747245469
  s21_decimal decimal_check = {
      {0x3C2CB79D, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6838) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 3656273013.5441854660747245469
  s21_decimal decimal_check = {{0x3C2CB79D, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6839) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div6840) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div6841) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div6842) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div6843) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div6844) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div6845) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -3656273013.5441854660747245477
  s21_decimal decimal_check = {
      {0x3C2CB7A5, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6846) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 3656273013.5441854660747245477
  s21_decimal decimal_check = {{0x3C2CB7A5, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6847) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -461486534.27193966464914174773
  s21_decimal decimal_check = {
      {0xB5783335, 0x26F79F2C, 0x951D457B, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6848) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 461486534.27193966464914174773
  s21_decimal decimal_check = {{0xB5783335, 0x26F79F2C, 0x951D457B, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6849) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
  // -60937883.559069757767912075783
  s21_decimal decimal_check = {{0xEF53207, 0x12134824, 0xC4E6A2C7, 0x80150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6850) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // 60937883.559069757767912075783
  s21_decimal decimal_check = {{0xEF53207, 0x12134824, 0xC4E6A2C7, 0x150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6851) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -7312546027.0883709321494490946
  s21_decimal decimal_check = {
      {0x78596F42, 0x7C17235E, 0xEC47F688, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6852) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 7312546027.0883709321494490946
  s21_decimal decimal_check = {{0x78596F42, 0x7C17235E, 0xEC47F688, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6853) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // -3656273013544.1854660747245473
  s21_decimal decimal_check = {
      {0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80100000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6854) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // 3656273013544.1854660747245473
  s21_decimal decimal_check = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x100000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6855) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // -192435421765.48344558288023933
  s21_decimal decimal_check = {
      {0xE9C6B17D, 0xB4DDAAFD, 0x3E2DE28F, 0x80110000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6856) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // 192435421765.48344558288023933
  s21_decimal decimal_check = {{0xE9C6B17D, 0xB4DDAAFD, 0x3E2DE28F, 0x110000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6857) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
  // -0.0000922973068328982915674025
  s21_decimal decimal_check = {{0x15E16FA9, 0x78650450, 0xC372, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6858) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
  // 0.0000922973068328982915674025
  s21_decimal decimal_check = {{0x15E16FA9, 0x78650450, 0xC372, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6859) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // -85129239.91177662895235057332
  s21_decimal decimal_check = {
      {0x273CC6B4, 0x459DD67E, 0x1B81B9C6, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6860) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // 85129239.91177662895235057332
  s21_decimal decimal_check = {{0x273CC6B4, 0x459DD67E, 0x1B81B9C6, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6861) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // -17025.847982355325790470114664
  s21_decimal decimal_check = {
      {0x4E798D68, 0x8B3BACFC, 0x3703738C, 0x80180000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6862) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // 17025.847982355325790470114664
  s21_decimal decimal_check = {{0x4E798D68, 0x8B3BACFC, 0x3703738C, 0x180000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6863) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // -85129239.93159732467938907896
  s21_decimal decimal_check = {
      {0x885C56F8, 0x611F9044, 0x1B81B9C6, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6864) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // 85129239.93159732467938907896
  s21_decimal decimal_check = {{0x885C56F8, 0x611F9044, 0x1B81B9C6, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6865) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // -3656638677.4119266587405986072
  s21_decimal decimal_check = {{0xAB802918, 0x5B33DCC, 0x76270197, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6866) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // 3656638677.4119266587405986072
  s21_decimal decimal_check = {{0xAB802918, 0x5B33DCC, 0x76270197, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6867) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // -2553877197.9479197403816723689
  s21_decimal decimal_check = {
      {0x991504E9, 0x235EB0CD, 0x52852D53, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6868) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // 2553877197.9479197403816723689
  s21_decimal decimal_check = {{0x991504E9, 0x235EB0CD, 0x52852D53, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6869) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // -432168.85920954292171551660503
  s21_decimal decimal_check = {
      {0x87C5D9D7, 0x2D871913, 0x8BA42B90, 0x80170000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6870) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // 432168.85920954292171551660503
  s21_decimal decimal_check = {{0x87C5D9D7, 0x2D871913, 0x8BA42B90, 0x170000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6871) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // -457034126.69302318325934056841
  s21_decimal decimal_check = {{0xB37E589, 0x4D8E761B, 0x93ACFA15, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6872) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // 457034126.69302318325934056841
  s21_decimal decimal_check = {{0xB37E589, 0x4D8E761B, 0x93ACFA15, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6873) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // -3652620393.1510344316430814658
  s21_decimal decimal_check = {
      {0x658B8DC2, 0xC2756F86, 0x7605C48A, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6874) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // 3652620393.1510344316430814658
  s21_decimal decimal_check = {{0x658B8DC2, 0xC2756F86, 0x7605C48A, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6875) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal_check = {
      {0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6876) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // 3656273013.5441854660747245473
  s21_decimal decimal_check = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6877) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // -365627301.35441854660747245473
  s21_decimal decimal_check = {
      {0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6878) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // 365627301.35441854660747245473
  s21_decimal decimal_check = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6879) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div6880) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div6881) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div6882) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div6883) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // 0.0000000000000000025585110092
  s21_decimal decimal_check = {{0xF4FDCC4C, 0x5, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6884) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // -0.0000000000000000025585110092
  s21_decimal decimal_check = {{0xF4FDCC4C, 0x5, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6885) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6886) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6887) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -5.8345741632702390863554084715
  s21_decimal decimal_check = {{0x89EFF6B, 0xAC35A812, 0xBC86775F, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6888) {
  // -3656273013.5441854660747245473
  s21_decimal decimal1 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 5.8345741632702390863554084715
  s21_decimal decimal_check = {{0x89EFF6B, 0xAC35A812, 0xBC86775F, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6889) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6890) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6891) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.0000000000000000000790951527
  s21_decimal decimal_check = {{0x2F24F667, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6892) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.0000000000000000000790951527
  s21_decimal decimal_check = {{0x2F24F667, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6893) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6894) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6895) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000000000237285458
  s21_decimal decimal_check = {{0xE24B052, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6896) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.0000000000000000000237285458
  s21_decimal decimal_check = {{0xE24B052, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6897) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // 0.0000000000000000000158190305
  s21_decimal decimal_check = {{0x96DCAE1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6898) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // -0.0000000000000000000158190305
  s21_decimal decimal_check = {{0x96DCAE1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6899) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 0.0000000000000000000158190305
  s21_decimal decimal_check = {{0x96DCAE1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6900) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // -0.0000000000000000000158190305
  s21_decimal decimal_check = {{0x96DCAE1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6901) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 158190305.3618156786992619726
  s21_decimal decimal_check = {{0xD34520CE, 0x5EA58203, 0x51C8500, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6902) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // -158190305.3618156786992619726
  s21_decimal decimal_check = {{0xD34520CE, 0x5EA58203, 0x51C8500, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6903) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // 0.145904803863597774522701572
  s21_decimal decimal_check = {{0x17EA5704, 0x4428E872, 0x78B08B, 0x1B0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6904) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // -0.145904803863597774522701572
  s21_decimal decimal_check = {{0x17EA5704, 0x4428E872, 0x78B08B, 0x801B0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6905) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6906) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6907) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // 0.1459048038975688839184546461
  s21_decimal decimal_check = {{0x98C07A9D, 0xAE4FF9E5, 0x4B6E570, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6908) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // -0.1459048038975688839184546461
  s21_decimal decimal_check = {{0x98C07A9D, 0xAE4FF9E5, 0x4B6E570, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6909) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // 0.2918096077951377678369092922
  s21_decimal decimal_check = {{0x3180F53A, 0x5C9FF3CB, 0x96DCAE1, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6910) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // -0.2918096077951377678369092922
  s21_decimal decimal_check = {{0x3180F53A, 0x5C9FF3CB, 0x96DCAE1, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6911) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // 0.0729524019572772193111316598
  s21_decimal decimal_check = {{0xF88B1876, 0x5855B64E, 0x25B72B8, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6912) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // -0.0729524019572772193111316598
  s21_decimal decimal_check = {{0xF88B1876, 0x5855B64E, 0x25B72B8, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6913) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // 125331272.21387033806739660717
  s21_decimal decimal_check = {{0x5E7CDFAD, 0x12C0A10E, 0x287F28EC, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6914) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // -125331272.21387033806739660717
  s21_decimal decimal_check = {
      {0x5E7CDFAD, 0x12C0A10E, 0x287F28EC, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6915) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 313328180.53467584516849151794
  s21_decimal decimal_check = {{0xEC382F32, 0x2EE192A3, 0x653DE64E, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6916) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // -313328180.53467584516849151794
  s21_decimal decimal_check = {
      {0xEC382F32, 0x2EE192A3, 0x653DE64E, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6917) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 313328180.5346758451684915336
  s21_decimal decimal_check = {{0x979F3888, 0x4B02843, 0xA1FCA3B, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6918) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -313328180.5346758451684915336
  s21_decimal decimal_check = {{0x979F3888, 0x4B02843, 0xA1FCA3B, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6919) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 313328180.53467584516849151795
  s21_decimal decimal_check = {{0xEC382F33, 0x2EE192A3, 0x653DE64E, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6920) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -313328180.53467584516849151795
  s21_decimal decimal_check = {
      {0xEC382F33, 0x2EE192A3, 0x653DE64E, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6921) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 626656361.06935169033698303581
  s21_decimal decimal_check = {{0xD8705E5D, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6922) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -626656361.06935169033698303581
  s21_decimal decimal_check = {
      {0xD8705E5D, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6923) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div6924) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div6925) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div6926) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div6927) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div6928) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div6929) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 626656361.06935169033698303593
  s21_decimal decimal_check = {{0xD8705E69, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6930) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -626656361.06935169033698303593
  s21_decimal decimal_check = {
      {0xD8705E69, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

/* START_TEST(test_div6931) { */
/*     // 626656361.06935169033698303587 */
/*     s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
 */
/*     // 7.9228162514264337593543950335 */
/*     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
 */
/*     // 79095152.680907839349630986301 */
/*     s21_decimal decimal_check = {{0x4380683D, 0x7C5364BF, 0xFF91FA12,
 * 0x150000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div6932) { */
/*     // 626656361.06935169033698303587 */
/*     s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
 */
/*     // -7.9228162514264337593543950335 */
/*     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
 * 0x801C0000}}; */
/*     // -79095152.680907839349630986301 */
/*     s21_decimal decimal_check = {{0x4380683D, 0x7C5364BF, 0xFF91FA12,
 * 0x80150000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_div6933) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
  // 10444272.684489194838949717264
  s21_decimal decimal_check = {{0x4EBD6510, 0xBA4B30E1, 0x21BF4CC4, 0x150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6934) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // -10444272.684489194838949717264
  s21_decimal decimal_check = {
      {0x4EBD6510, 0xBA4B30E1, 0x21BF4CC4, 0x80150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6935) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 1253312722.1387033806739660717
  s21_decimal decimal_check = {{0x5E7CDFAD, 0x12C0A10E, 0x287F28EC, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6936) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -1253312722.1387033806739660717
  s21_decimal decimal_check = {
      {0x5E7CDFAD, 0x12C0A10E, 0x287F28EC, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6937) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // 626656361069.35169033698303587
  s21_decimal decimal_check = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x110000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6938) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // -626656361069.35169033698303587
  s21_decimal decimal_check = {
      {0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80110000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6939) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // 32981913740.492194228262265046
  s21_decimal decimal_check = {{0xC2C1E0D6, 0x8230D040, 0x6A91FFE6, 0x120000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6940) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // -32981913740.492194228262265046
  s21_decimal decimal_check = {
      {0xC2C1E0D6, 0x8230D040, 0x6A91FFE6, 0x80120000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6941) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
  // 0.0000158190305324984128082068
  s21_decimal decimal_check = {{0x36F99094, 0x837D94EA, 0x217F, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6942) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
  // -0.0000158190305324984128082068
  s21_decimal decimal_check = {{0x36F99094, 0x837D94EA, 0x217F, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6943) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // 14590480.38975688839184546461
  s21_decimal decimal_check = {{0x98C07A9D, 0xAE4FF9E5, 0x4B6E570, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6944) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // -14590480.38975688839184546461
  s21_decimal decimal_check = {{0x98C07A9D, 0xAE4FF9E5, 0x4B6E570, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6945) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // 2918.0960779513776783690929221
  s21_decimal decimal_check = {{0xEF099445, 0x9E3F85EF, 0x5E49ECCD, 0x190000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6946) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // -2918.0960779513776783690929221
  s21_decimal decimal_check = {
      {0xEF099445, 0x9E3F85EF, 0x5E49ECCD, 0x80190000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6947) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // 14590480.393153999333002675073
  s21_decimal decimal_check = {{0xF5C98381, 0xFE44B95E, 0x2F24F666, 0x150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6948) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // -14590480.393153999333002675073
  s21_decimal decimal_check = {
      {0xF5C98381, 0xFE44B95E, 0x2F24F666, 0x80150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6949) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // 626719032.9726489552325062865
  s21_decimal decimal_check = {{0xC8A230D1, 0x8B218567, 0x1440192C, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6950) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // -626719032.9726489552325062865
  s21_decimal decimal_check = {
      {0xC8A230D1, 0x8B218567, 0x1440192C, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6951) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // 437714411.7946199799900802522
  s21_decimal decimal_check = {{0xE3560DDA, 0x19149E02, 0xE24B052, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6952) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // -437714411.7946199799900802522
  s21_decimal decimal_check = {{0xE3560DDA, 0x19149E02, 0xE24B052, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6953) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // 74070.334375065209403862260466
  s21_decimal decimal_check = {{0x37759AF2, 0x4F051F83, 0xEF558B68, 0x180000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6954) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // -74070.334375065209403862260466
  s21_decimal decimal_check = {
      {0x37759AF2, 0x4F051F83, 0xEF558B68, 0x80180000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6955) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // 78332045.133668961292122879484
  s21_decimal decimal_check = {{0xCE8C75FC, 0x7533EE99, 0xFD1ABFC3, 0x150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6956) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // -78332045.133668961292122879484
  s21_decimal decimal_check = {
      {0xCE8C75FC, 0x7533EE99, 0xFD1ABFC3, 0x80150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6957) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // 626030330.73861307725972331256
  s21_decimal decimal_check = {{0x12055AF8, 0x24A33D07, 0xCA4803E7, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6958) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // -626030330.73861307725972331256
  s21_decimal decimal_check = {
      {0x12055AF8, 0x24A33D07, 0xCA4803E7, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6959) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // 626656361.06935169033698303587
  s21_decimal decimal_check = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6960) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -626656361.06935169033698303587
  s21_decimal decimal_check = {
      {0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6961) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // 62665636.106935169033698303587
  s21_decimal decimal_check = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6962) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -62665636.106935169033698303587
  s21_decimal decimal_check = {
      {0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6963) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div6964) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div6965) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div6966) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div6967) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // -0.0000000000000000004385086105
  s21_decimal decimal_check = {{0x55F1A99, 0x1, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6968) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // 0.0000000000000000004385086105
  s21_decimal decimal_check = {{0x55F1A99, 0x1, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6969) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // 0.1713921139772618486656577484
  s21_decimal decimal_check = {{0xADFCAFCC, 0x291786E7, 0x589B8EB, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6970) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -0.1713921139772618486656577484
  s21_decimal decimal_check = {{0xADFCAFCC, 0x291786E7, 0x589B8EB, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6971) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6972) {
  // 626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6973) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6974) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6975) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.0000000000000000000790951527
  s21_decimal decimal_check = {{0x2F24F667, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6976) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.0000000000000000000790951527
  s21_decimal decimal_check = {{0x2F24F667, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6977) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6978) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6979) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000000000237285458
  s21_decimal decimal_check = {{0xE24B052, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6980) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.0000000000000000000237285458
  s21_decimal decimal_check = {{0xE24B052, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6981) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // -0.0000000000000000000158190305
  s21_decimal decimal_check = {{0x96DCAE1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6982) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // 0.0000000000000000000158190305
  s21_decimal decimal_check = {{0x96DCAE1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6983) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // -0.0000000000000000000158190305
  s21_decimal decimal_check = {{0x96DCAE1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6984) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // 0.0000000000000000000158190305
  s21_decimal decimal_check = {{0x96DCAE1, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6985) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // -158190305.3618156786992619726
  s21_decimal decimal_check = {{0xD34520CE, 0x5EA58203, 0x51C8500, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6986) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // 158190305.3618156786992619726
  s21_decimal decimal_check = {{0xD34520CE, 0x5EA58203, 0x51C8500, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6987) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // -0.145904803863597774522701572
  s21_decimal decimal_check = {{0x17EA5704, 0x4428E872, 0x78B08B, 0x801B0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6988) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // 0.145904803863597774522701572
  s21_decimal decimal_check = {{0x17EA5704, 0x4428E872, 0x78B08B, 0x1B0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6989) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6990) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000079095153
  s21_decimal decimal_check = {{0x4B6E571, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6991) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // -0.1459048038975688839184546461
  s21_decimal decimal_check = {{0x98C07A9D, 0xAE4FF9E5, 0x4B6E570, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6992) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // 0.1459048038975688839184546461
  s21_decimal decimal_check = {{0x98C07A9D, 0xAE4FF9E5, 0x4B6E570, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6993) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // -0.2918096077951377678369092922
  s21_decimal decimal_check = {{0x3180F53A, 0x5C9FF3CB, 0x96DCAE1, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6994) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // 0.2918096077951377678369092922
  s21_decimal decimal_check = {{0x3180F53A, 0x5C9FF3CB, 0x96DCAE1, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6995) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // -0.0729524019572772193111316598
  s21_decimal decimal_check = {{0xF88B1876, 0x5855B64E, 0x25B72B8, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6996) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // 0.0729524019572772193111316598
  s21_decimal decimal_check = {{0xF88B1876, 0x5855B64E, 0x25B72B8, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6997) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // -125331272.21387033806739660717
  s21_decimal decimal_check = {
      {0x5E7CDFAD, 0x12C0A10E, 0x287F28EC, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6998) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // 125331272.21387033806739660717
  s21_decimal decimal_check = {{0x5E7CDFAD, 0x12C0A10E, 0x287F28EC, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div6999) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // -313328180.53467584516849151794
  s21_decimal decimal_check = {
      {0xEC382F32, 0x2EE192A3, 0x653DE64E, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7000) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // 313328180.53467584516849151794
  s21_decimal decimal_check = {{0xEC382F32, 0x2EE192A3, 0x653DE64E, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7001) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -313328180.5346758451684915336
  s21_decimal decimal_check = {{0x979F3888, 0x4B02843, 0xA1FCA3B, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7002) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 313328180.5346758451684915336
  s21_decimal decimal_check = {{0x979F3888, 0x4B02843, 0xA1FCA3B, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7003) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -313328180.53467584516849151795
  s21_decimal decimal_check = {
      {0xEC382F33, 0x2EE192A3, 0x653DE64E, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7004) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 313328180.53467584516849151795
  s21_decimal decimal_check = {{0xEC382F33, 0x2EE192A3, 0x653DE64E, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7005) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -626656361.06935169033698303581
  s21_decimal decimal_check = {
      {0xD8705E5D, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7006) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 626656361.06935169033698303581
  s21_decimal decimal_check = {{0xD8705E5D, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7007) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div7008) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div7009) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div7010) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div7011) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 2);
}

START_TEST(test_div7012) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 1);
}

START_TEST(test_div7013) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -626656361.06935169033698303593
  s21_decimal decimal_check = {
      {0xD8705E69, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7014) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 626656361.06935169033698303593
  s21_decimal decimal_check = {{0xD8705E69, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

/* START_TEST(test_div7015) { */
/*     // -626656361.06935169033698303587 */
/*     s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C,
 * 0x80140000}}; */
/*     // 7.9228162514264337593543950335 */
/*     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
 */
/*     // -79095152.680907839349630986301 */
/*     s21_decimal decimal_check = {{0x4380683D, 0x7C5364BF, 0xFF91FA12,
 * 0x80150000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

/* START_TEST(test_div7016) { */
/*     // -626656361.06935169033698303587 */
/*     s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C,
 * 0x80140000}}; */
/*     // -7.9228162514264337593543950335 */
/*     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
 * 0x801C0000}}; */
/*     // 79095152.680907839349630986301 */
/*     s21_decimal decimal_check = {{0x4380683D, 0x7C5364BF, 0xFF91FA12,
 * 0x150000}}; */
/*     s21_decimal result; */
/*     s21_div(decimal1, decimal2, &result); */
/*     ck_assert_int_eq(s21_is_equal(decimal_check, result), 1); */

/* } */

START_TEST(test_div7017) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
  // -10444272.684489194838949717264
  s21_decimal decimal_check = {
      {0x4EBD6510, 0xBA4B30E1, 0x21BF4CC4, 0x80150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7018) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // 10444272.684489194838949717264
  s21_decimal decimal_check = {{0x4EBD6510, 0xBA4B30E1, 0x21BF4CC4, 0x150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7019) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -1253312722.1387033806739660717
  s21_decimal decimal_check = {
      {0x5E7CDFAD, 0x12C0A10E, 0x287F28EC, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7020) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 1253312722.1387033806739660717
  s21_decimal decimal_check = {{0x5E7CDFAD, 0x12C0A10E, 0x287F28EC, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7021) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // -626656361069.35169033698303587
  s21_decimal decimal_check = {
      {0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80110000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7022) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // 626656361069.35169033698303587
  s21_decimal decimal_check = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x110000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7023) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // -32981913740.492194228262265046
  s21_decimal decimal_check = {
      {0xC2C1E0D6, 0x8230D040, 0x6A91FFE6, 0x80120000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7024) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // 32981913740.492194228262265046
  s21_decimal decimal_check = {{0xC2C1E0D6, 0x8230D040, 0x6A91FFE6, 0x120000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7025) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
  // -0.0000158190305324984128082068
  s21_decimal decimal_check = {{0x36F99094, 0x837D94EA, 0x217F, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7026) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
  // 0.0000158190305324984128082068
  s21_decimal decimal_check = {{0x36F99094, 0x837D94EA, 0x217F, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7027) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // -14590480.38975688839184546461
  s21_decimal decimal_check = {{0x98C07A9D, 0xAE4FF9E5, 0x4B6E570, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7028) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // 14590480.38975688839184546461
  s21_decimal decimal_check = {{0x98C07A9D, 0xAE4FF9E5, 0x4B6E570, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7029) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // -2918.0960779513776783690929221
  s21_decimal decimal_check = {
      {0xEF099445, 0x9E3F85EF, 0x5E49ECCD, 0x80190000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7030) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // 2918.0960779513776783690929221
  s21_decimal decimal_check = {{0xEF099445, 0x9E3F85EF, 0x5E49ECCD, 0x190000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7031) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // -14590480.393153999333002675073
  s21_decimal decimal_check = {
      {0xF5C98381, 0xFE44B95E, 0x2F24F666, 0x80150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7032) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // 14590480.393153999333002675073
  s21_decimal decimal_check = {{0xF5C98381, 0xFE44B95E, 0x2F24F666, 0x150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7033) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // -626719032.9726489552325062865
  s21_decimal decimal_check = {
      {0xC8A230D1, 0x8B218567, 0x1440192C, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7034) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // 626719032.9726489552325062865
  s21_decimal decimal_check = {{0xC8A230D1, 0x8B218567, 0x1440192C, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7035) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // -437714411.7946199799900802522
  s21_decimal decimal_check = {{0xE3560DDA, 0x19149E02, 0xE24B052, 0x80130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7036) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // 437714411.7946199799900802522
  s21_decimal decimal_check = {{0xE3560DDA, 0x19149E02, 0xE24B052, 0x130000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7037) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // -74070.334375065209403862260466
  s21_decimal decimal_check = {
      {0x37759AF2, 0x4F051F83, 0xEF558B68, 0x80180000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7038) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // 74070.334375065209403862260466
  s21_decimal decimal_check = {{0x37759AF2, 0x4F051F83, 0xEF558B68, 0x180000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7039) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // -78332045.133668961292122879484
  s21_decimal decimal_check = {
      {0xCE8C75FC, 0x7533EE99, 0xFD1ABFC3, 0x80150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7040) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // 78332045.133668961292122879484
  s21_decimal decimal_check = {{0xCE8C75FC, 0x7533EE99, 0xFD1ABFC3, 0x150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7041) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // -626030330.73861307725972331256
  s21_decimal decimal_check = {
      {0x12055AF8, 0x24A33D07, 0xCA4803E7, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7042) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // 626030330.73861307725972331256
  s21_decimal decimal_check = {{0x12055AF8, 0x24A33D07, 0xCA4803E7, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7043) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // -626656361.06935169033698303587
  s21_decimal decimal_check = {
      {0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7044) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // 626656361.06935169033698303587
  s21_decimal decimal_check = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7045) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // -62665636.106935169033698303587
  s21_decimal decimal_check = {
      {0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7046) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // 62665636.106935169033698303587
  s21_decimal decimal_check = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x150000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7047) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div7048) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div7049) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div7050) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  s21_decimal result;
  ck_assert_int_eq(s21_div(decimal1, decimal2, &result), 3);
}

START_TEST(test_div7051) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // 0.0000000000000000004385086105
  s21_decimal decimal_check = {{0x55F1A99, 0x1, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7052) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // -0.0000000000000000004385086105
  s21_decimal decimal_check = {{0x55F1A99, 0x1, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7053) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // -0.1713921139772618486656577484
  s21_decimal decimal_check = {{0xADFCAFCC, 0x291786E7, 0x589B8EB, 0x801C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7054) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 0.1713921139772618486656577484
  s21_decimal decimal_check = {{0xADFCAFCC, 0x291786E7, 0x589B8EB, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7055) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_div7056) {
  // -626656361.06935169033698303587
  s21_decimal decimal1 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(decimal_check, result), 1);
}

START_TEST(test_round_ok200) {
  // -2640938749860586450661146624.0
  s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80010000}};
  // -2640938749860586450661146624
  s21_decimal decimal_check = {{0x0, 0x80000000, 0x8888888, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok201) {
  // 2640938749860586.4506611466240
  s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0xD0000}};
  // 2640938749860586
  s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok202) {
  // -2640938749860586.4506611466240
  s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x800D0000}};
  // -2640938749860586
  s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok203) {
  // 2.6409387498605864506611466240
  s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x1C0000}};
  // 3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok204) {
  // -2.6409387498605864506611466240
  s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x801C0000}};
  // -3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok205) {
  // 6148914691236517205
  s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 6148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok206) {
  // -6148914691236517205
  s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

/* START_TEST(test_round_ok207) { */
/*     // 614891469123651720.5 */
/*     s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x10000}}; */
/*     // 614891469123651720 */
/*     s21_decimal decimal_check = {{0x88888888, 0x8888888, 0x0, 0x0}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

/* START_TEST(test_round_ok208) { */
/*     // -614891469123651720.5 */
/*     s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80010000}}; */
/*     // -614891469123651720 */
/*     s21_decimal decimal_check = {{0x88888888, 0x8888888, 0x0, 0x80000000}};
 */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

START_TEST(test_round_ok209) {
  // 6148914.691236517205
  s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0xC0000}};
  // 6148915
  s21_decimal decimal_check = {{0x5DD333, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok210) {
  // -6148914.691236517205
  s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};
  // -6148915
  s21_decimal decimal_check = {{0x5DD333, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok211) {
  // 6.148914691236517205
  s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x120000}};
  // 6
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok212) {
  // -6.148914691236517205
  s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80120000}};
  // -6
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok213) {
  // 6148914689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};
  // 6148914689804861440
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok214) {
  // -6148914689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok215) {
  // 614891468980486144.0
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};
  // 614891468980486144
  s21_decimal decimal_check = {{0x80000000, 0x8888888, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok216) {
  // -614891468980486144.0
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};
  // -614891468980486144
  s21_decimal decimal_check = {{0x80000000, 0x8888888, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok217) {
  // 6148914.689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0xC0000}};
  // 6148915
  s21_decimal decimal_check = {{0x5DD333, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok218) {
  // -6148914.689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x800C0000}};
  // -6148915
  s21_decimal decimal_check = {{0x5DD333, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok219) {
  // 6.148914689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x120000}};
  // 6
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok220) {
  // -6.148914689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80120000}};
  // -6
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok221) {
  // 1431655765
  s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x0}};
  // 1431655765
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok222) {
  // -1431655765
  s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -1431655765
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

/* START_TEST(test_round_ok223) { */
/*     // 143165576.5 */
/*     s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}}; */
/*     // 143165576 */
/*     s21_decimal decimal_check = {{0x8888888, 0x0, 0x0, 0x0}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

/* START_TEST(test_round_ok224) { */
/*     // -143165576.5 */
/*     s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80010000}}; */
/*     // -143165576 */
/*     s21_decimal decimal_check = {{0x8888888, 0x0, 0x0, 0x80000000}}; */
/*     s21_decimal result; */
/*     s21_round(decimal, &result); */

/*     ck_assert_int_eq(s21_is_equal(result, decimal_check), 1); */

/* } */

START_TEST(test_round_ok225) {
  // 143165.5765
  s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x40000}};
  // 143166
  s21_decimal decimal_check = {{0x22F3E, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok226) {
  // -143165.5765
  s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80040000}};
  // -143166
  s21_decimal decimal_check = {{0x22F3E, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok227) {
  // 1.431655765
  s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x90000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok228) {
  // -1.431655765
  s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok229) {
  // 18446744078004518913
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x0}};
  // 18446744078004518913
  s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok230) {
  // -18446744078004518913
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000000}};
  // -18446744078004518913
  s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok231) {
  // 1844674407800451891.3
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x10000}};
  // 1844674407800451891
  s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok232) {
  // -1844674407800451891.3
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80010000}};
  // -1844674407800451891
  s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok233) {
  // 184467440780.04518913
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000}};
  // 184467440780
  s21_decimal decimal_check = {{0xF31DC48C, 0x2A, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok234) {
  // -184467440780.04518913
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80080000}};
  // -184467440780
  s21_decimal decimal_check = {{0xF31DC48C, 0x2A, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok235) {
  // 1.8446744078004518913
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x130000}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok236) {
  // -1.8446744078004518913
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80130000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok237) {
  // 18446744078004518912
  s21_decimal decimal = {{0x0, 0x1, 0x1, 0x0}};
  // 18446744078004518912
  s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok238) {
  // -18446744078004518912
  s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80000000}};
  // -18446744078004518912
  s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok239) {
  // 1844674407800451891.2
  s21_decimal decimal = {{0x0, 0x1, 0x1, 0x10000}};
  // 1844674407800451891
  s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok240) {
  // -1844674407800451891.2
  s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80010000}};
  // -1844674407800451891
  s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok241) {
  // 18446744078.004518912
  s21_decimal decimal = {{0x0, 0x1, 0x1, 0x90000}};
  // 18446744078
  s21_decimal decimal_check = {{0x4B82FA0E, 0x4, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok242) {
  // -18446744078.004518912
  s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80090000}};
  // -18446744078
  s21_decimal decimal_check = {{0x4B82FA0E, 0x4, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok243) {
  // 1.8446744078004518912
  s21_decimal decimal = {{0x0, 0x1, 0x1, 0x130000}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok244) {
  // -1.8446744078004518912
  s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80130000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok245) {
  // 18446744073709551617
  s21_decimal decimal = {{0x1, 0x0, 0x1, 0x0}};
  // 18446744073709551617
  s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok246) {
  // -18446744073709551617
  s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80000000}};
  // -18446744073709551617
  s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok247) {
  // 1844674407370955161.7
  s21_decimal decimal = {{0x1, 0x0, 0x1, 0x10000}};
  // 1844674407370955162
  s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok248) {
  // -1844674407370955161.7
  s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80010000}};
  // -1844674407370955162
  s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok249) {
  // 1844674407.3709551617
  s21_decimal decimal = {{0x1, 0x0, 0x1, 0xA0000}};
  // 1844674407
  s21_decimal decimal_check = {{0x6DF37F67, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok250) {
  // -1844674407.3709551617
  s21_decimal decimal = {{0x1, 0x0, 0x1, 0x800A0000}};
  // -1844674407
  s21_decimal decimal_check = {{0x6DF37F67, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok251) {
  // 1.8446744073709551617
  s21_decimal decimal = {{0x1, 0x0, 0x1, 0x130000}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok252) {
  // -1.8446744073709551617
  s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80130000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok253) {
  // 18446744073709551616
  s21_decimal decimal = {{0x0, 0x0, 0x1, 0x0}};
  // 18446744073709551616
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok254) {
  // -18446744073709551616
  s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80000000}};
  // -18446744073709551616
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok255) {
  // 1844674407370955161.6
  s21_decimal decimal = {{0x0, 0x0, 0x1, 0x10000}};
  // 1844674407370955162
  s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok256) {
  // -1844674407370955161.6
  s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80010000}};
  // -1844674407370955162
  s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok257) {
  // 184467440.73709551616
  s21_decimal decimal = {{0x0, 0x0, 0x1, 0xB0000}};
  // 184467441
  s21_decimal decimal_check = {{0xAFEBFF1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok258) {
  // -184467440.73709551616
  s21_decimal decimal = {{0x0, 0x0, 0x1, 0x800B0000}};
  // -184467441
  s21_decimal decimal_check = {{0xAFEBFF1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok259) {
  // 1.8446744073709551616
  s21_decimal decimal = {{0x0, 0x0, 0x1, 0x130000}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok260) {
  // -1.8446744073709551616
  s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80130000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok261) {
  // 4294967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};
  // 4294967297
  s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok262) {
  // -4294967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};
  // -4294967297
  s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok263) {
  // 429496729.7
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
  // 429496730
  s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok264) {
  // -429496729.7
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
  // -429496730
  s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok265) {
  // 42949672.97
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x20000}};
  // 42949673
  s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok266) {
  // -42949672.97
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80020000}};
  // -42949673
  s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok267) {
  // 429496.7297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x40000}};
  // 429497
  s21_decimal decimal_check = {{0x68DB9, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok268) {
  // -429496.7297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80040000}};
  // -429497
  s21_decimal decimal_check = {{0x68DB9, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok269) {
  // 4.294967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x90000}};
  // 4
  s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok270) {
  // -4.294967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80090000}};
  // -4
  s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok271) {
  // 42.94967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000}};
  // 43
  s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok272) {
  // -42.94967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80080000}};
  // -43
  s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok273) {
  // 4294967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x0}};
  // 4294967296
  s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok274) {
  // -4294967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000000}};
  // -4294967296
  s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok275) {
  // 429496729.6
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x10000}};
  // 429496730
  s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok276) {
  // -429496729.6
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80010000}};
  // -429496730
  s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok277) {
  // 42949672.96
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x20000}};
  // 42949673
  s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok278) {
  // -42949672.96
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80020000}};
  // -42949673
  s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok279) {
  // 4294967.296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
  // 4294967
  s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok280) {
  // -4294967.296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
  // -4294967
  s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok281) {
  // 4.294967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
  // 4
  s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok282) {
  // -4.294967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
  // -4
  s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok283) {
  // 42.94967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000}};
  // 43
  s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok284) {
  // -42.94967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80080000}};
  // -43
  s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok285) {
  // 1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok286) {
  // -1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok287) {
  // 0.1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok288) {
  // -0.1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok289) {
  // 0.0000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok290) {
  // -0.0000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok291) {
  // 0.00000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0xE0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok292) {
  // -0.00000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800E0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok293) {
  // 0.000000000000000000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1B0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok294) {
  // -0.000000000000000000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801B0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok295) {
  // 0.0000000000000000000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok296) {
  // -0.0000000000000000000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok297) {
  // 39614081266355540835774234624
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};
  // 39614081266355540835774234624
  s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok298) {
  // -39614081266355540835774234624
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};
  // -39614081266355540835774234624
  s21_decimal decimal_check = {
      {0x80000000, 0x80000000, 0x80000000, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok299) {
  // 3961408126635554083577423462.4
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x10000}};
  // 3961408126635554083577423462
  s21_decimal decimal_check = {{0xA6666666, 0xD9999999, 0xCCCCCCC, 0x0}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok300) {
  // -3961408126635554083577423462.4
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80010000}};
  // -3961408126635554083577423462
  s21_decimal decimal_check = {{0xA6666666, 0xD9999999, 0xCCCCCCC, 0x80000000}};
  s21_decimal result;
  s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

int main() {
  Suite *s1 = suite_create("s21_decimal: ");
  TCase *tc1_1 = tcase_create("s21_decimal: ");
  TCase *tc = tcase_create("Core");
  TCase *tc_core = tcase_create("C#");
  SRunner *sr = srunner_create(s1);
  int result;
  tcase_set_timeout(tc, 40);

  tcase_add_test(tc_core, test_round_ok200);
  tcase_add_test(tc_core, test_round_ok201);
  tcase_add_test(tc_core, test_round_ok202);
  tcase_add_test(tc_core, test_round_ok203);
  tcase_add_test(tc_core, test_round_ok204);
  tcase_add_test(tc_core, test_round_ok205);
  tcase_add_test(tc_core, test_round_ok206);
  /* tcase_add_test(tc_core, test_round_ok207); */
  /* tcase_add_test(tc_core, test_round_ok208); */
  tcase_add_test(tc_core, test_round_ok209);
  tcase_add_test(tc_core, test_round_ok210);
  tcase_add_test(tc_core, test_round_ok211);
  tcase_add_test(tc_core, test_round_ok212);
  tcase_add_test(tc_core, test_round_ok213);
  tcase_add_test(tc_core, test_round_ok214);
  tcase_add_test(tc_core, test_round_ok215);
  tcase_add_test(tc_core, test_round_ok216);
  tcase_add_test(tc_core, test_round_ok217);
  tcase_add_test(tc_core, test_round_ok218);
  tcase_add_test(tc_core, test_round_ok219);
  tcase_add_test(tc_core, test_round_ok220);
  tcase_add_test(tc_core, test_round_ok221);
  tcase_add_test(tc_core, test_round_ok222);
  /* tcase_add_test(tc_core, test_round_ok223); */
  /* tcase_add_test(tc_core, test_round_ok224); */
  tcase_add_test(tc_core, test_round_ok225);
  tcase_add_test(tc_core, test_round_ok226);
  tcase_add_test(tc_core, test_round_ok227);
  tcase_add_test(tc_core, test_round_ok228);
  tcase_add_test(tc_core, test_round_ok229);
  tcase_add_test(tc_core, test_round_ok230);
  tcase_add_test(tc_core, test_round_ok231);
  tcase_add_test(tc_core, test_round_ok232);
  tcase_add_test(tc_core, test_round_ok233);
  tcase_add_test(tc_core, test_round_ok234);
  tcase_add_test(tc_core, test_round_ok235);
  tcase_add_test(tc_core, test_round_ok236);
  tcase_add_test(tc_core, test_round_ok237);
  tcase_add_test(tc_core, test_round_ok238);
  tcase_add_test(tc_core, test_round_ok239);
  tcase_add_test(tc_core, test_round_ok240);
  tcase_add_test(tc_core, test_round_ok241);
  tcase_add_test(tc_core, test_round_ok242);
  tcase_add_test(tc_core, test_round_ok243);
  tcase_add_test(tc_core, test_round_ok244);
  tcase_add_test(tc_core, test_round_ok245);
  tcase_add_test(tc_core, test_round_ok246);
  tcase_add_test(tc_core, test_round_ok247);
  tcase_add_test(tc_core, test_round_ok248);
  tcase_add_test(tc_core, test_round_ok249);
  tcase_add_test(tc_core, test_round_ok250);
  tcase_add_test(tc_core, test_round_ok251);
  tcase_add_test(tc_core, test_round_ok252);
  tcase_add_test(tc_core, test_round_ok253);
  tcase_add_test(tc_core, test_round_ok254);
  tcase_add_test(tc_core, test_round_ok255);
  tcase_add_test(tc_core, test_round_ok256);
  tcase_add_test(tc_core, test_round_ok257);
  tcase_add_test(tc_core, test_round_ok258);
  tcase_add_test(tc_core, test_round_ok259);
  tcase_add_test(tc_core, test_round_ok260);
  tcase_add_test(tc_core, test_round_ok261);
  tcase_add_test(tc_core, test_round_ok262);
  tcase_add_test(tc_core, test_round_ok263);
  tcase_add_test(tc_core, test_round_ok264);
  tcase_add_test(tc_core, test_round_ok265);
  tcase_add_test(tc_core, test_round_ok266);
  tcase_add_test(tc_core, test_round_ok267);
  tcase_add_test(tc_core, test_round_ok268);
  tcase_add_test(tc_core, test_round_ok269);
  tcase_add_test(tc_core, test_round_ok270);
  tcase_add_test(tc_core, test_round_ok271);
  tcase_add_test(tc_core, test_round_ok272);
  tcase_add_test(tc_core, test_round_ok273);
  tcase_add_test(tc_core, test_round_ok274);
  tcase_add_test(tc_core, test_round_ok275);
  tcase_add_test(tc_core, test_round_ok276);
  tcase_add_test(tc_core, test_round_ok277);
  tcase_add_test(tc_core, test_round_ok278);
  tcase_add_test(tc_core, test_round_ok279);
  tcase_add_test(tc_core, test_round_ok280);
  tcase_add_test(tc_core, test_round_ok281);
  tcase_add_test(tc_core, test_round_ok282);
  tcase_add_test(tc_core, test_round_ok283);
  tcase_add_test(tc_core, test_round_ok284);
  tcase_add_test(tc_core, test_round_ok285);
  tcase_add_test(tc_core, test_round_ok286);
  tcase_add_test(tc_core, test_round_ok287);
  tcase_add_test(tc_core, test_round_ok288);
  tcase_add_test(tc_core, test_round_ok289);
  tcase_add_test(tc_core, test_round_ok290);
  tcase_add_test(tc_core, test_round_ok291);
  tcase_add_test(tc_core, test_round_ok292);
  tcase_add_test(tc_core, test_round_ok293);
  tcase_add_test(tc_core, test_round_ok294);
  tcase_add_test(tc_core, test_round_ok295);
  tcase_add_test(tc_core, test_round_ok296);
  tcase_add_test(tc_core, test_round_ok297);
  tcase_add_test(tc_core, test_round_ok298);
  tcase_add_test(tc_core, test_round_ok299);
  tcase_add_test(tc_core, test_round_ok300);
  tcase_add_test(tc_core, test_div6801);
  tcase_add_test(tc_core, test_div6802);
  tcase_add_test(tc_core, test_div6803);
  tcase_add_test(tc_core, test_div6804);
  tcase_add_test(tc_core, test_div6805);
  tcase_add_test(tc_core, test_div6806);
  tcase_add_test(tc_core, test_div6807);
  tcase_add_test(tc_core, test_div6808);
  tcase_add_test(tc_core, test_div6809);
  tcase_add_test(tc_core, test_div6810);
  tcase_add_test(tc_core, test_div6811);
  tcase_add_test(tc_core, test_div6812);
  /* tcase_add_test(tc_core, test_div6813); */
  /* tcase_add_test(tc_core, test_div6814); */
  /* tcase_add_test(tc_core, test_div6815); */
  /* tcase_add_test(tc_core, test_div6816); */
  tcase_add_test(tc_core, test_div6817);
  tcase_add_test(tc_core, test_div6818);
  tcase_add_test(tc_core, test_div6819);
  tcase_add_test(tc_core, test_div6820);
  tcase_add_test(tc_core, test_div6821);
  tcase_add_test(tc_core, test_div6822);
  tcase_add_test(tc_core, test_div6823);
  tcase_add_test(tc_core, test_div6824);
  tcase_add_test(tc_core, test_div6825);
  tcase_add_test(tc_core, test_div6826);
  tcase_add_test(tc_core, test_div6827);
  tcase_add_test(tc_core, test_div6828);
  tcase_add_test(tc_core, test_div6829);
  tcase_add_test(tc_core, test_div6830);
  /* tcase_add_test(tc_core, test_div6831); */
  /* tcase_add_test(tc_core, test_div6832); */
  tcase_add_test(tc_core, test_div6833);
  tcase_add_test(tc_core, test_div6834);
  tcase_add_test(tc_core, test_div6835);
  tcase_add_test(tc_core, test_div6836);
  tcase_add_test(tc_core, test_div6837);
  tcase_add_test(tc_core, test_div6838);
  tcase_add_test(tc_core, test_div6839);
  tcase_add_test(tc_core, test_div6840);
  tcase_add_test(tc_core, test_div6841);
  tcase_add_test(tc_core, test_div6842);
  tcase_add_test(tc_core, test_div6843);
  tcase_add_test(tc_core, test_div6844);
  tcase_add_test(tc_core, test_div6845);
  tcase_add_test(tc_core, test_div6846);
  tcase_add_test(tc_core, test_div6847);
  tcase_add_test(tc_core, test_div6848);
  tcase_add_test(tc_core, test_div6849);
  tcase_add_test(tc_core, test_div6850);
  tcase_add_test(tc_core, test_div6851);
  tcase_add_test(tc_core, test_div6852);
  tcase_add_test(tc_core, test_div6853);
  tcase_add_test(tc_core, test_div6854);
  tcase_add_test(tc_core, test_div6855);
  tcase_add_test(tc_core, test_div6856);
  tcase_add_test(tc_core, test_div6857);
  tcase_add_test(tc_core, test_div6858);
  tcase_add_test(tc_core, test_div6859);
  tcase_add_test(tc_core, test_div6860);
  tcase_add_test(tc_core, test_div6861);
  tcase_add_test(tc_core, test_div6862);
  tcase_add_test(tc_core, test_div6863);
  tcase_add_test(tc_core, test_div6864);
  tcase_add_test(tc_core, test_div6865);
  tcase_add_test(tc_core, test_div6866);
  tcase_add_test(tc_core, test_div6867);
  tcase_add_test(tc_core, test_div6868);
  tcase_add_test(tc_core, test_div6869);
  tcase_add_test(tc_core, test_div6870);
  tcase_add_test(tc_core, test_div6871);
  tcase_add_test(tc_core, test_div6872);
  tcase_add_test(tc_core, test_div6873);
  tcase_add_test(tc_core, test_div6874);
  tcase_add_test(tc_core, test_div6875);
  tcase_add_test(tc_core, test_div6876);
  tcase_add_test(tc_core, test_div6877);
  tcase_add_test(tc_core, test_div6878);
  tcase_add_test(tc_core, test_div6879);
  tcase_add_test(tc_core, test_div6880);
  tcase_add_test(tc_core, test_div6881);
  tcase_add_test(tc_core, test_div6882);
  tcase_add_test(tc_core, test_div6883);
  tcase_add_test(tc_core, test_div6884);
  tcase_add_test(tc_core, test_div6885);
  tcase_add_test(tc_core, test_div6886);
  tcase_add_test(tc_core, test_div6887);
  tcase_add_test(tc_core, test_div6888);
  tcase_add_test(tc_core, test_div6889);
  tcase_add_test(tc_core, test_div6890);
  tcase_add_test(tc_core, test_div6891);
  tcase_add_test(tc_core, test_div6892);
  tcase_add_test(tc_core, test_div6893);
  tcase_add_test(tc_core, test_div6894);
  tcase_add_test(tc_core, test_div6895);
  tcase_add_test(tc_core, test_div6896);
  tcase_add_test(tc_core, test_div6897);
  tcase_add_test(tc_core, test_div6898);
  tcase_add_test(tc_core, test_div6899);
  tcase_add_test(tc_core, test_div6900);
  tcase_add_test(tc_core, test_div6901);
  tcase_add_test(tc_core, test_div6902);
  tcase_add_test(tc_core, test_div6903);
  tcase_add_test(tc_core, test_div6904);
  tcase_add_test(tc_core, test_div6905);
  tcase_add_test(tc_core, test_div6906);
  tcase_add_test(tc_core, test_div6907);
  tcase_add_test(tc_core, test_div6908);
  tcase_add_test(tc_core, test_div6909);
  tcase_add_test(tc_core, test_div6910);
  tcase_add_test(tc_core, test_div6911);
  tcase_add_test(tc_core, test_div6912);
  tcase_add_test(tc_core, test_div6913);
  tcase_add_test(tc_core, test_div6914);
  tcase_add_test(tc_core, test_div6915);
  tcase_add_test(tc_core, test_div6916);
  tcase_add_test(tc_core, test_div6917);
  tcase_add_test(tc_core, test_div6918);
  tcase_add_test(tc_core, test_div6919);
  tcase_add_test(tc_core, test_div6920);
  tcase_add_test(tc_core, test_div6921);
  tcase_add_test(tc_core, test_div6922);
  tcase_add_test(tc_core, test_div6923);
  tcase_add_test(tc_core, test_div6924);
  tcase_add_test(tc_core, test_div6925);
  tcase_add_test(tc_core, test_div6926);
  tcase_add_test(tc_core, test_div6927);
  tcase_add_test(tc_core, test_div6928);
  tcase_add_test(tc_core, test_div6929);
  tcase_add_test(tc_core, test_div6930);
  /* tcase_add_test(tc_core, test_div6931); */
  /* tcase_add_test(tc_core, test_div6932); */
  tcase_add_test(tc_core, test_div6933);
  tcase_add_test(tc_core, test_div6934);
  tcase_add_test(tc_core, test_div6935);
  tcase_add_test(tc_core, test_div6936);
  tcase_add_test(tc_core, test_div6937);
  tcase_add_test(tc_core, test_div6938);
  tcase_add_test(tc_core, test_div6939);
  tcase_add_test(tc_core, test_div6940);
  tcase_add_test(tc_core, test_div6941);
  tcase_add_test(tc_core, test_div6942);
  tcase_add_test(tc_core, test_div6943);
  tcase_add_test(tc_core, test_div6944);
  tcase_add_test(tc_core, test_div6945);
  tcase_add_test(tc_core, test_div6946);
  tcase_add_test(tc_core, test_div6947);
  tcase_add_test(tc_core, test_div6948);
  tcase_add_test(tc_core, test_div6949);
  tcase_add_test(tc_core, test_div6950);
  tcase_add_test(tc_core, test_div6951);
  tcase_add_test(tc_core, test_div6952);
  tcase_add_test(tc_core, test_div6953);
  tcase_add_test(tc_core, test_div6954);
  tcase_add_test(tc_core, test_div6955);
  tcase_add_test(tc_core, test_div6956);
  tcase_add_test(tc_core, test_div6957);
  tcase_add_test(tc_core, test_div6958);
  tcase_add_test(tc_core, test_div6959);
  tcase_add_test(tc_core, test_div6960);
  tcase_add_test(tc_core, test_div6961);
  tcase_add_test(tc_core, test_div6962);
  tcase_add_test(tc_core, test_div6963);
  tcase_add_test(tc_core, test_div6964);
  tcase_add_test(tc_core, test_div6965);
  tcase_add_test(tc_core, test_div6966);
  tcase_add_test(tc_core, test_div6967);
  tcase_add_test(tc_core, test_div6968);
  tcase_add_test(tc_core, test_div6969);
  tcase_add_test(tc_core, test_div6970);
  tcase_add_test(tc_core, test_div6971);
  tcase_add_test(tc_core, test_div6972);
  tcase_add_test(tc_core, test_div6973);
  tcase_add_test(tc_core, test_div6974);
  tcase_add_test(tc_core, test_div6975);
  tcase_add_test(tc_core, test_div6976);
  tcase_add_test(tc_core, test_div6977);
  tcase_add_test(tc_core, test_div6978);
  tcase_add_test(tc_core, test_div6979);
  tcase_add_test(tc_core, test_div6980);
  tcase_add_test(tc_core, test_div6981);
  tcase_add_test(tc_core, test_div6982);
  tcase_add_test(tc_core, test_div6983);
  tcase_add_test(tc_core, test_div6984);
  tcase_add_test(tc_core, test_div6985);
  tcase_add_test(tc_core, test_div6986);
  tcase_add_test(tc_core, test_div6987);
  tcase_add_test(tc_core, test_div6988);
  tcase_add_test(tc_core, test_div6989);
  tcase_add_test(tc_core, test_div6990);
  tcase_add_test(tc_core, test_div6991);
  tcase_add_test(tc_core, test_div6992);
  tcase_add_test(tc_core, test_div6993);
  tcase_add_test(tc_core, test_div6994);
  tcase_add_test(tc_core, test_div6995);
  tcase_add_test(tc_core, test_div6996);
  tcase_add_test(tc_core, test_div6997);
  tcase_add_test(tc_core, test_div6998);
  tcase_add_test(tc_core, test_div6999);
  tcase_add_test(tc_core, test_div7000);
  tcase_add_test(tc_core, test_div7001);
  tcase_add_test(tc_core, test_div7002);
  tcase_add_test(tc_core, test_div7003);
  tcase_add_test(tc_core, test_div7004);
  tcase_add_test(tc_core, test_div7005);
  tcase_add_test(tc_core, test_div7006);
  tcase_add_test(tc_core, test_div7007);
  tcase_add_test(tc_core, test_div7008);
  tcase_add_test(tc_core, test_div7009);
  tcase_add_test(tc_core, test_div7010);
  tcase_add_test(tc_core, test_div7011);
  tcase_add_test(tc_core, test_div7012);
  tcase_add_test(tc_core, test_div7013);
  tcase_add_test(tc_core, test_div7014);
  /* tcase_add_test(tc_core, test_div7015); */
  /* tcase_add_test(tc_core, test_div7016); */
  tcase_add_test(tc_core, test_div7017);
  tcase_add_test(tc_core, test_div7018);
  tcase_add_test(tc_core, test_div7019);
  tcase_add_test(tc_core, test_div7020);
  tcase_add_test(tc_core, test_div7021);
  tcase_add_test(tc_core, test_div7022);
  tcase_add_test(tc_core, test_div7023);
  tcase_add_test(tc_core, test_div7024);
  tcase_add_test(tc_core, test_div7025);
  tcase_add_test(tc_core, test_div7026);
  tcase_add_test(tc_core, test_div7027);
  tcase_add_test(tc_core, test_div7028);
  tcase_add_test(tc_core, test_div7029);
  tcase_add_test(tc_core, test_div7030);
  tcase_add_test(tc_core, test_div7031);
  tcase_add_test(tc_core, test_div7032);
  tcase_add_test(tc_core, test_div7033);
  tcase_add_test(tc_core, test_div7034);
  tcase_add_test(tc_core, test_div7035);
  tcase_add_test(tc_core, test_div7036);
  tcase_add_test(tc_core, test_div7037);
  tcase_add_test(tc_core, test_div7038);
  tcase_add_test(tc_core, test_div7039);
  tcase_add_test(tc_core, test_div7040);
  tcase_add_test(tc_core, test_div7041);
  tcase_add_test(tc_core, test_div7042);
  tcase_add_test(tc_core, test_div7043);
  tcase_add_test(tc_core, test_div7044);
  tcase_add_test(tc_core, test_div7045);
  tcase_add_test(tc_core, test_div7046);
  tcase_add_test(tc_core, test_div7047);
  tcase_add_test(tc_core, test_div7048);
  tcase_add_test(tc_core, test_div7049);
  tcase_add_test(tc_core, test_div7050);
  tcase_add_test(tc_core, test_div7051);
  tcase_add_test(tc_core, test_div7052);
  tcase_add_test(tc_core, test_div7053);
  tcase_add_test(tc_core, test_div7054);
  tcase_add_test(tc_core, test_div7055);
  tcase_add_test(tc_core, test_div7056);

  tcase_add_test(tc_core, test_div1500);
  tcase_add_test(tc_core, test_div1501);
  tcase_add_test(tc_core, test_div1502);
  tcase_add_test(tc_core, test_div1503);
  tcase_add_test(tc_core, test_div1504);
  tcase_add_test(tc_core, test_div1505);
  tcase_add_test(tc_core, test_div1506);
  tcase_add_test(tc_core, test_div1507);
  tcase_add_test(tc_core, test_div1508);
  tcase_add_test(tc_core, test_div1509);
  tcase_add_test(tc_core, test_div1510);
  tcase_add_test(tc_core, test_div1511);
  tcase_add_test(tc_core, test_div1512);
  tcase_add_test(tc_core, test_div1513);
  tcase_add_test(tc_core, test_div1514);
  tcase_add_test(tc_core, test_div1515);
  tcase_add_test(tc_core, test_div1516);
  tcase_add_test(tc_core, test_div1517);
  tcase_add_test(tc_core, test_div1518);
  tcase_add_test(tc_core, test_div1519);
  tcase_add_test(tc_core, test_div1520);
  tcase_add_test(tc_core, test_div1521);
  tcase_add_test(tc_core, test_div1522);
  tcase_add_test(tc_core, test_div1523);
  tcase_add_test(tc_core, test_div1524);
  tcase_add_test(tc_core, test_div1525);
  tcase_add_test(tc_core, test_div1526);
  tcase_add_test(tc_core, test_div1527);
  tcase_add_test(tc_core, test_div1528);
  tcase_add_test(tc_core, test_div1529);
  tcase_add_test(tc_core, test_div1530);
  tcase_add_test(tc_core, test_div1531);
  tcase_add_test(tc_core, test_div1532);
  tcase_add_test(tc_core, test_div1533);
  tcase_add_test(tc_core, test_div1534);
  tcase_add_test(tc_core, test_div1535);
  tcase_add_test(tc_core, test_div1536);
  tcase_add_test(tc_core, test_div1537);
  tcase_add_test(tc_core, test_div1538);
  tcase_add_test(tc_core, test_div1539);
  tcase_add_test(tc_core, test_div1540);
  tcase_add_test(tc_core, test_div1541);
  tcase_add_test(tc_core, test_div1542);
  tcase_add_test(tc_core, test_div1543);
  tcase_add_test(tc_core, test_div1544);
  tcase_add_test(tc_core, test_div1545);
  tcase_add_test(tc_core, test_div1546);
  tcase_add_test(tc_core, test_div1547);
  tcase_add_test(tc_core, test_div1548);
  tcase_add_test(tc_core, test_div1549);
  tcase_add_test(tc_core, test_div1550);
  tcase_add_test(tc_core, test_div1551);
  tcase_add_test(tc_core, test_div1552);
  tcase_add_test(tc_core, test_div1553);
  tcase_add_test(tc_core, test_div1554);
  /* tcase_add_test(tc_core, test_div1555); */
  /* tcase_add_test(tc_core, test_div1556); */
  /* tcase_add_test(tc_core, test_div1557); */
  /* tcase_add_test(tc_core, test_div1558); */
  tcase_add_test(tc_core, test_div1559);
  tcase_add_test(tc_core, test_div1560);
  tcase_add_test(tc_core, test_div1561);
  tcase_add_test(tc_core, test_div1562);
  tcase_add_test(tc_core, test_div1563);
  tcase_add_test(tc_core, test_div1564);
  tcase_add_test(tc_core, test_div1565);
  tcase_add_test(tc_core, test_div1566);
  tcase_add_test(tc_core, test_div1567);
  tcase_add_test(tc_core, test_div1568);
  tcase_add_test(tc_core, test_div1569);
  tcase_add_test(tc_core, test_div1570);
  tcase_add_test(tc_core, test_div1571);
  tcase_add_test(tc_core, test_div1572);
  tcase_add_test(tc_core, test_div1573);
  tcase_add_test(tc_core, test_div1574);
  tcase_add_test(tc_core, test_div1575);
  tcase_add_test(tc_core, test_div1576);
  tcase_add_test(tc_core, test_div1577);
  tcase_add_test(tc_core, test_div1578);
  tcase_add_test(tc_core, test_div1579);
  tcase_add_test(tc_core, test_div1580);
  tcase_add_test(tc_core, test_div1581);
  tcase_add_test(tc_core, test_div1582);
  tcase_add_test(tc_core, test_div1583);
  tcase_add_test(tc_core, test_div1584);
  tcase_add_test(tc_core, test_div1585);
  tcase_add_test(tc_core, test_div1586);
  tcase_add_test(tc_core, test_div1587);
  tcase_add_test(tc_core, test_div1588);
  tcase_add_test(tc_core, test_div1589);
  tcase_add_test(tc_core, test_div1590);
  tcase_add_test(tc_core, test_div1591);
  tcase_add_test(tc_core, test_div1592);
  tcase_add_test(tc_core, test_div1593);
  tcase_add_test(tc_core, test_div1594);
  /* tcase_add_test(tc_core, test_div1595); */
  /* tcase_add_test(tc_core, test_div1596); */
  tcase_add_test(tc_core, test_div1597);
  tcase_add_test(tc_core, test_div1598);
  tcase_add_test(tc_core, test_div1599);
  tcase_add_test(tc_core, test_div1600);

  tcase_add_test(tc_core, test_div_manual1);
  tcase_add_test(tc_core, test_div_manual2);
  tcase_add_test(tc_core, test_div_manual3);
  tcase_add_test(tc_core, test_div_manual4);
  tcase_add_test(tc_core, test_div_manual5);
  tcase_add_test(tc_core, test_div_manual6);
  tcase_add_test(tc_core, test_div_manual7);
  tcase_add_test(tc_core, test_div_manual8);
  tcase_add_test(tc_core, test_div_manual9);
  tcase_add_test(tc_core, test_div_manual10);
  tcase_add_test(tc_core, test_div_manual11);
  tcase_add_test(tc_core, test_div_manual12);
  tcase_add_test(tc_core, test_div_manual13);
  tcase_add_test(tc_core, test_div_manual14);
  tcase_add_test(tc_core, test_div_manual15);
  tcase_add_test(tc_core, test_div_manual16);
  tcase_add_test(tc_core, test_div_manual17);
  tcase_add_test(tc_core, test_div_manual18);
  tcase_add_test(tc_core, test_div_manual19);
  tcase_add_test(tc_core, test_div_manual20);
  tcase_add_test(tc_core, test_div_manual21);
  tcase_add_test(tc_core, test_div_manual22);
  tcase_add_test(tc_core, test_div_manual23);
  tcase_add_test(tc_core, test_div_manual24);
  tcase_add_test(tc_core, test_div_manual25);
  tcase_add_test(tc_core, test_div_manual26);
  tcase_add_test(tc_core, test_div_manual27);

  tcase_add_test(tc_core, test_div3000);
  tcase_add_test(tc_core, test_div3001);
  tcase_add_test(tc_core, test_div3002);
  tcase_add_test(tc_core, test_div3003);
  tcase_add_test(tc_core, test_div3004);
  tcase_add_test(tc_core, test_div3005);
  tcase_add_test(tc_core, test_div3006);
  tcase_add_test(tc_core, test_div3007);
  tcase_add_test(tc_core, test_div3008);
  tcase_add_test(tc_core, test_div3009);
  tcase_add_test(tc_core, test_div3010);
  tcase_add_test(tc_core, test_div3011);
  tcase_add_test(tc_core, test_div3012);
  tcase_add_test(tc_core, test_div3013);
  tcase_add_test(tc_core, test_div3014);
  tcase_add_test(tc_core, test_div3015);
  tcase_add_test(tc_core, test_div3016);
  tcase_add_test(tc_core, test_div3017);
  tcase_add_test(tc_core, test_div3018);
  tcase_add_test(tc_core, test_div3019);
  tcase_add_test(tc_core, test_div3020);
  tcase_add_test(tc_core, test_div3021);
  tcase_add_test(tc_core, test_div3022);
  tcase_add_test(tc_core, test_div3023);
  tcase_add_test(tc_core, test_div3024);
  tcase_add_test(tc_core, test_div3025);
  tcase_add_test(tc_core, test_div3026);
  tcase_add_test(tc_core, test_div3027);
  tcase_add_test(tc_core, test_div3028);
  /* tcase_add_test(tc_core, test_div3029); */
  /* tcase_add_test(tc_core, test_div3030); */
  tcase_add_test(tc_core, test_div3031);
  tcase_add_test(tc_core, test_div3032);
  tcase_add_test(tc_core, test_div3033);
  tcase_add_test(tc_core, test_div3034);
  tcase_add_test(tc_core, test_div3035);
  tcase_add_test(tc_core, test_div3036);
  tcase_add_test(tc_core, test_div3037);
  tcase_add_test(tc_core, test_div3038);
  tcase_add_test(tc_core, test_div3039);
  tcase_add_test(tc_core, test_div3040);
  tcase_add_test(tc_core, test_div3041);
  tcase_add_test(tc_core, test_div3042);
  tcase_add_test(tc_core, test_div3043);
  tcase_add_test(tc_core, test_div3044);
  tcase_add_test(tc_core, test_div3045);
  tcase_add_test(tc_core, test_div3046);
  tcase_add_test(tc_core, test_div3047);
  tcase_add_test(tc_core, test_div3048);
  tcase_add_test(tc_core, test_div3049);
  tcase_add_test(tc_core, test_div3050);
  tcase_add_test(tc_core, test_div3051);
  tcase_add_test(tc_core, test_div3052);
  /* tcase_add_test(tc_core, test_div3053); */
  /* tcase_add_test(tc_core, test_div3054); */
  /* tcase_add_test(tc_core, test_div3055); */
  /* tcase_add_test(tc_core, test_div3056); */
  /* tcase_add_test(tc_core, test_div3057); */
  /* tcase_add_test(tc_core, test_div3058); */
  tcase_add_test(tc_core, test_div3059);
  tcase_add_test(tc_core, test_div3060);
  tcase_add_test(tc_core, test_div3061);
  tcase_add_test(tc_core, test_div3062);
  tcase_add_test(tc_core, test_div3063);
  tcase_add_test(tc_core, test_div3064);
  /* tcase_add_test(tc_core, test_div3065); */
  /* tcase_add_test(tc_core, test_div3066); */
  tcase_add_test(tc_core, test_div3067);
  tcase_add_test(tc_core, test_div3068);
  tcase_add_test(tc_core, test_div3069);
  tcase_add_test(tc_core, test_div3070);
  tcase_add_test(tc_core, test_div3071);
  tcase_add_test(tc_core, test_div3072);
  tcase_add_test(tc_core, test_div3073);
  tcase_add_test(tc_core, test_div3074);
  tcase_add_test(tc_core, test_div3075);
  tcase_add_test(tc_core, test_div3076);
  /* tcase_add_test(tc_core, test_div3077); */
  /* tcase_add_test(tc_core, test_div3078); */
  tcase_add_test(tc_core, test_div3079);
  tcase_add_test(tc_core, test_div3080);
  tcase_add_test(tc_core, test_div3081);
  tcase_add_test(tc_core, test_div3082);
  tcase_add_test(tc_core, test_div3083);
  tcase_add_test(tc_core, test_div3084);
  tcase_add_test(tc_core, test_div3085);
  tcase_add_test(tc_core, test_div3086);
  tcase_add_test(tc_core, test_div3087);
  tcase_add_test(tc_core, test_div3088);
  tcase_add_test(tc_core, test_div3089);
  tcase_add_test(tc_core, test_div3090);
  tcase_add_test(tc_core, test_div3091);
  tcase_add_test(tc_core, test_div3092);
  tcase_add_test(tc_core, test_div3093);
  tcase_add_test(tc_core, test_div3094);
  tcase_add_test(tc_core, test_div3095);
  tcase_add_test(tc_core, test_div3096);
  tcase_add_test(tc_core, test_div3097);
  tcase_add_test(tc_core, test_div3098);
  tcase_add_test(tc_core, test_div3099);
  tcase_add_test(tc_core, test_div3100);

  tcase_add_test(tc_core, test_div1);
  tcase_add_test(tc_core, test_div2);
  tcase_add_test(tc_core, test_div3);
  tcase_add_test(tc_core, test_div4);
  tcase_add_test(tc_core, test_div5);
  tcase_add_test(tc_core, test_div6);
  tcase_add_test(tc_core, test_div7);
  tcase_add_test(tc_core, test_div8);
  tcase_add_test(tc_core, test_div9);
  tcase_add_test(tc_core, test_div10);
  tcase_add_test(tc_core, test_div11);
  tcase_add_test(tc_core, test_div12);
  tcase_add_test(tc_core, test_div13);
  tcase_add_test(tc_core, test_div14);
  tcase_add_test(tc_core, test_div15);
  tcase_add_test(tc_core, test_div16);
  tcase_add_test(tc_core, test_div17);
  tcase_add_test(tc_core, test_div18);
  tcase_add_test(tc_core, test_div19);
  tcase_add_test(tc_core, test_div20);
  tcase_add_test(tc_core, test_div21);
  tcase_add_test(tc_core, test_div22);
  tcase_add_test(tc_core, test_div23);
  tcase_add_test(tc_core, test_div24);
  tcase_add_test(tc_core, test_div25);
  tcase_add_test(tc_core, test_div26);
  tcase_add_test(tc_core, test_div27);
  tcase_add_test(tc_core, test_div28);
  tcase_add_test(tc_core, test_div29);
  tcase_add_test(tc_core, test_div30);
  tcase_add_test(tc_core, test_div31);
  tcase_add_test(tc_core, test_div32);
  tcase_add_test(tc_core, test_div33);
  tcase_add_test(tc_core, test_div34);
  tcase_add_test(tc_core, test_div35);
  tcase_add_test(tc_core, test_div36);
  tcase_add_test(tc_core, test_div37);
  tcase_add_test(tc_core, test_div38);
  tcase_add_test(tc_core, test_div39);
  tcase_add_test(tc_core, test_div40);
  tcase_add_test(tc_core, test_div41);
  tcase_add_test(tc_core, test_div42);
  tcase_add_test(tc_core, test_div43);
  tcase_add_test(tc_core, test_div44);
  tcase_add_test(tc_core, test_div45);
  tcase_add_test(tc_core, test_div46);
  tcase_add_test(tc_core, test_div47);
  tcase_add_test(tc_core, test_div48);
  tcase_add_test(tc_core, test_div49);
  tcase_add_test(tc_core, test_div50);
  tcase_add_test(tc_core, test_div51);
  tcase_add_test(tc_core, test_div52);
  tcase_add_test(tc_core, test_div53);
  tcase_add_test(tc_core, test_div54);
  tcase_add_test(tc_core, test_div55);
  tcase_add_test(tc_core, test_div56);
  tcase_add_test(tc_core, test_div57);
  tcase_add_test(tc_core, test_div58);
  tcase_add_test(tc_core, test_div59);
  tcase_add_test(tc_core, test_div60);
  tcase_add_test(tc_core, test_div61);
  tcase_add_test(tc_core, test_div62);
  /* tcase_add_test(tc_core, test_div63); */
  /* tcase_add_test(tc_core, test_div64); */
  tcase_add_test(tc_core, test_div65);
  tcase_add_test(tc_core, test_div66);
  tcase_add_test(tc_core, test_div67);
  tcase_add_test(tc_core, test_div68);
  tcase_add_test(tc_core, test_div69);
  tcase_add_test(tc_core, test_div70);
  tcase_add_test(tc_core, test_div71);
  tcase_add_test(tc_core, test_div72);
  tcase_add_test(tc_core, test_div73);
  tcase_add_test(tc_core, test_div74);
  tcase_add_test(tc_core, test_div75);
  tcase_add_test(tc_core, test_div76);
  tcase_add_test(tc_core, test_div77);
  tcase_add_test(tc_core, test_div78);
  /* tcase_add_test(tc_core, test_div79); */
  /* tcase_add_test(tc_core, test_div80); */
  tcase_add_test(tc_core, test_div81);
  tcase_add_test(tc_core, test_div82);
  tcase_add_test(tc_core, test_div83);
  tcase_add_test(tc_core, test_div84);
  tcase_add_test(tc_core, test_div85);
  tcase_add_test(tc_core, test_div86);
  tcase_add_test(tc_core, test_div87);
  tcase_add_test(tc_core, test_div88);
  tcase_add_test(tc_core, test_div89);
  tcase_add_test(tc_core, test_div90);
  tcase_add_test(tc_core, test_div91);
  tcase_add_test(tc_core, test_div92);
  tcase_add_test(tc_core, test_div93);
  tcase_add_test(tc_core, test_div94);
  tcase_add_test(tc_core, test_div95);
  tcase_add_test(tc_core, test_div96);
  tcase_add_test(tc_core, test_div97);
  tcase_add_test(tc_core, test_div98);
  tcase_add_test(tc_core, test_div99);
  tcase_add_test(tc_core, test_div100);

  tcase_add_test(tc_core, test_mul2001);
  tcase_add_test(tc_core, test_mul2002);
  tcase_add_test(tc_core, test_mul2003);
  tcase_add_test(tc_core, test_mul2004);
  tcase_add_test(tc_core, test_mul2005);
  tcase_add_test(tc_core, test_mul2006);
  tcase_add_test(tc_core, test_mul2007);
  tcase_add_test(tc_core, test_mul2008);
  tcase_add_test(tc_core, test_mul2009);
  tcase_add_test(tc_core, test_mul2010);
  tcase_add_test(tc_core, test_mul2011);
  tcase_add_test(tc_core, test_mul2012);
  tcase_add_test(tc_core, test_mul2013);
  tcase_add_test(tc_core, test_mul2014);
  tcase_add_test(tc_core, test_mul2015);
  tcase_add_test(tc_core, test_mul2016);
  tcase_add_test(tc_core, test_mul2017);
  tcase_add_test(tc_core, test_mul2018);
  tcase_add_test(tc_core, test_mul2019);
  tcase_add_test(tc_core, test_mul2020);
  tcase_add_test(tc_core, test_mul2021);
  tcase_add_test(tc_core, test_mul2022);
  tcase_add_test(tc_core, test_mul2023);
  tcase_add_test(tc_core, test_mul2024);
  tcase_add_test(tc_core, test_mul2025);
  tcase_add_test(tc_core, test_mul2026);
  tcase_add_test(tc_core, test_mul2027);
  tcase_add_test(tc_core, test_mul2028);
  tcase_add_test(tc_core, test_mul2029);
  tcase_add_test(tc_core, test_mul2030);
  tcase_add_test(tc_core, test_mul2031);
  tcase_add_test(tc_core, test_mul2032);
  tcase_add_test(tc_core, test_mul2033);
  tcase_add_test(tc_core, test_mul2034);
  tcase_add_test(tc_core, test_mul2035);
  tcase_add_test(tc_core, test_mul2036);
  tcase_add_test(tc_core, test_mul2037);
  tcase_add_test(tc_core, test_mul2038);
  tcase_add_test(tc_core, test_mul2039);
  tcase_add_test(tc_core, test_mul2040);
  tcase_add_test(tc_core, test_mul2041);
  tcase_add_test(tc_core, test_mul2042);
  tcase_add_test(tc_core, test_mul2043);
  tcase_add_test(tc_core, test_mul2044);
  tcase_add_test(tc_core, test_mul2045);
  tcase_add_test(tc_core, test_mul2046);
  tcase_add_test(tc_core, test_mul2047);
  tcase_add_test(tc_core, test_mul2048);
  tcase_add_test(tc_core, test_mul2049);
  tcase_add_test(tc_core, test_mul2050);
  tcase_add_test(tc_core, test_mul2051);
  tcase_add_test(tc_core, test_mul2052);
  tcase_add_test(tc_core, test_mul2053);
  tcase_add_test(tc_core, test_mul2054);
  tcase_add_test(tc_core, test_mul2055);
  tcase_add_test(tc_core, test_mul2056);
  tcase_add_test(tc_core, test_mul2057);
  tcase_add_test(tc_core, test_mul2058);
  tcase_add_test(tc_core, test_mul2059);
  tcase_add_test(tc_core, test_mul2060);
  tcase_add_test(tc_core, test_mul2061);
  tcase_add_test(tc_core, test_mul2062);
  tcase_add_test(tc_core, test_mul2063);
  tcase_add_test(tc_core, test_mul2064);
  tcase_add_test(tc_core, test_mul2065);
  tcase_add_test(tc_core, test_mul2066);
  tcase_add_test(tc_core, test_mul2067);
  tcase_add_test(tc_core, test_mul2068);
  tcase_add_test(tc_core, test_mul2069);
  tcase_add_test(tc_core, test_mul2070);
  tcase_add_test(tc_core, test_mul2071);
  tcase_add_test(tc_core, test_mul2072);
  tcase_add_test(tc_core, test_mul2073);
  tcase_add_test(tc_core, test_mul2074);
  tcase_add_test(tc_core, test_mul2075);
  tcase_add_test(tc_core, test_mul2076);
  tcase_add_test(tc_core, test_mul2077);
  tcase_add_test(tc_core, test_mul2078);
  tcase_add_test(tc_core, test_mul2079);
  tcase_add_test(tc_core, test_mul2080);
  tcase_add_test(tc_core, test_mul2081);
  tcase_add_test(tc_core, test_mul2082);
  tcase_add_test(tc_core, test_mul2083);
  tcase_add_test(tc_core, test_mul2084);
  tcase_add_test(tc_core, test_mul2085);
  tcase_add_test(tc_core, test_mul2086);
  tcase_add_test(tc_core, test_mul2087);
  tcase_add_test(tc_core, test_mul2088);
  tcase_add_test(tc_core, test_mul2089);
  tcase_add_test(tc_core, test_mul2090);
  tcase_add_test(tc_core, test_mul2091);
  tcase_add_test(tc_core, test_mul2092);
  tcase_add_test(tc_core, test_mul2093);
  tcase_add_test(tc_core, test_mul2094);
  tcase_add_test(tc_core, test_mul2095);
  tcase_add_test(tc_core, test_mul2096);
  /* tcase_add_test(tc_core, test_mul2097); */
  /* tcase_add_test(tc_core, test_mul2098); */
  tcase_add_test(tc_core, test_mul2099);
  tcase_add_test(tc_core, test_mul2100);

  tcase_add_test(tc_core, test_mul1000);
  tcase_add_test(tc_core, test_mul1001);
  tcase_add_test(tc_core, test_mul1002);
  tcase_add_test(tc_core, test_mul1003);
  tcase_add_test(tc_core, test_mul1004);
  tcase_add_test(tc_core, test_mul1005);
  tcase_add_test(tc_core, test_mul1006);
  tcase_add_test(tc_core, test_mul1007);
  tcase_add_test(tc_core, test_mul1008);
  tcase_add_test(tc_core, test_mul1009);
  tcase_add_test(tc_core, test_mul1010);
  tcase_add_test(tc_core, test_mul1011);
  tcase_add_test(tc_core, test_mul1012);
  tcase_add_test(tc_core, test_mul1013);
  tcase_add_test(tc_core, test_mul1014);
  tcase_add_test(tc_core, test_mul1015);
  tcase_add_test(tc_core, test_mul1016);
  tcase_add_test(tc_core, test_mul1017);
  tcase_add_test(tc_core, test_mul1018);
  tcase_add_test(tc_core, test_mul1019);
  tcase_add_test(tc_core, test_mul1020);
  tcase_add_test(tc_core, test_mul1021);
  tcase_add_test(tc_core, test_mul1022);
  tcase_add_test(tc_core, test_mul1023);
  tcase_add_test(tc_core, test_mul1024);
  tcase_add_test(tc_core, test_mul1025);
  tcase_add_test(tc_core, test_mul1026);
  tcase_add_test(tc_core, test_mul1027);
  tcase_add_test(tc_core, test_mul1028);
  tcase_add_test(tc_core, test_mul1029);
  tcase_add_test(tc_core, test_mul1030);
  tcase_add_test(tc_core, test_mul1031);
  tcase_add_test(tc_core, test_mul1032);
  tcase_add_test(tc_core, test_mul1033);
  tcase_add_test(tc_core, test_mul1034);
  tcase_add_test(tc_core, test_mul1035);
  tcase_add_test(tc_core, test_mul1036);
  tcase_add_test(tc_core, test_mul1037);
  tcase_add_test(tc_core, test_mul1038);
  tcase_add_test(tc_core, test_mul1039);
  tcase_add_test(tc_core, test_mul1040);
  tcase_add_test(tc_core, test_mul1041);
  tcase_add_test(tc_core, test_mul1042);
  tcase_add_test(tc_core, test_mul1043);
  tcase_add_test(tc_core, test_mul1044);
  tcase_add_test(tc_core, test_mul1045);
  tcase_add_test(tc_core, test_mul1046);
  tcase_add_test(tc_core, test_mul1047);
  tcase_add_test(tc_core, test_mul1048);
  tcase_add_test(tc_core, test_mul1049);
  tcase_add_test(tc_core, test_mul1050);
  tcase_add_test(tc_core, test_mul1051);
  tcase_add_test(tc_core, test_mul1052);
  tcase_add_test(tc_core, test_mul1053);
  tcase_add_test(tc_core, test_mul1054);
  tcase_add_test(tc_core, test_mul1055);
  tcase_add_test(tc_core, test_mul1056);
  tcase_add_test(tc_core, test_mul1057);
  tcase_add_test(tc_core, test_mul1058);
  tcase_add_test(tc_core, test_mul1059);
  tcase_add_test(tc_core, test_mul1060);
  tcase_add_test(tc_core, test_mul1061);
  tcase_add_test(tc_core, test_mul1062);
  tcase_add_test(tc_core, test_mul1063);
  tcase_add_test(tc_core, test_mul1064);
  tcase_add_test(tc_core, test_mul1065);
  tcase_add_test(tc_core, test_mul1066);
  tcase_add_test(tc_core, test_mul1067);
  tcase_add_test(tc_core, test_mul1068);
  tcase_add_test(tc_core, test_mul1069);
  tcase_add_test(tc_core, test_mul1070);
  tcase_add_test(tc_core, test_mul1071);
  tcase_add_test(tc_core, test_mul1072);
  tcase_add_test(tc_core, test_mul1073);
  tcase_add_test(tc_core, test_mul1074);
  tcase_add_test(tc_core, test_mul1075);
  tcase_add_test(tc_core, test_mul1076);
  tcase_add_test(tc_core, test_mul1077);
  tcase_add_test(tc_core, test_mul1078);
  tcase_add_test(tc_core, test_mul1079);
  tcase_add_test(tc_core, test_mul1080);
  tcase_add_test(tc_core, test_mul1081);
  tcase_add_test(tc_core, test_mul1082);
  tcase_add_test(tc_core, test_mul1083);
  tcase_add_test(tc_core, test_mul1084);
  tcase_add_test(tc_core, test_mul1085);
  tcase_add_test(tc_core, test_mul1086);
  tcase_add_test(tc_core, test_mul1087);
  tcase_add_test(tc_core, test_mul1088);
  tcase_add_test(tc_core, test_mul1089);
  tcase_add_test(tc_core, test_mul1090);
  tcase_add_test(tc_core, test_mul1091);
  tcase_add_test(tc_core, test_mul1092);
  tcase_add_test(tc_core, test_mul1093);
  tcase_add_test(tc_core, test_mul1094);
  tcase_add_test(tc_core, test_mul1095);
  tcase_add_test(tc_core, test_mul1096);
  tcase_add_test(tc_core, test_mul1097);
  tcase_add_test(tc_core, test_mul1098);
  tcase_add_test(tc_core, test_mul1099);
  tcase_add_test(tc_core, test_mul1100);

  tcase_add_test(tc_core, test_mul1);
  tcase_add_test(tc_core, test_mul2);
  tcase_add_test(tc_core, test_mul3);
  tcase_add_test(tc_core, test_mul4);
  tcase_add_test(tc_core, test_mul5);
  tcase_add_test(tc_core, test_mul6);
  tcase_add_test(tc_core, test_mul7);
  tcase_add_test(tc_core, test_mul8);
  tcase_add_test(tc_core, test_mul9);
  tcase_add_test(tc_core, test_mul10);
  tcase_add_test(tc_core, test_mul11);
  tcase_add_test(tc_core, test_mul12);
  tcase_add_test(tc_core, test_mul13);
  tcase_add_test(tc_core, test_mul14);
  tcase_add_test(tc_core, test_mul15);
  tcase_add_test(tc_core, test_mul16);
  tcase_add_test(tc_core, test_mul17);
  tcase_add_test(tc_core, test_mul18);
  tcase_add_test(tc_core, test_mul19);
  tcase_add_test(tc_core, test_mul20);
  tcase_add_test(tc_core, test_mul21);
  tcase_add_test(tc_core, test_mul22);
  tcase_add_test(tc_core, test_mul23);
  tcase_add_test(tc_core, test_mul24);
  tcase_add_test(tc_core, test_mul25);
  tcase_add_test(tc_core, test_mul26);
  tcase_add_test(tc_core, test_mul27);
  tcase_add_test(tc_core, test_mul28);
  tcase_add_test(tc_core, test_mul29);
  tcase_add_test(tc_core, test_mul30);
  tcase_add_test(tc_core, test_mul31);
  tcase_add_test(tc_core, test_mul32);
  tcase_add_test(tc_core, test_mul33);
  tcase_add_test(tc_core, test_mul34);
  tcase_add_test(tc_core, test_mul35);
  tcase_add_test(tc_core, test_mul36);
  tcase_add_test(tc_core, test_mul37);
  tcase_add_test(tc_core, test_mul38);
  tcase_add_test(tc_core, test_mul39);
  tcase_add_test(tc_core, test_mul40);
  tcase_add_test(tc_core, test_mul41);
  tcase_add_test(tc_core, test_mul42);
  tcase_add_test(tc_core, test_mul43);
  tcase_add_test(tc_core, test_mul44);
  tcase_add_test(tc_core, test_mul45);
  tcase_add_test(tc_core, test_mul46);
  tcase_add_test(tc_core, test_mul47);
  tcase_add_test(tc_core, test_mul48);
  tcase_add_test(tc_core, test_mul49);
  tcase_add_test(tc_core, test_mul50);
  tcase_add_test(tc_core, test_mul51);
  tcase_add_test(tc_core, test_mul52);
  tcase_add_test(tc_core, test_mul53);
  tcase_add_test(tc_core, test_mul54);
  tcase_add_test(tc_core, test_mul55);
  tcase_add_test(tc_core, test_mul56);
  tcase_add_test(tc_core, test_mul57);
  tcase_add_test(tc_core, test_mul58);
  tcase_add_test(tc_core, test_mul59);
  tcase_add_test(tc_core, test_mul60);
  tcase_add_test(tc_core, test_mul61);
  tcase_add_test(tc_core, test_mul62);
  tcase_add_test(tc_core, test_mul63);
  tcase_add_test(tc_core, test_mul64);
  tcase_add_test(tc_core, test_mul65);
  tcase_add_test(tc_core, test_mul66);
  tcase_add_test(tc_core, test_mul67);
  tcase_add_test(tc_core, test_mul68);
  tcase_add_test(tc_core, test_mul69);
  tcase_add_test(tc_core, test_mul70);
  tcase_add_test(tc_core, test_mul71);
  tcase_add_test(tc_core, test_mul72);
  tcase_add_test(tc_core, test_mul73);
  tcase_add_test(tc_core, test_mul74);
  tcase_add_test(tc_core, test_mul75);
  tcase_add_test(tc_core, test_mul76);
  tcase_add_test(tc_core, test_mul77);
  tcase_add_test(tc_core, test_mul78);
  tcase_add_test(tc_core, test_mul79);
  tcase_add_test(tc_core, test_mul80);
  tcase_add_test(tc_core, test_mul81);
  tcase_add_test(tc_core, test_mul82);
  tcase_add_test(tc_core, test_mul83);
  tcase_add_test(tc_core, test_mul84);
  tcase_add_test(tc_core, test_mul85);
  tcase_add_test(tc_core, test_mul86);
  tcase_add_test(tc_core, test_mul87);
  tcase_add_test(tc_core, test_mul88);
  tcase_add_test(tc_core, test_mul89);
  tcase_add_test(tc_core, test_mul90);
  tcase_add_test(tc_core, test_mul91);
  tcase_add_test(tc_core, test_mul92);
  tcase_add_test(tc_core, test_mul93);
  tcase_add_test(tc_core, test_mul94);
  tcase_add_test(tc_core, test_mul95);
  tcase_add_test(tc_core, test_mul96);
  tcase_add_test(tc_core, test_mul97);
  tcase_add_test(tc_core, test_mul98);
  tcase_add_test(tc_core, test_mul99);
  tcase_add_test(tc_core, test_mul100);

  suite_add_tcase(s1, tc);
  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc1_1, test_round_ok1);
  tcase_add_test(tc_core, test_round_ok1);
  tcase_add_test(tc_core, test_round_ok2);
  /* tcase_add_test(tc_core, test_round_ok3); */
  /* tcase_add_test(tc_core, test_round_ok4); */
  tcase_add_test(tc_core, test_round_ok5);
  tcase_add_test(tc_core, test_round_ok6);
  tcase_add_test(tc_core, test_round_ok7);
  tcase_add_test(tc_core, test_round_ok8);
  tcase_add_test(tc_core, test_round_ok9);
  tcase_add_test(tc_core, test_round_ok10);
  tcase_add_test(tc_core, test_round_ok11);
  /* tcase_add_test(tc_core, test_round_ok12); */
  /* tcase_add_test(tc_core, test_round_ok13); */
  /* tcase_add_test(tc_core, test_round_ok14); */
  tcase_add_test(tc_core, test_round_ok15);
  tcase_add_test(tc_core, test_round_ok16);
  tcase_add_test(tc_core, test_round_ok17);
  tcase_add_test(tc_core, test_round_ok18);
  tcase_add_test(tc_core, test_round_ok19);
  /* tcase_add_test(tc_core, test_round_ok20); */
  tcase_add_test(tc_core, test_round_ok21);
  tcase_add_test(tc_core, test_round_ok22);
  tcase_add_test(tc_core, test_round_ok23);
  tcase_add_test(tc_core, test_round_ok24);
  tcase_add_test(tc_core, test_round_ok25);
  tcase_add_test(tc_core, test_round_ok26);
  tcase_add_test(tc_core, test_round_ok27);
  tcase_add_test(tc_core, test_round_ok28);
  tcase_add_test(tc_core, test_round_ok29);
  tcase_add_test(tc_core, test_round_ok30);
  tcase_add_test(tc_core, test_round_ok31);
  tcase_add_test(tc_core, test_round_ok32);
  tcase_add_test(tc_core, test_round_ok33);
  tcase_add_test(tc_core, test_round_ok34);
  tcase_add_test(tc_core, test_round_ok35);
  tcase_add_test(tc_core, test_round_ok36);
  tcase_add_test(tc_core, test_round_ok37);
  tcase_add_test(tc_core, test_round_ok38);
  tcase_add_test(tc_core, test_round_ok39);
  tcase_add_test(tc_core, test_round_ok40);
  tcase_add_test(tc_core, test_round_ok41);
  tcase_add_test(tc_core, test_round_ok42);
  /* tcase_add_test(tc_core, test_round_ok43); */
  /* tcase_add_test(tc_core, test_round_ok44); */
  tcase_add_test(tc_core, test_round_ok45);
  tcase_add_test(tc_core, test_round_ok46);
  tcase_add_test(tc_core, test_round_ok47);
  tcase_add_test(tc_core, test_round_ok48);
  tcase_add_test(tc_core, test_round_ok49);
  tcase_add_test(tc_core, test_round_ok50);
  tcase_add_test(tc_core, test_round_ok51);
  tcase_add_test(tc_core, test_round_ok52);
  tcase_add_test(tc_core, test_round_ok53);
  tcase_add_test(tc_core, test_round_ok54);
  tcase_add_test(tc_core, test_round_ok55);
  tcase_add_test(tc_core, test_round_ok56);
  tcase_add_test(tc_core, test_round_ok57);
  tcase_add_test(tc_core, test_round_ok58);
  tcase_add_test(tc_core, test_round_ok59);
  tcase_add_test(tc_core, test_round_ok60);
  tcase_add_test(tc_core, test_round_ok61);
  tcase_add_test(tc_core, test_round_ok62);
  tcase_add_test(tc_core, test_round_ok63);
  tcase_add_test(tc_core, test_round_ok64);
  tcase_add_test(tc_core, test_round_ok65);
  tcase_add_test(tc_core, test_round_ok66);
  tcase_add_test(tc_core, test_round_ok67);
  tcase_add_test(tc_core, test_round_ok68);
  tcase_add_test(tc_core, test_round_ok69);
  /* tcase_add_test(tc_core, test_round_ok70); */
  /* tcase_add_test(tc_core, test_round_ok71); */
  /* tcase_add_test(tc_core, test_round_ok72); */
  tcase_add_test(tc_core, test_round_ok73);
  tcase_add_test(tc_core, test_round_ok74);
  tcase_add_test(tc_core, test_round_ok75);
  tcase_add_test(tc_core, test_round_ok76);
  tcase_add_test(tc_core, test_round_ok77);
  /* tcase_add_test(tc_core, test_round_ok78); */
  tcase_add_test(tc_core, test_round_ok79);
  tcase_add_test(tc_core, test_round_ok80);
  tcase_add_test(tc_core, test_round_ok81);
  tcase_add_test(tc_core, test_round_ok82);
  tcase_add_test(tc_core, test_round_ok83);
  tcase_add_test(tc_core, test_round_ok84);
  tcase_add_test(tc_core, test_round_ok85);
  tcase_add_test(tc_core, test_round_ok86);
  tcase_add_test(tc_core, test_round_ok87);
  tcase_add_test(tc_core, test_round_ok88);
  tcase_add_test(tc_core, test_round_ok89);
  tcase_add_test(tc_core, test_round_ok90);
  tcase_add_test(tc_core, test_round_ok91);
  tcase_add_test(tc_core, test_round_ok92);
  tcase_add_test(tc_core, test_round_ok93);
  tcase_add_test(tc_core, test_round_ok94);
  tcase_add_test(tc_core, test_round_ok95);
  tcase_add_test(tc_core, test_round_ok96);
  tcase_add_test(tc_core, test_round_ok97);
  tcase_add_test(tc_core, test_round_ok98);
  tcase_add_test(tc_core, test_round_ok99);
  tcase_add_test(tc_core, test_round_ok100);
  // tests_add
  tcase_add_test(tc1_1, test_s21_add_1);
  tcase_add_test(tc1_1, test_s21_add_2);
  tcase_add_test(tc1_1, test_s21_add_3);
  tcase_add_test(tc1_1, test_s21_add_4);
  tcase_add_test(tc1_1, test_s21_add_5);
  tcase_add_test(tc1_1, test_s21_add_6);
  tcase_add_test(tc1_1, test_s21_add_7);
  tcase_add_test(tc1_1, test_s21_add_9);
  tcase_add_test(tc1_1, test_s21_add_11);
  tcase_add_test(tc1_1, test_s21_add_12);
  tcase_add_test(tc1_1, test_s21_add_13);
  tcase_add_test(tc1_1, test_s21_add_14);
  tcase_add_test(tc1_1, test_s21_add_15);
  tcase_add_test(tc1_1, test_s21_add_16);
  tcase_add_test(tc1_1, test_s21_add_17);
  tcase_add_test(tc1_1, test_s21_add_18);
  tcase_add_test(tc1_1, test_s21_add_19);
  tcase_add_test(tc1_1, test_s21_add_20);
  tcase_add_test(tc1_1, test_s21_add_21);
  tcase_add_test(tc1_1, test_s21_add_22);
  tcase_add_test(tc1_1, test_s21_add_23);
  tcase_add_test(tc1_1, test_s21_add_24);
  tcase_add_test(tc1_1, test_s21_add_25);
  tcase_add_test(tc1_1, test_s21_add_26);

  tcase_add_test(tc1_1, add_1);
  tcase_add_test(tc1_1, add_2);
  tcase_add_test(tc1_1, add_3);
  tcase_add_test(tc1_1, add_4);
  tcase_add_test(tc1_1, add_5);
  tcase_add_test(tc1_1, add_6);
  tcase_add_test(tc1_1, add_7);
  tcase_add_test(tc1_1, add_8);
  tcase_add_test(tc1_1, add_9);
  tcase_add_test(tc1_1, add_10);
  tcase_add_test(tc1_1, add_11);
  tcase_add_test(tc1_1, add_12);

  /*    /1* // tests_sub *1/ */
  tcase_add_test(tc1_1, test_s21_sub_1);
  tcase_add_test(tc1_1, test_s21_sub_2);
  tcase_add_test(tc1_1, test_s21_sub_3);
  tcase_add_test(tc1_1, test_s21_sub_4);
  tcase_add_test(tc1_1, test_s21_sub_5);
  tcase_add_test(tc1_1, test_s21_sub_6);
  tcase_add_test(tc1_1, test_s21_sub_7);
  tcase_add_test(tc1_1, test_s21_sub_8);
  tcase_add_test(tc1_1, test_s21_sub_9);
  tcase_add_test(tc1_1, test_s21_sub_10);

  tcase_add_test(tc1_1, sub_1);
  tcase_add_test(tc1_1, sub_2);
  tcase_add_test(tc1_1, sub_3);
  tcase_add_test(tc1_1, sub_4);
  tcase_add_test(tc1_1, sub_5);
  tcase_add_test(tc1_1, sub_6);
  tcase_add_test(tc1_1, sub_7);
  tcase_add_test(tc1_1, sub_8);
  tcase_add_test(tc1_1, sub_9);
  tcase_add_test(tc1_1, sub_10);
  tcase_add_test(tc1_1, sub_11);
  tcase_add_test(tc1_1, sub_12);

  /* //thalassa tests */
  tcase_add_test(tc, sub_test_1);
  tcase_add_test(tc, sub_test_2);
  tcase_add_test(tc, sub_test_3);
  tcase_add_test(tc, sub_test_4);
  tcase_add_test(tc, sub_test_5);
  tcase_add_test(tc, sub_test_6);
  tcase_add_test(tc, sub_test_7);
  tcase_add_test(tc, sub_test_8);
  tcase_add_test(tc, sub_test_9);
  tcase_add_test(tc, sub_test_10);
  tcase_add_test(tc, sub_test_11);
  tcase_add_test(tc, sub_test_12);
  tcase_add_test(tc, sub_test_13);
  tcase_add_test(tc, sub_test_14);
  tcase_add_test(tc, sub_test_15);
  tcase_add_test(tc, sub_test_16);
  tcase_add_test(tc, sub_test_17);
  tcase_add_test(tc, sub_test_18);
  tcase_add_test(tc, sub_test_19);
  tcase_add_test(tc, sub_test_20);
  tcase_add_test(tc, sub_test_21);
  tcase_add_test(tc, s21_subTest1);
  tcase_add_test(tc, s21_subTest2);
  tcase_add_test(tc, s21_subTest3);
  tcase_add_test(tc, s21_subTest4);
  tcase_add_test(tc, s21_subTest5);
  tcase_add_test(tc, s21_subTest6);
  tcase_add_test(tc, s21_subTest7);
  tcase_add_test(tc, s21_subTest8);
  tcase_add_test(tc, s21_subTest9);
  tcase_add_test(tc, s21_subTest10);
  tcase_add_test(tc, s21_subTest11);
  tcase_add_test(tc, s21_subTest12);
  tcase_add_test(tc, s21_subTest13);
  tcase_add_test(tc, s21_subTest14);
  tcase_add_test(tc, s21_subTest15);
  tcase_add_test(tc, s21_subTest16);
  tcase_add_test(tc, s21_subTest17);
  tcase_add_test(tc, s21_subTest18);
  tcase_add_test(tc, s21_subTest19);
  tcase_add_test(tc, s21_subTest20);
  tcase_add_test(tc, s21_subTest21);
  tcase_add_test(tc, s21_subTest22);
  tcase_add_test(tc, s21_subTest23);
  tcase_add_test(tc, s21_subTest24);
  tcase_add_test(tc, s21_subTest25);
  tcase_add_test(tc, s21_subTest26);
  tcase_add_test(tc, s21_subTest27);
  tcase_add_test(tc, s21_subTest28);
  tcase_add_test(tc, s21_subTest29);
  tcase_add_test(tc, s21_subTest30);
  tcase_add_test(tc, s21_subTest31);
  tcase_add_test(tc, s21_subTest32);
  tcase_add_test(tc, s21_subTest33);
  tcase_add_test(tc, s21_test_decimal_sub_simple_0);
  tcase_add_test(tc, s21_test_decimal_sub_simple_1);
  tcase_add_test(tc, s21_test_decimal_sub_simple_2);
  tcase_add_test(tc, s21_test_decimal_sub_simple_3);
  tcase_add_test(tc, s21_test_decimal_sub_simple_7);
  tcase_add_test(tc, s21_test_decimal_sub_simple_8);
  tcase_add_test(tc, s21_test_decimal_sub_simple_10);
  tcase_add_test(tc, s21_test_decimal_sub_simple_11);
  tcase_add_test(tc, s21_sub_int_22);
  tcase_add_test(tc, s21_sub_int_23);
  tcase_add_test(tc, s21_sub_int_24);
  tcase_add_test(tc, s21_sub_int_25);
  tcase_add_test(tc, s21_sub_int_26);
  tcase_add_test(tc, s21_sub_inf_27);
  tcase_add_test(tc, s21_sub_neg_inf_28);
  tcase_add_test(tc, s21_sub_max_30);
  tcase_add_test(tc, s21_sub_max_31);
  tcase_add_test(tc, s21_sub_max_32);
  tcase_add_test(tc, s21_sub_max_33);
  tcase_add_test(tc, s21_sub_max_34);
  tcase_add_test(tc, s21_sub_max_35);
  // tests_mul
  tcase_add_test(tc1_1, test_s21_mul_1);
  tcase_add_test(tc1_1, test_s21_mul_2);
  tcase_add_test(tc1_1, test_s21_mul_3);
  tcase_add_test(tc1_1, test_s21_mul_4);
  tcase_add_test(tc1_1, test_s21_mul_5);
  tcase_add_test(tc1_1, test_s21_mul_6);
  tcase_add_test(tc1_1, test_s21_mul_7);
  tcase_add_test(tc1_1, test_s21_mul_8);
  /* tcase_add_test(tc1_1, test_s21_mul_9); */
  tcase_add_test(tc1_1, test_s21_mul_10);

  /* tests_mul */
  tcase_add_test(tc1_1, test_s21_div_1);
  tcase_add_test(tc1_1, test_s21_div_2);
  tcase_add_test(tc1_1, test_s21_div_3);
  tcase_add_test(tc1_1, test_s21_div_4);
  tcase_add_test(tc1_1, test_s21_div_5);

  tcase_add_test(tc1_1, div_1);
  tcase_add_test(tc1_1, div_2);
  tcase_add_test(tc1_1, div_3);
  tcase_add_test(tc1_1, div_4);
  tcase_add_test(tc1_1, div_5);
  tcase_add_test(tc1_1, div_6);
  tcase_add_test(tc1_1, div_7);
  tcase_add_test(tc1_1, div_8);
  tcase_add_test(tc1_1, div_9);
  tcase_add_test(tc1_1, div_10);
  tcase_add_test(tc1_1, div_11);
  tcase_add_test(tc1_1, div_12);
  tcase_add_test(tc1_1, div_13);
  tcase_add_test(tc1_1, div_14);
  tcase_add_test(tc1_1, div_15);

  // // tests_mod
  tcase_add_test(tc1_1, test_s21_mod_1);
  tcase_add_test(tc1_1, test_s21_mod_2);
  tcase_add_test(tc1_1, test_s21_mod_3);
  tcase_add_test(tc1_1, test_s21_mod_4);

  // test_compare from Decimal_pistoletiki_testiki
  tcase_add_test(tc1_1, compare_01);
  tcase_add_test(tc1_1, compare_02);
  tcase_add_test(tc1_1, compare_03);
  tcase_add_test(tc1_1, compare_04);
  tcase_add_test(tc1_1, compare_05);
  tcase_add_test(tc1_1, compare_06);
  tcase_add_test(tc1_1, compare_07);
  tcase_add_test(tc1_1, compare_08);
  tcase_add_test(tc1_1, compare_09);
  tcase_add_test(tc1_1, compare_10);
  tcase_add_test(tc1_1, compare_11);
  tcase_add_test(tc1_1, compare_12);
  tcase_add_test(tc1_1, compare_13);
  tcase_add_test(tc1_1, compare_14);
  tcase_add_test(tc1_1, compare_15);
  tcase_add_test(tc1_1, compare_16);
  tcase_add_test(tc1_1, compare_17);

  // tests_is_less
  tcase_add_test(tc1_1, test_s21_is_less_1);
  tcase_add_test(tc1_1, test_s21_is_less_2);
  tcase_add_test(tc1_1, test_s21_is_less_3);
  tcase_add_test(tc1_1, test_s21_is_less_4);
  tcase_add_test(tc1_1, test_s21_is_less_5);
  tcase_add_test(tc1_1, test_s21_is_less_6);
  tcase_add_test(tc1_1, test_s21_is_less_7);
  tcase_add_test(tc1_1, test_s21_is_less_8);

  // tests_is_less_or_equal
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_1);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_2);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_3);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_4);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_5);

  // tests_is_greater
  tcase_add_test(tc1_1, test_s21_is_greater_1);
  tcase_add_test(tc1_1, test_s21_is_greater_2);
  tcase_add_test(tc1_1, test_s21_is_greater_3);
  tcase_add_test(tc1_1, test_s21_is_greater_4);

  // tests_is_greater_or_equal
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_1);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_2);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_3);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_4);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_5);

  // tests_is_equal
  tcase_add_test(tc1_1, test_s21_is_equal_1);
  tcase_add_test(tc1_1, test_s21_is_equal_2);
  tcase_add_test(tc1_1, test_s21_is_equal_3);
  tcase_add_test(tc1_1, test_s21_is_equal_4);
  tcase_add_test(tc1_1, test_s21_is_equal_5);

  // tests_is_not_equal
  tcase_add_test(tc1_1, test_s21_is_not_equal_1);
  tcase_add_test(tc1_1, test_s21_is_not_equal_2);
  tcase_add_test(tc1_1, test_s21_is_not_equal_3);
  tcase_add_test(tc1_1, test_s21_is_not_equal_4);
  tcase_add_test(tc1_1, test_s21_is_not_equal_5);

  // Thalassa tests

  tcase_add_test(tc, equal_1);
  tcase_add_test(tc, equal_2);
  tcase_add_test(tc, equal_3);
  tcase_add_test(tc, equal_4);
  tcase_add_test(tc, equal_5);
  tcase_add_test(tc, equal_6);
  tcase_add_test(tc, equal_7);
  tcase_add_test(tc, equal_8);
  tcase_add_test(tc, equal_9);
  tcase_add_test(tc, equal_10);
  tcase_add_test(tc, s21_equal_null_12);
  tcase_add_test(tc, s21_is_equalTest1);
  tcase_add_test(tc, s21_is_equalTest2);
  tcase_add_test(tc, s21_is_equalTest3);
  tcase_add_test(tc, s21_is_equalTest4);
  tcase_add_test(tc, s21_is_equalTest5);
  tcase_add_test(tc, s21_is_equalTest6);
  tcase_add_test(tc, s21_is_equalTest7);
  tcase_add_test(tc, s21_is_equalTest8);
  tcase_add_test(tc, s21_is_equalTest9);
  tcase_add_test(tc, s21_is_equalTest10);
  tcase_add_test(tc, s21_is_equalTest11);
  tcase_add_test(tc, s21_is_equalTest12);
  tcase_add_test(tc, s21_is_equalTest13);
  tcase_add_test(tc, s21_is_equalTest14);
  tcase_add_test(tc, s21_is_equalTest15);
  tcase_add_test(tc, s21_is_equalTest16);
  tcase_add_test(tc, s21_is_equalTest17);
  tcase_add_test(tc, s21_is_equalTest18);
  tcase_add_test(tc, s21_is_equalTest19);
  tcase_add_test(tc, s21_is_equalTest20);
  tcase_add_test(tc, s21_is_equalTest21);
  tcase_add_test(tc, s21_is_equalTest22);
  tcase_add_test(tc, s21_is_equalTest23);
  tcase_add_test(tc, s21_is_equalTest24);
  tcase_add_test(tc, s21_is_equalTest25);
  tcase_add_test(tc, s21_is_equalTest26);
  tcase_add_test(tc, s21_is_equalTest27);
  tcase_add_test(tc, s21_is_equalTest28);
  tcase_add_test(tc, s21_is_equalTest29);
  tcase_add_test(tc, s21_is_equalTest30);
  tcase_add_test(tc, s21_is_equalTest31);
  tcase_add_test(tc, s21_is_equalTest32);
  tcase_add_test(tc, s21_is_equalTest33);
  tcase_add_test(tc, s21_is_equalTest34);
  tcase_add_test(tc, s21_is_equalTest35);
  tcase_add_test(tc, s21_is_equalTest36);
  // not equal
  tcase_add_test(tc, not_equal_1);
  tcase_add_test(tc, not_equal_2);
  tcase_add_test(tc, not_equal_3);
  tcase_add_test(tc, not_equal_4);
  tcase_add_test(tc, not_equal_5);
  tcase_add_test(tc, not_equal_6);
  tcase_add_test(tc, s21_not_equal_7);
  // // less

  tcase_add_test(tc, less_1);
  tcase_add_test(tc, less_2);
  tcase_add_test(tc, less_3);
  tcase_add_test(tc, less_4);
  tcase_add_test(tc, less_5);
  tcase_add_test(tc, less_6);
  tcase_add_test(tc, less_7);
  tcase_add_test(tc, s21_less_8);

  // less or equal

  tcase_add_test(tc, less_or_equal_1);
  tcase_add_test(tc, less_or_equal_2);
  tcase_add_test(tc, less_or_equal_3);
  tcase_add_test(tc, less_or_equal_4);
  tcase_add_test(tc, less_or_equal_5);
  tcase_add_test(tc, less_or_equal_6);
  tcase_add_test(tc, less_or_equal_7);
  tcase_add_test(tc, less_or_equal_8);
  tcase_add_test(tc, less_or_equal_9);
  tcase_add_test(tc, less_or_equal_10);
  tcase_add_test(tc, less_or_equal_11);
  tcase_add_test(tc, less_or_equal_12);
  tcase_add_test(tc, less_or_equal_13);
  tcase_add_test(tc, less_or_equal_14);
  tcase_add_test(tc, less_or_equal_15);
  tcase_add_test(tc, less_or_equal_16);
  tcase_add_test(tc, less_or_equal_17);
  tcase_add_test(tc, less_or_equal_18);
  tcase_add_test(tc, less_or_equal_19);
  tcase_add_test(tc, less_or_equal_20);
  tcase_add_test(tc, less_or_equal_21);
  tcase_add_test(tc, less_or_equal_22);
  tcase_add_test(tc, s21_less_or_equal_23);
  tcase_add_test(tc, s21_test_is_less_or_equal_1);
  tcase_add_test(tc, s21_test_is_less_or_equal_2);
  tcase_add_test(tc, s21_test_is_less_or_equal_2i);
  tcase_add_test(tc, s21_test_is_less_or_equal_3);
  tcase_add_test(tc, s21_test_is_less_or_equal_4);
  tcase_add_test(tc, s21_test_is_less_or_equal_41);
  tcase_add_test(tc, s21_test_is_less_or_equal_5);
  tcase_add_test(tc, s21_test_is_less_or_equal_6);
  tcase_add_test(tc, s21_test_is_less_or_equal_7);
  tcase_add_test(tc, s21_test_is_less_or_equal_8);
  tcase_add_test(tc, s21_test_is_less_or_equal_8);
  tcase_add_test(tc, s21_test_is_less_or_equal_9);
  tcase_add_test(tc, s21_test_is_less_or_equal_10);
  tcase_add_test(tc, s21_is_less_or_equalTest1);
  tcase_add_test(tc, s21_is_less_or_equalTest2);
  tcase_add_test(tc, s21_is_less_or_equalTest3);
  tcase_add_test(tc, s21_is_less_or_equalTest4);
  tcase_add_test(tc, s21_is_less_or_equalTest5);
  tcase_add_test(tc, s21_is_less_or_equalTest6);
  tcase_add_test(tc, s21_is_less_or_equalTest7);
  tcase_add_test(tc, s21_is_less_or_equalTest8);
  tcase_add_test(tc, s21_is_less_or_equalTest9);
  tcase_add_test(tc, s21_is_less_or_equalTest10);
  tcase_add_test(tc, s21_is_less_or_equalTest11);
  tcase_add_test(tc, s21_is_less_or_equalTest12);
  tcase_add_test(tc, s21_is_less_or_equalTest13);
  tcase_add_test(tc, s21_is_less_or_equalTest14);
  tcase_add_test(tc, s21_is_less_or_equalTest15);
  tcase_add_test(tc, s21_is_less_or_equalTest16);
  tcase_add_test(tc, s21_is_less_or_equalTest18);
  tcase_add_test(tc, s21_is_less_or_equalTest19);
  tcase_add_test(tc, s21_is_less_or_equalTest20);
  tcase_add_test(tc, s21_is_less_or_equalTest21);
  tcase_add_test(tc, s21_is_less_or_equalTest22);
  tcase_add_test(tc, s21_is_less_or_equalTest23);
  tcase_add_test(tc, s21_is_less_or_equalTest24);
  tcase_add_test(tc, s21_is_less_or_equalTest25);
  tcase_add_test(tc, s21_is_less_or_equalTest26);
  tcase_add_test(tc, s21_is_less_or_equalTest27);
  tcase_add_test(tc, s21_is_less_or_equalTest28);
  tcase_add_test(tc, s21_is_less_or_equalTest29);
  tcase_add_test(tc, s21_is_less_or_equalTest30);
  tcase_add_test(tc, s21_is_less_or_equalTest31);
  tcase_add_test(tc, s21_is_less_or_equalTest32);
  tcase_add_test(tc, s21_is_less_or_equalTest33);
  tcase_add_test(tc, s21_is_less_or_equalTest34);
  tcase_add_test(tc, s21_is_less_or_equalTest35);
  tcase_add_test(tc, s21_is_less_or_equalTest36);

  // greater

  tcase_add_test(tc, greater_1);
  tcase_add_test(tc, greater_2);
  tcase_add_test(tc, greater_3);
  tcase_add_test(tc, greater_4);
  tcase_add_test(tc, greater_5);
  tcase_add_test(tc, greater_6);
  tcase_add_test(tc, greater_7);
  tcase_add_test(tc, greater_8);
  tcase_add_test(tc, greater_9);
  tcase_add_test(tc, greater_10);
  tcase_add_test(tc, greater_11);
  tcase_add_test(tc, greater_12);
  tcase_add_test(tc, greater_13);
  tcase_add_test(tc, greater_14);
  tcase_add_test(tc, greater_15);
  tcase_add_test(tc, greater_16);
  tcase_add_test(tc, greater_17);
  tcase_add_test(tc, greater_18);
  tcase_add_test(tc, greater_19);
  tcase_add_test(tc, greater_20);
  tcase_add_test(tc, greater_21);
  tcase_add_test(tc, greater_22);
  tcase_add_test(tc, greater_23);
  tcase_add_test(tc, greater_24);
  tcase_add_test(tc, greater_25);
  tcase_add_test(tc, greater_26);
  tcase_add_test(tc, greater_27);
  tcase_add_test(tc, greater_27);
  tcase_add_test(tc, greater_28);
  tcase_add_test(tc, greater_29);
  tcase_add_test(tc, greater_30);
  tcase_add_test(tc, greater_31);
  tcase_add_test(tc, greater_32);
  tcase_add_test(tc, greater_33);
  tcase_add_test(tc, greater_34);
  tcase_add_test(tc, greater_35);
  tcase_add_test(tc, greater_36);
  tcase_add_test(tc, greater_37);
  tcase_add_test(tc, greater_38);
  tcase_add_test(tc, greater_39);
  tcase_add_test(tc, greater_40);
  tcase_add_test(tc, greater_41);
  tcase_add_test(tc, greater_42);
  tcase_add_test(tc, greater_43);
  tcase_add_test(tc, greater_44);
  tcase_add_test(tc, greater_45);
  tcase_add_test(tc, greater_46);
  tcase_add_test(tc, greater_47);
  tcase_add_test(tc, greater_48);
  tcase_add_test(tc, greater_49);
  tcase_add_test(tc, greater_50);
  tcase_add_test(tc, greater_51);
  tcase_add_test(tc, greater_52);
  tcase_add_test(tc, greater_53);
  tcase_add_test(tc, greater_54);
  tcase_add_test(tc, greater_55);
  tcase_add_test(tc, greater_56);
  tcase_add_test(tc, greater_57);
  tcase_add_test(tc, greater_58);
  tcase_add_test(tc, greater_59);
  tcase_add_test(tc, greater_60);

  // greater or equal

  tcase_add_test(tc, greater_or_equal_1);
  tcase_add_test(tc, greater_or_equal_2);
  tcase_add_test(tc, greater_or_equal_3);
  tcase_add_test(tc, greater_or_equal_4);
  tcase_add_test(tc, greater_or_equal_5);
  tcase_add_test(tc, greater_or_equal_6);
  tcase_add_test(tc, greater_or_equal_7);
  tcase_add_test(tc, greater_or_equal_8);
  tcase_add_test(tc, greater_or_equal_9);
  tcase_add_test(tc, greater_or_equal_10);
  tcase_add_test(tc, greater_or_equal_11);
  tcase_add_test(tc, greater_or_equal_12);
  tcase_add_test(tc, greater_or_equal_13);

  // tests_from_int_to_decimal
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal1);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal2);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_3);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_4);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_5);

  // tests_int_to_decimal from Pistoletiki Testiki
  tcase_add_test(tc1_1, int_to_dec_1);
  tcase_add_test(tc1_1, int_to_dec_2);
  tcase_add_test(tc1_1, int_to_dec_3);
  tcase_add_test(tc1_1, int_to_dec_4);
  tcase_add_test(tc1_1, int_to_dec_5);

  // tests_from_float_to_decimal
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal1);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal2);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_3);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_4);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_5);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_6);

  // tests from_float_to_decimal from Pistoletiki Testiki
  tcase_add_test(tc1_1, float_1);
  tcase_add_test(tc1_1, float_2);
  tcase_add_test(tc1_1, float_3);
  tcase_add_test(tc1_1, float_4);
  tcase_add_test(tc1_1, float_5);
  tcase_add_test(tc1_1, float_6);
  tcase_add_test(tc1_1, float_7);
  tcase_add_test(tc1_1, float_8);
  tcase_add_test(tc1_1, float_9);
  tcase_add_test(tc1_1, float_10);
  tcase_add_test(tc1_1, float_11);
  tcase_add_test(tc1_1, float_12);
  tcase_add_test(tc1_1, float_13);
  tcase_add_test(tc1_1, float_14);
  tcase_add_test(tc1_1, float_15);
  tcase_add_test(tc1_1, float_16);
  tcase_add_test(tc1_1, float_17);

  // tests_from_decimal_to_int
  tcase_add_test(tc1_1, test_s21_decimal_to_int_1);
  tcase_add_test(tc1_1, test_s21_decimal_to_int_2);
  tcase_add_test(tc1_1, test_s21_decimal_to_int_3);
  tcase_add_test(tc1_1, test_s21_decimal_to_int_4);

  // tests_from_decimal_to_int from Pistoletiki Testiki
  tcase_add_test(tc1_1, dec_to_int_1);
  tcase_add_test(tc1_1, dec_to_int_2);
  /* tcase_add_test(tc1_1, dec_to_int_3); */
  tcase_add_test(tc1_1, dec_to_int_4);
  tcase_add_test(tc1_1, dec_to_int_5);
  tcase_add_test(tc1_1, dec_to_int_6);
  tcase_add_test(tc1_1, dec_to_int_7);
  tcase_add_test(tc1_1, dec_to_int_8);
  tcase_add_test(tc1_1, dec_to_int_9);

  // tests_from_decimal_to_float
  tcase_add_test(tc1_1, test_s21_decimal_to_float_1);
  tcase_add_test(tc1_1, test_s21_decimal_to_float_2);
  tcase_add_test(tc1_1, test_s21_decimal_to_float_3);
  tcase_add_test(tc1_1, test_s21_decimal_to_float_4);

  //  test_floor
  tcase_add_test(tc1_1, test_s21_floor_1);
  tcase_add_test(tc1_1, test_s21_floor_2);
  tcase_add_test(tc1_1, test_s21_floor_3);
  tcase_add_test(tc1_1, test_s21_floor_4);
  tcase_add_test(tc1_1, test_s21_floor_5);
  tcase_add_test(tc1_1, test_s21_floor_6);
  tcase_add_test(tc1_1, test_s21_floor_7);
  tcase_add_test(tc1_1, test_s21_floor_8);

  // // tests_round
  tcase_add_test(tc1_1, test_s21_round_1);
  tcase_add_test(tc1_1, test_s21_round_2);
  tcase_add_test(tc1_1, test_s21_round_3);
  tcase_add_test(tc1_1, test_s21_round_4);
  tcase_add_test(tc1_1, test_s21_round_5);

  // tests_negate
  tcase_add_test(tc1_1, test_s21_negate_1);
  tcase_add_test(tc1_1, test_s21_negate_2);

  // tests_truncate
  tcase_add_test(tc1_1, test_s21_truncate_1);
  tcase_add_test(tc1_1, test_s21_truncate_2);

  // Thalassa converter
  tcase_add_test(tc, s21_from_decimal_to_int_1);
  tcase_add_test(tc, s21_from_decimal_to_int_2);
  tcase_add_test(tc, s21_from_decimal_to_int_4);
  tcase_add_test(tc, s21_from_decimal_to_int_5);
  tcase_add_test(tc, s21_from_decimal_to_int_6);
  tcase_add_test(tc, s21_test_from_decimal_to_int_0);
  tcase_add_test(tc, s21_test_from_decimal_to_int_1);
  tcase_add_test(tc, s21_test_from_decimal_to_int_3);
  tcase_add_test(tc, s21_test_from_decimal_to_int_4);
  tcase_add_test(tc, s21_test_from_decimal_to_int_6);
  tcase_add_test(tc, s21_test_from_decimal_to_int_7);
  tcase_add_test(tc, s21_test_from_decimal_to_int_8);
  tcase_add_test(tc, s21_test_from_decimal_to_int_9);
  tcase_add_test(tc, s21_test_from_decimal_to_int_10);
  tcase_add_test(tc, s21_test_from_decimal_to_int_11);
  tcase_add_test(tc, s21_test_from_decimal_to_int_12);
  tcase_add_test(tc, s21_test_from_decimal_to_int_14);
  tcase_add_test(tc, s21_test_from_decimal_to_int_15);
  tcase_add_test(tc, s21_test_from_decimal_to_int_16);
  tcase_add_test(tc, s21_test_from_decimal_to_int_17);
  tcase_add_test(tc, s21_from_decimal_to_intTest1);
  tcase_add_test(tc, s21_from_decimal_to_intTest2);
  tcase_add_test(tc, s21_from_decimal_to_intTest3);
  tcase_add_test(tc, s21_from_decimal_to_intTest4);
  tcase_add_test(tc, s21_from_decimal_to_intTest5);
  tcase_add_test(tc, s21_from_decimal_to_intTest6);
  tcase_add_test(tc, s21_from_decimal_to_intTest7);
  tcase_add_test(tc, s21_from_decimal_to_intTest8);
  tcase_add_test(tc, s21_from_decimal_to_intTest9);
  tcase_add_test(tc, s21_from_decimal_to_intTest10);
  tcase_add_test(tc, s21_from_decimal_to_intTest11);
  tcase_add_test(tc, s21_from_decimal_to_intTest12);
  tcase_add_test(tc, s21_from_decimal_to_intTest13);
  tcase_add_test(tc, s21_from_decimal_to_intTest14);
  tcase_add_test(tc, s21_from_decimal_to_intTest15);

  // from int to decimal

  tcase_add_test(tc, s21_from_int_to_decimal1);
  tcase_add_test(tc, s21_test_from_int_to_decimal_0);
  tcase_add_test(tc, s21_test_from_int_to_decimal1);
  tcase_add_test(tc, s21_test_from_int_to_decimal2);
  tcase_add_test(tc, s21_test_from_int_to_decimal_3);
  tcase_add_test(tc, s21_test_from_int_to_decimal_4);
  tcase_add_test(tc, s21_test_from_int_to_decimal_5);
  tcase_add_test(tc, s21_from_int_to_decimalTest1);
  tcase_add_test(tc, s21_from_int_to_decimalTest2);
  tcase_add_test(tc, s21_from_int_to_decimalTest3);
  tcase_add_test(tc, s21_from_int_to_decimalTest4);
  tcase_add_test(tc, s21_from_int_to_decimalTest5);
  tcase_add_test(tc, s21_from_int_to_decimalTest6);
  tcase_add_test(tc, s21_from_int_to_decimalTest7);
  tcase_add_test(tc, s21_from_int_to_decimalTest8);
  tcase_add_test(tc, s21_from_int_to_decimalTest9);
  tcase_add_test(tc, from_int_to_decimal_0);
  tcase_add_test(tc, from_int_to_decimal1);

  // from float to decimal

  tcase_add_test(tc, s21_from_float_to_decimal1);
  tcase_add_test(tc, s21_from_float_to_decimal2);
  tcase_add_test(tc, s21_from_float_to_decimal_3);
  tcase_add_test(tc, s21_from_float_to_decimal_4);
  tcase_add_test(tc, s21_from_float_to_decimal_5);
  tcase_add_test(tc, s21_from_float_to_decimal_6);
  tcase_add_test(tc, s21_from_float_to_decimal_7);
  tcase_add_test(tc, s21_from_float_to_decimal_8);
  tcase_add_test(tc, s21_from_float_to_decimal10);
  tcase_add_test(tc, s21_from_float_to_decimal11);
  tcase_add_test(tc, s21_from_float_to_decimal12);
  tcase_add_test(tc, s21_from_float_to_decimal13);
  tcase_add_test(tc, s21_from_float_to_decimal14);
  tcase_add_test(tc, s21_from_float_to_decimal15);
  tcase_add_test(tc, s21_from_float_to_decimal16);
  tcase_add_test(tc, s21_from_float_to_decimal17);
  tcase_add_test(tc, s21_from_float_to_decimal18);

  // from decimaal to float

  tcase_add_test(tc, s21_from_decimal_to_float_1);
  tcase_add_test(tc, s21_from_decimal_to_float_2);
  tcase_add_test(tc, s21_from_decimal_to_float_3);
  tcase_add_test(tc, s21_from_decimal_to_float_4);
  tcase_add_test(tc, s21_from_decimal_to_float_5);
  tcase_add_test(tc, s21_from_decimal_to_float_7);
  tcase_add_test(tc, s21_from_decimal_to_float_8);
  tcase_add_test(tc, s21_from_decimal_to_float_9);
  tcase_add_test(tc, s21_from_decimal_to_float_10);
  tcase_add_test(tc, s21_from_decimal_to_floatTest1);
  tcase_add_test(tc, s21_from_decimal_to_floatTest2);
  tcase_add_test(tc, s21_from_decimal_to_floatTest3);
  tcase_add_test(tc, s21_from_decimal_to_floatTest4);
  tcase_add_test(tc, s21_from_decimal_to_floatTest5);
  tcase_add_test(tc, s21_from_decimal_to_floatTest6);
  tcase_add_test(tc, s21_from_decimal_to_floatTest7);

  tcase_add_test(tc, add_test_1);
  tcase_add_test(tc, add_test_2);
  tcase_add_test(tc, add_test_3);
  tcase_add_test(tc, add_test_4);
  tcase_add_test(tc, add_test_5);
  tcase_add_test(tc, add_test_6);
  tcase_add_test(tc, add_test_7);
  tcase_add_test(tc, add_test_8);
  tcase_add_test(tc, add_test_9);
  tcase_add_test(tc, add_test_10);
  tcase_add_test(tc, add_test_11);
  tcase_add_test(tc, add_test_12);
  tcase_add_test(tc, add_test_13);
  tcase_add_test(tc, add_test_14);
  tcase_add_test(tc, add_test_15);
  tcase_add_test(tc, add_test_16);
  tcase_add_test(tc, add_test_17);
  tcase_add_test(tc, add_test_18);
  tcase_add_test(tc, add_test_19);
  tcase_add_test(tc, add_test_20);
  tcase_add_test(tc, s21_test_decimal_add_0);
  tcase_add_test(tc, s21_test_decimal_add_1);
  tcase_add_test(tc, s21_test_decimal_add_2);
  tcase_add_test(tc, s21_test_decimal_add_3);
  tcase_add_test(tc, s21_test_decimal_add_4);
  tcase_add_test(tc, s21_test_decimal_add_5);
  tcase_add_test(tc, s21_test_decimal_add_6);
  tcase_add_test(tc, s21_test_decimal_add_7);
  tcase_add_test(tc, s21_test_decimal_add_8);
  tcase_add_test(tc, s21_test_decimal_add_8_1);
  tcase_add_test(tc, s21_test_decimal_add_9);
  tcase_add_test(tc, s21_test_decimal_add_10);
  tcase_add_test(tc, s21_test_decimal_add_11);
  tcase_add_test(tc, s21_test_decimal_add_12);
  tcase_add_test(tc, s21_test_decimal_add_13);
  tcase_add_test(tc, s21_test_decimal_add_14);
  tcase_add_test(tc, s21_test_decimal_add_15);
  tcase_add_test(tc, s21_test_decimal_add_16);
  tcase_add_test(tc, s21_test_decimal_add_17);
  tcase_add_test(tc, s21_test_decimal_add_18);
  tcase_add_test(tc, s21_test_decimal_add_19);
  tcase_add_test(tc, s21_test_decimal_add_20);
  tcase_add_test(tc, s21_test_decimal_add_21);
  tcase_add_test(tc, s21_test_decimal_add_25);
  tcase_add_test(tc, s21_test_decimal_add_26);
  tcase_add_test(tc, s21_test_decimal_add_27);
  tcase_add_test(tc, s21_test_decimal_add_28);
  tcase_add_test(tc, s21_test_decimal_add_29);
  tcase_add_test(tc, s21_test_decimal_add_30);
  tcase_add_test(tc, add_0);
  tcase_add_test(tc, thalassa_add_1);
  tcase_add_test(tc, thalassa_add_2);
  tcase_add_test(tc, thalassa_add_3);
  tcase_add_test(tc, thalassa_add_4);
  tcase_add_test(tc, thalassa_add_5);
  tcase_add_test(tc, thalassa_add_6);
  tcase_add_test(tc, thalassa_add_7);
  tcase_add_test(tc, thalassa_add_8);
  tcase_add_test(tc, thalassa_add_9);
  tcase_add_test(tc, thalassa_add_10);
  tcase_add_test(tc, thalassa_add_11);
  tcase_add_test(tc, thalassa_add_12);
  tcase_add_test(tc, thalassa_add_13);
  tcase_add_test(tc, thalassa_add_14);
  tcase_add_test(tc, thalassa_add_15);
  tcase_add_test(tc, thalassa_add_16);
  tcase_add_test(tc, s21_test_decimal_add_simple_0);
  tcase_add_test(tc, s21_test_decimal_add_simple_1);
  tcase_add_test(tc, s21_test_decimal_add_simple_2);
  tcase_add_test(tc, s21_test_decimal_add_simple_3);
  tcase_add_test(tc, s21_test_decimal_add_simple_4);
  tcase_add_test(tc, s21_test_decimal_add_simple_5);
  tcase_add_test(tc, s21_test_decimal_add_simple_6);
  tcase_add_test(tc, s21_test_decimal_add_simple_7);
  tcase_add_test(tc, s21_test_decimal_add_simple_8);
  tcase_add_test(tc, s21_test_decimal_add_simple_9);
  tcase_add_test(tc, s21_test_decimal_add_simple_10);
  tcase_add_test(tc, s21_test_decimal_add_simple_11);
  tcase_add_test(tc, s21_test_decimal_add_simple_12);
  tcase_add_test(tc, s21_test_decimal_add_simple_13);
  tcase_add_test(tc, s21_test_decimal_add_simple_14);
  tcase_add_test(tc, s21_test_decimal_add_simple_20);
  tcase_add_test(tc, s21_test_decimal_add_simple_21);
  tcase_add_test(tc, s21_test_decimal_add_simple_22);
  tcase_add_test(tc, s21_test_decimal_add_simple_23);
  tcase_add_test(tc, add_test_21);
  tcase_add_test(tc, add_test_22);
  tcase_add_test(tc, add_test_23);
  tcase_add_test(tc, add_test_24);
  tcase_add_test(tc, add_test_25);
  tcase_add_test(tc, add_test_26);
  tcase_add_test(tc, add_test_27);
  tcase_add_test(tc, add_test_28);
  tcase_add_test(tc, add_test_29);
  tcase_add_test(tc, add_test_30);
  tcase_add_test(tc, s21_add_max_31);
  tcase_add_test(tc, s21_add_max_32);
  tcase_add_test(tc, s21_add_max_33);
  tcase_add_test(tc, s21_add_max_34);
  tcase_add_test(tc, s21_add_max_35);
  tcase_add_test(tc, s21_add_max_36);
  tcase_add_test(tc, add_test_37);

  tcase_add_test(tc, mul_test_1);
  tcase_add_test(tc, mul_test_2);
  tcase_add_test(tc, mul_test_3);
  tcase_add_test(tc, mul_test_4);
  tcase_add_test(tc, mul_test_5);
  tcase_add_test(tc, mul_test_6);
  tcase_add_test(tc, mul_test_7);
  tcase_add_test(tc, mul_test_8);

  tcase_add_test(tc, s21_div_box_1_3_0_0);
  tcase_add_test(tc, s21_div_box_1_3_0_1);
  tcase_add_test(tc, s21_div_box_1_3_1_0);
  tcase_add_test(tc, s21_div_box_1_3_1_1);
  tcase_add_test(tc, s21_div_box_1_3_10_10);
  tcase_add_test(tc, s21_div_box_1_3_28_28);
  tcase_add_test(tc, s21_div_box_1_3_28_0);
  tcase_add_test(tc, s21_div_box_1_3_0_28);
  tcase_add_test(tc, s21_div_box_1_3_5_15);
  tcase_add_test(tc, s21_div_box_1_3_15_5);
  tcase_add_test(tc, s21_div_box_1_3_5_0);
  tcase_add_test(tc, s21_div_box_1_3_0_5);

  tcase_add_test(tc, div_test_1);
  tcase_add_test(tc, div_test_2);
  tcase_add_test(tc, div_test_3);
  tcase_add_test(tc, div_test_4);
  tcase_add_test(tc, div_test_5);
  tcase_add_test(tc, div_test_6);
  tcase_add_test(tc, div_test_7);
  tcase_add_test(tc, div_test_8);

  tcase_add_test(tc, s21_negate_1);
  tcase_add_test(tc, s21_negate_2);
  tcase_add_test(tc, s21_negate_3);
  tcase_add_test(tc, s21_negate_4);
  tcase_add_test(tc, s21_negate_5);
  tcase_add_test(tc, s21_test_negate_0);
  tcase_add_test(tc, s21_test_negate_1);
  tcase_add_test(tc, s21_test_negate_2);
  tcase_add_test(tc, s21_test_negate_3);
  tcase_add_test(tc, s21_test_negate_4);
  tcase_add_test(tc, s21_test_negate_5);
  tcase_add_test(tc, s21_test_negate_6);
  tcase_add_test(tc, s21_test_negate_7);
  tcase_add_test(tc, s21_test_negate_8);
  tcase_add_test(tc, negate_0);
  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);

  tcase_add_test(tc, s21_trun_1);
  tcase_add_test(tc, s21_trun_2);
  tcase_add_test(tc, s21_trun_3);
  tcase_add_test(tc, s21_trun_4);
  tcase_add_test(tc, s21_truncate_1);
  tcase_add_test(tc, s21_truncate_2);
  tcase_add_test(tc, s21_truncate_3);
  tcase_add_test(tc, s21_truncate_4);
  tcase_add_test(tc, s21_truncate_5);
  tcase_add_test(tc, s21_truncate_6);
  tcase_add_test(tc, s21_truncate_7);
  tcase_add_test(tc, s21_truncate_8);
  tcase_add_test(tc, s21_truncateTest1);
  tcase_add_test(tc, s21_truncateTest2);
  tcase_add_test(tc, s21_truncateTest3);
  tcase_add_test(tc, s21_truncateTest4);
  tcase_add_test(tc, s21_truncateTest5);
  tcase_add_test(tc, s21_truncateTest6);
  tcase_add_test(tc, s21_truncateTest7);
  tcase_add_test(tc, s21_truncateTest8);
  tcase_add_test(tc, s21_truncateTest9);
  tcase_add_test(tc, s21_truncateTest10);
  tcase_add_test(tc, s21_truncateTest11);

  tcase_add_test(tc, s21_floor_1);
  tcase_add_test(tc, s21_floor_2);
  tcase_add_test(tc, s21_floor_3);
  tcase_add_test(tc, s21_floor_4);
  tcase_add_test(tc, s21_floor_5);
  tcase_add_test(tc, s21_floor_6);
  tcase_add_test(tc, s21_floor_7);
  tcase_add_test(tc, s21_floor_8);
  tcase_add_test(tc, s21_floor_9);
  tcase_add_test(tc, s21_floor_10);
  tcase_add_test(tc, s21_floor_11);
  tcase_add_test(tc, s21_floor_01);
  tcase_add_test(tc, s21_floor_02);
  tcase_add_test(tc, s21_floorTest1);
  tcase_add_test(tc, s21_floorTest2);
  tcase_add_test(tc, s21_floorTest3);
  tcase_add_test(tc, s21_floorTest4);
  tcase_add_test(tc, s21_floorTest5);
  tcase_add_test(tc, s21_floorTest6);
  tcase_add_test(tc, s21_floorTest7);
  tcase_add_test(tc, s21_floorTest8);
  tcase_add_test(tc, s21_floorTest9);
  tcase_add_test(tc, s21_floorTest10);
  tcase_add_test(tc, s21_floorTest11);

  tcase_add_test(tc, s21_round_1);
  tcase_add_test(tc, s21_round_2);
  tcase_add_test(tc, s21_round_3);
  tcase_add_test(tc, s21_round_4);
  tcase_add_test(tc, s21_round_5);
  tcase_add_test(tc, s21_round_6);
  tcase_add_test(tc, s21_round_7);
  tcase_add_test(tc, s21_round_8);
  tcase_add_test(tc, s21_round_9);
  tcase_add_test(tc, s21_round_10);
  tcase_add_test(tc, s21_round_11);
  tcase_add_test(tc, s21_round_12);
  tcase_add_test(tc, s21_round_13);
  tcase_add_test(tc, s21_roundTest1);
  tcase_add_test(tc, s21_roundTest2);
  tcase_add_test(tc, s21_roundTest3);
  tcase_add_test(tc, s21_roundTest4);
  tcase_add_test(tc, s21_roundTest5);
  tcase_add_test(tc, s21_roundTest6);
  /* tcase_add_test(tc, s21_roundTest7); */
  tcase_add_test(tc, s21_roundTest8);
  tcase_add_test(tc, s21_roundTest9);
  tcase_add_test(tc, s21_roundTest10);
  tcase_add_test(tc, s21_roundTest11);
  tcase_add_test(tc, s21_roundTest12);
  tcase_add_test(tc, s21_roundTest13);
  tcase_add_test(tc, s21_roundTest14);
  tcase_add_test(tc, s21_roundTest15);

  tcase_add_test(tc, mod_test_1);
  tcase_add_test(tc, mod_test_2);
  tcase_add_test(tc, mod_test_3);
  tcase_add_test(tc, mod_test_4);
  tcase_add_test(tc, mod_test_5);
  tcase_add_test(tc, mod_test_6);
  tcase_add_test(tc, mod_test_7);
  tcase_add_test(tc, mod_test_8);
  tcase_add_test(tc, mod_test_9);
  tcase_add_test(tc, mod_test_10);
  tcase_add_test(tc, mod_test_11);
  tcase_add_test(tc, mod_test_12);
  tcase_add_test(tc, mod_test_13);
  tcase_add_test(tc, mod_test_14);
  tcase_add_test(tc, mod_test_15);

  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}
