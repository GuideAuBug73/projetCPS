typedef struct n{
  int nombreSymboles;
  int *NbSymb;
  char **Symb;
  int profondeur;
}enTete_t, *penTete_t;

enTete_t lectureTableLongueur(char *fichier);
