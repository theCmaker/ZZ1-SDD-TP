#include "tree.h"

int creerNoeud(tree_t ** r, char);

/*  int lecture_abr(char * ch, abr_t ** r)
  Entrees :
    char * ch : chaine de representation de l'arbre
    abr_t ** r : pointeur de tête de l'arbre
  
  Sortie :
    int : code d'reteur sur la creation
*/
int creerArbre(char * ch, tree_t **r) {
    stack_t p;                    /* Allocation du pointeur de la pile */
    tree_t **cour = r;                     /* Element de parcours */
    int cpt = 0;                       /* Compteur de parcours de la chaine */
    int taille = strlen(ch);                 /* Taille max de la pile */
    int ret = 0;                       /* erreur ou non, sera le retour de la fonction */

    ret = init(&p,taille); /* Initialisation de la pile */

    if (ret == 0) { /* Pile mal initialisee */
        printf("** reteur de creation de la pile **\n\n");
    } else { /* On va traiter la chaine */
        cpt++; /* Avance dans la chaine car le premier caractere est forcement une parenthese ouvrante */
      while (ch[cpt] != ')' || !empty(p)) { /* Parcours de la chaine */
        switch(ch[cpt]) { /* Teste le caractere courant de la chaine */
          case '(': /* Creation d'un lien vertical */
            push(&p,cour);         /* Empile l'adresse de l'element courant pour y revenir */
            cpt++;             /* Caractere suivant, donc nouvelle racine */
            cour = &((*cour)->lv);     /* On va sur le fils de l'element qu'on traitait avant */
            creerNoeud(cour, ch[cpt]);  /* Cree l'element fils */
            break;
          case ')': /* Il faut remonter sur les liens horizontaux */
            if (!empty(p)) { /* ou ch[cpt + 1] != '\0' pour le dernier cas ? */
              pop(&p, &cour); /* Depile l'adresse de l'element et on passera au suivant */
            }
            break;
          case ',': /* Il faut aller lire le reste */
            cpt++;
          default: /* On a un lien horizontal a ajouter */
            cour = &((*cour)->lh);    /* On passe au frere */
            creerNoeud(cour, ch[cpt]);  /* Cree le nouveau lien */
        }
        cpt++; /* Caractere suivant */
      }
    }
    supp(&p); /* Suppression de la pile */
    return ret;
}


int creerArbre_2(char *ch, tree_t **r) {
  stack_t p;                    /* Pile */
  tree_t **prec = r;            /* Pointeur de parcours de l'arbre */
  char *cour = ch;              /* Caractere courant */
  int taille = strlen(ch);      /* Taille max de la pile */
  int ret = 0;                  /* Variable de retour */

  cour++;                       /* On consomme la premiere parenthese */
  if (init(&p,taille)) {
    ret = 1;                    /* Allocation ok */
    while (ret && (!empty(p) || *cour != ')')) {   /* Aucun souci et chaine non-finie */
      switch (*cour) {  
        case '(':               /* Creation lien vertical */
          push(&p,&((*prec)->lh));  /* Sauvegarde de l'adresse lien horizontal */
          prec = &((*prec)->lv);    /* Deplacement sur le lien vertical */
          break;
        case ',':               /* Preparation ajout frere */
          prec = &((*prec)->lh);    /* Deplacement sur le lien horizontal */
          break;
        case ')':               /* Retour au niveau superieur */
          pop(&p,&prec);            /* Recuperation du lien horizontal parent */
          break;
        default:                /* Ajout d'un noeud */
          if (!creerNoeud(prec,*cour)) {
            ret = 0; /* Problème allocation */
          }
      }
      cour++;                   /* Passage caractere suivant */
    }
    supp(&p);                   /* Liberation pile */
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
