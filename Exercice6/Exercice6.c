#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define NMAX 100 

typedef struct {
    int n;
    float matrice[NMAX][NMAX];
} MATCARREE;

bool symetrique(MATCARREE m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            if (m.matrice[i][j] != m.matrice[j][i]) {
                return false; // Les éléments symétriques ne sont pas égaux
            }
        }
    }
    return true; // La matrice est symétrique
}

double* symCompacte(MATCARREE m, int n) {
    if (!symetrique(m)) {
        return NULL; // La matrice n'est pas symétrique
    }

    double* compacte = (double*)malloc(n * (n + 1) / 2 * sizeof(double));
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            compacte[k++] = m.matrice[i][j];
        }
    }
    return compacte;
}

double acces(double *c, int i, int j, int n) {
    if (i < 0 || i >= n || j < 0 || j >= n) {
        return 0.0; // Indice invalide, retourne 0
    }
    if (i < j) {
        int temp = i;
        i = j;
        j = temp; // Échange i et j pour être dans la moitié supérieure de la matrice
    }
    int k = i * (i + 1) / 2 + j;
    return c[k];
}


void traiterLigne(double *c, int n, int i, void (*traiterCoef)(double)) {
    for (int j = 0; j <= i; j++) {
        int k = i * (i + 1) / 2 + j;
        traiterCoef(c[k]);
    }
}

void afficher(double *c, int n) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", acces(c, i, j, n));
        }
        printf("\n");
    }
}

void traiterCoef(double x) {
    printf("%.2f ", x); // Traitement minimal, juste pour afficher le coefficient
}


int main() {
    MATCARREE matrice;
    matrice.n = 3; // Exemple avec une matrice 3x3

    // Initialisation de la matrice symétrique pour le test
    matrice.matrice[0][0] = 1;
    matrice.matrice[0][1] = 2;
    matrice.matrice[0][2] = 3;
    matrice.matrice[1][0] = 2;
    matrice.matrice[1][1] = 4;
    matrice.matrice[1][2] = 5;
    matrice.matrice[2][0] = 3;
    matrice.matrice[2][1] = 5;
    matrice.matrice[2][2] = 6;

    // Test de la fonction symetrique
    if (symetrique(matrice)) {
        printf("La matrice est symétrique.\n");
    } else {
        printf("La matrice n'est pas symétrique.\n");
        return 1; // Sortie avec erreur
    }

    // Test de la fonction symCompacte
    double* compacte = symCompacte(matrice, matrice.n);
    if (compacte != NULL) {
        printf("Matrice compacte : \n");
        afficher(compacte, matrice.n); // Affichage de la matrice compacte
        free(compacte); // Libération de la mémoire allouée dynamiquement
    } else {
        printf("La matrice n'est pas symétrique, impossible de la compacter.\n");
        return 1; // Sortie avec erreur
    }

    return 0; // Sortie sans erreur
}