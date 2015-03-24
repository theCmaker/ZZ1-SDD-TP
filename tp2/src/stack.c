/*  stack.c
  Fonctions de gestion de la structure de pile

  -----| DERECURSIVATION DE FONCTION PAR PILE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/
#include "stack.h"

/*  int init(stack_t *p, int n)
Fonction d'initialisation de la pile avec une taille max

  Entrees :
    *p : pointeur sur la pile
    n : taille maximum de la pile

  Sortie :
    int : code d'erreur
      1 si aucune erreur
      0 si erreur de creation de la pile
*/
int init(stack_t *p, int n) {
  int ret = 1;
  p->max = n;
  p->top = -1;
  p->val = (int*) malloc(n*sizeof(int));
  if (p->val == NULL) {
    ret = 0;
  }
  return ret;
}

/*  void supp(stack_t *p)
Fonction de suppression de la pile

  Entree :
    *p : pointeur sur la tete de la pile

  Sortie :
    Aucune
*/
void supp(stack_t *p) {
  free(p->val);
  p->top = -1; /* Empeche de depiler */
  p->max = 0; /* Empeche d'empiler */
}

/*  int empty(stack_t *p)
Teste si la pile est vide ou non

  Entree :
    p : tete de la pile

  Sortie :
    int : booleen
      0 si la pile n'est pas vide
      1 si la pile est vide
*/
int empty(stack_t p) {
  return (p.top == -1)?1:0;
}

/*  int full(stack_t p)
Teste si la pile est pleine ou non

  Entree :
    p : tete de la pile

  Sortie :
    int : booleen
      0 si la pile n'est pas pleine
      1 si la pile est pleine
*/
int full(stack_t p) {
  return (p.top == p.max-1)?1:0;
}

/*  int pop(stack_t *p, datatype *v)
Recupere le premier element de la pile (et l'enleve) et retourne un code d'erreur

  Entree :
    *p : pointeur sur la tete de la pile
    *v : pointeur sur un element du type de la pile, variable en I/O

  Sortie :
    int : code d'erreur
      0 si rien n'est retourne dans la variable v
      1 si on a recupere l'element en tete
*/
int pop(stack_t *p, datatype *v) {
  int ok = 0;
  if (!empty(*p)) {
    *v = p->val[p->top];
    ok = 1;
    p->top--;
  }
  return ok;
}

/*  int top(stack_t *p, datatype *v)
Retourne l'element en tete de la pile (sans l'enlever) et retourne un code d'erreur

  Entree :
    *p : pointeur sur la tete de la pile
    *v : pointeur sur un element du type de la pile, variable en I/O

  Sortie :
    int : code d'erreur
      0 si rien n'est retourne
      1 si on recupere l'element en tete
*/
int top(stack_t *p, datatype *v) {
  int ok = 0;
  if (!empty(*p)) {
    *v = p->val[p->top];
    ok = 1;
  }
  return ok;
}

/*  int push(stack_t *p, datatype v)
Insere un element en tete de la pile

  Entree :
    *p : pointeur sur la tete de la pile
    v : element a inserer dans la pile

  Sortie :
    int : code d'erreur
      0 si l'element n'est pas ajoute dans la pile
      1 si l'element est ajoute dans la pile
*/
int push(stack_t *p, datatype v) {
  int ok = 0;
  if (!full(*p)) {
    p->top++;
    p->val[p->top] = v;
    ok = 1;
  }
  return ok;
}
