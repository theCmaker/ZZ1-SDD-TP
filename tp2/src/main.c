/*  main.c
  Fonction principale du programme, pour les tests

  -----| DERECURSIVATION DE FONCTION PAR PILE |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

#include "truc.h"
#include "stack.h"

extern int P[];

void pile_test(int);
void afficher_P();

int main(int argc, char *argv[]) {
  FILE *f;
  char buf[100];
  int i, s, n;
  if (argc > 1) {
    /* Lecture de fichier de commandes */
    f = fopen(argv[1],"r");
    if (f) {
      while (!feof(f)) {
        buf[0] = '\0';
        fgets(buf,100,f);
        switch (buf[0]) {
          case 'p': /* pile */
            sscanf(&buf[1],"%d",&n);
            pile_test(n);
            break;
          case 't': /* truc iteratif */
            afficher_P();
            sscanf(&buf[1],"%d %d", &s, &i);
            printf("Reponse: %s\n",(truc_iter(s,i))?"Vrai":"Faux");
            break;
          case 'T': /* truc recursif */
            afficher_P();
            sscanf(&buf[1],"%d %d", &s, &i);
            printf("Reponse: %s\n",(TRUC(s,i))?"Vrai":"Faux");
            break;
          case '#': /* texte */
            printf("%s",&buf[1]);
            break;
          default:
            puts("\n");
        }
      }
    } else {
      fprintf(stderr, "Fichier invalide\n");
    }
  } else {
    /* Fonctions de tests de base */
    printf("Test de pile:\n");
    pile_test(4);
    printf("Fonction recursive:\n");
    TRUC(9,1);
    printf("Fonction iterative:\n");
    truc_iter(9,1);
  }
  return 0;
}


void pile_test(int n) {
  stack_t p;
  int i = 0;
  if (init(&p,n)) {
    while (push(&p,i)) {
      printf("Empiler: %d\n",i);
      ++i;
    }
    while (pop(&p,&i)) {
      printf("Depiler: %d\n",i);
    }
    supp(&p);
  }
}

void afficher_P() {
  int i;
  printf("Tableau P : ");
  for (i = 1; i <= N; ++i) {
    printf("%d ",P[i]);
  }
  printf("\n");
}