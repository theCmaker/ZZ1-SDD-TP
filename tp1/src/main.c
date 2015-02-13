#include <stdio.h>
#include "gestion_news.h"

int main(int argc, char *argv[]) {
  cell_t *liste = NULL;
  if (argc > 1) {
    charger(&liste,argv[1]);
  }
  if (liste) {
    printf("Affichage de la liste après récupération\n");
    afficher_liste(liste);

    printf("Affichage des messages du jour\n");
    afficher_messages_jour(liste);

    printf("Affichage des messages d'après-demain\n");
    afficher_messages_date(liste,getDate()+2);
  }
  return 0;
}
