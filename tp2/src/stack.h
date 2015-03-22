/*  stack.h
  Header

  -----| DERECURSIFICATION DE FONCTION PAR PILE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#ifndef __STACK__H
#define __STACK__H

  #include <stdio.h>
  #include <stdlib.h>

  typedef int datatype; /* permet d'utiliser des types differents avec la pile */

  typedef struct _stack_t {
    int       max;  /* nombre max d'elements dans la pile */
    int       top;  /* position de l'element en tete de pile */
    datatype *val;  /* tableau des valeurs de la pile */
  } stack_t;

  int init(stack_t *,int);
  void supp(stack_t *);
  int empty(stack_t);
  int full(stack_t);
  int pop(stack_t *, datatype *);
  int top(stack_t *, datatype *);
  int push(stack_t *, datatype);

#endif
