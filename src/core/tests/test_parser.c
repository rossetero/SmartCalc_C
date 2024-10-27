#include "tests.h"

START_TEST(parser_1) {
  char* test = "2+1.15-3^3";
  char* expect = "2.0000000|+|1.1500000|-|3.0000000|^|3.0000000|";
  char res[256] = {'\0'};
  _stack_t* o = get_parsing_output(test);
  from_stack_to_string(o, res);
  destroy(o);
  ck_assert_str_eq(res, expect);
}
END_TEST

START_TEST(parser_2) {
  char* test = "2mod1.15";
  char* expect = "2.0000000|mod|1.1500000|";
  char res[256] = {'\0'};
  _stack_t* o = get_parsing_output(test);
  from_stack_to_string(o, res);
  destroy(o);
  ck_assert_str_eq(res, expect);
}
END_TEST

START_TEST(parser_3) {
  char* test = "sin(x)+cos(x+atan(x^log(x)))/acos(x)*asin(tan(x))-ln(sqrt(x))";
  char* expect =
      "sin|(|x|)|+|cos|(|x|+|atan|(|x|^|log|(|x|)|)|)|/"
      "|acos|(|x|)|*|asin|(|tan|(|x|)|)|-|ln|(|sqrt|(|x|)|)|";
  char res[256] = {'\0'};
  _stack_t* o = get_parsing_output(test);
  from_stack_to_string(o, res);
  destroy(o);
  ck_assert_str_eq(res, expect);
}
END_TEST

START_TEST(parser_4) {
  char* test = "-2mod1.15+(+2)";
  char* expect =
      "0.0000000|-|2.0000000|mod|1.1500000|+|(|0.0000000|+|2.0000000|)|";
  char res[256] = {'\0'};
  _stack_t* o = get_parsing_output(test);
  from_stack_to_string(o, res);
  destroy(o);
  ck_assert_str_eq(res, expect);
}
END_TEST

Suite* test_parser() {
  Suite* s = suite_create("test_parser");
  TCase* o = tcase_create("test_parser");
  suite_add_tcase(s, o);

  tcase_add_test(o, parser_1);
  tcase_add_test(o, parser_2);
  tcase_add_test(o, parser_3);
  tcase_add_test(o, parser_4);

  return s;
}