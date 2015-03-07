#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int init(stack_t *p, int n) {
  int ret = 1;
  p->max = n;
  p->top = -1;
  p->val = (int*) malloc(n*sizeof(int));
  if (p->val == NULL) {
    ret = 0;
  }
  return ret;
}

void supp(stack_t *p) {
  free(p->val);
}

int empty(stack_t p) {
  return (p.top == -1)?1:0;
}

int full(stack_t p) {
  return (p.top == p.max-1)?1:0;
}

int pop(stack_t *p, datatype *v) {
  int ok = 0;
  if (!empty(*p)) {
    *v = p->val[p->top];
    ok = 1;
    p->top--;
  }
  return ok;
}

int top(stack_t *p, datatype *v) {
  int ok = 0;
  if (!empty(*p)) {
    *v = p->val[p->top];
    ok = 1;
  }
  return ok;
}

int push(stack_t *p, datatype v) {
  int ok = 0;
  if (!full(*p)) {
    p->top++;
    p->val[p->top] = v;
    ok = 1;
  }
  return ok;
}
