typedef struct n{
  int nombreSymboles;
  int *NbSymb;
  char **Symb;
  int profondeur;
  int index;
}enTete_t, *penTete_t;

enTete_t lectureTableLongueur(char *fichier);
