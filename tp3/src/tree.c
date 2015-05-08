#include "tree.h"

int creerNoeud(tree_t ** r, char);

/*  int creerArbre(char *ch, tree_t **r)
  Entrees :
    char *ch : chaine de representation de l'arbre
    tree_t **r : pointeur double de tête de l'arbre
  
  Sortie :
    int : code de retour sur la creation
*/
int creerArbre(char *ch, tree_t **r) {
  stack_t p;                    /* Pile */
  tree_t **prec = r;            /* Pointeur de parcours de l'arbre */
  tree_t *tmp;                  /* Pointeur temporaire */
  char *cour = ch;              /* Caractere courant */
  int taille = strlen(ch)/2;    /* Taille max de la pile */
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
        pop(&p,&tmp);             /* Recuperation du lien horizontal parent */
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

void afficherArbre(tree_t *t) {
  stack_t p;                    /* Pile */
  tree_t *cour = t;             /* Pointeur de parcours de l'arbre */

  if (cour != NULL && init(&p,100)) {
    do {
      while (cour != NULL) {
        push(&p,cour);               /* Sauvegarde du point courant */
        if (isupper(cour->letter)) { /* Detection fin de mot */
          dump(p,afficherPoint);     /* Affichage du mot (lecture pile) */
          printf("\n");
        }
        cour = cour->lv;             /* Deplacement sur le lien vertical */
      }
      /* On a atteint une feuille */
      while (!empty(p) && cour == NULL) {  /* Recherche du premier frere des ascendants */
        pop(&p,&cour);               /* Recuperation du lien horizontal parent */
        cour = cour->lh;             /* Deplacement sur le lien horizontal */
      }
    } while (!empty(p) || cour != NULL);
    supp(&p);
  }
}


void afficherPoint(tree_t *t) {
  printf("%c",tolower(t->letter));
}


void libererArbre(tree_t **t) {
  stack_t p;                    /* Pile */
  tree_t *cour = *t;            /* Pointeur de parcours de l'arbre */
  tree_t *tmp;

  if (cour != NULL && init(&p,100)) {
    do {
      while (cour != NULL) {
        tmp = cour;                  /* Sauvegarde du courant */
        if (cour->lh != NULL) {
          push(&p,cour->lh);         /* Sauvegarde du frere */
        }
        cour = cour->lv;             /* Deplacement sur le lien vertical */
        free(tmp);                   /* Suppression du point courant */
      }
      if(!empty(p)) {
        pop(&p,&cour);               /* Recuperation du premier lien horizontal parmi les parents */
      }
    } while (!empty(p) || cour != NULL);
    supp(&p);
    *t = NULL;
  }
}