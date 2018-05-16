#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <math.h>
#include <string.h>

#define max(a,b) ((a)>(b)?(a):(b))
int convert_vers_dec(unsigned int taille, char tab[taille])
{
  int result = 0;
  for (int i = 0;i < taille;i++){
    if(tab[i] == '1'){
      result += pow(2,i);
    }
  }
  return result;
}

void parcours_largeur(arbre a, int level, pdoublet tab, int cpt)
{

  if (a == NULL)
  return;
  if (level == 0)
  {
    if(a->gauche == NULL && a->droit == NULL){
      while(tab[cpt].symb != 0){
        cpt++;
      }
      tab[cpt].symb = a->s;
      tab[cpt].code = convert_vers_dec(strlen(a->c),a->c);
    }
  }
  else if (level > 0)
  {
    parcours_largeur(a->droit, level - 1,tab,cpt);
    parcours_largeur(a->gauche, level - 1,tab,cpt);

  }
}

int hauteur_arbre (arbre a){
  if(a == NULL){
    return 0;
  }
  return 1 + max(hauteur_arbre(a->gauche),hauteur_arbre(a->droit));
}

pdoublet * tableau_code(arbre a){
  pdoublet * tabdetab;
  int h = hauteur_arbre(a);
  for(int i = 0; i <= h;i++){
    pdoublet tab = malloc(sizeof(doublet) *256);
    parcours_largeur(a,i,tab,0);
    tabdetab[i] = tab;
    free(tab);
  }
  return tabdetab;
}

void tri(pdoublet T,int taille){
  char Clef;
  int i, j;

  for (j = 1; j < taille; j++) {
    i = j - 1;
    Clef = T[j].symb;
    while ((i >= 0) && (T[i].symb >= Clef)) {
      T[i + 1].symb = T[i].symb;
      i = i - 1;
    }
    T[i + 1].symb = Clef;
  }

}

pdoublet *tableau_change(pdoublet * tabdetab,int taille){
  int i; int j=0;
  for(i=0;i<taille;i++){
    tri(tabdetab[i],256);
  }
}
