#ifndef __LISTE_NEWS_H__
#define __LISTE_NEWS_H__

  typedef struct _news_t {
    int  debut;
    int  fin;
    char texte[101];
    struct _news_t *suiv;
  } news_t;

  typedef struct _news_t cell_t;

  cell_t ** rech_prec(cell_t **, int, short int*);
  void supp_cell(cell_t **);
  void ins_cell(cell_t **, cell_t *);
  cell_t * creer_cell(int, int, char *);

#endif
