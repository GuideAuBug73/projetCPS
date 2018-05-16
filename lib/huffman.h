#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "header.h"
typedef struct _noeud{
    char s;
    char *c;
    int occ;
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


typedef struct _doublet{
  char symb;
  int code;
}doublet, *pdoublet;

arbre Construire_arbre_liste(pliste_t);
void afficher_arbre(arbre,int);
void afficher_file(File*);
#endif
