/*  main.c
  Fonction principale du programme, pour les tests

  -----| DERECURSIFICATION DE FONCTION PAR PILE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "truc.h"
#include "stack.h"

int main(int argc, char *argv[]) {
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
  if (argc > 2) {
    TRUC(atoi(argv[1]),atoi(argv[2]));
    truc_iter(atoi(argv[1]),atoi(argv[2]));
  }
  return 0;
}
