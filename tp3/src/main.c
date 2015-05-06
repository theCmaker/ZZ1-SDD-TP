/*  main.c
  Fonction principale du programme, pour les tests

  -----| ARBRES |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include "tree.h"

int main(/*int argc, char *argv[]*/) {
  tree_t *monArbre = NULL;
  if (creerArbre("(a(b(z(h,u)k)x(m)f(p,v,e)))",&monArbre)) {
  /*if (creerArbre("(a(b,c)d)",&monArbre)) {*/
    afficherArbre(monArbre);
    printf("\n");
  } else {
    fprintf(stderr, "Probleme creation arbre\n");
  }
  return 0;
}
