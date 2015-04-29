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

  int creerArbre(char *, tree_t **);

#endif
