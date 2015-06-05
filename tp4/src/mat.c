#include "mat.h"
int init_mat(mat_t *);

int lire_matrice(char *fichier, mat_t *m) {
  FILE *f = fopen(fichier,"r");
  int row, col, val;
  int res = 1;
  int read;
  if (init_mat(m) && f) {
     while (res && !feof(f)) {
       read = fscanf(f,"%d %d %d", &row, &col, &val);
       if (read >= 3 && inser_val(m,row,col,val)) {
         printf("Ajout effectue: li:%d, col:%d, val:%d\n",row,col,val);
       } else if (read >= 3) {
         res = 0;
       }
     }
  } else {
    res = 0;
  }
  afficher_matrice(*m);
  return res;
}

int init_mat(mat_t *m) {
  int res = 0;
  m->nbrow = 0;
  m->nbcol = 0;
  m->rows = (row_t*) malloc((MAX_ROWS+1)*sizeof(row_t));
  if (m->rows) {
    m->rows[0].row = MAX_ROWS+1;
    res = 1;
  }
  return res;
}

int rech_dich(mat_t *m, int row, short int *existe) {
  int deb, fin, mil;
  deb = 0;
  fin = m->nbrow;
  if (row < m->rows[m->nbrow].row) {
    while (deb != fin) {
      mil = (deb + fin)/2;
      if (row < m->rows[mil].row) {
        fin = mil;
      } else {
        deb = mil + 1;
      }
    }
  }
  *existe = (m->rows[deb].row == row);
  return deb;
}

void decal_rows(mat_t *m, int r, int d) {
  int i;
  for (i = m->nbrow; i >= r; i-=1) {
    m->rows[i+d] = m->rows[i];
  }
}

void inser_row(mat_t *m, int r, int row) {
  decal_rows(m,r,1);
  m->nbrow++;
  m->rows[r].row = row;
  m->rows[r].cols = NULL;
}

int inser_val(mat_t *m, int row, int col, int val) {
  short int existe;
  int res = 1;
  cell_t *c;
  int r = rech_dich(m,row,&existe);  /* Recherche dichotomique */
  if (!existe) {
    /*r++;*/                 /* Passe sur le rang de la ligne a inserer */
    inser_row(m,r,row);  /* Insere une ligne au rang r */
  }
  c = creer_cell(col,val);
  if (col > m->nbcol) {
    m->nbcol = col;
  }
  if (c) {
    ins_cell (&(m->rows[r].cols),c);
  } else {
    res = 0;
  }
  return res;
}

int element(mat_t m, int i, int j) {
  int elt = 0;
  cell_t **prec;
  short int existe;
  int r = rech_dich(&m,i,&existe);
  if (existe) {
    prec = rech_prec(&(m.rows[r].cols),j,&existe);
    if (existe) {
      elt = (*prec)->next->val;
    }
  }
  return elt;
}

void afficher_matrice(mat_t m) {
  int i, j;
  int ligne_cour = 0;
  cell_t *col_cour;
  int max_col = m.nbcol;
  for (i = 1; i <= m.rows[m.nbrow-1].row; ++i) {
    j = 1;
    if (m.rows[ligne_cour].row == i) {
      col_cour = m.rows[ligne_cour].cols;
      while (col_cour && j <= max_col) {
        if (col_cour->col == j) {
          printf("%d\t",col_cour->val);
          col_cour = col_cour->next;
        } else {
          printf("0\t");
        }
        j++;
      }
      ligne_cour++;
    }
    while (j <= max_col) {
      printf("0\t");
      j++;
    }
    printf("\n");
  }
}
