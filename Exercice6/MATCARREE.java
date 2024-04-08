// Déclaration d'un type MATCARREE représentant une matrice carrée
class MATCARREE {
    double[][] matrice;

    public MATCARREE(double[][] matrice) {
        this.matrice = matrice;
    }

    // Vérifie si la matrice est symétrique
    public boolean estSymetrique() {
        int n = matrice.length;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (matrice[i][j] != matrice[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    // Calcul du nombre de nombres réels nécessaires pour représenter une matrice symétrique
    public static int nombresReelsPourSymetrique(int n) {
        return n * (n + 1) / 2;
    }

    // Construction de la représentation compacte d'une matrice symétrique
    public static double[] symCompacte(MATCARREE m) {
        if (!m.estSymetrique()) {
            return null; // Retourne NULL si la matrice n'est pas symétrique
        }
        int n = m.matrice.length;
        double[] compacte = new double[nombresReelsPourSymetrique(n)];
        int index = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                compacte[index++] = m.matrice[i][j];
            }
        }
        return compacte;
    }

    // Accès au coefficient de la matrice symétrique représentée de manière compacte
    public static double acces(double[] compacte, int i, int j) {
        if (i < j) {
            int temp = i;
            i = j;
            j = temp; // Assure que i >= j pour la représentation compacte
        }
        int n = (int) (Math.sqrt(1 + 8 * compacte.length) - 1) / 2;
        int index = i * (i + 1) / 2 + j; // Calcul de l'index dans la représentation compacte
        return compacte[index];
    }

    // Traitement de chaque coefficient d'une ligne de la matrice symétrique représentée de manière compacte
    public static void traiterLigne(double[] compacte, int i, TraitementCoefficient traitement) {
        int n = (int) (Math.sqrt(1 + 8 * compacte.length) - 1) / 2;
        int debut = i * (i + 1) / 2;
        int fin = (i + 1) * (i + 2) / 2;
        for (int index = debut; index < fin; index++) {
            traitement.traiter(compacte[index]);
        }
    }

    // Interface pour le traitement des coefficients
    interface TraitementCoefficient {
        void traiter(double coefficient);
    }

    // Affichage de la matrice symétrique à partir de sa représentation compacte
    public static void afficher(double[] compacte) {
        int n = (int) (Math.sqrt(1 + 8 * compacte.length) - 1) / 2;
        int index = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i >= j) {
                    System.out.print(compacte[index++] + " ");
                } else {
                    System.out.print(compacte[j * (j + 1) / 2 + i] + " ");
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        // Exemple de création d'une matrice carrée
        double[][] matrice = {{1, 2, 3}, {2, 4, 5}, {3, 5, 6}};
        MATCARREE m = new MATCARREE(matrice);

        // Vérification si la matrice est symétrique et affichage
        if (m.estSymetrique()) {
            System.out.println("La matrice est symétrique.");
            double[] compacte = MATCARREE.symCompacte(m);
            System.out.println("Représentation compacte :");
            for (double coef : compacte) {
                System.out.print(coef + " ");
            }
            System.out.println();
            System.out.println("Accès à un coefficient : " + MATCARREE.acces(compacte, 1, 0));

            // Traitement d'une ligne avec une fonction traiterCoef
            MATCARREE.traiterLigne(compacte, 1, coef -> System.out.print(coef + " "));
            System.out.println();

            // Affichage de la matrice à partir de la représentation compacte
            System.out.println("Affichage de la matrice :");
            MATCARREE.afficher(compacte);
        } else {
            System.out.println("La matrice n'est pas symétrique.");
        }
    }
}
