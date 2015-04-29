/*  list.h
  Header

  -----| LISTE CHAINEE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#ifndef __LISTE_H__
#define __LISTE_H__

  #include <string.h>

  typedef struct _node_t {
    char letter;
    struct _node_t *son;
    struct _node_t *bro;
  } node_t;

  typedef struct _node_t cell_t;

  cell_t ** rech_prec(cell_t **, char, short int*);
  void supp_cell(cell_t **);
  void liberer_liste(cell_t **);
  void ins_cell(cell_t **, cell_t *);
  cell_t * creer_cell(char);

#endif
