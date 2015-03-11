/*  truc.c
  Fonction recursive et son equivalent en iteratif

  -----| DERECURSIFICATION DE FONCTION PAR PILE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include <stdio.h>
#include "stack.h"
#include "truc.h"

#define N 10

int P[N+1] = {0,1,3,2,5,5,2,7,1,9,1};

/*  int TRUC(int S, int I)
  Fonction sous forme recursive qui affiche la decomposition de
  S en I entiers pris a partir d'un tableau d'entiers (defini ici en statique)

  Entrees :
    int S : Nombre a decomposer
    int I : Nombre d'entiers utilises pour decomposer S

  Sortie :
    int : entier sous forme de booleen
      0 si on a pas pu decomposer S exactement
      1 sinon
*/
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

/*  int truc_iter(int s, int i)
  Meme fonction qu'au dessus, mais sous forme iterative

  Entrees :
    int s : Nombre a decomposer
    int i : Nombre d'entiers utilises pour decomposer S

  Sortie :
    int : entier sous forme de booleen
      0 si on a pas pu decomposer S exactement
      1 sinon
*/
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
