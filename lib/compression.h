#ifndef COMPRESSION_H
#define COMPRESSION_H
#include "canonique.h"

char * creer_entete(pdoublet* symb);
char* lecture_fichier(char* fichier,int taille);
char* codage_texte(char* c,pdoublet* tab,int nbCarac);
char*  convertion_charbin_to_char(char *c,int lg);
char* convertion_char_to_charbin(char* c,int lg);
void save_compression(char* entete,char* data,int caractereUtile);
void save_decompression(char* data);




#endif
