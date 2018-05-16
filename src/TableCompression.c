#include "Table.h"
#include "huffman.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int feuille(pnoeud a)
{
  if (a == NULL)
    return 0;
  else
  {
    if ((a->gauche == NULL) && (a->droit == NULL))
      return 1;
    else
      return 0;
  }
}

void encodage_rec(pnoeud a)
{
  if (a->gauche != NULL)
  {
    char *tempg = malloc(sizeof(char)*(strlen(a->c)+1));
		strcpy(tempg,a->c);
    strcat(tempg, "1");
    a->gauche->c = tempg;
    encodage_rec(a->gauche);
  }
  if (a->droit != NULL)
  {
		char *tempd = malloc(sizeof(char)*(strlen(a->c)+1));
		strcpy(tempd,a->c);
    strcat(tempd, "0");
    a->droit->c = tempd;
    encodage_rec(a->droit);
  }
}

void encodage(pnoeud a)
{
  if (a != NULL)
  {
    if (a->gauche != NULL)
    {
      a->gauche->c = "1";
      encodage_rec(a->gauche);
    }
    if (a->droit != NULL)
    {
      a->droit->c = "0";
      encodage_rec(a->droit);
    }
  }
}

void afficher_post_encodage(arbre a, int niveau)
{
  int i;
  if (a != NULL)
  {
    afficher_post_encodage(a->droit, niveau + 1);
    for (i = 0; i < niveau; i++)
    {
      printf("\t");
    }
    printf("(%i) ", niveau);
    if(feuille(a)){
      printf( "\"%s\" ",a->c);
    }
    printf("%i [%c]\n \n", a->occ, a->s);

    afficher_post_encodage(a->gauche, niveau + 1);
  }
}
