/*  tree.h
  Header

  -----| GESTION DU DICTIONNAIRE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#ifndef __TREE__H
#define __TREE__H

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <ctype.h>
  #include "list.h"
  typedef node_t tree_t;
  #include "stack.h"

  #define DEBUG 0
  #define STACKSIZE 200
  
  int  creerArbre(char *, tree_t **);
  void libererArbre(tree_t **);
  void afficherArbrePref(tree_t *, char *);
  void afficherArbre(tree_t *);
  void afficherPoint(tree_t *);
  int  insererMot(tree_t **, char *);
  void rech_motif(tree_t **, char *);

#endif
