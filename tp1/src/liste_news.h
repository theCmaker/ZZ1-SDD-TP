#ifndef __LISTE_NEWS_H__
#define __LISTE_NEWS_H__

  #include <string.h>

  typedef struct _news_t {
    int  debut;
    int  fin;
    char *texte;
    struct _news_t *suiv;
  } news_t;

  typedef struct _news_t cell_t;

  cell_t ** rech_prec(cell_t **, int, short int*);
  void supp_cell(cell_t **);
  void liberer_liste(cell_t **);
  void ins_cell(cell_t **, cell_t *);
  cell_t * creer_cell(int, int, char *);

#endif
