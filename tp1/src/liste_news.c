/*	liste_news.c
	Fonctions de gestion de la liste chainee

	-----| GESTION DE NEWS PAR LISTE CHAINEE |-----

	BARBESANGE Benjamin,
	PISSAVY Pierre-Loup

	ISIMA 1ere Annee, 2014-2015
*/

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
  /* Booleen de presence     */
  /* 1 : present             */
  /* 0 : absent              */
  *existe = (*prec && (*prec)->debut == debut)?1:0;
  return prec;
}

void supp_cell(cell_t **prec) {
  cell_t *elt = *prec;
  *prec = elt->suiv;
  free(elt->texte);
  free(elt);
}

void liberer_liste(cell_t **liste) {
  while (*liste) {
    supp_cell(liste);
  }
  *liste = NULL;
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
    elt->texte = (char*) malloc((strlen(message)+1)*sizeof(char));
    strcpy(elt->texte,message);
  }
  return elt;
}
