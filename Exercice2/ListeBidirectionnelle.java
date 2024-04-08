public class ListeBidirectionnelle {

    String mot;
    ListeBidirectionnelle suivant;
    ListeBidirectionnelle precedent;

    ListeBidirectionnelle premier = null;
    ListeBidirectionnelle dernier = null;

    // Première version de la fonction ajoute_devant
    public void ajoute_devant1(String s) {
        ListeBidirectionnelle nouveau = new ListeBidirectionnelle();
        nouveau.mot = s;
        nouveau.suivant = premier;
        nouveau.precedent = null;

        if (premier != null) {
            premier.precedent = nouveau;
        } else {
            dernier = nouveau; // Premier maillon ajouté
        }

        premier = nouveau;
    }

    // Deuxième version de la fonction ajoute_devant avec premier et dernier en paramètres
    public void ajoute_devant2(ListeBidirectionnelle premier, ListeBidirectionnelle dernier, String s) {
        ListeBidirectionnelle nouveau = new ListeBidirectionnelle();
        nouveau.mot = s;
        nouveau.suivant = premier;
        nouveau.precedent = null;

        if (premier != null) {
            premier.precedent = nouveau;
        } else {
            dernier = nouveau; // Premier maillon ajouté
        }

        premier = nouveau;
    }

    // Fonction pour supprimer un maillon de la liste
public void supprimer(String s) {
    ListeBidirectionnelle actuel = premier;
    while (actuel != null) {

        if (actuel.mot.equals(s)) {

            if (actuel.precedent != null) {
                actuel.precedent.suivant = actuel.suivant;
            } else {
                premier = actuel.suivant;
            }
            if (actuel.suivant != null) {
                actuel.suivant.precedent = actuel.precedent;
            } else {
                dernier = actuel.precedent;
            }
            break; // Sort de la boucle après la suppression
        }
        actuel = actuel.suivant; // Avance au maillon suivant
    }
}

    

    public static void main(String[] args) {
        ListeBidirectionnelle liste = new ListeBidirectionnelle();
        liste.ajoute_devant1("chat");
        liste.ajoute_devant1("chien");
        liste.ajoute_devant1("oiseau");
        liste.ajoute_devant2(liste.premier, liste.dernier, "oiseau");
        liste.ajoute_devant2(liste.premier, liste.dernier, "serpent");
    
        System.out.println("Liste avant suppression :");
        ListeBidirectionnelle temp = liste.premier;
        while (temp != null) {
            System.out.println(temp.mot);
            temp = temp.suivant;
        }
        System.out.println("Supression de chien ....");
        liste.supprimer("chien");
    
        System.out.println("\nListe après suppression :");
        temp = liste.premier;
        while (temp != null) {
            System.out.println(temp.mot);
            temp = temp.suivant;
        }
    }
    
}
