#include <stdio.h>
#include "gestion_news.h"

int main(int argc, char *argv[]) {
  int old_deb = 20150225;
  int new_deb = 20150226;
  cell_t *liste = NULL;
  if (argc > 1) {
    charger(&liste,argv[1]);
  }
  if (liste) {
    printf("Affichage de la liste apres recuperation\n");
    afficher_liste(liste);

    printf("Affichage des messages du jour\n");
    afficher_messages_jour(liste);

    printf("Suppression des messages obsoletes\n");
    supprimer_obsoletes(&liste);
    afficher_liste(liste);

    printf("Modification des dates de debut: %d -> %d\n",old_deb,new_deb);
    remplacer_date(&liste,old_deb,new_deb);
    afficher_liste(liste);

    liberer_liste(&liste);
  }
  return 0;
}
