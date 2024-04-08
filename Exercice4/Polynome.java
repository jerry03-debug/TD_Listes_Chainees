class Polynome {
    double coefficient;
    int exposant;
    Polynome suivant;

    public Polynome(double coefficient, int exposant, Polynome suivant) {
        this.coefficient = coefficient;
        this.exposant = exposant;
        this.suivant = suivant;
    }

    public static Polynome derivee(Polynome poly) {
        Polynome resultat = null;
        Polynome courant = poly;

        while (courant != null) {
            if (courant.exposant > 0) {
                Polynome monome = new Polynome(courant.coefficient * courant.exposant, courant.exposant - 1, null);
                if (resultat == null) {
                    resultat = monome;
                } else {
                    Polynome temp = resultat;
                    while (temp.suivant != null) {
                        temp = temp.suivant;
                    }
                    temp.suivant = monome;
                }
            }
            courant = courant.suivant;
        }

        return resultat;
    }

    public static Polynome deriveeKiememe(Polynome poly, int k) {
        Polynome resultat = poly;
        for (int i = 0; i < k; i++) {
            resultat = derivee(resultat);
        }
        return resultat;
    }

    public static void main(String[] args) {
        Polynome p1 = new Polynome(2.0, 3, null);
        Polynome p2 = new Polynome(1.0, 2, p1);
        Polynome p3 = new Polynome(3.0, 1, p2);
        Polynome poly = p3;

        Polynome derivee1 = derivee(poly);

        // Affichage du polynôme d'origine et de sa dérivée
        System.out.print("Polynome d'origine : ");
        Polynome courant = poly;
        while (courant != null) {
            System.out.print(courant.coefficient + "x^" + courant.exposant + " ");
            courant = courant.suivant;
            if (courant != null) {
                System.out.print("+ ");
            }
        }
        System.out.println();

        System.out.print("Derivee du polynome : ");
        courant = derivee1;
        while (courant != null) {
            System.out.print(courant.coefficient + "x^" + courant.exposant + " ");
            courant = courant.suivant;
            if (courant != null) {
                System.out.print("+ ");
            }
        }
        System.out.println();
    }
}
