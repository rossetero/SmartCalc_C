#include "../core.h"

_stack_t* get_polish(_stack_t* input) {
  _stack_t* output = NULL;
  _stack_t* op_stack = NULL;
  while (input) {
    if (input->type <= 1) {
      output = push(output, input->val, input->p, input->type);

    } else if (input->type >= 4) {
      if (op_stack && input->p <= op_stack->p) {
        output = push(output, op_stack->val, op_stack->p, op_stack->type);
        op_stack = pop(op_stack);
      }
      op_stack = push(op_stack, input->val, input->p, input->type);
    } else if (input->type == OPEN_BRACE) {
      op_stack = push(op_stack, input->val, input->p, input->type);
    } else if (input->type == CLOSE_BRACE) {
      while (op_stack->type != OPEN_BRACE) {
        output = push(output, op_stack->val, op_stack->p, op_stack->type);
        op_stack = pop(op_stack);
      }
      op_stack = pop(op_stack);
    }
    input = pop(input);
  }
  while (op_stack) {
    output = push(output, op_stack->val, op_stack->p, op_stack->type);
    op_stack = pop(op_stack);
  }
  _stack_t* routput = reverse(output);
  return routput;
}