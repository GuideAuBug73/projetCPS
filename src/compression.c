#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "compression.h"


char *c="011011000010000101011010";


char*  convertion_charbin_to_char(char *c,int lg) {
  char *fin=malloc(sizeof(char)*lg/8);
  strcpy(fin,"");
  int nombre;
  char *tranfo=malloc(sizeof(char)*2);;
  for(int i=0;i<lg;i+=8){
    nombre=0;
    tranfo[1]='\0';
    for(int j=i;j<i+8 && j<lg;j++){
      nombre+=(c[j]-'0')*pow(2,7-(j-i));
    }
    tranfo[0]=(char)nombre;
    strcat(fin,tranfo);
  }
  return fin;
}


char* convertion_char_to_charbin(char* c,int lg){
  char *fin=malloc(sizeof(char)*lg*8);
  strcpy(fin,"");
  int nombre;
  int k;
  char* tranfo=malloc(sizeof(char));
  for(int i=0;i<lg;i++){
    nombre=c[i];
    if(nombre<0){
      nombre+=256;
    }
    for(int j=7;j>=0;j--){
      k=nombre>>j;
      if(k&1){
        tranfo="1";
      }else{
        tranfo="0";
      }
      strcat(fin,tranfo);
    }
  }
  return fin;
}


char * creer_entete(pdoublet* tab){
  char*fin=malloc(sizeof(char)*256);
  char* tranfo=malloc(sizeof(char));
  int k;
  int j;
  for(int i=0;i<256;i++){
    k=0;
    j=1;
    tranfo[0]='0';
    while(tab[j] != NULL){
      while(tab[j][k].symb != '\0'){
        //printf("%c , %c\n",i,tab[j][k].symb );
        if(i==tab[j][k].symb){
          char c=j+48;
          tranfo[0]=c;
        }
        k++;
      }
      k = 0;
      j++;
    }
    strcat(fin,tranfo);
  }
  return fin;
}


void save_compression(char* entete,char* data,int caractereUtile){
  FILE* file=fopen("../exemple/compression.pen","w");
  int taille_entete=strlen(entete);
  int taille_data=strlen(data);
  fprintf(file, "%d",caractereUtile );
  fputs("\n",file);
  for(int i=0;i<taille_entete;i++){
    fprintf(file, "%c",entete[i] );
    }
    fputs("\n",file);
      for(int j=0;j<taille_data;j++){
    fprintf(file, "%c",data[j] );

  }
  printf("mamamama\n" );
  fclose(file);
  printf("papapaap\n" );
}


void save_decompression(char* data){
  FILE* file=fopen("../exemple/decompression.txt","w");
  int taille_data=strlen(data);
  for(int j=0;j<taille_data;j++){
    fprintf(file, "%c",data[j] );
  }
  fclose(file);
}


char* codage_texte(char* c,pdoublet* tab,int nbCarac){
  char*fin=malloc(sizeof(char)*nbCarac);
  int k;
  int j;
  for(int i=0;i<strlen(c);i++){
    k=0;
    j=1;
    while(tab[j] != NULL){
      while(tab[j][k].symb != '\0'){
        if(c[i]==tab[j][k].symb){
          strcat(fin,tab[j][k].code);
        }
        k++;
      }
      k = 0;
      j++;
    }
  }
  return fin;
}
char* lecture_fichier(char* fichier,int taille){
  char* fin = malloc(sizeof(char)*taille);
  FILE* f = NULL;
  char lettre;
  char* tranfo=malloc(sizeof(char));
  f = fopen(fichier,"r");
  if (f != NULL)
  {
    fscanf(f, "%c", &lettre);
    tranfo[0]=lettre;
    strcat(fin,tranfo);
    while(!feof(f)){
      fscanf(f, "%c", &lettre);
      tranfo[0]=lettre;
      strcat(fin,tranfo);
    }
  }
  fclose(f);
  return fin;
}
