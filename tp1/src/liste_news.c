#include <stdio.h>
#include <stdlib.h>
#include "liste_news.h"

void adj_cell(cell_t **prec, cell_t *elt) {
  elt->suiv = (*prec);
  (*prec) = elt;
}

cell_t ** rech_prec(cell_t **liste, int debut, short int *existe) {
  cell_t **prec = liste;
  while ((*prec) && (*prec)->debut > debut) {
    prec = &((*prec)->suiv);
  }
  /* Booléen de présence     */
  /* 1 : présent             */
  /* 0 : absent              */
  *existe = (*prec && (*prec)->debut == debut)?1:0;
  return prec;
}

void supp_cell(cell_t **prec) {
  cell_t *elt = *prec;
  *prec = elt->suiv;
  free(elt);
}

void ins_cell(cell_t **liste, cell_t *elt) {
  short int existe;
  cell_t **prec = rech_prec(liste,elt->debut,&existe);
  adj_cell(prec,elt);
}

news_t * creer_cell(int debut, int fin, char *message) {
  news_t *elt = (news_t*) malloc(sizeof(news_t));
  if (elt) {
    elt->debut = debut;
    elt->fin = fin;
    strcpy(elt->texte,message);
  }
  return elt;
}
