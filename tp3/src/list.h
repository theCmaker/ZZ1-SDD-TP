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
  #include <ctype.h>

  typedef struct _node_t {
    char letter;
    struct _node_t *lv;
    struct _node_t *lh;
  } node_t;

  typedef node_t cell_t;

  void adj_cell(cell_t **, cell_t *);
  cell_t ** rech_prec(cell_t **, char, short int*);
  void supp_cell(cell_t **);
  void liberer_liste(cell_t **);
  void ins_cell(cell_t **, cell_t *);
  cell_t * creer_cell(char);

#endif
