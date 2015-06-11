/*  main.c
  Fonction principale du programme, pour les tests

  -----| ARBRES |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include "mat.h"
#define COLUMNS 81 /* Nombre max de caracteres par ligne + 1 */

int main(int argc, char *argv[]) {
  int i, j;
  mat_t m;
  FILE *f;
  char buf[COLUMNS];
  char text[COLUMNS];
  if (argc > 1) {
    /* Lecture de fichier de commandes */
    f = fopen(argv[1],"r");
    if (f) {
      while (!feof(f)) {
        buf[0] = '\0';
        text[0] = '\0';
        fgets(buf,COLUMNS,f);
        switch (buf[0]) {
          case 'R': /* creer */
            sscanf(&buf[1],"%s",text);
            lire_matrice(text,&m);
            break;
          case 'E': /* element */
            sscanf(&buf[1],"%d %d",&i, &j);
            element(&m,i,j);
            break;
          case 'A': /* afficher */
            afficher_matrice(&m);
            break;
          case 'L': /* liberer */
            liberer_matrice(&m);
            break;
          case '#': /* texte */
            printf("%s",&buf[1]);
            break;
          default:
            puts("\n");
        }
      }
      fclose(f);
    } else {
      fprintf(stderr, "Fichier invalide\n");
    }
  } else {
    fprintf(stderr, "Merci de donner un fichier de commandes en argument\n");
  }
  return 0;
}
