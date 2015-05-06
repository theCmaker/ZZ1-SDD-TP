/*  tree.h
  Header

  -----| ARBRES |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#ifndef __TREE__H
#define __TREE__H

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "list.h"
  typedef node_t tree_t;
  #include "stack.h"

  #define DEBUG 0

  int creerArbre(char *, tree_t **);
  void afficherArbre(tree_t *t);
  void afficherPoint(tree_t *t);


#endif
