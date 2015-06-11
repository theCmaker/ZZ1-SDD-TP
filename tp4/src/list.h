/*  list.h
  Header

  -----| LISTE CHAINEE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#ifndef __LISTE_H__
#define __LISTE_H__

  typedef struct _node_t {
    int col;               /* Numero de colonne */
    int val;               /* Valeur */
    struct _node_t *next;  /* Colonne suivante */
  } node_t;

  typedef node_t cell_t;

  cell_t ** rech_prec(cell_t **, int, short int*);
  void supp_cell(cell_t **);
  void liberer_liste(cell_t **);
  int ins_cell(cell_t **, cell_t *);
  cell_t * creer_cell(int, int);

#endif
