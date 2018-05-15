
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

void enfiler(File *f, pnoeud n){
  element *nouveau = malloc(sizeof(element));
  nouveau -> noeud = n;
  nouveau -> suivant = NULL;
  if(f->premier !=NULL){
    element *courant = f->premier;
    while(courant->suivant != NULL){
      courant = courant -> suivant;
    }
    courant -> suivant = nouveau;
  }
  else {
    f->premier = nouveau;
  }
}

pnoeud defiler_min(File *f){

  if(f->premier !=NULL){

    int min = f->premier->noeud->occ;
    element *element_min = f->premier;
    element *courant = f->premier;
    element *precedent = courant;
    while(courant->suivant != NULL ){

      if(min>courant->suivant->noeud->occ){
        precedent = courant;
        min = courant->suivant->noeud->occ;
        element_min = courant->suivant;
      }
      courant = courant -> suivant;
    }
    if (precedent != element_min){
      precedent -> suivant = element_min -> suivant;
    }
    else{
      f->premier = element_min->suivant;
    }
    return element_min->noeud;
  }
  else {
    return NULL ;
  }
}



pnoeud allouer_noeud(){
  pnoeud nouveau = (pnoeud)malloc(sizeof(noeud));
  nouveau->p = 0;
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
  int cpt =0;
  while(l!=NULL){
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
    if(n->droit == NULL){
    }
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
      printf("\t");}
      printf("(%i) ",niveau);
      printf("%i, [%c] \n \n", a->occ,a->s);

      afficher_arbre(a->gauche,niveau+1);
    }
  }
  int main(void){
    liste_t l;
    liste_t l2,l3,l4,l5;
    l.nom = 'a';
    l.nb = 12;
    l.next = &l2;
    l2.nom = 'b';
    l2.nb = 15;
    l2.next = &l3;
    l3.nom = 'd';
    l3.nb = 27;
    l3.next = &l4;
    l4.nom = 'c';
    l4.nb = 40;
    l4.next = &l5;
    l5.nom = 'e';
    l5.nb = 41;
    l5.next = NULL;
    arbre a = Construire_arbre_liste(&l);
    afficher_arbre(a,0);
  }
