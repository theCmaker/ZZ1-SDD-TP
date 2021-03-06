/*  mat.h
  Header

  -----| MATRICE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#ifndef __MAT_H__
#define __MAT_H__
  #include <stdio.h>
  #include <stdlib.h>
  #include "list.h"

  #define MAX_ROWS 50

  typedef struct _row_t {
    int row;      /* Numero de ligne */
    cell_t *cols; /* Liste chainee des colonnes */
  } row_t;

  typedef struct _mat_t {
    int nbrow;   /* Nombre de lignes */
    int nbcol;   /* Nombre de colonnes */
    row_t *rows; /* Lignes */
  } mat_t;

  int init_mat(mat_t *);
  int lire_matrice(char *, mat_t*);
  void afficher_matrice(mat_t *);
  int element(mat_t *, int, int);
  void liberer_matrice(mat_t *);


#endif

