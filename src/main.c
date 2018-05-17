#include <stdio.h>
#include <string.h>
#include "header.h"
#include "huffman.h"
#include "canonique.h"
#include "Table.h"
#include "compression.h"
int main()
{
    tab_occur tri = nbOccurences("../exemple/exem1.txt");
    printf("  ____ ___  __  __ ____  ____  _____ ____ ____   ___  ____  \n");
    printf(" / ___/ _ \\|  \\/  |  _ \\|  _ \\| ____/ ___/ ___| / _ \\|  _ \\ \n");
    printf("| |  | | | | |\\/| | |_) | |_) |  _| \\___ \\___ \\| | | | |_) |\n");
    printf("| |__| |_| | |  | |  __/|  _ <| |___ ___) |__) | |_| |  _ < \n");
    printf(" \\____\\___/|_|  |_|_|   |_| \\_\\_____|____/____/ \\___/|_| \\_\\\n");

    printf("\n%d\n", tri.nbOccurences);
    pliste_t liste = triTable(tri);
    arbre a = Construire_arbre_liste(liste);
    encodage(a);
    afficher_post_encodage(a, 0);
    pdoublet *tableau_codage = tableau_code(a);
    printf("====== TABLEAU NON CANONIQUE ======\n");
    affichage_codage(tableau_codage);
    tableau_change(tableau_codage);
    printf("====== TABLEAU CANONIQUE ======\n");
    affichage_codage(tableau_codage);
    char *entete = creer_entete(tableau_codage);
    printf("\n\n\n");
    for (int i = 0; i < 256; i++)
    {
        printf("%c", entete[i]);
    }
    printf("\n\n\n");

    char *text = lecture_fichier("../exemple/exem1.txt", tri.nbOccurences);
    printf("%s\n\n", text);
    char *codage = codage_texte(text, tableau_codage, tri.nbOccurences);
    printf("%s\n\n", codage);
    char *compress = convertion_charbin_to_char(codage, strlen(codage));
    printf("%s\n\n", compress);
    char *decompress = convertion_char_to_charbin(compress, strlen(compress));
    printf("%s\n\n", decompress);


    return 0;
}
