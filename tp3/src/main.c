/*  main.c
  Fonction principale du programme, pour les tests

  -----| ARBRES |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include "tree.h"

int main(/*int argc, char *argv[]*/) {
  tree_t *monArbre;
  if (creerArbre_2("(a(b(z(h,u)k)x(m)f(p,v,e)))",&monArbre)) {
    afficherArbre(monArbre);
    printf("\n");
  } else {
    fprintf(stderr, "Probleme creation arbre\n");
  }
  return 0;
}
