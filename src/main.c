#include <stdlib.h>
#include <stdio.h>
#include "header.h"
#include "huffman.h"

int main()
{
    tab_occur tri = nbOccurences("../exemple/exem1.txt");
    pliste_t liste = triTable(tri);
    arbre a = Construire_arbre_liste(liste);
    afficher_arbre(a,0);
    printf("OK");

    return 0;
}
