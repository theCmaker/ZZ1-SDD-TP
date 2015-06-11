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
  elt->next = (*prec);
  (*prec) = elt;
}

/*  cell_t ** rech_prec(cell_t **liste, int col, short int *existe)
  Recherche le precedent d'un element dans la liste chainee triee selon les colonnes

  Entrees :
    cell_t **liste : pointeur sur le pointeur du premier element de la liste chainee
    int col : indice de colonne
    short int *existe : variable en entree/sortie indiquant si la colonne est presente ou non
      0 : absence
      1 : presence

  Sortie :
    cell_t ** : pointeur sur le pointeur de l'element precedent
*/
cell_t ** rech_prec(cell_t **liste, int col, short int *existe) {
  cell_t **prec = liste;
  while ((*prec) && (*prec)->col < col) {
    prec = &((*prec)->next);
  }
  /* Booleen de presence     */
  /* 1 : present             */
  /* 0 : absent              */
  *existe = (*prec && (*prec)->col == col)?1:0;
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
  *prec = elt->next;
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
  Les colonnes sont triees par ordre croissant

  Entrees :
    cell_t **liste : pointeur sur le pointeur du premier element de la liste chainee
    cell_t *elt : pointeur sur l'element a inserer dans la liste chainee

  Sortie :
    Aucune
*/
int ins_cell(cell_t **liste, cell_t *elt) {
  short int existe;
  cell_t **prec = rech_prec(liste,elt->val,&existe);
  if (!existe) {
    adj_cell(prec,elt);
  }
  return (int) !existe;
}

/*  node_t * creer_cell(int col, int val)
  Permet de creer un element de la liste chainee a partir du numero 
  de colonne et de la valeur

  Entrees :
    int col : numero de colonne
    int val : valeur

  Sortie :
    node_t* : pointeur sur l'element cree
*/
node_t * creer_cell(int col, int val) {
  node_t *elt = (node_t*) malloc(sizeof(node_t));
  if (elt) {
    elt->val = val;
    elt->col = col;
  }
  return elt;
}
