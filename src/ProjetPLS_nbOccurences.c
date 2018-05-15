#include <stdlib.h>
#include <stdio.h>
#include "header.h"

tab_occur nbOccurences(char *fichier){
  tab_occur tab;
  tab.nbOccurences=0;
  for(int i=0 ; i<256 ; i++){
    tab.tab[i] = 0;
  }
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
    tab.tab[lettre]++;
    tab.nbOccurences++;
    while(!feof(f)){
      fscanf(f, "%c", &lettre);
      tab.tab[lettre]++;
      tab.nbOccurences++;
    }
  }
  else
  {
    // On affiche un message d'erreur si on veut
    printf("Impossible d'ouvrir le fichier test.txt");
  }
  return tab;
}

pliste_t triTable(tab_occur tab){
  pliste_t liste=NULL ;
  pliste_t first;
  for(int i=0;i<256;i++){
    if(tab.tab[i]!=0){
      first=malloc(sizeof(pliste_t));
      first->nom=i;
      first->nb=tab.tab[i];
      first->next=NULL;
      if(liste==NULL){
        liste=first;
      }else{
        pliste_t test=liste;
        if(liste->nb>first->nb){
          first->next=liste;
          liste=first;
        }else{
        while(test->next!=NULL && test->next->nb<=first->nb){
          test=test->next;
        }
        first->next=test->next;
        test->next=first;
      }}
    }
  }
  return liste;
}

int main(){
  tab_occur tri =nbOccurences("../exemple/exem1.txt");
  pliste_t liste=triTable(tri);
  while(liste!=NULL){
    printf("%c : %d\n",liste->nom,liste->nb );
    liste=liste->next;
  }
  return 0;
}
