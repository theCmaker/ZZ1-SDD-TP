/*  mat.c
  Fonctions de gestion de matrice

  -----| MATRICE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include "mat.h"
int inser_val(mat_t *m, int row, int col, int val);

/*  int init_mat(mat_t *m)
  Initialise la matrice en allouant le tableau de structures correspondant aux
  lignes

  Entrees :
    *m : adresse de la structure de matrice a initialiser

  Sortie :
    res : booleen indiquant la reussite de l'initialisation (1: OK, 0: erreur)
*/
int init_mat(mat_t *m) {
  int res = 0;  /* Retour */
  m->nbrow = 0; /* Nb de lignes */
  m->nbcol = 0; /* Nb de colonnes */
  m->rows = (row_t*) malloc((MAX_ROWS+1)*sizeof(row_t));
  if (m->rows) {  /* Allocation reussie */
    m->rows[0].row = MAX_ROWS+1; /* Initialisation de la valeur max pour la dichotomie */
    res = 1;    /* Mission accomplie */
  }
  return res;
}

/*  int lire_matrice(char *fichier, mat_t *m)
  Lit un fichier représentant une matrice et inscrit le contenu dans une structure
  de matrice

  Entrees :
    *fichier : chaine de caracteres: nom du fichier
    *m       : adresse de la structure de matrice a ecrire

  Sortie :
    res : booleen indiquant la reussite de la lecture (1: OK, 0: erreur)
*/
int lire_matrice(char *fichier, mat_t *m) {
  FILE *f = fopen(fichier,"r");
  int row, col, val;  /* Valeurs qui seront lues */
  int res = 1;        /* Valeur de retour */
  int read;           /* Indique le nombre de valeurs lues */
  if (init_mat(m) && f) { /* Initialisation et ouverture flux OK */
     while (res && !feof(f)) {  /* Fichier non fini et pas d'erreur */
       read = 0;      /* Cpt de valeurs car fscanf n'aime pas les fins de fichier */
       read = fscanf(f,"%d %d %d", &row, &col, &val); /* Lecture */
       if (read >= 3 && !inser_val(m,row,col,val)) {  /* Lecture ou insertion non reussies */
         res = 0; /* Erreur */
       }
     }
     fclose(f);       /* Fermeture du flux */
  } else {            /* Erreur */
    res = 0;
  }
  return res;
}

/*  int rech_dich(mat_t *m, int row, short int *existe)
  Realise une recherche dichotomique sur les lignes pour trouver le rang d'insertion.

  Entrees :
    *m      : adresse de la matrice
    row     : indice de la ligne a rechercher
    *existe : booleen de presence a modifier

  Sortie :
    deb : rang d'insertion ou de position de la ligne row
*/
int rech_dich(mat_t *m, int row, short int *existe) {
  int deb, fin, mil; /* Indices locaux */
  deb = 0;           /* Recherche entre le debut */
  fin = m->nbrow;    /* Et la fin */
  while (deb != fin) {    /* Tant qu'il reste plus d'un élément dans le 'sous-tableau' */
    mil = (deb + fin)/2;  /* Rang du milieu */
    if (row <= m->rows[mil].row) {  /* Comparaison avec la valeur centrale */
      fin = mil;      /* Inférieure */
    } else {
      deb = mil + 1;  /* Supérieure */
    }
  }
  *existe = (m->rows[deb].row == row); /* Test existence */
  return deb;
}

/*  void decal_rows(mat_t *m, int r)
  Decale les lignes d'une matrice en vue d'une insertion.

  Entrees :
    *m : adresse de la matrice
    r  : rang a partir duquel decaler

  Sortie :
    Aucune
*/
void decal_rows(mat_t *m, int r) {
  int i;  /* Indice de boucle */
  for (i = m->nbrow; i >= r; i-=1) {
    m->rows[i+1] = m->rows[i]; /* Recopie */
  }
}

/*  void inser_row(mat_t *m, int r, int row)
  Insere une ligne row dans une matrice m en position r

  Entrees :
    *m : adresse de la matrice
    r  : rang d'insertion
    row: indice de la ligne a inserer

  Sortie :
    Aucune
*/
void inser_row(mat_t *m, int r, int row) {
  decal_rows(m,r);  /* Decalage vers la droite */
  m->nbrow++;       /* Ajout d'une ligne */
  m->rows[r].row = row;   /* Insertion de la ligne */
  m->rows[r].cols = NULL; /* Initialisation pointeur de colonnes */
}

/*  int inser_val(mat_t *m, int row, int col, int val)
  Insere une valeur val dans une matrice m en ligne row et colonne col

  Entrees :
    *m : adresse de la matrice
    row: numero de ligne
    col: numero de colonne
    val: valeur a inserer

  Sortie :
    res: booleen de retour (1: reussite, 0: echec)
*/
int inser_val(mat_t *m, int row, int col, int val) {
  short int existe; /* Booleen pour les tests d'existence */
  int res = 1;      /* Valeur de retour */
  cell_t *c;        
  int r = rech_dich(m,row,&existe);  /* Recherche ligne d'insertion */
  if (!existe) {
    inser_row(m,r,row);    /* Ajout d'une ligne si necessaire */
  }
  c = creer_cell(col,val); /* Creation de la cellule*/
  if (c) {  /* Creation reussie */
    ins_cell (&(m->rows[r].cols),c);  /* Ajout de la valeur */
    if (col > m->nbcol) {
      m->nbcol = col;     /* Actualisation du nombre maximal de colonnes */
    }
  } else { /* Erreur memoire */
    res = 0;
  }
  return res;
}

/*  int element(mat_t *m, int i, int j)
  Retourne M(i,j)

  Entrees :
    *m : adresse de la matrice
    i  : indice de ligne
    j  : indice de colonne

  Sortie :
    elt : valeur de M(i,j)
*/
int element(mat_t *m, int i, int j) {
  int elt = 0;    /* Valeur par defaut (matrice creuse!) */
  cell_t **prec;  /* Pointeur de recherche */ 
  int r;          /* Rang de la ligne dans la matrice creuse */
  short int existe;  /* Booleen d'existence */

  if (i < m->rows[m->nbrow].row && j < m->nbcol) { /* Element dans la matrice */
    r = rech_dich(m,i,&existe); /* Recherche de la ligne */
    if (existe) {   /* Ligne presente */
      prec = rech_prec(&(m->rows[r].cols),j,&existe);   /* Recherche colonne */
      if (existe) { /* Colonne présente */
        elt = (*prec)->val; /* Copie valeur */
      }
    }
  }
  return elt;
}

/*  void afficher_matrice(mat_t *m)
  Affiche la matrice m

  Entrees :
    *m : adresse de la matrice (evite de recopier toute 
          la structure majeure lors de l'appel)

  Sortie :
    Aucune
*/
void afficher_matrice(mat_t *m) {
  int i, j;           /* Ligne reelle / colonne reelle */
  int ligne_cour = 0; /* Ligne dans la structure */
  cell_t *col_cour;   /* Pointeur de parcours des colonnes de la structure */
  int max_col = m->nbcol; /* Nombre de colonnes reelles */
  int max_row = m->rows[m->nbrow-1].row; /* Nombre de lignes reelles */

  for (i = 1; i <= max_row; ++i) {  /* Pour chaque ligne de la matrice */
    j = 1;                          /* Depart sur la colonne 1 */
    if (m->rows[ligne_cour].row == i) {    /* Ligne presente dans la structure */
      col_cour = m->rows[ligne_cour].cols; /* Premiere colonne */
      while (col_cour && j <= max_col) {    /* Pour toutes les colonnes jusqu'a la fin de la liste */
        if (col_cour->col == j) {       /* Colonne presente dans la structure */
          printf("%d\t",col_cour->val);
          col_cour = col_cour->next;    /* Colonne suivante (struct) */
        } else {                        /* Colonne absente (i.e. 0) */
          printf("0\t");            
        }
        j++;                            /* Colonne suivante (reelle) */
      }
      ligne_cour++;                     /* Ligne de la structure traitee */
    }
    while (j <= max_col) {              /* Complete la ligne courante */
      printf("0\t");
      j++;                              /* Colonne suivante (reelle) */
    }
    printf("\n");                       /* Ligne i traitee */
  }
}

/*  void liberer_matrice(mat_t *m)
  Libère la mémoire allouée pour la matrice m

  Entrees :
    *m : adresse de la matrice

  Sortie :
    Aucune
*/
void liberer_matrice(mat_t *m){
  int i;  /* Lignes */
  for (i = 0; i < m->nbrow; i++) { /* Suppression de chaque ligne */
    liberer_liste(&(m->rows[i].cols)); /* Suppression des colonnes */
  }
  free(m->rows);    /* Suppression du tableau de lignes */
  m->rows = NULL;   
  m->nbrow = 0;     /* Actualisation lignes */
  m->nbcol = 0;     /* Actualisation colonnes */
}
