#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <math.h>
#include <string.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

pnoeud allouer_noeud()
{
  pnoeud nouveau = (pnoeud)malloc(sizeof(noeud));
  nouveau->s = '\0';
  nouveau->occ = 0;
  nouveau->droit = NULL;
  nouveau->gauche = NULL;
  nouveau->p = 0;
  return nouveau;
}

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

pnoeud defiler(File *f)
{
  if (f == NULL)
  {
    return NULL;
  }
  pnoeud n;
  if (f->premier != NULL)
  {
    element *elementDefile = f->premier;
    n = elementDefile->noeud;
    f->premier = elementDefile->suivant;
    //free(elementDefile);
  }
  return n;
}

pnoeud pronfondeur_max(File *f)
{
  element *courant = f->premier;
  element *nmax = f->premier;
  while (courant != NULL)
  {
    if (courant->noeud->p > nmax->noeud->p)
    {
      nmax = courant;
      courant = courant->suivant;
    }
  }
  return nmax->noeud;
}

/*int nb_noeud_prof(File *f){
p = pronfondeur_max(&f);
int cpt = 0;
element * courant = f->premier;
while (courant!=NULL){
if(courant->noeud)
}
}
*/

pnoeud defiler_min(File *f)
{

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

        //if((courant->noeud->p>=element_min->noeud->p)||((courant->noeud->p==element_min->noeud->p) && (min > courant->suivant->noeud->occ))){
        precedent = courant;
        min = courant->suivant->noeud->occ;
        element_min = courant->suivant;
      }

      courant = courant->suivant;
    }
    if (precedent != element_min)
    {
      precedent->suivant = element_min->suivant;
    }
    else
    {
      f->premier = element_min->suivant;
    }
    return element_min->noeud;
  }
  else
  {
    return NULL;
  }
}

pnoeud defiler_min_profondeur(File *f, int prof)
{
  if (f->premier != NULL)
  {
    element *element_min = malloc(sizeof(element) * 10);
    pnoeud noeud = allouer_noeud();
    element_min->noeud = noeud;
    element_min->noeud->p = prof;
    element_min->noeud->occ = 100000000;
    element *courant = f->premier;
    element *precedent = courant;
    element *save;
    while (courant != NULL)
    {
      if ((courant->noeud->p == prof) && (element_min->noeud->occ > courant->noeud->occ + 1))
      {
        //  printf("profondeur courant %i valeur : %c, occurence %i\n",courant->noeud->p,courant->noeud->s,courant->noeud->occ);
        //if((courant->noeud->p>=element_min->noeud->p)||((courant->noeud->p==element_min->noeud->p) && (min > courant->suivant->noeud->occ))){
        save = precedent;
        element_min->noeud->occ = courant->noeud->occ;
        element_min = courant;
      }
      precedent = courant;
      courant = courant->suivant;
    }
    if (element_min->noeud->occ == 100000000)
    {
      return NULL;
    }
    if (save != element_min)
    {
      save->suivant = element_min->suivant;
    }
    else
    {
      f->premier = element_min->suivant;
    }
    return element_min->noeud;
  }
  else
  {
    return NULL;
  }
}

pnoeud defiler_recherche(File *f, pnoeud n)
{
  if (f->premier != NULL)
  {
    element *courant = f->premier;
    element *precedent = f->premier;
    while (courant != NULL)
    {
      if (courant->noeud == n)
      {
        precedent->suivant = courant->suivant;
        return n;
      }
      precedent = courant;
      courant = courant->suivant;
    }
  }
  return NULL;
}

void afficher_file(File *f)
{
  element *courant = f->premier;
  while (courant != NULL)
  {
    printf("%i\n", courant->noeud->occ);
    courant = courant->suivant;
  }
}

void afficher_arbre(arbre a, int niveau)
{
  int i;
  if (a != NULL)
  {
    afficher_arbre(a->droit, niveau + 1);
    for (i = 0; i < niveau; i++)
    {
      printf("\t");
    }
    printf("(%i) ", niveau);

    printf(" [%c] \n \n", a->s);

    afficher_arbre(a->gauche, niveau + 1);
  }
}

arbre Construire_arbre_liste(pliste_t l)
{
  int i;
  File f;
  pnoeud noeud_min1;
  pnoeud noeud_min2;
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
    n->p = 0;
    enfiler(&f, n);
  }

  for (i = 0; i < cpt - 1; i++)
  {

    n = allouer_noeud();

    //  n->gauche = defiler_min(&f);
    //  n->droit = defiler_min(&f);
    noeud_min1 = defiler_min(&f);
    int p = noeud_min1->p;
    pnoeud test = defiler_min_profondeur(&f, p);
    if (test == NULL)
    {
      noeud_min2 = defiler_min(&f);
    }
    else
    {
      noeud_min2 = test;
    }
    
    if ((noeud_min1->p) > (noeud_min2->p))
    {
      n->gauche = noeud_min1;
      n->droit = noeud_min2;
    }
    else
    {
      n->gauche = noeud_min2;
      n->droit = noeud_min1;
    }
    n->occ = n->gauche->occ + n->droit->occ;
    n->p = 1 + max((n->gauche->p), (n->droit->p));
    enfiler(&f, n);
  }
  return defiler(&f); //n
}

arbre Construire_arbre_tablongueur(char **symb, int *nbsymb, int profondeur)
{
  int m;
  int i;
  int p = 0;
  pnoeud courant;
  File *nouveaux = malloc(sizeof(File) * 256);
  nouveaux->premier = NULL;
  pnoeud *anciens = malloc(sizeof(pnoeud) * 256);
  anciens[0] = allouer_noeud();
  pnoeud premier = anciens[0];
  for (p = 1; p <= profondeur; p++)
  {
    //  afficher_arbre(premier,0);
    i = 0;
    while (anciens[i] != NULL)
    {
      anciens[i]->droit = allouer_noeud();
      enfiler(nouveaux, anciens[i]->droit);
      anciens[i]->gauche = allouer_noeud();
      enfiler(nouveaux, anciens[i]->gauche);
      i++;
    }
    for (m = 0; m < nbsymb[p]; m++)
    {
      courant = defiler(nouveaux);
      courant->s = symb[p][m];
    }

    i = 0;
    for (int j = 0; j < 256; j++)
    {
      anciens[j] = NULL;
    }
    while (nouveaux->premier != NULL)
    {
      anciens[i] = defiler(nouveaux);
      i++;
    }
  }
  return premier;
}

char **createArray(int m, int n)
{
  char **rows = malloc(m * sizeof(char *));
  for (int i = 0; i < m; ++i)
  {
    char *values = malloc(n * sizeof(char));
    rows[i] = values;
  }
  return rows;
}
