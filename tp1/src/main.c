/*  main.c
  Fichier principal permettant les tests

  -----| GESTION DE NEWS PAR LISTE CHAINEE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include <stdio.h>
#include "gestion_news.h"

int main(int argc, char *argv[]) {
  int old_deb = 20150217;
  int new_deb = 20150226;
  cell_t *liste = NULL;
  if (argc > 1) {
    charger(&liste,argv[1]);
  }
  if (liste) {
    printf("Affichage de la liste apres recuperation\n");
    afficher_liste(liste);

    printf("\nAffichage des messages du jour\n");
    afficher_messages_jour(liste);

    printf("\nSuppression des messages obsoletes\n");
    supprimer_obsoletes(&liste);
    afficher_liste(liste);

    printf("\nModification des dates de debut: %d -> %d\n",old_deb,new_deb);
    remplacer_date(&liste,old_deb,new_deb);
    afficher_liste(liste);

    liberer_liste(&liste);
  }
  return 0;
}