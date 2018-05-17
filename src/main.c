#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include "huffman.h"
#include "canonique.h"
#include "Table.h"
#include "compression.h"
#include "decompression.h"
int main()
{
    printf("  ____ ___  __  __ ____  ____  _____ ____ ____   ___  ____  \n");
    printf(" / ___/ _ \\|  \\/  |  _ \\|  _ \\| ____/ ___/ ___| / _ \\|  _ \\ \n");
    printf("| |  | | | | |\\/| | |_) | |_) |  _| \\___ \\___ \\| | | | |_) |\n");
    printf("| |__| |_| | |  | |  __/|  _ <| |___ ___) |__) | |_| |  _ < \n");
    printf(" \\____\\___/|_|  |_|_|   |_| \\_\\_____|____/____/ \\___/|_| \\_\\\n");


    tab_occur tri = nbOccurences("../exemple/exem1.txt");
    pliste_t liste = triTable(tri);
    arbre a = Construire_arbre_liste(liste);
    encodage(a);
    //afficher_post_encodage(a, 0);
    int h = hauteur_arbre(a);
    pdoublet *tableau_codage = tableau_code(a);
    //printf("====== TABLEAU NON CANONIQUE ======\n");
    //affichage_codage(tableau_codage);
    tableau_change(tableau_codage,h);
    //printf("====== TABLEAU CANONIQUE ======\n");
    affichage_codage(tableau_codage);
    char *entete = creer_entete(tableau_codage);
    /*for (int i = 0; i < 256; i++)
    {
        printf("%c", entete[i]);
    }
    printf("\n\n\n");*/

    char *text = lecture_fichier("../exemple/exem1.txt", tri.nbOccurences);
    printf("%s\n\n", text);
    char *codage = codage_texte(text, tableau_codage, tri.nbOccurences*h);
    printf("codage %s\n\n", codage);
    char *compress = convertion_charbin_to_char(codage, strlen(codage));
    save_compression(entete,compress,tri.nbOccurences,"../exemple/exem1.txt");
    enTete_t tete = lectureTableLongueur("../exemple/exem2.pen");
    char* data = recupData(tete.index,"../exemple/exem2.pen",tete);
    arbre arb = Construire_arbre_tablongueur(tete.Symb,tete.NbSymb,tete.profondeur);
    afficher_arbre(arb,0);
    //afficher_arbre(arb,0);
    char* data2=convertion_char_to_charbin(data,strlen(data));
    printf("codage %s\n",data2 );
    char* dataDecompres = decompression_final(data2,arb,tete.nombreSymboles);
    printf("%s\n",dataDecompres );
    save_decompression(dataDecompres,"../exemple/exem1.txt");




    /*
    char *decompress = convertion_char_to_charbin(compress, strlen(compress));
    printf("%s\n\n", decompress);*/
    /*
    free(tableau_codage);
    free(a);
    free(entete);
    free(text);
    free(codage);
    free(compress);*/
    return 0;
}
