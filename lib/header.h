typedef struct l{
  char nom;
  int nb;
  struct l* next;
}liste_t, *pliste_t;

typedef struct t{
  int nbOccurences;
  int tab[256];
}tab_occur, *ptab_occur;


tab_occur nbOccurences(char *fichier);
pliste_t triTable(tab_occur);
