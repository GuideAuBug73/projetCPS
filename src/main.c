#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include "huffman.h"
#include "canonique.h"
#include "Table.h"
#include "compression.h"
#include "decompression.h"
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Rentrez l'option de compression/decompression PUIS le nom du fichier en paramètre d'entrée ! \n");
        return 0;
    }
    if (argv[1][0] != '-')
    {
        printf("Les seuls options sont -c ou -d\n");
        return 0;
    }
    if (argv[1][1] == 'c')
    {
        tab_occur tri = nbOccurences(argv[2]);
        printf("  ____ ___  __  __ ____  ____  _____ ____ ____   ___  ____  \n");
        printf(" / ___/ _ \\|  \\/  |  _ \\|  _ \\| ____/ ___/ ___| / _ \\|  _ \\ \n");
        printf("| |  | | | | |\\/| | |_) | |_) |  _| \\___ \\___ \\| | | | |_) |\n");
        printf("| |__| |_| | |  | |  __/|  _ <| |___ ___) |__) | |_| |  _ < \n");
        printf(" \\____\\___/|_|  |_|_|   |_| \\_\\_____|____/____/ \\___/|_| \\_\\\n");

        pliste_t liste = triTable(tri);
        arbre a = Construire_arbre_liste(liste);
        encodage(a);
        afficher_post_encodage(a, 0);
        int h = hauteur_arbre(a);
        pdoublet *tableau_codage = tableau_code(a);
        printf("====== TABLEAU NON CANONIQUE ======\n");
        affichage_codage(tableau_codage);
        tableau_change(tableau_codage, h);
        printf("====== TABLEAU CANONIQUE ======\n");
        affichage_codage(tableau_codage);
        char *entete = creer_entete(tableau_codage);
        printf("\n\n\nLISTE DE LONGUEUR DANS ENTETE ");
        for (int i = 0; i < 256; i++)
        {
            printf("%c", entete[i]);
        }
        printf("\n\n\n"); 

        char *text = lecture_fichier(argv[2], tri.nbOccurences);
        printf(" Message : %s\n\n", text);
        char *codage = codage_texte(text, tableau_codage, tri.nbOccurences*h);
        printf("Code : %s\n\n", codage);
        char *compress = convertion_charbin_to_char(codage, strlen(codage));
        printf("%s\n\n", compress);
        save_compression(entete, compress, tri.nbOccurences, argv[2]);
    }
    else if (argv[1][1] == 'd')
    {
        int lg = strlen(argv[2]);
        if(argv[2][lg-1] != 'n' || argv[2][lg-2] !='e' || argv[2][lg-3] != 'p' || argv[2][lg-4] != '.'){
            printf("Le fichier a décompressé doit avoir l'extension \".pen\"\n");
            return 0;
        }
        enTete_t entete = lectureTableLongueur(argv[2]);
        char *data = recupData(entete.index,argv[2],entete);
        arbre abr = Construire_arbre_tablongueur(entete.Symb,entete.NbSymb,entete.profondeur);
        afficher_arbre(abr,0);
        char *binaire = convertion_char_to_charbin(data,strlen(data));
        char *message = decompression_final(binaire,abr,entete.nombreSymboles);
        save_decompression(message,argv[2]);
        
    }
    else
    {
        printf("Les seuls options sont -c ou -d\n");
        return 0;
    }
    return 0;
}
