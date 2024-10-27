#include "../core.h"

void destroy(_stack_t *top) {
  while (top) {
    _stack_t *tmp = top;
    top = top->next;
    free(tmp);
  }
}
_stack_t *push(_stack_t *top, double val, prt_t p, type_t type) {
  _stack_t *tmp = (_stack_t *)malloc(sizeof(_stack_t));
  tmp->val = val;
  tmp->p = p;
  tmp->type = type;
  tmp->next = top;
  top = tmp;
  return top;
}

_stack_t *pop(_stack_t *top) {
  if (top) {
    _stack_t *tmp = top;
    top = top->next;
    free(tmp);
  }
  return top;
}

// void print_stack(_stack_t *top) {
//   _stack_t *tmp = top;
//   int cnt = 1;
//   while (tmp) {
//     printf("%5d: val:%10.2lf p:%5d type:%5d\n", cnt, tmp->val, tmp->p,
//            tmp->type);

//     cnt++;
//     tmp = tmp->next;
//   }
// }

char *from_stack_to_string(_stack_t *top, char *str) {
  _stack_t *tmp = top;
  while (tmp) {
    switch (tmp->type) {
      case NUM: {
        char tmpstr[256];
        sprintf(tmpstr, "%0.7lf", tmp->val);
        strcat(str, tmpstr);
      } break;
      case X:
        strcat(str, "x");
        break;
      case OPEN_BRACE:
        strcat(str, "(");
        break;
      case CLOSE_BRACE:
        strcat(str, ")");
        break;
      case SUM:
        strcat(str, "+");
        break;
      case SUB:
        strcat(str, "-");
        break;
      case MUL:
        strcat(str, "*");
        break;
      case DIV:
        strcat(str, "/");
        break;
      case POW:
        strcat(str, "^");
        break;
      case MOD:
        strcat(str, "mod");
        break;
      case SIN:
        strcat(str, "sin");
        break;
      case COS:
        strcat(str, "cos");
        break;
      case TAN:
        strcat(str, "tan");
        break;
      case LOG10:
        strcat(str, "log");
        break;
      case LN:
        strcat(str, "ln");
        break;
      case SQRT:
        strcat(str, "sqrt");
        break;
      case ASIN:
        strcat(str, "asin");
        break;
      case ACOS:
        strcat(str, "acos");
        break;
      case ATAN:
        strcat(str, "atan");
        break;
    }
    strcat(str, "|");
    tmp = tmp->next;
  }
  return str;
}

_stack_t *reverse(_stack_t *s1) {
  _stack_t *s2 = NULL;
  while (s1) {
    s2 = push(s2, s1->val, s1->p, s1->type);
    s1 = pop(s1);
  }
  return s2;
}
