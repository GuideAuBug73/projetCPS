#include <stdlib.h>
#include <stdio.h>

void nbOccurences(char *fichier, char **nbOcc, int *nbSymbole){
  FILE* f = NULL;
  f = fopen(fichier,"r");
  if (fichier != NULL)
  {

  }
  else
  {
    // On affiche un message d'erreur si on veut
    printf("Impossible d'ouvrir le fichier test.txt");
  }
}
