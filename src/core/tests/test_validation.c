#include "tests.h"

START_TEST(validate_1) {
  char* test = "2+2";
  ck_assert_int_eq(1, is_valid(test));
}
END_TEST

START_TEST(validate_2) {
  char* test = "2+";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_3) {
  char* test = "(2*(4+6)";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_4) {
  char* test = "sin(x+cos())";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_5) {
  char* test = "2.34.4+2";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_6) {
  char* test = "*23/3";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_7) {
  char* test = "-23+345.45";
  ck_assert_int_eq(1, is_valid(test));
}
END_TEST

START_TEST(validate_8) {
  char* test = "-+23+345.45";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_9) {
  char* test = "-)23+345.45";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_10) {
  char* test =
      "cos(x+asin(x-7mod5)+ln(34^tan(1)))^log(1000)+atan(acos(sqrt(x)))";
  ck_assert_int_eq(1, is_valid(test));
}
END_TEST

START_TEST(validate_11) {
  char* test = "7mod4mo5+2";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_12) {
  char* test = "7mod4mod5+2mod";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_13) {
  char* test = "si(x)+cos+cos(x)+tanx+log(x)+ln+log+asin+acos+atan(sqrt)+atan";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_14) {
  char* test = "((x))))))+((((x))";
  ck_assert_int_eq(0, is_valid(test));
}
END_TEST

START_TEST(validate_15) {
  char* test = "(((x)))+((((x))))";
  ck_assert_int_eq(1, is_valid(test));
}
END_TEST

Suite* test_validation() {
  Suite* s = suite_create("test_validation");
  TCase* o = tcase_create("test_validation");
  suite_add_tcase(s, o);

  tcase_add_test(o, validate_1);
  tcase_add_test(o, validate_2);
  tcase_add_test(o, validate_3);
  tcase_add_test(o, validate_4);
  tcase_add_test(o, validate_5);
  tcase_add_test(o, validate_6);
  tcase_add_test(o, validate_7);
  tcase_add_test(o, validate_8);
  tcase_add_test(o, validate_9);
  tcase_add_test(o, validate_10);
  tcase_add_test(o, validate_11);
  tcase_add_test(o, validate_12);
  tcase_add_test(o, validate_13);
  tcase_add_test(o, validate_14);
  tcase_add_test(o, validate_15);

  return s;
}