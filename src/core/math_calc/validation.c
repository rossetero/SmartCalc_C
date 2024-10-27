#include "../core.h"
#include "bkts_stack.h"
int is_valid(char* exp) {
  int cor_cnt = 0;

  cor_cnt += validate_all_numbers(exp);

  cor_cnt += validate_all_opers(exp);

  cor_cnt += validate_all_mods(exp);

  cor_cnt += validate_bkts(exp);

  cor_cnt += validate_all_sins(exp);

  cor_cnt += validate_all_coses(exp);

  cor_cnt += validate_all_tans(exp);

  cor_cnt += validate_all_logs(exp);

  cor_cnt += validate_all_asins(exp);

  cor_cnt += validate_all_acoses(exp);

  cor_cnt += validate_all_atans(exp);

  cor_cnt += validate_all_sqrts(exp);

  cor_cnt += validate_all_lns(exp);

  return cor_cnt == 13;
}

int validate_num(char* lex) {
  int status = VALID;
  char* end = NULL;
  strtod(lex, &end);
  if (strcmp(lex, "x") && *end != '\0') status = INVALID;
  return status;
}

int validate_all_numbers(char* exp) {
  int status = VALID;
  char* str = strdup(exp);
  char* seps = "+-*/^()cosintaqrlnogmd";
  char* pch = strtok(str, seps);
  while (pch != NULL && status) {
    if (!validate_num(pch)) status = INVALID;
    pch = strtok(NULL, seps);
  }
  free(str);
  return status;
}

int is_oper(char ch) {
  int t = 1;
  char* opers = "+-*/^";
  if (!strchr(opers, ch)) t = 0;
  return t;
}

int validate_oper(char* exp, int i) {
  int a = is_oper(exp[i - 1]);
  int b = is_oper(exp[i + 1]) || exp[i + 1] == ')' || exp[i + 1] == '.';
  return !a && !b;
}

int validate_all_opers(char* exp) {
  int status = VALID;
  int i = 0;
  if ((exp[0] == '-' || exp[0] == '+') &&
      (is_oper(exp[i + 1]) || exp[i + 1] == ')')) {
    status = INVALID;
  } else if ((exp[0] == '-' || exp[0] == '+') &&
             !(is_oper(exp[i + 1]) || exp[i + 1] == ')')) {
    i++;
  } else if (is_oper(exp[0])) {
    status = INVALID;
  }

  while (status && exp[i]) {
    if (is_oper(exp[i]) && !validate_oper(exp, i)) {
      status = INVALID;
    }
    ++i;
  }
  return status;
}

int is_mod(char* exp, int i) {
  return strlen(exp) - i > 3 && exp[i] == 'm' && exp[i + 1] == 'o' &&
         exp[i + 2] == 'd';
}

int validate_mod(char* exp, int i) {
  int a = is_oper(exp[i - 1]);
  int b = is_oper(exp[i + 3]) || exp[i + 3] == ')' || exp[i + 3] == '.';
  return !a && !b;
}

int validate_all_mods(char* exp) {
  int status = VALID;
  unsigned int i = 0;
  if (is_mod(exp, 0)) status = INVALID;
  while (status && exp[i] && i < strlen(exp)) {
    if (exp[i] == 'm') {
      if (!is_mod(exp, i) || !validate_mod(exp, i)) {
        status = INVALID;
      }

      i += 3;
    } else {
      ++i;
    }
  }
  return status;
}

int validate_bkts(char* exp) {
  int i = 0;
  int prev = 0;
  bstack* stack = NULL;
  int status = VALID;
  while (status && exp[i]) {
    if (exp[i] == '(') {
      stack = bpush(stack, '(');
      prev = i;
    }
    if (exp[i] == ')') {
      // i-prev>1 - check for non empty brackets
      if (stack != NULL && i - prev > 1 &&
          (is_oper(exp[i + 1]) || exp[i + 1] == ')' || exp[i + 1] == 'm')) {
        stack = bpop(stack);
      } else {
        status = INVALID;
      }
    }
    ++i;
  }
  // if open brackets left in stack
  if (status && stack != NULL) {
    status = INVALID;
  }
  bdestroy(stack);
  return status;
}

int validate_func_3(char* exp, int i) {
  int a = is_oper(exp[i - 1]) || exp[i - 1] == '(' || exp[i - 1] == 'a';
  int b = exp[i + 3] == '(';
  return a && b;
}

int is_sin(char* exp, int i) {
  return strlen(exp) - i > 3 && exp[i] == 's' && exp[i + 1] == 'i' &&
         exp[i + 2] == 'n';
}

int validate_all_sins(char* exp) {
  int status = VALID;
  unsigned int i = 0;
  while (status && exp[i] && i < strlen(exp)) {
    if (exp[i] == 's' && exp[i + 1] == 'i') {
      if (!is_sin(exp, i) || !validate_func_3(exp, i)) {
        status = INVALID;
      }
      i += 3;
    } else {
      ++i;
    }
  }
  return status;
}

int is_cos(char* exp, int i) {
  return strlen(exp) - i > 3 && exp[i] == 'c' && exp[i + 1] == 'o' &&
         exp[i + 2] == 's';
}

int validate_all_coses(char* exp) {
  int status = VALID;
  unsigned int i = 0;
  while (status && exp[i] && i < strlen(exp)) {
    if (exp[i] == 'c') {
      if (!is_cos(exp, i) || !validate_func_3(exp, i)) {
        status = INVALID;
      }
      i += 3;
    } else {
      ++i;
    }
  }
  return status;
}

int is_tan(char* exp, int i) {
  return strlen(exp) - i > 3 && exp[i] == 't' && exp[i + 1] == 'a' &&
         exp[i + 2] == 'n';
}

int validate_all_tans(char* exp) {
  int status = VALID;
  unsigned int i = 0;
  while (status && exp[i] && i < strlen(exp)) {
    if (exp[i] == 't' && exp[i + 1] == 'a') {
      if (!is_tan(exp, i) || !validate_func_3(exp, i)) {
        status = INVALID;
      }
      i += 3;
    } else {
      ++i;
    }
  }
  return status;
}

int is_log(char* exp, int i) {
  return strlen(exp) - i > 3 && exp[i] == 'l' && exp[i + 1] == 'o' &&
         exp[i + 2] == 'g';
}

int validate_all_logs(char* exp) {
  int status = VALID;
  unsigned int i = 0;
  while (status && exp[i] && i < strlen(exp)) {
    if (exp[i] == 'l' && exp[i + 1] == 'o') {
      if (!is_log(exp, i) || !validate_func_3(exp, i)) {
        status = INVALID;
      }
      i += 3;
    } else {
      ++i;
    }
  }
  return status;
}

int validate_func_4(char* exp, int i) {
  int a = is_oper(exp[i - 1]) || exp[i - 1] == '(';
  int b = exp[i + 4] == '(';
  return a && b;
}

int is_asin(char* exp, int i) {
  return strlen(exp) - i > 4 && exp[i] == 'a' && exp[i + 1] == 's' &&
         exp[i + 2] == 'i' && exp[i + 3] == 'n';
}

int validate_all_asins(char* exp) {
  int status = VALID;
  unsigned int i = 0;
  while (status && exp[i] && i < strlen(exp)) {
    if (exp[i] == 'a' && exp[i + 1] == 's') {
      if (!is_asin(exp, i) || !validate_func_4(exp, i)) {
        status = INVALID;
      }
      i += 4;
    } else {
      ++i;
    }
  }
  return status;
}

int is_acos(char* exp, int i) {
  return strlen(exp) - i > 4 && exp[i] == 'a' && exp[i + 1] == 'c' &&
         exp[i + 2] == 'o' && exp[i + 3] == 's';
}

int validate_all_acoses(char* exp) {
  int status = VALID;
  unsigned int i = 0;
  while (status && exp[i] && i < strlen(exp)) {
    if (exp[i] == 'a' && exp[i + 1] == 'c') {
      if (!is_acos(exp, i) || !validate_func_4(exp, i)) {
        status = INVALID;
      }
      i += 4;
    } else {
      ++i;
    }
  }
  return status;
}

int is_atan(char* exp, int i) {
  return strlen(exp) - i > 4 && exp[i] == 'a' && exp[i + 1] == 't' &&
         exp[i + 2] == 'a' && exp[i + 3] == 'n';
}

int validate_all_atans(char* exp) {
  int status = VALID;
  unsigned int i = 0;
  while (status && exp[i] && i < strlen(exp)) {
    if (exp[i] == 'a' && exp[i + 1] == 't') {
      if (!is_atan(exp, i) || !validate_func_4(exp, i)) {
        status = INVALID;
      }
      i += 4;
    } else {
      ++i;
    }
  }
  return status;
}

int is_sqrt(char* exp, int i) {
  return strlen(exp) - i > 4 && exp[i] == 's' && exp[i + 1] == 'q' &&
         exp[i + 2] == 'r' && exp[i + 3] == 't';
}

int validate_all_sqrts(char* exp) {
  int status = VALID;
  unsigned int i = 0;
  while (status && exp[i] && i < strlen(exp)) {
    if (exp[i] == 's' && exp[i + 1] == 'q') {
      if (!is_sqrt(exp, i) || !validate_func_4(exp, i)) {
        status = INVALID;
      }
      i += 4;
    } else {
      ++i;
    }
  }
  return status;
}

int validate_func_2(char* exp, int i) {
  int a = is_oper(exp[i - 1]) || exp[i - 1] == '(';
  int b = exp[i + 2] == '(';
  return a && b;
}

int is_ln(char* exp, int i) {
  return strlen(exp) - i > 2 && exp[i] == 'l' && exp[i + 1] == 'n';
}

int validate_all_lns(char* exp) {
  int status = VALID;
  unsigned int i = 0;
  while (status && exp[i] && i < strlen(exp)) {
    if (exp[i] == 'l' && exp[i + 1] == 'n') {
      if (!is_ln(exp, i) || !validate_func_2(exp, i)) {
        status = INVALID;
      }
      i += 2;
    } else {
      ++i;
    }
  }
  return status;
}