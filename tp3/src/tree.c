#include "tree.h"
#include "stack.h"

int creerNoeud(tree_t ** r, char);

/*  int lecture_abr(char * ch, abr_t ** r)
  Entrees :
    char * ch : chaine de representation de l'arbre
    abr_t ** r : pointeur de tête de l'arbre
  
  Sortie :
    int : code d'reteur sur la creation
*/
int creerArbre(char * ch, tree_t **r) {
    stack_t *p = (stack_t*)malloc(1*sizeof(stack_t));   //Allocation du pointeur de la pile
    tree_t **cour = r;                     //Element de parcours
    int cpt = 0;                       //Compteur de parcours de la chaine
    int taille = strlen(ch);                 //Taille max de la pile
    int ret = 0;                       //erreur ou non, sera le retour de la fonction

    ret = init(p,taille); //Initialisation de la pile

    if (ret == 0) { //Pile mal initialisee
        printf("** reteur de creation de la pile **\n\n");
    } else { //On va traiter la chaine
        cpt++; //Avance dans la chaine car le premier caractere est forcement une parenthese ouvrante

        if (ch[cpt] != ')') { //Arbre non vide
            creerNoeud(cour, ch[cpt]);  //Creation de la premiere racine
            cpt++;             //Passe au caractere suivant

      while ((ch[cpt] != '\0') && (!ret)) { //Parcours de la chaine
        switch(ch[cpt]) { //Teste le caractere courant de la chaine
          case '(': //Creation d'un lien vertical
            push(p,cour);         //Empile l'adresse de l'element courant pour y revenir
            cpt++;             //Caractere suivant, donc nouvelle racine
            cour = &((*cour)->son);     //On va sur le fils de l'element qu'on traitait avant
            creerNoeud(cour, ch[cpt]);  //Cree l'element fils
            break;
          case ')': //Il faut remonter sur les liens horizontaux
            if (!empty(*p)) { ///ou ch[cpt + 1] != '\0' pour le dernier cas ?
              pop(p, &cour); //Depile l'adresse de l'element et on passera au suivant
            }
            break;
          case ',': //Il faut aller lire le reste
            //On ne fait rien car on passera directement au caractere suivant
            break;
          default: //On a un lien horizontal a ajouter
            cour = &((*cour)->bro);    //On passe au frere
            creerNoeud(cour, ch[cpt]);  //Cree le nouveau lien
        }
        cpt++; //Caractere suivant
      }
    }
    }
    supp(p); //Suppression de la pile
    return ret;
}

int creerNoeud(tree_t ** r, char v) {
  /**
    Va creer un nouvel element avec une valeur v
    a l'adresse r
  **/
  return 0;
}
