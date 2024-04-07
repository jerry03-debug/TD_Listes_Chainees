import java.util.*;

// Définition des classes pour les structures de données
class Maillon {
    int numero;
    Maillon suiv, prec;

    Maillon(int num) {
        this.numero = num;
        this.suiv = null;
        this.prec = null;
    }
}

class LCB {
    Maillon tete, queue;

    LCB() {
        this.tete = null;
        this.queue = null;
    }
}

class Node {
    String nom;
    LCB numeros;
    Node gauche, droit;

    Node(String nom) {
        this.nom = nom;
        this.numeros = new LCB();
        this.gauche = null;
        this.droit = null;
    }
}

public class Exercice8 {
    // Ajouter un numéro à une liste chaînée bidirectionnelle (LCB)
    static LCB ajoutNumero(int num, LCB numeros) {
        // Création du nouveau maillon
        Maillon nouveauMaillon = new Maillon(num);

        // Cas où la LCB est vide
        if (numeros.tete == null) {
            numeros.tete = nouveauMaillon;
            numeros.queue = nouveauMaillon;
        } else {
            // Parcours de la LCB pour trouver l'emplacement d'insertion
            Maillon current = numeros.tete;
            while (current != null && current.numero < num) {
                current = current.suiv;
            }

            // Insertion du nouveau maillon
            if (current == null) { // Nouveau numéro est le plus grand, l'ajouter à la fin
                numeros.queue.suiv = nouveauMaillon;
                nouveauMaillon.prec = numeros.queue;
                numeros.queue = nouveauMaillon;
            } else if (current.prec == null) { // Insérer au début
                nouveauMaillon.suiv = numeros.tete;
                numeros.tete.prec = nouveauMaillon;
                numeros.tete = nouveauMaillon;
            } else { // Insérer au milieu
                nouveauMaillon.suiv = current;
                nouveauMaillon.prec = current.prec;
                current.prec.suiv = nouveauMaillon;
                current.prec = nouveauMaillon;
            }
        }
        return numeros;
    }

    // Ajouter un nom propre avec ses numéros de page associés dans un ABR
    static Node ajoutNomPropre(String nom, int[] t, Node a) {
        // Si l'arbre est vide, créer un nouveau nœud
        if (a == null) {
            // Créer un nouveau nœud
            a = new Node(nom);

            // Insérer les numéros de page dans la liste
            for (int i = 0; i < t.length; i++) {
                a.numeros = ajoutNumero(t[i], a.numeros);
            }
        } else {
            // Comparer le nom avec le nom actuel dans le nœud
            int cmp = nom.compareTo(a.nom);
            // Si le nom est inférieur, aller à gauche
            if (cmp < 0) {
                a.gauche = ajoutNomPropre(nom, t, a.gauche);
            }
            // Si le nom est supérieur, aller à droite
            else if (cmp > 0) {
                a.droit = ajoutNomPropre(nom, t, a.droit);
            }
            // Si le nom est déjà présent, mettre à jour la liste des numéros de page
            else {
                for (int i = 0; i < t.length; i++) {
                    a.numeros = ajoutNumero(t[i], a.numeros);
                }
            }
        }
        return a;
    }

    // Supprimer un numéro de page pour un nom donné dans un ABR
    static Node supprimerNumero(String nom, int numero, Node a) {
        if (a == null) {
            return null; // Si l'arbre est vide, retourner null
        }
        int cmp = nom.compareTo(a.nom);
        if (cmp < 0) {
            a.gauche = supprimerNumero(nom, numero, a.gauche);
        } else if (cmp > 0) {
            a.droit = supprimerNumero(nom, numero, a.droit);
        } else {
            // Si le nom est trouvé, supprimer le numéro de page de la LCB
            Maillon current = a.numeros.tete;
            while (current != null) {
                if (current.numero == numero) {
                    // Supprimer le maillon contenant le numéro donné
                    if (current.prec == null) {
                        // Premier maillon
                        a.numeros.tete = current.suiv;
                        if (a.numeros.tete != null) {
                            a.numeros.tete.prec = null;
                        } else {
                            a.numeros.queue = null; // La liste est maintenant vide
                        }
                    } else {
                        // Maillon au milieu ou à la fin
                        current.prec.suiv = current.suiv;
                        if (current.suiv != null) {
                            current.suiv.prec = current.prec;
                        } else {
                            a.numeros.queue = current.prec; // Le dernier maillon est supprimé
                        }
                    }
                    break; // Sortir de la boucle après avoir trouvé et supprimé le numéro
                }
                current = current.suiv;
            }
        }
        return a;
    }

    // Afficher une liste chaînée bidirectionnelle (LCB)
    static void afficherLCB(LCB numeros) {
        Maillon current = numeros.tete;
        while (current != null) {
            System.out.print(current.numero + " ");
            current = current.suiv;
        }
        System.out.println();
    }

    // Afficher l'index alphabétique à partir de l'ABR
    static void afficherIndex(Node a) {
        if (a != null) {
            afficherIndex(a.gauche);
            System.out.print(a.nom + " : ");
            afficherLCB(a.numeros);
            afficherIndex(a.droit);
        }
    }

    // Fonction main pour tester les fonctions
    public static void main(String[] args) {
        // Exemple pour tester les fonctions
        Node index = null;

        // Ajouter des noms et leurs numéros de page associés
        int[] pagesFatou = {110, 250, 300};
        index = ajoutNomPropre("Fatou", pagesFatou, index);

        int[] pagesMamadou = {3, 14, 101};
        index = ajoutNomPropre("Mamadou", pagesMamadou, index);

        int[] pagesOusseynou = {11, 50};
        index = ajoutNomPropre("Ousseynou", pagesOusseynou, index);

        int[] pagesPierre = {3, 7, 100, 287};
        index = ajoutNomPropre("Pierre", pagesPierre, index);

        int[] pagesSoda = {6, 10, 34, 66, 98};
        index = ajoutNomPropre("Soda", pagesSoda, index);

        // Afficher l'index
        System.out.println("Index alphabétique :");
        afficherIndex(index);

        // Supprimer un numéro de page pour un nom donné
        index = supprimerNumero("Pierre", 287, index);

        // Afficher l'index mis à jour
        System.out.println("\nIndex alphabétique après la suppression :");
        afficherIndex(index);

        // Exemple d'ajout d'un numéro supplémentaire
        System.out.println("\nExemple d'ajout d'un numéro supplémentaire :");
        index.numeros = ajoutNumero(105, index.numeros);
        afficherIndex(index);
    }
}
