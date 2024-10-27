#include "../core.h"

int check_domain(double x, type_t type) {
  int f = 0;
  int t = type;
  switch (t) {
    case SQRT:
      f = isnan(sqrt(x));
      break;
    case LN:
    case LOG10:
      f = isnan(log(x)) || isinf(log(x));
      break;
    case ACOS:
    case ASIN:
      f = isnan(asin(x));
      break;
    case TAN:
      f = (fabs(tan(x)) > 20003405433.95) ? 1 : 0;
      break;
  }
  return f;
}

int calc_func(double a, type_t type, double* res) {
  if (check_domain(a, type)) {
    return CALCULATION_ERROR;
  }
  *res = 0;
  int t = type;
  switch (t) {
    case COS:
      *res = cos(a);
      break;
    case SIN:
      *res = sin(a);
      break;
    case TAN:
      *res = tan(a);
      break;
    case ACOS:
      *res = acos(a);
      break;
    case ASIN:
      *res = asin(a);
      break;
    case ATAN:
      *res = atan(a);
      break;
    case SQRT:
      *res = sqrt(a);
      break;
    case LN:
      *res = log(a);
      break;
    case LOG10:
      *res = log10(a);
      break;
  }
  return OK;
}

int not_computable_mod(double a, double b, type_t type) {
  return type == MOD && ((int)a != a || (int)b != b);
}

int division_by_zero(double divisor, type_t type) {
  return type == DIV && divisor == 0;
}

int calc_op(double a, double b, type_t type, double* res) {
  int ib = 0;
  int ia = 0;
  if (not_computable_mod(a, b, type) || division_by_zero(a, type)) {
    return CALCULATION_ERROR;
  } else if (type == MOD) {
    ib = (int)b;
    ia = (int)a;
  }
  *res = 0;
  int t = type;
  switch (t) {
    case SUM:
      *res = b + a;
      break;
    case SUB:
      *res = b - a;
      break;
    case MUL:
      *res = b * a;
      break;
    case DIV:
      *res = b / a;
      break;
    case POW:
      *res = pow(b, a);
      break;
    case MOD:
      *res = (double)(ib % ia);
      break;
  }
  return OK;
}

int calculate(_stack_t* exp, double x, double* result) {
  int status = OK;
  *result = 0;
  _stack_t* numstack = NULL;
  while (exp && !status) {
    if (exp->type == NUM || exp->type == X) {
      if (exp->type == X) exp->val = x;
      numstack = push(numstack, exp->val, NUM_P, NUM);
    } else if (exp->type >= 4 && exp->type <= 9) {
      double a = numstack->val;
      double b = numstack->next->val;
      double loc_res = 0;
      if (!calc_op(a, b, exp->type, &loc_res)) {
        numstack = pop(numstack);
        numstack = pop(numstack);
        numstack = push(numstack, loc_res, NUM_P, NUM);
      } else {
        status = CALCULATION_ERROR;
        destroy(numstack);
        destroy(exp);
      }
    } else if (exp->type >= 10) {
      double a = numstack->val;
      double loc_res = 0;
      if (!calc_func(a, exp->type, &loc_res)) {
        numstack = pop(numstack);
        numstack = push(numstack, loc_res, NUM_P, NUM);
      } else {
        status = CALCULATION_ERROR;
        destroy(numstack);
        destroy(exp);
      }
    }
    if (!status) {
      exp = pop(exp);
    }
  }
  if (!status) {
    *result = numstack->val;
    numstack = pop(numstack);
  }
  return status;
}