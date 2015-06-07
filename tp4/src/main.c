/*  main.c
  Fonction principale du programme, pour les tests

  -----| ARBRES |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include "mat.h"

int main(int argc, char *argv[]) {
  mat_t m;
  if (argc > 1) {
    if (lire_matrice(argv[1],&m)) {
      printf("Matrice lue\n");
      afficher_matrice(m);
      printf("%d\n",element(m,2,2));
      printf("%d\n",element(m,5,1));
      liberer_matrice(&m);
    } else {
      printf("Erreur probable\n");
    }
  }
  return 0;
}
