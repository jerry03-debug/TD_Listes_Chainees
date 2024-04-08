#include <stdio.h>
#include <stdlib.h>

// Définition de la structure pour représenter un terme d'un polynôme
struct polynome {
    float coefficient;
    int exposant;
    struct polynome *suivant;
};

// Alias pour struct polynome* pour simplifier l'utilisation de pointeurs
typedef struct polynome *PTR;

// Prototypes des fonctions
PTR DERIVEE(PTR poly);
PTR DERIVEEKIEME(PTR poly, int k);
void afficherPolynome(PTR poly);

// Fonction pour calculer la dérivée d'un polynôme
PTR DERIVEE(PTR poly) {
    PTR resultat = NULL; // Initialise le résultat à NULL
    PTR courant = poly; // Initialise un pointeur courant au début du polynôme
    
    // Parcourt chaque terme du polynôme
    while (courant != NULL) {
        // Vérifie si l'exposant du terme est supérieur à 0
        if (courant->exposant > 0) {
            // Alloue de la mémoire pour un nouveau terme dérivé
            PTR monome = malloc(sizeof(struct polynome));
            // Calcule le coefficient du terme dérivé
            monome->coefficient = courant->coefficient * courant->exposant;
            // Calcule l'exposant du terme dérivé
            monome->exposant = courant->exposant - 1;
            monome->suivant = NULL; // Initialise le pointeur suivant à NULL

            // Ajoute le terme dérivé à la liste résultante
            if (resultat == NULL) {
                resultat = monome; // Si la liste résultante est vide, le nouveau terme devient la tête de liste
            } else {
                // Sinon, parcourt la liste résultante jusqu'au dernier terme
                PTR temp = resultat;
                while (temp->suivant != NULL) {
                    temp = temp->suivant;
                }
                // Ajoute le nouveau terme à la fin de la liste résultante
                temp->suivant = monome;
            }
        }
        courant = courant->suivant; // Passe au terme suivant du polynôme
    }

    return resultat; // Retourne la liste résultante après calcul de la dérivée
}

// Fonction pour calculer la dérivée k-ième d'un polynôme
PTR DERIVEEKIEME(PTR poly, int k) {
    PTR resultat = poly; // Initialise le résultat au polynôme d'origine
    // Applique la dérivée k fois en appelant la fonction DERIVEE
    for (int i = 0; i < k; i++) {
        resultat = DERIVEE(resultat);
    }
    return resultat; // Retourne le résultat après k dérivations
}

// Fonction pour afficher un polynôme
void afficherPolynome(PTR poly) {
    PTR courant = poly;
    while (courant != NULL) {
        printf("%.1fx^%d ", courant->coefficient, courant->exposant);
        courant = courant->suivant;
        if (courant != NULL) {
            printf("+ ");
        }
    }
    printf("\n");
}

int main() {
    // Crée un polynôme en initialisant les termes
    struct polynome p1 = {2.0, 3, NULL};
    struct polynome p2 = {1.0, 2, &p1};
    struct polynome p3 = {3.0, 1, &p2};
    PTR poly = &p3; // Initialise le polynôme principal avec le dernier terme

    // Appelle la fonction DERIVEE pour calculer la dérivée du polynôme une fois
    PTR derivee1 = DERIVEE(poly);

    // Affiche les résultats
    printf("Polynome d'origine : ");
    afficherPolynome(poly);
    printf("Derivee du polynome : ");
    afficherPolynome(derivee1);

    return 0;
}