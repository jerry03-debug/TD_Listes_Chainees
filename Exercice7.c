#include <stdio.h>
#include <stdlib.h>

// Déclaration d'une structure ARB_BIN représentant un arbre binaire d'entiers
struct ARB_BIN {
    int etiquette;
    struct ARB_BIN *gauche;
    struct ARB_BIN *droite;
};

// 1°) Déclaration d’une structure ARB_BIN permettant de représenter un arbre binaire d'entier
typedef struct ARB_BIN ARB_BIN;

// 2°) Procédure FEUILLE(A) pour afficher la liste des étiquettes des feuilles de A
void FEUILLE(ARB_BIN *A) {
    if (A != NULL) {
        if (A->gauche == NULL && A->droite == NULL)
            printf("%d ", A->etiquette);
        FEUILLE(A->gauche);
        FEUILLE(A->droite);
    }
}

// 3°) Procédure DEGRE(A) pour afficher tous les nœuds de A avec leurs degrés respectifs
void DEGRE(ARB_BIN *A) {
    if (A != NULL) {
        int degre = 0;
        if (A->gauche != NULL)
            degre++;
        if (A->droite != NULL)
            degre++;
        printf("Noeud: %d, Degré: %d\n", A->etiquette, degre);
        DEGRE(A->gauche);
        DEGRE(A->droite);
    }
}

// 4°) Procédure PROFONDEUR pour afficher la profondeur d'un nœud x dans A
void PROFONDEUR(ARB_BIN *A, int x, int profondeurActuelle) {
    if (A != NULL) {
        if (A->etiquette == x) {
            printf("La profondeur de %d est: %d\n", x, profondeurActuelle);
            return;
        }
        PROFONDEUR(A->gauche, x, profondeurActuelle + 1);
        PROFONDEUR(A->droite, x, profondeurActuelle + 1);
    }
}

// 5°) Procédure HAUTEUR pour retourner la hauteur de A
int HAUTEUR(ARB_BIN *A) {
    if (A == NULL)
        return -1;
    int gauche_hauteur = HAUTEUR(A->gauche);
    int droite_hauteur = HAUTEUR(A->droite);
    return 1 + (gauche_hauteur > droite_hauteur ? gauche_hauteur : droite_hauteur);
}

// 6°) Fonction SOM_NOEUDS pour calculer et retourner la somme des nœuds de A
int SOM_NOEUDS(ARB_BIN *A) {
    if (A == NULL)
        return 0;
    return A->etiquette + SOM_NOEUDS(A->gauche) + SOM_NOEUDS(A->droite);
}

int main() {
    // Exemple de création d'un arbre binaire
    ARB_BIN *racine = (ARB_BIN *)malloc(sizeof(ARB_BIN));
    racine->etiquette = 1;
    racine->gauche = (ARB_BIN *)malloc(sizeof(ARB_BIN));
    racine->gauche->etiquette = 2;
    racine->gauche->gauche =  (ARB_BIN *)malloc(sizeof(ARB_BIN));
    racine->gauche->droite =  (ARB_BIN *)malloc(sizeof(ARB_BIN));
    racine->gauche->gauche->etiquette = 4;
    racine->gauche->droite->etiquette = 5;
    racine->droite = (ARB_BIN *)malloc(sizeof(ARB_BIN));
    racine->droite->etiquette = 3;
    racine->droite->gauche = NULL;
    racine->droite->droite = NULL;

    // 2°) Affichage des feuilles
    printf("Feuilles: ");
    FEUILLE(racine);
    printf("\n");

    // 3°) Affichage des nœuds avec leur degré
    printf("Nœuds et leurs degrés:\n");
    DEGRE(racine);

    // 4°) Affichage de la profondeur d'un nœud (par exemple, 3)
    PROFONDEUR(racine, 5, 0);

    // 5°) Calcul et affichage de la hauteur de l'arbre
    printf("Hauteur de l'arbre: %d\n", HAUTEUR(racine));

    // 6°) Calcul et affichage de la somme des nœuds de l'arbre
    printf("Somme des nœuds de l'arbre: %d\n", SOM_NOEUDS(racine));

    return 0;
}
