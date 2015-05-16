/*  tree.c
  Fonction de gestion de l'arbre

  -----| GESTION DU DICTIONNAIRE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include "tree.h"

tree_t *creerNoeud(char);

/*  int creerArbre(char *ch, tree_t **r)
Cree un arbre a partir d'un chaine caractre representant la notation parenthesee
et en prenant l'adresse du pointeur sur la tete de l'arbre

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
      *prec = creerNoeud(*cour);
      if (! (*prec)) {
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

/*  tree_t *creerNoeud(char v)
Cree un noeud ayant pour valeur le caractere entre

  Entrees :
    char : valeur du nouveau noeu cree
  
  Sortie :
    tree_t* : pointeur sur le nouvel element cree
*/
tree_t *creerNoeud(char v) {
  tree_t *r = (tree_t*) malloc (sizeof(tree_t));
  if (r) {
    r->lv = NULL;
    r->lh = NULL;
    r->letter = v;
  }
  return r;
}

/*  void afficherArbre(tree_t *t)
Affiche les mots contenus dans l'arbre

  Entrees :
    tree_t* : pointeur sur la tete de l'arbre
  
  Sortie :
    Aucune
*/
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

/*  void afficherPoint(tree_t *t)
Affiche la valeur d'un noeud, connaissant son adresse

  Entrees :
    tree_t* : pointeur sur le noeud
  
  Sortie :
    Aucune
*/
void afficherPoint(tree_t *t) {
  printf("%c",tolower(t->letter));
}

/*  void libererArbre(tree_t **t)
Libere la memoire occupee par l'arbre

  Entrees :
    tree_t** : adresse du pointeur sur la tete de l'arbre
  
  Sortie :
    Aucune
*/
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

void adjFils(tree_t **prec, tree_t *elt) {
  elt->lv = (*prec);
  (*prec) = elt;
}

int insererMot(tree_t **t, char *w) {
  int res = 1;
  char *cour = w;
  tree_t **arbre = t;
  tree_t *tmp;
  short int existe = 1;
  
  /* Avance dans l'arbre tant que le debut du mot y est present, sinon ajoute la premiere lettre manquante */
  while (existe && *arbre && *cour != '\0') {
    arbre = rech_prec(arbre,*cour,&existe); /* Cherche si la lettre est presente */
    if (existe) {
      arbre = &((*arbre)->lv); /* Va sur l'adresse du fils du frere */
    } else { /* Insertion de la premiere lettre manquante */
      tmp = creerNoeud(*cour);
      if (tmp) { /* L'element est correctement cree */
        adj_cell(arbre,tmp);
        arbre = &((*arbre)->lv);
      } else { /* Erreur*/
        res = 0;
      }
    }    
    cour++; /* Passe a la lettre suivante */
  }

  /* Insertion des lettres restantes selon des liens verticaux */
  while (res && *cour != '\0') {
    tmp = creerNoeud(*cour);
    if (tmp) { /* Element cree correctement */
      adjFils(arbre,tmp);
      arbre = &((*arbre)->lv); /* Passe au fils du frere */
      cour++; /* Passe a la lettre suivante */
    } else { /* Erreur */
      res = 0;
    }
  }
  return res;
}
