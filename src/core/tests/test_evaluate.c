#include "tests.h"

START_TEST(eval_0) {
  char* test = "2+2+";
  double x = 0;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, INVALID_SINTAX);
}
END_TEST

START_TEST(eval_1) {
  char* test = "2+2";
  double expect = 4;
  double x = 0;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_2) {
  char* test = "2.1111111+2";
  double expect = 4.1111111;
  double x = 0;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_3) {
  char* test = "2.1111111mod2";
  double x = 0;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(eval_4) {
  char* test = "3mod2";
  double expect = 1;
  double x = 0;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_5) {
  char* test = "2+2*2";
  double expect = 6;
  double x = 0;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_6) {
  char* test = "(2+2)*x";
  double expect = 8;
  double x = 2;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_7) {
  char* test = "(3-2)^x/2";
  double expect = 0.5;
  double x = 1234;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_8) {
  char* test = "2/x";
  double x = 0;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(eval_9) {
  char* test = "cos(x)";
  double x = -M_PI;
  double expect = -1;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_10) {
  char* test = "sin(x)";
  double x = -3 * M_PI / 2;
  double expect = 1;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_11) {
  char* test = "asin(x)";
  double x = -3 * M_PI / 2 + 1000;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(eval_12) {
  char* test = "acos(x)+asin(x)";
  double x = -1;
  double expect = M_PI / 2;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_13) {
  char* test = "sqrt(x)";
  double x = 2;
  double expect = sqrt(x);
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_14) {
  char* test = "sqrt(x)";
  double x = -2;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(eval_15) {
  char* test = "ln(x)+log(1000)+tan(3.14159265358979323846)";
  double x = M_E;
  double expect = 4;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_16) {
  char* test = "atan(x)";
  double x = 1;
  double expect = M_PI / 4;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

START_TEST(eval_17) {
  char* test = "atan(x*2+0.123)";
  double x = 1000000000;
  double expect = M_PI / 2;
  double res;
  int status = evaluate(test, x, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(expect, res, 0.0000001);
}
END_TEST

Suite* test_evaluate() {
  Suite* s = suite_create("test_evaluate");
  TCase* o = tcase_create("test_evaluate");
  suite_add_tcase(s, o);

  tcase_add_test(o, eval_0);
  tcase_add_test(o, eval_1);
  tcase_add_test(o, eval_2);
  tcase_add_test(o, eval_3);
  tcase_add_test(o, eval_4);
  tcase_add_test(o, eval_5);
  tcase_add_test(o, eval_6);
  tcase_add_test(o, eval_7);
  tcase_add_test(o, eval_8);
  tcase_add_test(o, eval_9);
  tcase_add_test(o, eval_10);
  tcase_add_test(o, eval_11);
  tcase_add_test(o, eval_12);
  tcase_add_test(o, eval_13);
  tcase_add_test(o, eval_14);
  tcase_add_test(o, eval_15);
  tcase_add_test(o, eval_16);
  tcase_add_test(o, eval_17);

  return s;
}