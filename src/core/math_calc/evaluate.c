#include "../core.h"

int evaluate(char* exp, double x, double* res) {
  if (!is_valid(exp)) {
    return INVALID_SINTAX;
  }
  _stack_t* o = NULL;
  _stack_t* rpn = NULL;
  o = get_parsing_output(exp);
  rpn = get_polish(o);
  return calculate(rpn, x, res);
}