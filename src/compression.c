#include <string.h>
#include <stdio.h>


char *c="0110110000001111";


char*  save_file(char *c,int lg) {
  char *fin;
  int nombre;
  char tranfo_nombre;
  char* tranfo;
  for(int i=0;i<lg;i+8){
    nombre=0;
    for(int j=i;j<i+8 && j<lg;j++){
      nombre+=c[j]-'0';
    }
    tranfo_nombre=(char)nombre;
    tranfo=(char*)tranfo_nombre;
    fin=strcat(fin,tranfo);
  }
}

int main(){
  char *s=save_file(c,16);
  printf("%s\n", s);
}
