public class Liste {
    String mot;
    Liste suivant;

    public Liste(String mot) {
        this.mot = mot;
        this.suivant = null;
    }

    public Liste ajouteFin(String mot) {
        Liste nouveauMaillon = new Liste(mot);
        if (this.suivant == null) {
            this.suivant = nouveauMaillon;
        } else {
            Liste dernier = this.suivant;
            while (dernier.suivant != null) {
                dernier = dernier.suivant;
            }
            dernier.suivant = nouveauMaillon;
        }
        return this;
    }

    public Liste supprimer(String mot) {
        Liste courant = this;
        Liste precedent = null;

        while (courant != null && !courant.mot.equals(mot)) {
            precedent = courant;
            courant = courant.suivant;
        }

        if (courant == null) {
            return this; // Le mot n'est pas présent dans la liste
        }

        if (precedent == null) {
            return this.suivant; // Le mot à supprimer est en tête de liste
        } else {
            precedent.suivant = courant.suivant; // Le mot à supprimer est à l'intérieur de la liste
            return this;
        }
    }

    public void premiers(int n) {
        Liste courant = this;
        int compteur = 0;

        while (courant != null && compteur < n) {
            System.out.println(courant.mot);
            courant = courant.suivant;
            compteur++;
        }
    }

    public void purifie() {
        Liste courant = this;

        while (courant != null && courant.suivant != null) {
            if (courant.mot.equals(courant.suivant.mot)) {
                courant.suivant = courant.suivant.suivant; // Supprime le maillon doublon
            } else {
                courant = courant.suivant; // Passe au maillon suivant
            }
        }
    }

    public static void main(String[] args) {
        Liste liste = new Liste("Bonjour")
                .ajouteFin("Bonjour")
                .ajouteFin("Bonjour")
                .ajouteFin("Salut")
                .ajouteFin("Salut")
                .ajouteFin("Salut")
                .ajouteFin("Au revoir")
                .ajouteFin("Au revoir");

        System.out.println("Liste initiale :");
        Liste temp = liste;
        while (temp != null) {
            System.out.println(temp.mot);
            temp = temp.suivant;
        }

        System.out.println("\nSuppression du mot \"Bonjour\" :");
        liste = liste.supprimer("Bonjour");
        temp = liste;
        while (temp != null) {
            System.out.println(temp.mot);
            temp = temp.suivant;
        }

        System.out.println("\nAffichage des 3 premiers mots :");
        liste.premiers(3);

        System.out.println("\nPurification de la liste :");
        liste.purifie();
        temp = liste;
        while (temp != null) {
            System.out.println(temp.mot);
            temp = temp.suivant;
        }
    }
}
