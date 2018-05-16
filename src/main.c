#include <stdio.h>
#include "header.h"
#include "huffman.h"
#include "canonique.h"
#include "Table.h"


int main()
{
    tab_occur tri = nbOccurences("../exemple/exem1.txt");
    printf("%d\n",tri.nbOccurences );
    pliste_t liste = triTable(tri);
    arbre a = Construire_arbre_liste(liste);
    encodage(a); 
    afficher_post_encodage(a,0);
    pdoublet *tableau_codage = tableau_code(a);
    affichage_codage(tableau_codage);
    return 0;   
}
