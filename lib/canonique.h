#ifndef CANONIQUE_H
#define CANONIQUE_H

typedef struct _doublet{
  char symb;
  char *code;
}doublet, *pdoublet;

pdoublet * tableau_code(arbre a);
pdoublet *tableau_change(pdoublet * tabdetab);
void affichage_codage(pdoublet* tab);

#endif