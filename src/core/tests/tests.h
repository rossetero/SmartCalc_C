#ifndef TESTS_H
#define TESTS_H
#include <check.h>

#include "../core.h"
Suite *test_validation(void);
Suite *test_parser(void);
Suite *test_rpn(void);
Suite *test_evaluate(void);
#endif