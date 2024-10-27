#include "../core.h"

int is_unar(char* exp, int i) { return i == 0 || exp[i - 1] == '('; }

_stack_t* parse_opers(_stack_t* output, char* exp, int i) {
  switch (exp[i]) {
    case '+':
      if (is_unar(exp, i)) {
        output = push(output, 0, NUM_P, NUM);
      }
      output = push(output, 0, PM_P, SUM);
      break;
    case '-':
      if (is_unar(exp, i)) {
        output = push(output, 0, NUM_P, NUM);
      }
      output = push(output, 0, PM_P, SUB);
      break;
    case '*':
      output = push(output, 0, MD_P, MUL);
      break;
    case '/':
      output = push(output, 0, MD_P, DIV);
      break;
    case '^':
      output = push(output, 0, POW_P, POW);
      break;
    case '(':
      output = push(output, 0, BRACE_P, OPEN_BRACE);
      break;
    case ')':
      output = push(output, 0, BRACE_P, CLOSE_BRACE);
      break;
  }
  return output;
}
// cosintaqrlnogmd

_stack_t* parse_funcs(_stack_t* output, char* exp, int* i) {
  if (is_ln(exp, *i)) {
    output = push(output, 0, FUNC_P, LN);
    *i += 2;
  } else if (is_mod(exp, *i)) {
    output = push(output, 0, MD_P, MOD);
    *i += 3;
  } else if (is_cos(exp, *i)) {
    output = push(output, 0, FUNC_P, COS);
    *i += 3;
  } else if (is_sin(exp, *i)) {
    output = push(output, 0, FUNC_P, SIN);
    *i += 3;
  } else if (is_tan(exp, *i)) {
    output = push(output, 0, FUNC_P, TAN);
    *i += 3;
  } else if (is_log(exp, *i)) {
    output = push(output, 0, FUNC_P, LOG10);
    *i += 3;
  } else if (is_acos(exp, *i)) {
    output = push(output, 0, FUNC_P, ACOS);
    *i += 4;
  } else if (is_asin(exp, *i)) {
    output = push(output, 0, FUNC_P, ASIN);
    *i += 4;
  } else if (is_atan(exp, *i)) {
    output = push(output, 0, FUNC_P, ATAN);
    *i += 4;
  } else if (is_sqrt(exp, *i)) {
    output = push(output, 0, FUNC_P, SQRT);
    *i += 4;
  }
  return output;
}

_stack_t* get_parsing_output(char* exp) {
  _stack_t* output = NULL;
  _stack_t* routput = NULL;
  char* end = NULL;
  int i = 0;
  while (exp[i]) {
    if (isdigit(exp[i])) {
      double num = strtod((exp + i), &end);
      output = push(output, num, NUM_P, NUM);
      i += (end - (exp + i));
    } else if (exp[i] == 'x') {
      output = push(output, 0, NUM_P, X);
      i++;
    } else if (strchr("+-/*^()", exp[i])) {
      output = parse_opers(output, exp, i);
      ++i;
    } else if (strchr("cstalm", exp[i])) {
      output = parse_funcs(output, exp, &i);
    }
  }
  routput = reverse(output);
  return routput;
}