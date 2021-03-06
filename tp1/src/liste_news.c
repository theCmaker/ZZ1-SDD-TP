/*  liste_news.c
  Fonctions de gestion de la liste chainee

  -----| GESTION DE NEWS PAR LISTE CHAINEE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "liste_news.h"

/*  void adj_cell(cell_t **prec, cell_t *elt)
  Ajoute une cellule apres un element partir d'un pointeur sur l'element
  et d'un pointeur sur le pointeur de l'element apres lequel ajouter

  Entrees :
    cell_t **prec : pointeur sur le pointeur de l'element apres lequel ajouter
    cell_t *elt : pointeur sur l'element a ajouter a la liste chainee

  Sortie :
    Aucune
*/
void adj_cell(cell_t **prec, cell_t *elt) {
  elt->suiv = (*prec);
  (*prec) = elt;
}

/*  cell_t ** rech_prec(cell_t **liste, int debut, short int *existe)
  Recherche le precedent d'un element dans la liste chainee a partir de la
  date de debut de message

  Entrees :
    cell_t **liste : pointeur sur le pointeur du premier element de la liste chainee
    int debut : date de debut de message que l'on souhaite inserer, sous la forme AAAAMMJJ
          on cherchera donc les messages dont la date est immediatement superieure
    short int *existe : variable en entre/sortie indiquant si on a ou pas de message ayant la date de debut
      0 : il n'y a pas de message avec cette date de debut
      1 : il y a au moins un message

  Sortie :
    cell_t ** : pointeur sur le pointeur de l'element precedent
*/
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

/*  void supp_cell(cell_t **prec)
  Permet de supprimer un element dans la liste chainee a partir
  de son precedent

  Entrees :
    cell_t **prec : pointeur sur le pointeur de l'element precedent l'element a supprimer

  Sortie :
    Aucune
*/
void supp_cell(cell_t **prec) {
  cell_t *elt = *prec;
  *prec = elt->suiv;
  free(elt->texte);
  free(elt);
}

/*  void liberer_liste(cell_t **liste)
  Libere les allocations memoires de la liste

  Entrees :
    cell_t **liste : pointeur sur le pointeur du premier element de la liste chainee

  Sortie :
    Aucune
*/
void liberer_liste(cell_t **liste) {
  while (*liste) {
    supp_cell(liste);
  }
  *liste = NULL;
}

/*  void ins_cell(cell_t **liste, cell_t *elt)
  Permet d'inserer une cellule a la bonne place dans la liste chainee
  Les messages sont tries par ordre decroissant des date de debut

  Entrees :
    cell_t **liste : pointeur sur le pointeur du premier element de la liste chainee
    cell_t *elt : pointeur sur l'element a inserer dans la liste chainee

  Sortie :
    Aucune
*/
void ins_cell(cell_t **liste, cell_t *elt) {
  short int existe;
  cell_t **prec = rech_prec(liste,elt->debut,&existe);
  adj_cell(prec,elt);
}

/*  news_t * creer_cell(int debut, int fin, char *message)
  Permet de creer un element de la liste chainee a partir de
  la date de debut et de fin de validite ainsi que le texte du message

  Entrees :
    int debut : date de debut de validite de message sous la forme AAAAMMJJ
    int fin : date de fin de validite de message sous la forme AAAAMMJJ
    char *message : texte du message

  Sortie :
    news_t* : pointeur sur l'element cree
*/
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