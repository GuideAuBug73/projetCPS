typedef struct _noeud{
    int p;
    char *c;
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

typedef struct l{
  char nom;
  int nb;
  struct l* next;
}liste_t,*pliste_t;

typedef struct _doublet{
  char symb;
  int code;
}doublet, *pdoublet;
