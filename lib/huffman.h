
typedef struct _noeud{
    char s;
    int occ;
    struct _noeud *droit;
    struct _noeud *gauche;
} noeud, *pnoeud;

typedef pnoeud arbre;

// liste : occurence, nom, *next
typedef struct element element;
struct element {
  pnoeud noeud;
  element *suivant;
};

typedef struct File File;
struct File {
  element *premier;
};


arbre Construire_arbre_liste(pliste_t);
void afficher_arbre(arbre,int);
void afficher_file(File*);
 