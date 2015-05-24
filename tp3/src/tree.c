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
        ret = 0;                  /* Problème allocation */
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

/*  void afficherArbrePref(tree_t *t, char *prefixe)
Affiche les mots contenus dans l'arbre avec un prefixe donne en entre

  Entrees :
    tree_t* : pointeur sur la tete de l'arbre
    char * : prefixe a ecrire avant chaque mot de l'arbre
  
  Sortie :
    Aucune
*/
void afficherArbrePref(tree_t *t, char *prefixe) {
  stack_t p;                    /* Pile */
  tree_t *cour = t;             /* Pointeur de parcours de l'arbre */

  if (cour != NULL && init(&p,100)) {
    do {
      while (cour != NULL) {
        push(&p,cour);               /* Sauvegarde du point courant */
        if (isupper(cour->letter)) { /* Detection fin de mot */
          printf("%s", prefixe);     /* Affiche le prefixe */
          dump(p,afficherPoint);     /* Affichage du mot (lecture pile) */
          printf("\n");
        }
        cour = cour->lv;             /* Deplacement sur le lien vertical */
      }
      /* On a atteint une feuille */
      while (!empty(p) && cour == NULL) {  /* Recherche du premier frere des ascendants */
        pop(&p,&cour);               /* Recuperation du parent */
        cour = cour->lh;             /* Deplacement sur le lien horizontal */
      }
    } while (!empty(p) || cour != NULL);
    supp(&p);
  }
}

/*  void afficherArbrePref(tree_t *t)
Affiche les mots contenus dans l'arbre

  Entrees :
    tree_t* : pointeur sur la tete de l'arbre
  
  Sortie :
    Aucune
*/
void afficherArbre(tree_t *t) {
  afficherArbrePref(t, "");
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
  }
}

void adj_fils(tree_t **prec, tree_t *elt) {
  elt->lv = (*prec);
  (*prec) = elt;
}

tree_t **rech_mot(tree_t **t, char **w) {
  char *cour = *w;        /* Pointeur parcours du mot */
  tree_t **arbre = t;     /* Pointeur parcours de l'arbre */
  short int existe = 1;   /* Booleen d'existence de lettre */
  
  /* Avance dans l'arbre tant que le debut du mot y est present */
  while (existe && *arbre && !isupper(*cour)) {
    arbre = rech_prec(arbre,*cour,&existe);
    if (existe) {
      arbre = &((*arbre)->lv); /* va sur l'adresse du fils */
      cour++; /* Consommation du caractere */
    }
  }
  /* Test derniere lettre sensible a la casse pour indiquer la presence */
  if (*arbre && isupper(*cour)) {
    /* Recherche d'un hypothetique point d'insertion */
    arbre = rech_prec(arbre,*cour,&existe);
    if ((*arbre)->letter == *cour) {
      cour++;       /* Consommation du caractere */
    }
  }
  *w = cour; /* Mise a jour de la position des caracteres non encore presents dans l'arbre */

  return arbre;
}


int insererMot(tree_t **t, char *w) {
  int len;             /* Longueur du mot */
  int i;               /* Indice de parcours pour copie */
  int res = 1;         /* Code de retour */
  char *cour;          /* Copie du mot */
  tree_t *tmp;         /* Noeud temporaire de creation */
  tree_t **arbre = t;  /* Pointeur de parcours de l'arbre */

  if (*w != '\0') { /* Mot non vide */
    /* Traitement du mot */
    len = strlen(w);   /* Calcul longueur */
    cour = (char*) malloc ((len+1)*sizeof(char));
    if (cour) {        /* Allocation ok */
      i = 0;
      while (w[i+1] != '\0') {
        cour[i] = tolower(w[i]); /* Passage en minuscules */
        ++i;
      }
      cour[i] = toupper(w[i]); /* Derniere lettre majuscule */
      cour[++i] = '\0';

      /* Recherche d'un debut deja present dans l'arbre */
      arbre = rech_mot(t,&cour);
      
      if (*cour != '\0') { /* Mot non deja present dans l'arbre */
        /* Insertion dans la liste chainee horizontale */
        if (*arbre && (*arbre)->letter == tolower(*cour)) {
          /* Derniere lettre deja existante, necessite de changer la casse */
          (*arbre)->letter = *cour;  /* Passage en majuscule pour ajouter le mot */
          cour++;                    /* Consommation du dernier caractere */
        } else {
          /* Insertions necessaires */
          /* Ajout de lien horizontal */
          tmp = creerNoeud(*cour);
          if (tmp) {                 /* Noeud cree */
            adj_cell(arbre,tmp);     /* Insertion lien horizontal */
            arbre = &((*arbre)->lv); /* Pointeur sur noeud fils */
            cour++;                  /* Lettre suivante */

            /* Insertion des lettres restantes selon des liens verticaux */
            while (res && *cour != '\0') {
              tmp = creerNoeud(*cour);
              if (tmp) {                 /* Noeud cree */
                adj_fils(arbre,tmp);     /* Insertion lien vertical */
                arbre = &((*arbre)->lv); /* Pointeur sur noeud fils */
                cour++;                  /* Lettre suivante */
              } else {                   /* Noeud non cree */
                res = 0;
              }
            }
          } else {                   /* Noeud non cree */
            res = 0;
          }
        }
      }
      free(cour-len); /* Liberation a partir du pointeur sur le debut du mot */
    } else { /* Allocation ratee */
      res = 0;
    }
  }
  return res;
}

void rech_motif(tree_t **t, char *w) {
	tree_t **arbre = t;
	char *cour = w;

	arbre = rech_mot(t, &cour); /* recherche jusqu'a la fin du motif */

	afficherArbrePref(*arbre, w); /* il faudrait pouvoir push le motif dans la pile comme ca le dump affichera en entier */
}
