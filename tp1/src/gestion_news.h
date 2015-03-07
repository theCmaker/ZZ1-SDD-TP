/*  gestion_news.h
  Header

  -----| GESTION DE NEWS PAR LISTE CHAINEE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#ifndef __GESTION_NEWS_H__
#define __GESTION_NEWS_H__

  #include "liste_news.h"

  int charger(cell_t **, char *);
  int sauver(cell_t *, char *);
  int getDate();
  void afficher_messages_date(cell_t *, int);
  void afficher_message(cell_t *);
  void afficher_liste(cell_t *);
  void afficher_messages_jour(cell_t *);
  void afficher_messages_motif(cell_t *, char *);
  void supprimer_obsoletes(cell_t **);
  void remplacer_date(cell_t **, int, int);

#endif