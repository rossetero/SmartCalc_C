#include "bkts_stack.h"
void bdestroy(bstack *top) {
  while (top) {
    bstack *tmp = top;
    top = top->next;
    free(tmp);
  }
}
bstack *bpush(bstack *top, char p) {
  bstack *tmp = malloc(sizeof(bstack));
  tmp->br = p;
  tmp->next = top;
  top = tmp;
  return top;
}

bstack *bpop(bstack *top) {
  if (top) {
    bstack *tmp = top;
    top = top->next;
    free(tmp);
  }
  return top;
}