#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition des structures de données
typedef struct maillon {
    int numero;
    struct maillon *suiv, *prec;
} MAILLON, *PTR;

typedef struct lcb {
    PTR tete, queue;
} LCB;

typedef struct node {
    char nom[100];
    LCB numeros;
    struct node *gauche, *droit;
} ABR;

// Ajouter un numéro à une liste chaînée bidirectionnelle (LCB)
LCB ajout_numero(int num, LCB numeros) {
    // Création du nouveau maillon
    PTR nouveau_maillon = (PTR)malloc(sizeof(MAILLON));
    nouveau_maillon->numero = num;

    nouveau_maillon->suiv = NULL;
    nouveau_maillon->prec = NULL;

    // Cas où la LCB est vide
    if (numeros.tete == NULL) {
        numeros.tete = nouveau_maillon;
        numeros.queue = nouveau_maillon;
    } else {
        // Parcours de la LCB pour trouver l'emplacement d'insertion
        PTR current = numeros.tete;
        while (current != NULL && current->numero < num) {
            current = current->suiv;
        }

        // Insertion du nouveau maillon
        if (current == NULL) { // Nouveau numéro est le plus grand, l'ajouter à la fin
            numeros.queue->suiv = nouveau_maillon;
            nouveau_maillon->prec = numeros.queue;
            numeros.queue = nouveau_maillon;
        } else if (current->prec == NULL) { // Insérer au début
            nouveau_maillon->suiv = numeros.tete;
            numeros.tete->prec = nouveau_maillon;
            numeros.tete = nouveau_maillon;
        } else { // Insérer au milieu
            nouveau_maillon->suiv = current;
            nouveau_maillon->prec = current->prec;
            current->prec->suiv = nouveau_maillon;
            current->prec = nouveau_maillon;
        }
    }
    return numeros;
}


// Ajouter un nom propre avec ses numéros de page associés dans un ABR
ABR *ajout_nompropre(char *nom, int t[], int nombre, ABR *a) {
    // Si l'arbre est vide, créer un nouveau nœud
    if (a == NULL) {
        // Allouer de la mémoire pour le nouveau nœud
        a = (ABR *)malloc(sizeof(ABR));
        // Copier le nom propre dans le nouveau nœud
        strcpy(a->nom, nom);
        // Initialiser la liste des numéros de page
        a->numeros.tete = NULL;
        a->numeros.queue = NULL;
        // Insérer les numéros de page dans la liste
        for (int i = 0; i < nombre; i++) {
            a->numeros = ajout_numero(t[i], a->numeros);
        }
        // Initialiser les sous-arbres gauche et droit à NULL
        a->gauche = NULL;
        a->droit = NULL;
    } else {
        // Comparer le nom avec le nom actuel dans le nœud
        int cmp = strcmp(nom, a->nom);
        // Si le nom est inférieur, aller à gauche
        if (cmp < 0) {
            a->gauche = ajout_nompropre(nom, t, nombre, a->gauche);
        }
        // Si le nom est supérieur, aller à droite
        else if (cmp > 0) {
            a->droit = ajout_nompropre(nom, t, nombre, a->droit);
        }
        // Si le nom est déjà présent, mettre à jour la liste des numéros de page
        else {
            for (int i = 0; i < nombre; i++) {
                a->numeros = ajout_numero(t[i], a->numeros);
            }
        }
    }
    return a;
}


// Supprimer un numéro de page pour un nom donné dans un ABR
ABR *supprimer_numero(char *nom, int numero, ABR *a) {
    if (a == NULL) {
        return NULL; // Si l'arbre est vide, retourner NULL
    }
    int cmp = strcmp(nom, a->nom);
    if (cmp < 0) {
        a->gauche = supprimer_numero(nom, numero, a->gauche);
    } else if (cmp > 0) {
        a->droit = supprimer_numero(nom, numero, a->droit);
    } else {
        // Si le nom est trouvé, supprimer le numéro de page de la LCB
        PTR current = a->numeros.tete;
        while (current != NULL) {
            if (current->numero == numero) {
                // Supprimer le maillon contenant le numéro donné
                if (current->prec == NULL) {
                    // Premier maillon
                    a->numeros.tete = current->suiv;
                    if (a->numeros.tete != NULL) {
                        a->numeros.tete->prec = NULL;
                    } else {
                        a->numeros.queue = NULL; // La liste est maintenant vide
                    }
                } else {
                    // Maillon au milieu ou à la fin
                    current->prec->suiv = current->suiv;
                    if (current->suiv != NULL) {
                        current->suiv->prec = current->prec;
                    } else {
                        a->numeros.queue = current->prec; // Le dernier maillon est supprimé
                    }
                }
                free(current); // Libérer la mémoire du maillon supprimé
                break; // Sortir de la boucle après avoir trouvé et supprimé le numéro
            }
            current = current->suiv;
        }
    }
    return a;
}

// Afficher une liste chaînée bidirectionnelle (LCB)
void afficher_LCB(LCB numeros) {
    PTR current = numeros.tete;
    while (current != NULL) {
        printf("%d ", current->numero);
        current = current->suiv;
    }
    printf("\n");
}

// Afficher l'index alphabétique à partir de l'ABR
void afficher_index(ABR *a) {
    if (a != NULL) {
        afficher_index(a->gauche);
        printf("%s : ", a->nom);
        afficher_LCB(a->numeros);
        afficher_index(a->droit);
    }
}

// Fonction main pour tester les fonctions
int main() {
    // Exemple pour tester les fonctions
    ABR *index = NULL;

    // Ajouter des noms et leurs numéros de page associés
    int pages_fatou[] = {110, 250, 300};
    index = ajout_nompropre("Fatou", pages_fatou, 3, index);

    int pages_mamadou[] = {3, 14, 101};
    index = ajout_nompropre("Mamadou", pages_mamadou, 3, index);

    int pages_ousseynou[] = {11, 50};
    index = ajout_nompropre("Ousseynou", pages_ousseynou, 2, index);

    int pages_pierre[] = {3, 7, 100, 287};
    index = ajout_nompropre("Pierre", pages_pierre, 4, index);

    int pages_soda[] = {6, 10, 34, 66, 98};
    index = ajout_nompropre("Soda", pages_soda, 5, index);

    // Afficher l'index
    printf("Index alphabétique :\n");
    afficher_index(index);

    // Supprimer un numéro de page pour un nom donné
    index = supprimer_numero("Pierre", 287, index);

    // Afficher l'index mis à jour
    printf("\nIndex alphabétique après la suppression :\n");
    afficher_index(index);

    // Exemple d'ajout d'un numéro supplémentaire
    printf("\nExemple d'ajout d'un numéro supplémentaire :\n");
    index->numeros = ajout_numero(105, index->numeros);
    afficher_index(index);

    return 0;
}
