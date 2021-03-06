/*  list.c
  Fonctions de gestion de la liste chainee

  -----| LISTE CHAINEE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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
  elt->lh = (*prec);
  (*prec) = elt;
}

/*  cell_t ** rech_prec(cell_t **liste, char letter, short int *existe)
  Recherche le precedent d'un element dans la liste chainee

  Entrees :
    cell_t **liste : pointeur sur le pointeur du premier element de la liste chainee
    char lettre : caractere a chercher dans la liste
    short int *existe : variable en entree/sortie indiquant la présence de la lettre
      0 : absence
      1 : presence

  Sortie :
    cell_t ** : pointeur sur le pointeur de l'element precedent
*/
cell_t ** rech_prec(cell_t **liste, char letter, short int *existe) {
  cell_t **prec = liste;
  while ((*prec) && tolower((*prec)->letter) < tolower(letter)) {
    prec = &((*prec)->lh);
  }
  /* Booleen de presence     */
  /* 1 : present             */
  /* 0 : absent              */
  *existe = (*prec && tolower((*prec)->letter) == tolower(letter))?1:0;
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
  *prec = elt->lh;
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

  Entrees :
    cell_t **liste : pointeur sur le pointeur du premier element de la liste chainee
    cell_t *elt : pointeur sur l'element a inserer dans la liste chainee

  Sortie :
    Aucune
*/
void ins_cell(cell_t **liste, cell_t *elt) {
  short int existe;
  cell_t **prec = rech_prec(liste,elt->letter,&existe);
  adj_cell(prec,elt);
}

/*  node_t * creer_cell(char letter)
  Permet de creer un element de la liste chainee a partir du
  caractere donne en parametre

  Entrees :
    char letter : lettre a mettre dans l'element

  Sortie :
    node_t* : pointeur sur l'element cree
*/
node_t * creer_cell(char letter) {
  node_t *elt = (node_t*) malloc(sizeof(node_t));
  if (elt) {
    elt->letter = letter;
  }
  return elt;
}
