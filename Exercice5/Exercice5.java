// Déclaration de la classe Maillon
class Maillon {
    int indice;
    float valeur;
    Maillon suivant;

    // Constructeur de la classe Maillon
    Maillon(int indice, float valeur) {
        this.indice = indice;
        this.valeur = valeur;
        this.suivant = null;
    }
}

public class Exercice5 {
    // Fonction pour créer un nouveau maillon
    static Maillon nouveauMaillon(int indice, float valeur) {
        return new Maillon(indice, valeur);
    }

    // Fonction pour construire un vecteur creux à partir d'un tableau
    static Maillon vecteurCreux(float[] t) {
        Maillon tete = null;
        Maillon prec = null;

        for (int i = 0; i < t.length; i++) {
            if (t[i] != 0.0) {
                Maillon nouveau = nouveauMaillon(i, t[i]);
                if (tete == null) {
                    tete = nouveau;
                } else {
                    prec.suivant = nouveau;
                }
                prec = nouveau;
            }
        }
        return tete;
    }

    // Fonction pour calculer la somme de deux vecteurs creux
    static Maillon somme(Maillon a, Maillon b) {
        Maillon tete = null;
        Maillon prec = null;

        while (a != null && b != null) {
            if (a.indice < b.indice) {
                Maillon nouveau = nouveauMaillon(a.indice, a.valeur);
                if (tete == null) {
                    tete = nouveau;
                } else {
                    prec.suivant = nouveau;
                }
                prec = nouveau;
                a = a.suivant;
            } else if (a.indice > b.indice) {
                Maillon nouveau = nouveauMaillon(b.indice, b.valeur);
                if (tete == null) {
                    tete = nouveau;
                } else {
                    prec.suivant = nouveau;
                }
                prec = nouveau;
                b = b.suivant;
            } else {
                Maillon nouveau = nouveauMaillon(a.indice, a.valeur + b.valeur);
                if (tete == null) {
                    tete = nouveau;
                } else {
                    prec.suivant = nouveau;
                }
                prec = nouveau;
                a = a.suivant;
                b = b.suivant;
            }
        }

        while (a != null) {
            Maillon nouveau = nouveauMaillon(a.indice, a.valeur);
            if (tete == null) {
                tete = nouveau;
            } else {
                prec.suivant = nouveau;
            }
            prec = nouveau;
            a = a.suivant;
        }

        while (b != null) {
            Maillon nouveau = nouveauMaillon(b.indice, b.valeur);
            if (tete == null) {
                tete = nouveau;
            } else {
                prec.suivant = nouveau;
            }
            prec = nouveau;
            b = b.suivant;
        }
        return tete;
    }

    public static void main(String[] args) {
        float[] t1 = {1.0f, 0.0f, 3.0f, 0.0f, 5.0f, 0.0f};
        float[] t2 = {3.0f, 2.0f, 0.0f, 4.0f, 0.0f, 6.0f};

        Maillon a = vecteurCreux(t1);
        Maillon b = vecteurCreux(t2);

        System.out.println("Vecteur a:");
        Maillon tempA = a;
        while (tempA != null) {
            System.out.printf("(%d, %f) ", tempA.indice, tempA.valeur);
            tempA = tempA.suivant;
        }
        System.out.println();

        System.out.println("Vecteur b:");
        Maillon tempB = b;
        while (tempB != null) {
            System.out.printf("(%d, %f) ", tempB.indice, tempB.valeur);
            tempB = tempB.suivant;
        }
        System.out.println();

        Maillon sommeVecteurs = somme(a, b);

        System.out.println("Somme des vecteurs a et b:");
        Maillon tempSomme = sommeVecteurs;
        while (tempSomme != null) {
            System.out.printf("(%d, %f) ", tempSomme.indice, tempSomme.valeur);
            tempSomme = tempSomme.suivant;
        }
        System.out.println();
    }
}
