#include "tests.h"

START_TEST(rpn_1) {
  char* test = "2+1.15-3^3";
  char* expect = "2.0000000|1.1500000|+|3.0000000|3.0000000|^|-|";
  char res[256] = {'\0'};
  _stack_t* o = get_parsing_output(test);
  _stack_t* r = get_polish(o);
  from_stack_to_string(r, res);
  destroy(r);
  ck_assert_str_eq(res, expect);
}
END_TEST

START_TEST(rpn_2) {
  char* test = "2mod1.15";
  char* expect = "2.0000000|1.1500000|mod|";
  char res[256] = {'\0'};
  _stack_t* o = get_parsing_output(test);
  _stack_t* r = get_polish(o);
  from_stack_to_string(r, res);
  destroy(r);
  ck_assert_str_eq(res, expect);
}
END_TEST

START_TEST(rpn_3) {
  char* test = "sin(x)+cos(x+atan(x^log(x)))/acos(x)*asin(tan(x))-ln(sqrt(x))";
  char* expect =
      "x|sin|x|x|x|log|^|atan|+|cos|x|acos|x|tan|asin|x|sqrt|ln|-|*|/|+|";
  char res[256] = {'\0'};
  _stack_t* o = get_parsing_output(test);
  _stack_t* r = get_polish(o);
  from_stack_to_string(r, res);
  destroy(r);
  ck_assert_str_eq(res, expect);
}
END_TEST

START_TEST(rpn_4) {
  char* test = "-2mod1.15+(+2)";
  char* expect = "0.0000000|2.0000000|1.1500000|mod|0.0000000|2.0000000|+|+|-|";
  char res[256] = {'\0'};
  _stack_t* o = get_parsing_output(test);
  _stack_t* r = get_polish(o);
  from_stack_to_string(r, res);
  destroy(r);
  ck_assert_str_eq(res, expect);
}
END_TEST

Suite* test_rpn() {
  Suite* s = suite_create("test_rpn");
  TCase* o = tcase_create("test_rpn");
  suite_add_tcase(s, o);

  tcase_add_test(o, rpn_1);
  tcase_add_test(o, rpn_2);
  tcase_add_test(o, rpn_3);
  tcase_add_test(o, rpn_4);

  return s;
}