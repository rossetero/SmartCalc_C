#ifndef BKTS_STACK_H
#define BKTS_STACK_H
#include <stdlib.h>
typedef struct bkts {
  char br;
  struct bkts* next;
} bstack;

void bdestroy(bstack* top);
bstack* bpush(bstack* top, char p);
bstack* bpop(bstack* top);
#endif
