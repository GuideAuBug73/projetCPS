#include <stdio.h>
#include "header.h"
#include "huffman.h"
#include "Table.h"


int main()
{
    tab_occur tri = nbOccurences("../exemple/exem1.txt");
    printf("%d\n",tri->nbOccurences );
    pliste_t liste = triTable(tri);
    arbre a = Construire_arbre_liste(liste);
    afficher_arbre(a,0);
    encodage(a);
   printf("OK");
    afficher_post_encodage(a,0);
    return 0;
}
