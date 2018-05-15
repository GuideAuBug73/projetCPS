#include <stdlib.h>
#include <stdio.h>
#include "header.h"

int nbOccurences(char *fichier, int **nbOcc){
  // Tableau a initialiser et mettre à 0
  FILE* f = NULL;
  //lettre récupérée dans le fichier texte
  char lettre;
  //nombre total de symbols dans le fichier txt
  int nbSymbole=0;
  f = fopen(fichier,"r");
  if (f != NULL)
  {
    fscanf(f, "%c", &lettre);
    nbOcc[lettre]++;
    nbSymbole++;
    while(!feof(f)){
      fscanf(f, "%c", &lettre);
      nbOcc[lettre]++;
      nbSymbole++;
      printf("%d\n",nbOcc[lettre] );
    }
  }
  else
  {
    // On affiche un message d'erreur si on veut
    printf("Impossible d'ouvrir le fichier test.txt");
  }
  printf("%d\n",nbSymbole );
  return nbSymbole;
}

pliste_t triTable(int nbOcc[]){
  pliste_t liste=NULL ;
  pliste_t first;
  for(int i=0;i<256;i++){
    if(nbOcc[i]!=0){
      first=malloc(sizeof(pliste_t));
      first->nom=i-'0';
      first->nb=nbOcc[i];
      first->next=NULL;
      if(liste==NULL){
        liste=first;
      }else{
        pliste_t test=liste;
        while(test!=NULL){
          test=test->next;
        }
        test=first;
      }
    }
  }
  return liste;
}

int main(){
  int *nbOcc = malloc(256 * sizeof(int));
  for(int i=0 ; i<256 ; i++){
    nbOcc[i] = 0;
  }
  int nbSymbole =nbOccurences("../exemple/exem1.txt", &nbOcc);
  for(int i=0 ; i<256 ; i++){
    printf("%d ",nbOcc[i]);
  }
  pliste_t liste=triTable(nbOcc);
  while(liste!=NULL){
    printf("%c : %d\n",liste->nom,liste->nb );
    liste=liste->next;
  }
  return 0;
}
