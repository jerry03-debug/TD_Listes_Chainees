#include <stdio.h>
#include <stdlib.h>

// Déclaration des types
typedef struct maillon {
  int indice;
  float valeur;
  struct maillon *suivant;
} MAILLON;

typedef MAILLON *PTR;   // Type PTR est un typedef pour un pointeur vers un maillon

// Fonction pour créer un nouveau maillon
PTR nouveau_maillon(int indice, float valeur) {
  PTR nouveau = malloc(sizeof(MAILLON));    // Allocation de la mémoire pour le nouveau maillon
 
  // Affectation des valeurs aux champs du nouveau maillon
  nouveau->indice = indice;
  nouveau->valeur = valeur;
  nouveau->suivant = NULL;
  return nouveau;              // Retourne le pointeur vers le nouveau maillon
}

// Fonction pour construire un vecteur creux à partir d'un tableau
PTR vecteur_creux(float t[], int n) {
  // Pointeur vers la tête de la liste chaînée
  PTR tete = NULL;

  // Pointeur vers le maillon précédent dans la liste chaînée
  PTR prec = NULL;

  // Parcours du tableau
  for (int i = 0; i < n; i++) {
    // Si la valeur du tableau n'est pas nulle
    if (t[i] != 0.0) {
      // Création d'un nouveau maillon avec l'indice et la valeur
      PTR nouveau = nouveau_maillon(i, t[i]);

      // Si la liste est vide
      if (tete == NULL) {
        // Le nouveau maillon devient la tête de la liste
        tete = nouveau;
      } else {
        // Le nouveau maillon est ajouté à la fin de la liste
        prec->suivant = nouveau;
      }

      // Le pointeur `prec` est mis à jour pour pointer vers le nouveau maillon
      prec = nouveau;
    }
  }

  // Retourne la tête de la liste chaînée représentant le vecteur creux
  return tete;
}

// Fonction pour calculer la somme de deux vecteurs creux
PTR somme(PTR a, PTR b) {
  // Pointeur vers la tête de la liste chaînée résultante
  PTR tete = NULL;

  // Pointeur vers le maillon précédent dans la liste chaînée résultante
  PTR prec = NULL;

  // Parcours des deux listes chaînées en parallèle
  while (a != NULL && b != NULL) {
    // Comparaison des indices des deux maillons
    if (a->indice < b->indice) {
      // Le maillon de `a` est ajouté à la liste résultante
      PTR nouveau = nouveau_maillon(a->indice, a->valeur);

      if (tete == NULL) {
        // Le nouveau maillon devient la tête de la liste
        tete = nouveau;
      } else {
        // Le nouveau maillon est ajouté à la fin de la liste
        prec->suivant = nouveau;
      }

      // Le pointeur `prec` est mis à jour pour pointer vers le nouveau maillon
      prec = nouveau;

      // Passage au maillon suivant de `a`
      a = a->suivant;
    } else if (a->indice > b->indice) {
      // Le maillon de `b` est ajouté à la liste résultante
      PTR nouveau = nouveau_maillon(b->indice, b->valeur);

      if (tete == NULL) {
        tete = nouveau;
      } else {
        prec->suivant = nouveau;
      }
      prec = nouveau;
      // Passe aux maillons suivants dans les deux listes
      b = b->suivant;
    } else {
      // Si les indices sont égaux, ajoutez les valeurs et créez un nouveau maillon
      PTR nouveau = nouveau_maillon(a->indice, a->valeur + b->valeur);
      if (tete == NULL) {
        tete = nouveau;
      } else {
        prec->suivant = nouveau;
      }
      prec = nouveau;
      // Passe aux maillons suivants dans les deux listes
      a = a->suivant;
      b = b->suivant;
    }
  }
  // Une fois qu'une des listes est épuisée, ajoutez le reste des maillons de l'autre liste
  while (a != NULL) {
    PTR nouveau = nouveau_maillon(a->indice, a->valeur);
    if (tete == NULL) {
      tete = nouveau;
    } else {
      prec->suivant = nouveau;
    }
    prec = nouveau;
    a = a->suivant;
  }
  while (b != NULL) {
    PTR nouveau = nouveau_maillon(b->indice, b->valeur);
    if (tete == NULL) {
      tete = nouveau;
    } else {
      prec->suivant = nouveau;
    }
    prec = nouveau;
    b = b->suivant;
  }
  // Retourne la tête de la liste de résultat
  return tete;
}

int main() {
  // Déclaration de deux tableaux de nombres réels
  float t1[] = {1.0, 0.0, 3.0, 0.0, 5.0, 0.0};
  float t2[] = {3.0, 2.0, 0.0, 4.0, 0.0, 6.0};

  // Taille des tableaux
  int n = sizeof(t1) / sizeof(t1[0]);

  // Construction des vecteurs creux à partir des tableaux
  PTR a = vecteur_creux(t1, n);
  PTR b = vecteur_creux(t2, n);

  // Affichage des vecteurs creux
  printf("Vecteur a:\n");
  PTR temp_a = a;  // Sauvegarde du pointeur original
  while (temp_a != NULL) {
    printf("(%d, %f) ", temp_a->indice, temp_a->valeur);
    temp_a = temp_a->suivant;
  }
  printf("\n");

  printf("Vecteur b:\n");
  PTR temp_b = b;  // Sauvegarde du pointeur original
  while (temp_b != NULL) {
    printf("(%d, %f) ", temp_b->indice, temp_b->valeur);
    temp_b = temp_b->suivant;
  }
  printf("\n");

  // Calcul de la somme des deux vecteurs creux
  PTR somme_vecteurs = somme(a, b);

  // Affichage de la somme des vecteurs creux
  printf("Somme des vecteurs a et b:\n");
  PTR temp_somme = somme_vecteurs;  // Sauvegarde du pointeur original
  while (temp_somme != NULL) {
    printf("(%d, %f) ", temp_somme->indice, temp_somme->valeur);
    temp_somme = temp_somme->suivant;
  }
  printf("\n");

  // Libération de la mémoire allouée pour les vecteurs creux
  while (a != NULL) {
    PTR temp = a;
    a = a->suivant;
    free(temp);
  }

  while (b != NULL) {
    PTR temp = b;
    b = b->suivant;
    free(temp);
  }

  while (somme_vecteurs != NULL) {
    PTR temp = somme_vecteurs;
    somme_vecteurs = somme_vecteurs->suivant;
    free(temp);
  }

  return 0;
}
