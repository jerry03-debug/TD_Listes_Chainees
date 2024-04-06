#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct maillon {
    char *mot;
    struct maillon *suiv;
};

typedef struct maillon MAILLON, *PTR;

PTR ajoute_debut(char *mot, PTR L) {

    PTR nouveau = (PTR)malloc(sizeof(MAILLON));
     //nouveau->mot = *mot;
    nouveau->mot = malloc(strlen(mot) + 1); 
    strcpy(nouveau->mot, mot);
    nouveau->suiv = L;

    return nouveau;
}

PTR ajoute_fin(char *mot, PTR L) {
    PTR nouveau = (PTR)malloc(sizeof(MAILLON));

    //nouveau->mot = *mot;
    nouveau->mot = malloc(strlen(mot) + 1); 
    strcpy(nouveau->mot, mot);
    nouveau->suiv = NULL;

    //Si la liste est nulle le nouveau maillon devient la nouvelle liste (liste contenant un seul maillon nouveau)
    if (L == NULL) {
        return nouveau;
    }
    //Tant que le maillon courant (temp) a un suivant, on passe au prochain jusqu'au dernier maillon....
    PTR temp = L;
    while (temp->suiv != NULL) {
        temp = temp->suiv;
    }
    //...et une fois au dernier, on lui donne comme suivant le nouveau maillon. Ainsi le nouveau maillon devient le dernier.
    temp->suiv = nouveau;
    return L;
}

PTR supprimer(char *mot, PTR L) {
    PTR courant = L;
    PTR precedent = NULL;

    //A partir de la tete de la liste, on compare le mot de chaque maillon par le mot passé en parametre
        if (strcmp(courant->mot, mot) == 0) { //s'ils sont les meme ....
            if (precedent == NULL) { //...et que le maillon le contenant est le premier maillon de la liste alors on retourne le reste de la liste sans le premier
                return courant->suiv; 
            } else {
                precedent->suiv = courant->suiv; //...sinon si c'est un maillon interne on le supprime 
            }
            //On libere l'espace memoire alloue pour ce maillon
            free(courant->mot);
            free(courant);
            return L;
        }
        //si les mots ne sont pas les memes, on passe au maillon suivant
        else{
            precedent = courant;
            courant = courant->suiv;
        }

    return L;
}

void premiers(PTR liste, int n) {
    //Si l'utilisateur veut afficher n elements et que y a moins d'elements  dans la liste, on lui affiche tous les elements de la liste.
    //Par contre s'il y en a plus on lui affiche juste le nombre d'elements demandes
    int i = 0;
    PTR courant = liste;
    while (i < n && courant != NULL) {
        printf("%s\n", courant->mot);
        courant = courant->suiv;
        i++;
    }
}

void purifie(MAILLON *liste) {

    //Si la liste est nulle au depart on sort automatiquement de la fonction
    if (liste == NULL) {
        return;
    }
    //Sinon on compare a chaque iteration le mot du maillon courant avec celui de son suivant.
    PTR courant = liste;
    
    while (courant != NULL && courant->suiv != NULL) {
        //s'ils sont egaux, on supprime d'abord la deuxieme occurrence
        if (strcmp(courant->mot, courant->suiv->mot) == 0) {
            PTR temp = courant->suiv;
            courant->suiv = temp->suiv;

            //ensuite on libere son espace memoire
            free(temp->mot);
            free(temp);
        } 
        //sinon on passe a l'iteration suivante
        else {
            courant = courant->suiv;
        }
    }
}

int main() {
    PTR liste = NULL;
    liste = ajoute_fin("Bonjour", liste);
    liste = ajoute_fin("Bonjour", liste);
    liste = ajoute_fin("Bonjour", liste);
    liste = ajoute_fin("Salut", liste);
    liste = ajoute_fin("Salut", liste);
    liste = ajoute_fin("Salut", liste);
    liste = ajoute_fin("Au revoir", liste);
    liste = ajoute_fin("Au revoir", liste);

    printf("Liste initiale :\n");
    PTR temp = liste;
    while (temp != NULL) {
        printf("%s\n", temp->mot);
        temp = temp->suiv;
    }

    printf("\nSuppression du mot \"Bonjour\" :\n");
    liste = supprimer("Bonjour", liste);
    temp = liste;
    while (temp != NULL) {
        printf("%s\n", temp->mot);
        temp = temp->suiv;
    }

    printf("\nAffichage des 3 premiers mots :\n");
    premiers(liste, 3);

    printf("\nPurification de la liste :\n");
    purifie(liste);
    temp = liste;
    while (temp != NULL) {
        printf("%s\n", temp->mot);
        temp = temp->suiv;
    }

    return 0;
}
