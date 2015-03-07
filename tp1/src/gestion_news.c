/*  gestion_news.c
  Fonctions de gestion des news

  -----| GESTION DE NEWS PAR LISTE CHAINEE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gestion_news.h"

/* taille maximale de la chaine de caractere du message */
#define SIZE_BUF 118

char buf[SIZE_BUF+1];

/*  int charger(cell_t **liste, char *nom_fichier)
    Permet de charger les donnees d'un fichier passe en parametre
    dans une liste dont l'adresse du pointeur de tete est
    egalement passe en parametre

  Entrees :
    cell_t **liste : adresse du pointeur de tete de liste dans 
    char *nom_fichier : chemin et nom du fichier a partir duquel charger la liste

  Sortie :
    Entier indiquant un code d'erreur
      0 si aucune erreur
      1 si le fichier ne s'est pas charge
      2 si probleme d'allocation d'un element dans la liste
*/
int charger(cell_t **liste, char *nom_fichier) {
  int ret = 1;
  FILE *fichier = fopen(nom_fichier,"r");
  int debut, fin;
  char *scan;
  cell_t *tmp;
  if (fichier) {
    ret = 0;
    while (!feof(fichier) && ret == 0 && fgets(buf,SIZE_BUF+1,fichier)) {
      /* suppression du caractere \n residuel si le texte fait moins de 100 caracteres */
      scan = strchr(buf,'\n');
      if (scan) {
        *scan = '\0';
      }
      sscanf(buf,"%d %d",&debut, &fin);
      tmp = creer_cell(debut,fin,&buf[18]);
      if (tmp) {
        ins_cell(liste,tmp);
      } else {
        /* Code erreur: allocation de cellule */
        ret = 2;
      }
    }
    fclose(fichier);
  }
  return ret;
}

/*   int sauver(cell_t *liste, char *nom_fichier)
  Sauvegarde les donnees de la liste chainee dans un fichier passe
  en parametre

  Entrees :
    cell_t *liste : pointeur sur le premier element de la liste chainee
    char *nom_fichier : chemin et nom du fichier dans lequel sauvegarder
              ce fichier sera cree et effacera tout autre fichier
              du meme nom dans le repertoire specifie s'il y en a

  Sortie :
    Entier renvoyant un code d'erreur
      0 si aucune erreur
      1 si probleme de creation du fichier
*/
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

/*  int getDate()
  Retourne la date du jour au format AAAAMMJJ

  Entrees :
    Aucune

  Sortie :
    Entier representant la date du jour de la forme AAAAMMJJ
*/
int getDate() {
  time_t now = time(NULL);
  int datejour;
  struct tm t = *localtime(&now);
  datejour = (t.tm_year+1900)*10000+(t.tm_mon+1)*100+t.tm_mday;
  return datejour;
}

/*  void afficher_message(cell_t *m)
  Affiche le message d'un element de la liste chainee sous la forme
  "Debut : *debut*, Fin: *fin*, Message: *texte*"

  Entrees :
    cel_t *m : pointeur sur un element de la liste chainee

  Sortie :
    Aucune
*/
void afficher_message(cell_t *m) {
  printf("Debut: %d, Fin: %d, Message: %s\n",m->debut,m->fin,m->texte);
}

/*  void afficher_liste(cell_t *l)
  Affiche le contenu integral de la liste suivant le schema de la fonction
  afficher_message(cell_t *m)

  Entrees :
    cell_t *l : pointeur sur le premier element de la liste

  Sortie :
    Aucune
*/
void afficher_liste(cell_t *l) {
  cell_t *cour = l;
  while (cour) {
    afficher_message(cour);
    cour = cour->suiv;
  }
}

/*  void afficher_messages_date(cell_t *liste, int date)
  Affiche les messages de la liste correspondant a la date passee en parametre

  Entrees :
    cell_t *liste : pointeur sur le premier element de la liste chainee
    int date : date de debut des elements a traiter, de la forme AAAAMMJJ

  Sortie :
    Aucune
*/
void afficher_messages_date(cell_t *liste, int date) {
  cell_t *cour = liste;
  while (cour && cour->debut > date) {
    cour = cour->suiv;
  }
  while (cour && cour->debut == date) {
    afficher_message(cour);
    cour = cour->suiv;
  }
  while (cour) {
    while (cour && cour->fin >= date) {
      afficher_message(cour);
      cour = cour->suiv;
    }
    if (cour) {
      cour = cour->suiv;
    }
  }
}

/*  void afficher_messages_jour(cell_t *liste)
  Affiche les messages de la liste correspondant a la date du jour

  Entrees :
    cell_t *liste : pointeur sur le premier element de la liste chainee

  Sortie :
    Aucune
*/
void afficher_messages_jour(cell_t *liste) {
  afficher_messages_date(liste,getDate());
}

/*  void afficher_messages_motif(cell_t *liste, char *motif)
  Affiche les messages de la liste chainee correspondant a un motif
  passe en parametre

  Entrees :
    cell_t *liste : pointeur sur le premier element de la liste chainee
    char *motif : chaine de caractere representant le motif a chercher dans
            les messages de la liste

  Sortie :
    Aucune
*/
void afficher_messages_motif(cell_t *liste, char *motif) {
  cell_t *cour = liste;
  while (cour) {
    if (strstr(cour->texte,motif)) {
      afficher_message(cour);
    }
    cour = cour->suiv;
  }
}

/*  void supprimer_obsoletes(cell_t **liste)
  Supprime les messages devenus obsoletes dans la liste chainee
  Les messages sont obsoletes si leur date de fin est anterieure a la date du jour

  Entrees :
    cell_t **liste : adresse du pointeur sur le premier element de la liste chainee

  Sortie :
    Aucune
*/
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

/*  void remplacer_date(cell_t **liste, int date, int nvdate)
  Remplace la date de debut des messages ayant une date passee en parametre par une
  autre date aussi passee en parametre
  Cette fonction s'assure egalement que la liste reste triee

  Entrees :
    cell_t **liste : adresse du pointeur sur le premier element de la liste chainee
    int date : date de debut des elements a traiter, de la forme AAAAMMJJ
    int nvdate : nouvelle date de debut a assigner aux elements

  Sortie :
    Aucune
*/
void remplacer_date(cell_t **liste, int date, int nvdate) {
  cell_t *cour = *liste;
  while (cour && cour->debut > date) {
    cour = cour->suiv;
  }
  while (cour && cour->debut == date) {
    if (cour->fin >= nvdate) {
      cour->debut = nvdate;
    }
    cour = cour->suiv;
  }
  sauver(*liste,"/tmp/tmp_tp1_sdd.list");
  liberer_liste(liste);
  charger(liste,"/tmp/tmp_tp1_sdd.list");
}