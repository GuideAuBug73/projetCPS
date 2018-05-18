#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "header.h"
typedef struct _noeud{
    char s;
    char *c;
    int occ;
    int p;
    struct _noeud *droit;
    struct _noeud *gauche;
} noeud, *pnoeud;

typedef pnoeud arbre;

// liste : occurence, nom, *next
typedef struct element element;
struct element {
  pnoeud noeud;
  element *suivant;
};

typedef struct File File;
struct File {
  element *premier;
};


arbre Construire_arbre_liste(pliste_t);
void afficher_arbre(arbre,int);
void afficher_file(File*);
char **createArray(int m, int n) ;
arbre Construire_arbre_tablongueur(char** symb, int* nbsymb,int profondeur);
#endif
