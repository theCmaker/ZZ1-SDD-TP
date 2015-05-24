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
  char *motif1 = "";
  char *motif2 = "ab";
  
  if (creerArbre("(a(b(a(T))r(b(r(E))T(S)))b(a(i(L(l(e(R))))R(r(e)))i(e(N))o(s(s(E,U))))f(a(i(M,r(E))))j(o(u(e(T,u(R)))))k(i(m(o(n(O)))w(I)))m(a(S(s(E))))v(a(i(N)))y(a(c(K)))z(e(b(U))))",&monArbre)) {
    printf("**********\nAffichage avant insertion\n");
    afficherArbre(monArbre);
    insererMot(&monArbre,"aba"); 
    insererMot(&monArbre,"abattu");
    insererMot(&monArbre,"Arbore");   /*Debut deja present */
    insererMot(&monArbre,"artiSte");
    insererMot(&monArbre,"clIent");   /* Aucune lettre deja presente */
    insererMot(&monArbre,"arT");      /* Mot deja present */
    insererMot(&monArbre,"");         /* Mot vide */
    insererMot(&monArbre,"joue");     /* Mot inclus dans un mot deja present */
    insererMot(&monArbre,"kin");
    insererMot(&monArbre,"papa");
    
  	printf("**********\nAffichage apres insertion\n");
  	afficherArbre(monArbre);
  	
  	printf("**********\nRecherche du motif \"%s\"\n", motif1);
  	rech_motif(&monArbre, motif1);
  	
  	printf("**********\nRecherche du motif \"%s\"\n", motif2);
  	rech_motif(&monArbre, motif2);

    libererArbre(&monArbre);
  } else {
    fprintf(stderr, "Probleme creation arbre\n");
  }
  return 0;
}
