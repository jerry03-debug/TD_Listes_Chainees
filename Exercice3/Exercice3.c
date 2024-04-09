#include <stdio.h>
#include <stdlib.h>


//Structure d'un élément de la liste
typedef struct element {
int valeur;
struct element *suivant;
} Element;

//Type de pointeur vers le premier élément de la liste
typedef Element *Liste;

// Fonction pour créer et retourner une liste chaînée
Liste creerListe() {
    Liste tete = NULL;
    Liste nouveau,courant;

    for (int i = 0; i < 10; i++) {
        nouveau = malloc(sizeof(Element));
        
        printf("Entrez la valeur %d : ", i + 1);
        scanf("%d", &nouveau->valeur);
        nouveau->suivant = NULL;

        if (tete == NULL) { // Si c'est le premier élément, il devient la tête de liste
            tete = nouveau;
        } else {
            courant = tete;
            while (courant->suivant != NULL) {
                courant = courant->suivant; // Parcourt la liste jusqu'à atteindre le dernier élément
            }
            courant->suivant = nouveau; // Ajoute le nouvel élément à la courant de la liste
        }
    }
    printf("Fin de la saisie\n");
    return tete;
}





//2. Tester l'égalité de deux listes

int listesEgales(Liste liste1, Liste liste2) {
  while (liste1 != NULL && liste2 != NULL) {
    if (liste1->valeur != liste2->valeur) {
      return 0;
    }
    liste1 = liste1->suivant;
    liste2 = liste2->suivant;
  }

  return (liste1 == NULL && liste2 == NULL);
}




//3. Concaténer deux listes
//a) Dans une troisième liste

Liste concatenerListes(Liste liste1, Liste liste2) {
  Liste tete = NULL, courant = NULL;
  Element *nouveau;
  printf("Concatenation avec création\n");

  // Copie de chaque valeur dans les maillons de la liste 1 dans la nouvelle liste créee 
  while (liste1 != NULL) {
    nouveau = malloc(sizeof(Element));
    nouveau->valeur = liste1->valeur;
    nouveau->suivant = NULL;

    if (tete == NULL) {
      tete = courant = nouveau;
    } else {
      courant->suivant = nouveau;
      courant = nouveau;
    }
    liste1 = liste1->suivant;
  }
  // Copie de chaque valeur dans les maillons de la liste 2 à la fin de liste 
  while (liste2 != NULL) {
    nouveau = malloc(sizeof(Element));
    nouveau->valeur = liste2->valeur;
    nouveau->suivant = NULL;
    courant->suivant = nouveau;
    courant = nouveau;
    liste2 = liste2->suivant;
  }

  return tete;
}




// b) Sans créer une troisième liste
void concatenerListesSansCreation(Liste *liste1, Liste liste2) {
  printf("Concatenation sans création\n");
  while (*liste1 != NULL) {
    liste1 = &(*liste1)->suivant;
  }

  *liste1 = liste2;
}


int main(){
  //Utilisation
  Liste liste1, liste2, liste3;

  // Création des deux premières listes
  liste1 = creerListe();
  liste2 = creerListe();

  // Test de l'égalité des deux listes
  if (listesEgales(liste1, liste2)) {
    printf("Les deux listes sont égales.\n");
  } else {
    printf("Les deux listes sont différentes.\n");
  }

  // Concaténation des deux listes
  liste3 = concatenerListes(liste1, liste2);

  // Parcourir et afficher la liste concaténée
  while (liste3 != NULL) {
    printf("%d ", liste3->valeur);
    liste3 = liste3->suivant;
  }

  printf("\n");

  // Concaténation sans création d'une troisième liste
  concatenerListesSansCreation(&liste1, liste2);

  // Parcourir et afficher la liste concaténée
  while (liste1 != NULL) {
    printf("%d ", liste1->valeur);
    liste1 = liste1->suivant;
  }

  printf("\n");

  return 0;
}
