//Recupération des valeurs de longueur de l'en-tête
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "decompression.h"
#include "huffman.h"
#define max(a, b) ((a) > (b) ? (a) : (b))

/*
char **createArray(int m, int n) {
>>>>>>> Stashed changes
    char **rows = malloc(m * sizeof(char *));
    for (int i = 0; i < m; ++i) {
        char *values = malloc(n * sizeof(char));
        rows[i] = values;
    }
    return rows;
}*/

enTete_t lectureTableLongueur(char *fichier)
{
  enTete_t entete;
  FILE *f;
  int nombre;
  int longueur = 0;
  char buffer;
  int profondeur = 0;
  int tete[256];
  for (int i = 0; i < 256; i++)
  {
    tete[i] = 0;
  }
  f = fopen(fichier, "r");
  fscanf(f, "%d", &nombre);
  fscanf(f, "%c", &buffer);
  entete.nombreSymboles = nombre;
  for (int i = 0; i < 256; i++)
  {
    fscanf(f, "%d", &longueur);
    fscanf(f, "%c", &buffer);
    tete[i] = longueur;
    printf("%d",tete[i]);
  }
  printf("\n");
  entete.index = ftell(f);
  fclose(f);
  for (int i = 0; i < 256; i++)
  {
    profondeur = max(tete[i], profondeur);
  }
  entete.profondeur = profondeur;
  char **Symb = createArray(profondeur + 1, 256);
  int *NbSymb = malloc(sizeof(int) * profondeur + 1);
  for(int i = 0 ; i < profondeur + 1; i++){
    NbSymb[i] = 0;
  }
  int k = 0;
  longueur = 0;
  while (longueur <= profondeur)
  {
    Symb[longueur][0]='\0';
    for (int i = 0; i < 256; i++)
    {
      if (tete[i] == longueur)
      {
        NbSymb[longueur]++;
        Symb[longueur][k] = (char)i;
        Symb[longueur][k+1]='\0';
        k++;
      }
    }
    longueur++;
    k = 0;
  }
  entete.NbSymb = NbSymb;
  entete.Symb = Symb;
  return entete;
}

char *recupData(int offset, char *fichier, enTete_t tete)
{
  FILE *f = NULL;
  char carac = -1;
  int compt = 0;
  f = fopen(fichier, "r");
  for (int i = 0; i < offset + 1; i++)
  {
    fscanf(f, "%c", &carac);
  }
  if (f != NULL)
  {
    while (!feof(f))
    {
      fscanf(f, "%c", &carac);
      compt++;
    }
  }

  fclose(f);
  f = fopen(fichier, "r");
  for (int i = 0; i < offset + 1; i++)
  {
    fscanf(f, "%c", &carac);
  }
  //fseek(f,offset+2,SEEK_SET);
  char *data = malloc(sizeof(char) * compt);
  strcpy(data, "");
  if (f != NULL)
  {
    int i = 0;
    while (!feof(f))
    {
      fscanf(f, "%c", &carac);
      data[i] = carac;
      i++;
    }
  }
  else
  {
    printf("Ouverture de fichier impossible\n");
  }
  return data;
}

char *decompression_final(char *tab, arbre a, int nbmots)
{
  int cmpt = 0;
  pnoeud x = a;
  char *message = malloc(sizeof(char) * nbmots);
  int k = 0;
  for (int i = 0; i < nbmots; i++)
  {
    while (x->gauche != NULL && x->droit != NULL)
    {
      if (tab[k] == '0')
      {
        cmpt++;
        x = x->droit;
      }
      else if (tab[k] == '1')
      {
        cmpt++;
        x = x->gauche;
      }
      k++;
    }
    printf("%c\n", x->s);
    message[i] = x->s;
    x = a;
  }
  return message;
}

/*
int main(int argc, char *argv){
  enTete_t entetes;
  entetes = lectureTableLongueur("../exemple/compression.pen");
  printf("Nombre de symbole : %d\n",entetes.nombreSymboles);
  printf("Profondeur : %d\n", entetes.profondeur);
  printf("Tableau 1 :");
  for(int i = 0 ; i < 10 ; i++){
    printf("%d ",entetes.NbSymb[i]);
  }
  printf("\nTableau 2 :\n");
  for(int i = 1; i < 10 ; i++){
    for(int j = 0 ; j<strlen(entetes.Symb[i]) ; j++ ){
      printf("%c ",entetes.Symb[i][j]);
    }
    printf("test\n");
  }
  return 0;
}
*/
