#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


char *c="011011000010000101011010";


char*  convertion_charbin_to_char(char *c,int lg) {
  char *fin=malloc(sizeof(char)*lg/8);
  strcpy(fin,"");
  int nombre;
  char tranfo;
  char* tranfo_fin=malloc(sizeof(char));
  for(int i=0;i<lg;i=i+8){
    nombre=0;
    for(int j=i;j<i+8 && j<lg;j++){
      nombre+=(c[j]-'0')*pow(2,7-(j-i));
    }
    printf("%d\n",nombre );
    tranfo=(char)nombre;
    tranfo_fin[0]=tranfo;
    strcat(fin,tranfo_fin);
  }
  return fin;
}


char* convertion_char_to_charbin(char* c,int lg){
  char *fin=malloc(sizeof(char)*lg*8);
  strcpy(fin,"");
  int nombre;
  int k;
  char* tranfo;
  for(int i=0;i<lg;i++){
    nombre=c[i];
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


char * creer_entete(pdoublet** symb){
  char*fin=malloc(sizeof(char)*256);
  for(int init=0;init<256;init++){
    fin[init]=0;
  }
  for(int i=0;i<256;i++){
    int k=0;
    int j=0;
    while(tab[j] != NULL){
      while(tab[j][k].symb != '\0'){
        if(i==tab[j][k].symb){
          fin[i]=j;
        }
        k++;
      }
      k = 0;
      j++;
    }

  }
}


void save_compression(char* entete,char* data){
  FILE* file=fopen("../exemple/compression.pen");
  int taille_entete=strlen(entete);
  int taille_data=strlen(data);
  for(int i=0;i<taille_entete;i++){
    fprintf(file, "%s",entete[i] );
    fputs("",file);
  }
  for(int j=0;j<taille_data;j++){
    fprintf(file, "%s",data[j] );
  }
  fclose(file);
}


void save_compression(char* data){
  FILE* file=fopen("../exemple/decompression.pen");
  int taille_data=strlen(data);
  for(int j=0;j<taille_data;j++){
    fprintf(file, "%s",data[j] );
  }
  fclose(file);
}
