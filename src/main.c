#include "header.h"
#include "Table.h"

int main()
{
    tab_occur tri = nbOccurences("../exemple/exem1.txt");
    pliste_t liste = triTable(tri);
    arbre a = Construire_arbre_liste(liste);

    return 0;
}
