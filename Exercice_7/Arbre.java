package Exercice_7;
public class Arbre {
    // Déclaration d'une classe représentant un arbre binaire d'entiers
    static class ARB_BIN {
        int etiquette;
        ARB_BIN gauche;
        ARB_BIN droite;

        ARB_BIN(int value) {
            this.etiquette = value;
            this.gauche = null;
            this.droite = null;
        }
    }

    // Procédure FEUILLE pour afficher la liste des étiquettes des feuilles de A
    static void FEUILLE(ARB_BIN A) {
        if (A != null) {
            if (A.gauche == null && A.droite == null)
                System.out.print(A.etiquette + " ");
            FEUILLE(A.gauche);
            FEUILLE(A.droite);
        }
    }

    // Procédure DEGRE pour afficher tous les nœuds de A avec leurs degrés respectifs
    static void DEGRE(ARB_BIN A) {
        if (A != null) {
            int degre = 0;
            if (A.gauche != null)
                degre++;
            if (A.droite != null)
                degre++;
            System.out.println("Noeud: " + A.etiquette + ", Degré: " + degre);
            DEGRE(A.gauche);
            DEGRE(A.droite);
        }
    }

    // Procédure PROFONDEUR pour afficher la profondeur d'un nœud x dans A
    static void PROFONDEUR(ARB_BIN A, int x, int profondeurActuelle) {
        if (A != null) {
            if (A.etiquette == x) {
                System.out.println("La profondeur de " + x + " est: " + profondeurActuelle);
                return;
            }
            PROFONDEUR(A.gauche, x, profondeurActuelle + 1);
            PROFONDEUR(A.droite, x, profondeurActuelle + 1);
        }
    }

    // Fonction HAUTEUR pour retourner la hauteur de A
    static int HAUTEUR(ARB_BIN A) {
        if (A == null)
            return -1;
        int gauche_hauteur = HAUTEUR(A.gauche);
        int droite_hauteur = HAUTEUR(A.droite);
        return 1 + Math.max(gauche_hauteur, droite_hauteur);
    }

    // Fonction SOM_NOEUDS pour calculer et retourner la somme des nœuds de A
    static int SOM_NOEUDS(ARB_BIN A) {
        if (A == null)
            return 0;
        return A.etiquette + SOM_NOEUDS(A.gauche) + SOM_NOEUDS(A.droite);
    }

    public static void main(String[] args) {
        // Exemple de création d'un arbre binaire
        ARB_BIN racine = new ARB_BIN(1);
        racine.gauche = new ARB_BIN(2);
        racine.gauche.gauche = new ARB_BIN(4);
        racine.gauche.droite = new ARB_BIN(5);
        racine.droite = new ARB_BIN(3);

        // Affichage des feuilles
        System.out.print("Feuilles: ");
        FEUILLE(racine);
        System.out.println();

        // Affichage des nœuds avec leur degré
        System.out.println("Noeuds et leurs degrés:");
        DEGRE(racine);

        // Affichage de la profondeur d'un nœud (par exemple, 5)
        PROFONDEUR(racine, 5, 0);

        // Calcul et affichage de la hauteur de l'arbre
        System.out.println("Hauteur de l'arbre: " + HAUTEUR(racine));

        // Calcul et affichage de la somme des nœuds de l'arbre
        System.out.println("Somme des noeuds de l'arbre: " + SOM_NOEUDS(racine));
    }
}
