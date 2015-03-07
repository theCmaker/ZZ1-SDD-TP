#include <stdio.h>
#include "stack.h"

int main(void) {
  stack_t p;
  int i = 0;
  if (init(&p,10)) {
    while (push(&p,i)) {
      printf("Empiler: %d\n",i);
      ++i;
    }
    while (pop(&p,&i)) {
      printf("Depiler: %d\n",i);
    }
    supp(&p);
  }
  return 0;
}
