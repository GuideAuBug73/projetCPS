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
    printf("====== TABLEAU NON CANONIQUE ======\n");
    affichage_codage(tableau_codage);
    pdoublet *goodTab = tableau_change(tableau_codage);
    printf("====== TABLEAU CANONIQUE ======\n");
    affichage_codage(goodTab);
    return 0;   
}
