//Recupération des valeurs de longueur de l'en-tête
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "decompression.h"
#include "huffman.h"
#define max(a,b) ((a)>(b)?(a):(b))

/*char **createArray(int m, int n) {
    char **rows = malloc(m * sizeof(char *));
    for (int i = 0; i < m; ++i) {
        char *values = malloc(n * sizeof(char));
        rows[i] = values;
    }
    return rows;
}
*/
enTete_t lectureTableLongueur(char *fichier){
  enTete_t entete;
  FILE *f = NULL;
  int longueur = -1;
  int profondeur = 0;
  //longueur inferieur a 10
  int *NbSymb=malloc(9*sizeof(int));
  char **Symb=createArray(10, 512);
  for(int i = 0 ; i<9 ; i++){
    NbSymb[i]=0;
  }
  entete.NbSymb = NbSymb;
  f = fopen(fichier,"r");
  //calcul premier tableau tab[0] correspond au niveau 1
  if(f!=NULL){
    //calcul profondeur + premier tableau
    profondeur = longueur;
    fscanf(f,"%d",&longueur);
    if(longueur!=0){
      entete.NbSymb[longueur]++;
      profondeur = max(profondeur, longueur);
    }
    while(!feof(f)){
      fscanf(f,"%d",&longueur);
      if(longueur!=0){
        profondeur = max(profondeur, longueur);
        if(longueur != -1)
          entete.NbSymb[longueur]++;
        longueur = -1;
      }
    }
    entete.profondeur = profondeur;
    fclose(f);

    //calcul deuxieme tableau
    f = fopen(fichier,"r");
    int tete[256];for(int i=0 ; i<256 ; i++){
      tete[i]=0;
    }
    for(int i=0 ; i<256 ; i++){
      fscanf(f,"%d",&longueur);
      tete[i]=longueur;
    }
    fclose(f);
    //f = fopen(fichier,"r");
    for(int i=1 ; i<=entete.profondeur ; i++){
      int k=0;
      for(int j=0 ; j<256 ; j++){
        if(tete[j] == i){
          //printf("i : %d k : %d j : %d\n",i,k,j);
          Symb[i][k] = j;
          k++;
        }
      }
    }
    entete.Symb = Symb;
    //fclose(f);
  }
  else printf("Impossible d'ouvrir le fichier test.txt");
  return entete;
}

/*
int main(int argc, char *argv){
  enTete_t entete;
  entete = lectureTableLongueur("../exemple/256test.txt");
  printf("Profondeur : %d\n", entete.profondeur);
  printf("Tableau 1 :");
  for(int i = 0 ; i < 10 ; i++){
    printf("%d",entete.NbSymb[i]);
  }
  printf("\nTableau 2 :\n");
  for(int i = 1; i < 10 ; i++){
    for(int j = 0 ; j<strlen(entete.Symb[i]) ; j++ ){
      printf("%c ",entete.Symb[i][j]);
    }
    printf("test\n");
  }
  return 0;
}*/
