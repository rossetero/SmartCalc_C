#ifndef STACK_H
#define STACK_H
typedef enum {
  NUM,
  X,
  OPEN_BRACE,
  CLOSE_BRACE,
  SUM,
  SUB,
  MUL,
  DIV,
  POW,
  MOD,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG10
} type_t;

typedef enum {
  BRACE_P = -1,
  NUM_P = 0,
  PM_P = 1,
  MD_P = 2,
  POW_P = 3,
  FUNC_P = 4,

} prt_t;

typedef struct s {
  double val;
  prt_t p;
  type_t type;
  struct s* next;
} _stack_t;

void destroy(_stack_t* top);
_stack_t* push(_stack_t* top, double val, prt_t p, type_t type);
_stack_t* pop(_stack_t* top);
void print_stack(_stack_t* top);
_stack_t* reverse(_stack_t* s1);
char* from_stack_to_string(_stack_t* top, char* str);
#endif