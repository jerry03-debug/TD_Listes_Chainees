import java.util.Scanner;

public class ListesChainees {

    private static class Element {
        int valeur;
        Element suivant;

        public Element(int valeur) {
            this.valeur = valeur;
            this.suivant = null;
        }
    }

    private static Element creerElement(int valeur) {
        return new Element(valeur);
    }

    private static Element creerListe(int nbElements) {
        Scanner scanner = new Scanner(System.in);
        Element tete = null;
        Element courant = null;

        for (int i = 0; i < nbElements; i++) {
            System.out.printf("Entrez la valeur %d : ", i + 1);
            int valeur = scanner.nextInt();
            Element nouveau = creerElement(valeur);

            if (tete == null) {
                tete = nouveau;
            } else {
                courant.suivant = nouveau;
            }
            courant = nouveau;
        }

        return tete;
    }

    private static void afficherListe(Element liste) {
        while (liste != null) {
            System.out.printf("%d ", liste.valeur);
            liste = liste.suivant;
        }
        System.out.println();
    }

    private static boolean listesEgales(Element liste1, Element liste2) {
        while (liste1 != null && liste2 != null) {
            if (liste1.valeur != liste2.valeur) {
                return false;
            }
            liste1 = liste1.suivant;
            liste2 = liste2.suivant;
        }

        return liste1 == null && liste2 == null;
    }

    private static Element concatenerListes(Element liste1, Element liste2) {
        Element tete = null, courant = null;

        // Copie de la première liste
        while (liste1 != null) {
            Element nouveau = creerElement(liste1.valeur);
            if (tete == null) {
                tete = courant = nouveau;
            } else {
                courant.suivant = nouveau;
                courant = nouveau;
            }
            liste1 = liste1.suivant;
        }

        // Copie de la deuxième liste
        while (liste2 != null) {
            Element nouveau = creerElement(liste2.valeur);
            courant.suivant = nouveau;
            courant = nouveau;
            liste2 = liste2.suivant;
        }

        return tete;
    }

    private static void concatenerListesSansCreation(Element liste1, Element liste2) {
        while (liste1.suivant != null) {
            liste1 = liste1.suivant;
        }
        liste1.suivant = liste2;
    }

    public static void main(String[] args) {
        // Création des deux premières listes
        Element liste1 = creerListe(10);
        Element liste2 = creerListe(10);

        // Test de l'égalité des deux listes
        if (listesEgales(liste1, liste2)) {
            System.out.println("Les deux listes sont égales.");
        } else {
            System.out.println("Les deux listes sont différentes.");
        }

        // Concaténation des deux listes
        Element liste3 = concatenerListes(liste1, liste2);

        // Parcourir et afficher la liste concaténée
        afficherListe(liste3);

        // Concaténation sans création d'une troisième liste
        concatenerListesSansCreation(liste1, liste2);

        // Parcourir et afficher la liste concaténée
        afficherListe(liste1);
    }
}
