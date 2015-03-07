#ifndef __STACK__H
#define __STACK__H

  typedef int datatype;

  typedef struct _stack_t {
    int       max;
    int       top;
    datatype *val;
  } stack_t;

  int init(stack_t *,int);
  void supp(stack_t *);
  int empty(stack_t);
  int full(stack_t);
  int pop(stack_t *, datatype *);
  int top(stack_t *, datatype *);
  int push(stack_t *, datatype);

#endif
