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
