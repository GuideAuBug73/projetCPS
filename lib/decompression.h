typedef struct n{
  int nombreSymboles;
  int *NbSymb;
  char **Symb;
  int profondeur;
  int index;
}enTete_t, *penTete_t;

enTete_t lectureTableLongueur(char *fichier);


char* recupData(int offset, char* fichier,enTete_t tete);
