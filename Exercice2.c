#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct maillon {
    char *mot;
    struct maillon *precedent;
    struct maillon *suivant;
};

typedef struct maillon MAILLON, *PTR;

// Déclaration de la variable globale avec initialisation
PTR premier = NULL;
PTR dernier = NULL;



void ajouter_devant1(char *s) {

//Créer un nouveau maillon associé à la chaîne s 

   PTR nouveau = (PTR)malloc(sizeof(MAILLON));
   nouveau->mot = malloc(strlen(s) + 1); 
   strcpy(nouveau->mot, s);

//Ajouter en tête de la liste le nouveau maillon crée

      nouveau->precedent = NULL;
      nouveau->suivant = premier;

   if (premier != NULL){
      premier->precedent = nouveau;
   }
   else {
      dernier = nouveau;
   }

   premier = nouveau;  
}

void ajouter_devant2(char *s, PTR *premier, PTR *dernier) {

//Créer un nouveau maillon associé à la chaîne s 

   PTR nouveau = (PTR)malloc(sizeof(MAILLON));
   nouveau->mot = malloc(strlen(s) + 1); 
   strcpy(nouveau->mot, s);

//Ajouter en tête de la liste le nouveau maillon crée

   nouveau->precedent = NULL;
   nouveau->suivant = *premier; 
   if (*premier != NULL){
      (*premier)->precedent = nouveau;
   } 
   else {
      *dernier = nouveau;
   }
   
   *premier = nouveau;  
}


void supprimer(char *s) {
  PTR actuel = premier;

   while (actuel != NULL)
   {
      if (strcmp(actuel->mot, s) == 0){

         if (actuel->precedent !=NULL)
         {
            actuel->precedent->suivant = actuel->suivant;
         }
         if (actuel->suivant != NULL)
         {
            actuel->suivant->precedent = actuel->precedent;
         }
      
         // On libère la memoire
         free(actuel->mot);
         free(actuel);
      }
      // On passe au prochain maillon
      actuel = actuel->suivant;
   }
   
}


int main() {
    ajouter_devant1("chat");
    ajouter_devant1("chien");
    ajouter_devant1("oiseau");
    ajouter_devant1("serpent");

    printf("Liste avant suppression :\n");
    PTR temp = premier;
    while (temp != NULL) {
        printf("%s\n", temp->mot);
        temp = temp->suivant;
    }
    printf("\nSuppression de chien :\n");
    supprimer("chien");
    

    printf("\nListe apres suppression :\n");
    temp = premier;
    while (temp != NULL) {
        printf("%s\n", temp->mot);
        temp = temp->suivant;
    }

    return 0;
}

