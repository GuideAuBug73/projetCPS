#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "compression.h"


char *c="011011000010000101011010";


char*  convertion_charbin_to_char(char *c,int lg) {
  printf("codage %s\n\n", c);
  printf("%lu , %d\n",strlen(c),lg);
  char *fin=malloc(sizeof(char)*lg/8);
  strcpy(fin,"");
  int nombre;
  char *tranfo=malloc(sizeof(char)*2);;
  for(int i=0;i<lg;i+=8){
    nombre=0;
    tranfo[1]='\0';
    for(int j=i;j<i+8 && j<lg;j++){
      nombre+=(int)((c[j]-'0')*pow(2,7-(j-i)));
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
      //printf("%d\n",k );
      if(k&1){
        tranfo="1";
      }else{
        tranfo="0";
      }
      //printf("%c\n",tranfo[0] );
      strcat(fin,tranfo);
    }
  }
  return fin;
}


char * creer_entete(pdoublet* tab){
  char*fin=malloc(sizeof(char)*256*4);
  char* tranfo=malloc(sizeof(char)*3);
  int k;
  int j;
  char tempo;
  for(int i=0;i<256;i++){
    k=0;
    j=1;
    tranfo[0]='0';
    tranfo[1]='\0';
    while(tab[j] != NULL){
      while(tab[j][k].symb != '\0'){
        //printf("%c , %c\n",i,tab[j][k].symb );
        if(i==tab[j][k].symb){
          if (j>=10&&j<100){
            tranfo[0] = (char)(j/10+'0');
            tranfo[1] = (char)(j%10+'0');
            tranfo[2]='\0';
          }
          else if(j>=100){
            tranfo[0] = (char)(j/100+'0');
            tempo = j%100;
            tranfo[1] = (char)(tempo/10+'0');
            tranfo[2] = (char)(j%10+'0');
          }else if(j<10){
            tranfo[0]=(char)j+'0';
          }
        }
        k++;
      }
      k = 0;
      j++;
    }
    strcat(fin,tranfo);
    strcat(fin,",");
  }
  return fin;
}


char* RLE(char * entete){
  char sauvegarde[4];
  char* nouveau = malloc(sizeof(char)*4*256);
  int i = 0;
  int k = 0;
  int tempo;
  int cpt = 0 ;
  while(i<strlen(entete)){
    sauvegarde[0]= entete[i];
    sauvegarde[1]= entete[i+1];
    sauvegarde[2]= entete[i+2];
    sauvegarde[3]= entete[i+3];
    if((sauvegarde[1]==',')&&(sauvegarde[0])==(entete[i+2])){
      cpt = 0;
      i=i+2;
      while((sauvegarde[1]==',')&&(sauvegarde[0])==(entete[i+2])){
        i=i+2;
        cpt ++;
      }
      i++;
      nouveau[k]= sauvegarde[0];
      nouveau[k+1] = ',';
      nouveau[k+2] = sauvegarde[0];
      nouveau[k+3] = ',';
      k = k+4;
      if (cpt>0&&cpt<10){
        nouveau[k] = '+';
        k++;
        nouveau[k] = (char)(cpt+'0');
        k++;
        nouveau[k] = ',';
        k++;
      }
      if (cpt>=10&&cpt<100){
        nouveau[k] = '+';
        k++;
        nouveau[k] = (char)(cpt/10 + '0');
        k ++ ;
        nouveau[k] = (char)(cpt%10 + '0');
        k++;
      }
      else if(cpt>=100){
        nouveau[k] = '+';
        k++;
        nouveau[k] = (char)(cpt/100 + '0');
        k ++ ;
        tempo = cpt%100;
        nouveau[k] = (char)(tempo/10 + '0');
        k++;
        nouveau[k] = (char)(cpt%10 + '0');
        k++;
      }
    }

    else if((sauvegarde[0]!=',')&&(sauvegarde[1]!=',')&&(sauvegarde[2]==',')&&(sauvegarde[0]==entete[i+3])&&(sauvegarde[1]==entete[i+4])){
      cpt = 0;
      i = i+3;
      while((entete[i]!='\0'&&entete[i+1]!='\0'&&entete[i+2]!='\0'&&entete[i+3]!='\0')&&(sauvegarde[0]!=',')&&(sauvegarde[1]!=',')&&(sauvegarde[2]==',')&&(sauvegarde[0]==entete[i+3])&&(sauvegarde[1]==entete[i+4])){
        i=i+3;
        cpt ++;
      }
      i = i + 3;
      nouveau[k]= sauvegarde[0];
      nouveau[k+1] = sauvegarde[1];
      nouveau[k+2] = ',';
      nouveau[k+3] = sauvegarde[0];
      nouveau[k+4] = sauvegarde[1];
      nouveau[k+5] = ',';
      k = k+6;

      if (cpt>1&&cpt<10){
        nouveau[k] = '+';
        k++;
        nouveau[k] = (char)(cpt+'0');
        k++;
        nouveau[k] = ',';
        k++;
      }
      if (cpt>=10&&cpt<100){
        nouveau[k] = '+';
        k++;
        nouveau[k] = (char)(cpt/10+'0');
        k ++ ;
        nouveau[k] = (char)(cpt%10+'0');
        k++;
        nouveau[k] = ',';
        k++;
      }
      else if(cpt>=100){
        nouveau[k] = '+';
        k++;
        nouveau[k] = (char)(cpt/100+'0');
        k ++ ;
        tempo = cpt%100;
        nouveau[k] = (char)(tempo/10+'0');
        k++;
        nouveau[k] = (char)(cpt%10+'0');
        k++;
        nouveau[k] = ',';
        k++;
      }
    }

    else if((sauvegarde[0]!=',')&&(sauvegarde[1]!=',')&&(sauvegarde[2]!=',')&&(sauvegarde[3]==',')&&(sauvegarde[0]==entete[i+4])&&(sauvegarde[1]==entete[i+5])&&(sauvegarde[2]==entete[i+6])){
      cpt = 0;

      i = i+4;
      while((sauvegarde[0]!=',')&&(sauvegarde[1]!=',')&&(sauvegarde[2]!=',')&&(sauvegarde[3]==',')&&(sauvegarde[0]==entete[i+4])&&(sauvegarde[1]==entete[i+5])&&(sauvegarde[2]==entete[i+6])){
        i=i+4;
        cpt ++;
      }
      i = i+5;
      nouveau[k]= sauvegarde[0];
      nouveau[k+1] = sauvegarde[1];
      nouveau[k+2] = sauvegarde[2];
      nouveau[k+3] = ',';
      nouveau[k+4] = sauvegarde[0];
      nouveau[k+5] = sauvegarde[1];
      nouveau[k+6] = sauvegarde[2];
      nouveau[k+7] = ',';
      k = k+8;

      if (cpt>1&&cpt<10){
        nouveau[k] = '+';
        k++;
        nouveau[k] = (char)(cpt+'0');
        k++;
        nouveau[k] = ',';
        k++;
      }
      if (cpt>=10&&cpt<100){
        nouveau[k] = '+';
        k++;
        nouveau[k] = (char)(cpt/10+'0');
        k ++ ;
        nouveau[k] = (char)(cpt%10+'0');
        k++;
        nouveau[k] = ',';
        k++;
      }
      else if(cpt>=100){
        nouveau[k] = '+';
        k++;
        nouveau[k] = (char)(cpt/100+'0');
        k ++ ;
        tempo = cpt%100;
        nouveau[k] = (char)(tempo/10+'0');
        k++;
        nouveau[k] = (char)(cpt%10+'0');
        k++;
        nouveau[k] = ',';
        k++;
      }
    }

    else {
      if(sauvegarde[1]==','){
        nouveau[k] = sauvegarde[0];
        k++;
        nouveau[k] = ',';
        k++;
        i = i +2;
      }
      else if(sauvegarde[2]==','){
        nouveau[k] = sauvegarde[0];
        k++;
        nouveau[k] = sauvegarde[1];
        k++;
        nouveau[k] = ',';
        k++;
        i = i +3 ;
      }
      else if(sauvegarde[3]){
        nouveau[k] = sauvegarde[0];
        k++;
        nouveau[k] = sauvegarde[1];
        k++;
        nouveau[k] = sauvegarde[2];
        k++;
        nouveau[k] = ',';
        k++;
        i = i +4 ;
      }
      else {
        nouveau[k] = ',';
        k++;
        i++;
      }
    }
  }
  nouveau[k+1] = '\0';
  return nouveau;

}

void save_compression(char* entete,char* data,int caractereUtile,char* name){
  char name2[strlen(name)+1];
  strcpy(name2,"");
  int i=0;
  while(i<strlen(name)-4){ //Boucle jusqu'au point de notre nom de fichier
    name2[i]=name[i];   //Sauvegarde des caractères
    i++;
  }
  name2[i]='.';
  name2[i+1]='p';
  name2[i+2]='e';
  name2[i+3]='n';
  name2[i+4]='\0';
  //strcat(name2,".pen");
  FILE* file=fopen(name2,"w");
  int taille_entete=strlen(entete);
  int taille_data=strlen(data);
  fprintf(file, "%d",caractereUtile );
  fputs(",",file);
  for(int i=0;i<taille_entete;i++){
    fprintf(file, "%c",entete[i] );
  }
  fputs("\n",file);
  for(int j=0;j<taille_data;j++){
    fprintf(file, "%c",data[j] );

  }
  fclose(file);
}


void save_decompression(char* data,char* name){
  char name2[strlen(name)+4];
  strcpy(name2,"");
  int i=0;
  while(i<strlen(name)-4){ //Boucle jusqu'au point de notre nom de fichier
    name2[i]=name[i];   //Sauvegarde des caractères
    i++;
  }
  strcat(name2,".pen.txt");
  FILE* file=fopen(name2,"w");
  int taille_data=strlen(data);
  for(int j=0;j<taille_data;j++){
    fprintf(file, "%c",data[j] );
  }
  fclose(file);
}


char* codage_texte(char* c,pdoublet* tab,int nbCarac){
  char*fin=malloc(sizeof(char)*nbCarac);
  strcpy(fin,"");
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
  strcpy(fin,"");
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
  //fclose(f);
  return fin;
}
