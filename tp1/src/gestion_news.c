#include <stdio.h>
#include <stdlib.h>
#include "gestion_news.h"

#define SIZE_BUF 128

char buf[SIZE_BUF];

int charger(cell_t **liste, char *nom_fichier) {
  int ret = 1;
  FILE *fichier = fopen(nom_fichier,"r");
  int debut, fin;
  cell_t *tmp;
  if (fichier) {
    ret = 0;
    while (!feof(fichier) && ret == 0) {
      fgets(buf,SIZE_BUF,fichier);
      /*TODO: GESTION DE LA CHAINE DE CARACTERES (CHAINE COURTE) */
      buf[118] = '\0';
      sscanf(buf,"%d %d",&debut, &fin);
      tmp = creer_cell(debut,fin,&buf[18]);
      if (tmp) {
        ins_cell(liste,tmp);
      } else {
        ret = 2;
      }
    }
    fclose(fichier);
  }
  return ret;
}

int sauver(cell_t *liste, char *nom_fichier) {
  int ret = 1;
  cell_t *cour = liste;
  FILE *fichier = fopen(nom_fichier,"w+");
  if (fichier) {
    while (cour) {
      fprintf(fichier,"%d %d %s\n",cour->debut,cour->fin,cour->texte);
      cour = cour->suiv;
    }
    fclose(fichier);
    ret = 0;
  }
  return ret;
}

int getDate() {
  int date;
  /* TODO: RECUPERER DANS UNE CHAINE DE CARACTERES */
  /* system("date +%Y%m%d");
  sscanf(,"%d",&date); */
  return date;
}

void afficher_messages_date(cell_t *, int);
void afficher_messages_motif(cell_t *, char *);
void supprimer_obsoletes(cell_t **, int);
void remplacer_date(cell_t *, int, int);
