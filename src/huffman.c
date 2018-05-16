#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <math.h>
#include <string.h>


void enfiler(File *f, pnoeud n)
{
  element *nouveau = malloc(sizeof(element));
  nouveau->noeud = n;
  nouveau->suivant = NULL;
  if (f->premier != NULL)
  {
    element *courant = f->premier;
    while (courant->suivant != NULL)
    {
      courant = courant->suivant;
    }
    courant->suivant = nouveau;
  }
  else
  {
    f->premier = nouveau;
  }
}

pnoeud defiler(File *f){
  if(f == NULL){
    return NULL;
  }
  pnoeud n;
  if(f->premier != NULL){
    element *elementDefile = f->premier;
    n = elementDefile->noeud;
    f->premier = elementDefile->suivant;
    free(elementDefile);
  }
  return n;
}

pnoeud defiler_min(File *f){

  if (f->premier != NULL)
  {

    int min = f->premier->noeud->occ;
    element *element_min = f->premier;
    element *courant = f->premier;
    element *precedent = courant;
    while (courant->suivant != NULL)
    {

      if (min > courant->suivant->noeud->occ)
      {
        precedent = courant;
        min = courant->suivant->noeud->occ;
        element_min = courant->suivant;
      }
      courant = courant->suivant;
    }
    if (precedent != element_min){
      precedent -> suivant = element_min -> suivant;
    }
    else{
      f->premier = element_min->suivant;
    }
    return element_min->noeud;
  }
  else
  {
    return NULL;
  }
}

pnoeud allouer_noeud()
{
  pnoeud nouveau = (pnoeud)malloc(sizeof(noeud));
  nouveau->s = '\0';
  nouveau->occ = 0;
  nouveau->droit = NULL;
  nouveau->gauche = NULL;
  return nouveau;
}

void afficher_file(File *f){
  element *courant = f->premier;
  while(courant!=NULL){
    printf("%i\n", courant->noeud->occ);
    courant = courant->suivant;
  }
}

arbre Construire_arbre_liste(pliste_t l){
  int i;
  File f;
  f.premier = NULL;
  pnoeud n;
  int cpt = 0;
  while (l != NULL)
  {
    cpt++;
    n = allouer_noeud();
    n->s = l->nom;
    n->occ = l->nb;
    l = l->next;
    enfiler(&f,n);
  }

  for(i=0;i<cpt-1;i++){

    n = allouer_noeud();
    n->gauche = defiler_min(&f);
    n->droit = defiler_min(&f);
    n->occ = n->gauche->occ + n->droit->occ;
    enfiler(&f,n);
  }
  return defiler_min(&f); //n
}

void afficher_arbre(arbre a,int niveau){
  int i;
  if(a!=NULL){
    afficher_arbre(a->droit,niveau+1);
    for(i=0;i<niveau;i++){
      printf("\t");
    }
    printf("(%i) ",niveau);

    printf("%i, [%c] \n \n", a->occ,a->s);

    afficher_arbre(a->gauche,niveau+1);
  }
}



arbre Construire_arbre_tablongueur(char** symb, int* nbsymb,int profondeur){
  int m;
  int i ;
  int p =0;
  int c =0;
  char s;
  int k = 0;
  pnoeud courant;
  File *nouveaux = malloc(sizeof(File)*256);
  pnoeud *anciens = malloc(sizeof(pnoeud)*256);
  anciens[0] = allouer_noeud();
  pnoeud premier = anciens[0];
  for(p =1;p<=profondeur;p++){
  //  for(i=0;i<strlen(anciens);i++){
    i = 0;
    while(anciens[i]!=NULL){
      anciens[i]->droit = allouer_noeud();
      enfiler(nouveaux,anciens[i]->droit);
      anciens[i]->gauche = allouer_noeud();
      enfiler(nouveaux,anciens[i]->gauche);
      i++;
    }
    for(m = 0; m <nbsymb[p];m++){
      courant = defiler(nouveaux);
      courant->s = symb[p][m];
    }
    i = 0 ;
    while(nouveaux->premier!=NULL){
      anciens[i] = defiler(nouveaux);
      i++ ;
    }
  }
}
