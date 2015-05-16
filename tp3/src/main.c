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
  if (creerArbre("(a(b(a(T))r(b(r(E))T(S)))b(a(i(L(l(e(R))))R(r(e)))i(e(N))o(s(s(E,U))))f(a(i(M,r(E))))j(o(u(e(T,u(R)))))k(i(m(o(n(O)))w(I)))m(a(S(s(E))))v(a(i(N)))y(a(c(K)))z(e(b(U))))",&monArbre)) {
    afficherArbre(monArbre);
    insererMot(&monArbre,"arB");
    insererMot(&monArbre,"abattU");
    insererMot(&monArbre,"arborE");
    insererMot(&monArbre,"artistE");
    insererMot(&monArbre,"clienT");
    afficherArbre(monArbre);
    libererArbre(&monArbre);
  } else {
    fprintf(stderr, "Probleme creation arbre\n");
  }
  return 0;
}
