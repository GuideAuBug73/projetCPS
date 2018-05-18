//Recupération des valeurs de longueur de l'en-tête
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
  FILE *f = NULL;
  int nombre = 1, index=0;
  int longueur = -1;
  char buffer=0;
  int i = 1;
  int profondeur = 0;
  //longueur inferieur a 10
  int *NbSymb = malloc(9 * sizeof(int));
  char **Symb = createArray(10, 512);
  for (int i = 0; i < 9; i++)
  {
    NbSymb[i] = 0;
  }
  entete.NbSymb = NbSymb;
  f = fopen(fichier, "r");
  //calcul premier tableau tab[0] correspond au niveau 1
  if (f != NULL)
  {
    //recupération du nobre de nombre de symboles
    fscanf(f, "%d", &nombre);
    fscanf(f, "%c", &buffer);
    entete.nombreSymboles = nombre;
    //calcul profondeur + premier tableau
    longueur = -1;
    profondeur = longueur;
    fscanf(f, "%d", &longueur);
    fscanf(f, "%c", &buffer);
    if (longueur != 0)
    {
      entete.NbSymb[longueur]++;
      profondeur = max(profondeur, longueur);
    }
    while (i<256)
    {
      fscanf(f, "%d", &longueur);
      fscanf(f, "%c", &buffer);
      if (longueur != 0)
      {
        profondeur = max(profondeur, longueur);
        if (longueur != -1)
          entete.NbSymb[longueur]++;
        longueur = -1;
      }
      i++;
    }
    entete.profondeur = profondeur;
    //fclose(f);

    //calcul deuxieme tableau
    f = fopen(fichier, "r");
    int tete[256];
    for (int i = 0; i < 256; i++)
    {
      tete[i] = 0;
    }
    fscanf(f,"%d", &nombre);
    fscanf(f, "%c", &buffer);
    for (int i = 0; i < 256; i++)
    {
      fscanf(f, "%d", &longueur);
      fscanf(f, "%c", &buffer);
      tete[i] = longueur;
    }
    //fclose(f);
    //f = fopen(fichier,"r");
    for (int i = 1; i <= entete.profondeur; i++)
    {
      int k = 0;
      for (int j = 0; j < 256; j++)
      {
        if (tete[j] == i)
        {
          //printf("i : %d k : %d j : %d\n",i,k,j);
          Symb[i][k] = j;
          k++;
        }
      }
    }
    entete.Symb = Symb;
    index = ftell(f);
    entete.index = index;
    //fclose(f);
  }
  else
    printf("Impossible d'ouvrir le fichier test.txt");
  return entete;
}


char* recupData(int offset, char* fichier,enTete_t tete){
  FILE *f = NULL;
  char carac=-1;
    int compt=0;
  f = fopen(fichier, "r");
  for(int i=0;i<offset+1;i++){
    fscanf(f,"%c",&carac);
  }
  if (f!=NULL){
    while(!feof(f)){
      fscanf(f,"%c",&carac);
      compt++;
    }
  }

  fclose(f);
  f = fopen(fichier, "r");
  for(int i=0;i<offset+1;i++){
    fscanf(f,"%c",&carac);
  }
  //fseek(f,offset+2,SEEK_SET);
  char* data=malloc(sizeof(char)*compt);
  strcpy(data,"");
  if (f!=NULL){
    int i=0;
    while(!feof(f)){
      fscanf(f,"%c",&carac);
      data[i]=carac;
      i++;
    }
  }else{
    printf("Ouverture de fichier impossible\n" );
  }
  return data;
}


char *decompression_final(char *tab, arbre a, int nbmots)
{
  pnoeud x = a;
  char *message = malloc(sizeof(char)*nbmots);
  int k = 0;
  for (int i = 0; i < nbmots; i++)
  {
    while (x->gauche != NULL && x->droit != NULL)
    {
      if (tab[k] == '0')
      {
        x = x->droit;
      }
      else if (tab[k] == '1'){
        x = x->gauche;
      }
      k++;
    }
    printf("%c\n",x->s );
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
