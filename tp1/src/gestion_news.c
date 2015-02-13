#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gestion_news.h"

#define SIZE_BUF 118

char buf[SIZE_BUF+1];

/* -------------------------------------------------------------------- */
/* flush_stdin    Vide le buffer des caractères qui y restent           */
/*                                                                      */
/* En sortie:   le nombre de caractères vidés (sauf '\n')               */
/* -------------------------------------------------------------------- */
int flush_stdin() {
  char bin;
  int cpt = -1; /*compteur de caracteres excluant '\n'*/
  do { /*vidange buffer*/
    scanf("%c", &bin);
    ++cpt;
  } while (bin != 10);
  return cpt;
}

int charger(cell_t **liste, char *nom_fichier) {
  int ret = 1;
  FILE *fichier = fopen(nom_fichier,"r");
  int debut, fin;
  char *scan;
  cell_t *tmp;
  if (fichier) {
    ret = 0;
    while (!feof(fichier) && ret == 0 && fgets(buf,SIZE_BUF+1,fichier)) {
      /* suppression du caractère \n résiduel si le texte fait moins de 100 caractères */
      scan = strchr(buf,'\n');
      if (scan) {
        *scan = '\0';
      }
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
  time_t now = time(NULL);
  int datejour;
  struct tm t = *localtime(&now);
  datejour = (t.tm_year+1900)*10000+(t.tm_mon+1)*100+t.tm_mday;
  return datejour;
}

void afficher_message(cell_t *m) {
  printf("%s\n",m->texte);
}

void afficher_liste(cell_t *l) {
  cell_t *cour = l;
  while (cour) {
    afficher_message(cour);
    cour = cour->suiv;
  }
}

void traiter_elt_date_debut(cell_t *liste, int date, void (*fun)(cell_t *)) {
  cell_t *cour = liste;
  while (cour->debut > date) {
    cour = cour->suiv;
  }
  while (cour->debut == date) {
    fun(cour);
    cour = cour->suiv;
  }
}

void afficher_messages_date(cell_t *liste, int date) {
  traiter_elt_date_debut(liste,date,&afficher_message);
}

void afficher_messages_jour(cell_t *liste) {
  afficher_messages_date(liste,getDate());
}

void afficher_messages_motif(cell_t *liste, char *motif) {
  cell_t *cour = liste;
  while (cour) {
    if (strstr(cour->texte,motif)) {
      afficher_message(cour);
    }
    cour = cour->suiv;
  }
}

void supprimer_obsoletes(cell_t **liste) {
  int date = getDate();
  cell_t **prec = liste;
  while (*prec != NULL) {
    if ((*prec)->fin < date) {
      supp_cell(prec);
    } else {
      prec = &((*prec)->suiv);
    }
  }
}

void remplacer_date(cell_t *liste, int date, int nvdate) {
  cell_t *cour = liste;
  while (cour->debut > date) {
    cour = cour->suiv;
  }
  while (cour->debut == date) {
    cour->debut = nvdate;
  }
}
