#include "tree.h"

int creerNoeud(tree_t ** r, char);

/*  int creerArbre(char *ch, tree_t **r)
  Entrees :
    char *ch : chaine de representation de l'arbre
    abr_t **r : pointeur double de tête de l'arbre
  
  Sortie :
    int : code de retour sur la creation
*/
int creerArbre(char *ch, tree_t **r) {
  stack_t p;                    /* Pile */
  tree_t **prec = r;                 /* Pointeur de parcours de l'arbre */
  tree_t *tmp;
  char *cour = ch;              /* Caractere courant */
  int taille = strlen(ch);      /* Taille max de la pile */
  int ret = 0;                  /* Variable de retour */

  cour++;                       /* On consomme la premiere parenthese */
  if (init(&p,taille)) {
    ret = 1;                    /* Allocation ok */
    while (ret && (!empty(p) || *cour != ')')) {   /* Aucun souci et chaine non-finie */
      if (*cour == '(') {
        push(&p,*prec);           /* Sauvegarde de l'adresse courant */
        prec = &((*prec)->lv);    /* Deplacement sur le lien vertical */
        cour++;                   /* Acceleration, passe au prochain caractere */
      } else if (*cour == ',') {
        prec = &((*prec)->lh);    /* Deplacement sur le lien horizontal */
        cour++;
      }
      if (!creerNoeud(prec,*cour)) {
        ret = 0; /* Problème allocation */
      } else {
        cour++;                   /* Passage caractere suivant */
      }
      while (ret && !empty(p) && *cour == ')') {
        pop(&p,&tmp);            /* Recuperation du lien horizontal parent */
        prec = &(tmp->lh);
        cour++;
      }
    }
    supp(&p);                     /* Liberation pile */
  }
  return ret;
}

int creerNoeud(tree_t **r, char v) {
  int res = 0;
  *r = (tree_t*) malloc (sizeof(tree_t));
  if (*r) {
    res = 1;
    (*r)->lv = NULL;
    (*r)->lh = NULL;
    (*r)->letter = v;
  }
  return res;
}

void afficherArbre(tree_t *t){
  if (t != NULL) {
    printf("%c ",t->letter);
    afficherArbre(t->lv);
    afficherArbre(t->lh);
  }
}

void afficherPoint(tree_t *t){
  printf("%c ",t->letter);
}
