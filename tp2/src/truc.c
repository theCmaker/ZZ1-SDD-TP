#include <stdio.h>
#include "stack.h"

#define N 10

int P[N+1] = {0,1,3,2,5,5,2,7,1,9,1};

int TRUC(int,int);

int TRUC(int S, int I) {
  if (S == 0) {
    return 1;
  } else if (S < 0 || I > N) {
    return 0;
  } else if (TRUC(S-P[I],I+1)) {
    printf("%d\n",P[I]);
    return 1;
  } else {
    return TRUC(S,I+1);
  }
}

int truc_iter(int s, int i) {
  int sl = s;
  int il = i;
  int r;
  stack_t p;
  init(&p,N);
  do {
    while (sl > 0 && il <= N) {
      push(&p,sl);
      push(&p,il);
      sl -= P[il];
      ++il;
    }
    if (sl == 0) {
      r = 1;
      while (!empty(p)) {
        pop(&p,&il);
        pop(&p,&sl);
        printf("%d\n",P[il]);
      }
    } else {
      r = 0;
      if (!empty(p)) {
        pop(&p,&il);
        pop(&p,&sl);
        ++il;
      }
    }
  } while (!empty(p));
  return r;
}

int main(void) {
  int S, I;
  do {
    S = -1;
    while (S <= 0) {
      printf("S? ");
      scanf("%d",&S);
    }
    printf("I? ");
    scanf("%d",&I);

    if (I >= 0) {
      printf("Recursif:\n");
      TRUC(S,I);
      printf("Iteratif:\n");
      truc_iter(S,I);
    }
  } while (I >= 0);
  return 0;
}
