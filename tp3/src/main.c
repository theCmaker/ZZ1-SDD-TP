/*  main.c
  Fonction principale du programme, pour les tests

  -----| ARBRES |-----

  BARBESANGE Benjamin,
  PISSAVY Pierre-Loup

  ISIMA 1ere Annee, 2014-2015
*/

void test();

#include "tree.h"
int main(int argc, char *argv[]) {
  FILE *f;
  char buf[400];
  char text[400];
  tree_t *arbre = NULL;
  if (argc > 1) {
    /* Lecture de fichier de commandes */
    f = fopen(argv[1],"r");
    if (f) {
      while (!feof(f)) {
        buf[0] = '\0';
        text[0] = '\0';
        fgets(buf,400,f);
        switch (buf[0]) {
          case 'C': /* creer */
            sscanf(&buf[1],"%s",text);
            creerArbre(text,&arbre);
            break;
          case 'I': /* inserer */
            sscanf(&buf[1],"%s",text);
            insererMot(&arbre,text);
            break;
          case 'M': /* motif */
            sscanf(&buf[1],"%s",text);
            rech_motif(&arbre,text);
            break;
          case 'L': /* liberer */
            if (arbre) {
              libererArbre(&arbre);
            } else {
              printf("Liberation impossible\n");
            }
            break;
          case 'A': /* afficher */
            afficherArbre(arbre);
            break;
          case '#': /* texte */
            printf("%s",&buf[1]);
            break;
          default:
            puts("\n");
        }
      }
      if (arbre) {
        libererArbre(&arbre);
      }
      fclose(f);
    } else {
      fprintf(stderr, "Fichier invalide\n");
    }
  } else {
    /* Fonctions de tests de base */
    test();
  }
  return 0;
}

void test() {
  tree_t *monArbre = NULL;
  int i, nbMotifs = 4;
  char *motif[] = {"a","","az","x"};
  printf("##########\nDEBUT DU PROGRAMME DE TEST\n##########\n");
  
  if (creerArbre("(a(l(p(h(A))))b(r(a(v(E,O))))c(h(a(r(l(i(E))))))d(e(l(t(A(p(l(a(n(E)))))))))e(c(h(O))p(i(n(E))))g(o(l(F)))h(o(t(e(L))))i(n(d(i(A,e(N))))))",&monArbre)) {
    printf("**********\nAffichage avant insertion\n");
    afficherArbre(monArbre);

    insererMot(&monArbre,"ALPHABET");   /* Debut deja present */
    insererMot(&monArbre,"foxtrot");   /* Aucune lettre deja presente */
    insererMot(&monArbre,"echo");      /* Mot deja present */
    insererMot(&monArbre,"epi");     /* Mot inclus dans un mot deja present */
    insererMot(&monArbre,"");         /* Mot vide */
    
    printf("**********\nAffichage apres insertion\n");
    afficherArbre(monArbre);
  	
  	for (i = 0; i < nbMotifs; ++i) {
      printf("**********\nRecherche du motif \"%s\"\n", motif[i]);
      rech_motif(&monArbre, motif[i]);
  	}

    printf("**********\nInsertion dans l'arbre vide\n");
    libererArbre(&monArbre);
    insererMot(&monArbre,"alpha");

    printf("**********\nAffichage apres insertion\n");
    afficherArbre(monArbre);

    printf("**********\nLiberation de l'arbre\n");
    libererArbre(&monArbre);
    
    printf("**********\nAffichage apres liberation\n");
    afficherArbre(monArbre);

    printf("##########\nFIN DU PROGRAMME DE TEST\n##########\n");
  } else {
    fprintf(stderr, "Probleme creation arbre\n");
  }
}