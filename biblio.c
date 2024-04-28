#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NbrMax 100

void saisir_nom(char *nom) {
    printf("Saisir votre nom : ");
    scanf("%s", nom);
}

typedef struct {
    char titre[100];
    char auteur[100];
    int annee;
    char id[100];
    char description[100];
    char nom_utilisateur[100];
    char categorie[100];
    float prix;
    int disponibilite;  // use 1 for true and 0 for false
} Livre;


//================= Fonction d'ajout d'un livre ========================

Livre *ajouterLivre(Livre *livres, int *nb_livres) {
    int i=1;


    //Allocation de mémoire
    Livre *new_livres = realloc(livres, sizeof(Livre) * (*nb_livres + 1));
    
    if (new_livres == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        return livres;
    }

    FILE *fichier = fopen("bibliotheque.txt", "a"); // Ouvrir le fichier en mode ajout
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return livres;
    }


    livres = new_livres;

        printf("Saisir les informations du livre %d:\n", *nb_livres + 1);

        printf("Entrez ID du livre : ");
        scanf(" %s", livres[*nb_livres].id);

        printf("Entrez le titre du livre : ");
        scanf(" %s", livres[*nb_livres].titre);

        printf("Entrez la Description du livre : ");
        scanf(" %s", livres[*nb_livres].description);

        printf("Entrez le Nom utilisateur du livre : ");
        scanf(" %s", livres[*nb_livres].nom_utilisateur);

        printf("Entrez la Catégorie du livre : ");
        scanf(" %s", livres[*nb_livres].categorie);

        printf("Entrez le Prix du livre : ");
        scanf("%f", &livres[*nb_livres].prix);

        printf("Entrez le Nom de l'auteur : ");
        scanf(" %s", livres[*nb_livres].auteur);

        printf("Entrez l'Année de publication : ");
        scanf("%d", &livres[*nb_livres].annee);

        printf("la disponibilitedu livre : ");
        livres[*nb_livres].disponibilite = 1;

        printf("Le livre a été ajouté avec succès.\n");
        (*nb_livres)++;


    fclose(fichier); // Fermer le fichier
    return livres;
}

//================= Fonction pour modifier les information d'un livre ========================

void modifierLivre(Livre *livres, int *nb_livres) {
    int i;
    char id_recherche[30];
    printf("Entrez l'ID du livre que vous souhaitez modifier : ");
    scanf("%s", id_recherche);

    for (i = 0; i < *nb_livres; i++) {
        if (!strcmp(livres[i].id, id_recherche)) {
            printf("Livre trouvé!\n");

            printf("Entrez le nouveau titre du livre : ");
            scanf(" %s", livres[i].titre);

            printf("Entrez la nouvelle description du livre : ");
            scanf(" %s", livres[i].description);

            printf("Entrez le nouveau nom utilisateur du livre : ");
            scanf(" %s", livres[i].nom_utilisateur);

            printf("Entrez la nouvelle catégorie du livre : ");
            scanf(" %s", livres[i].categorie);

            printf("Entrez le nouveau prix du livre : ");
            scanf("%f", &livres[i].prix);

            printf("Entrez le nouveau nom de l'auteur : ");
            scanf(" %s", livres[i].auteur);

            printf("Entrez la nouvelle année de publication : ");
            scanf("%d", &livres[i].annee);

            printf("La disponibilité du livre (1 pour oui, 0 pour non) : ");
            scanf("%d", &livres[i].disponibilite);

            printf("Les informations du livre ont été modifiées avec succès.\n\n");
            printf("Titre: %s\n", livres[i].titre);
            printf("Auteur: %s\n", livres[i].auteur);
            printf("Année de publication: %d\n", livres[i].annee);
            printf("ID: %s\n", livres[i].id);
            printf("Description: %s\n", livres[i].description);
            printf("Nom utilisateur: %s\n", livres[i].nom_utilisateur);
            printf("Catégorie: %s\n", livres[i].categorie);
            printf("Prix: %.2f\n", livres[i].prix);
            printf("Disponibilité: %s\n", livres[i].disponibilite ? "Oui" : "Non");
            return;
        }else {
            printf("Livre non trouvé.\n");
        }
    }

    
}


//================= Fonction pour Afficher les livres ========================

void afficherLivre(Livre *livres,  int nb_livres) {
    int i = 0;
    for (i = 0; i < nb_livres; i++) {
        printf("Titre: %s\n", livres[i].titre);
        printf("Auteur: %s\n", livres[i].auteur);
        printf("Année de publication: %d\n", livres[i].annee);
        printf("ID: %s\n", livres[i].id);
        printf("Description: %s\n", livres[i].description);
        printf("Nom utilisateur: %s\n", livres[i].nom_utilisateur);
        printf("Catégorie: %s\n", livres[i].categorie);
        printf("Prix: %.2f\n", livres[i].prix);
        printf("Disponibilité: %s\n", livres[i].disponibilite ? "Oui" : "Non");
    }
}


//================= Fonction pour Supprimer les livres ========================

void supprimerLivre(Livre *livres, int *nb_livres) {
    int i;
    char id_recherche[30];
    printf("Entrez l'ID du livre que vous souhaitez supprimer : ");
    scanf("%s", id_recherche);

    for (i = 0; i < *nb_livres; i++) {
        if (!strcmp(livres[i].id, id_recherche)) {
            printf("Livre trouvé!\n");

            // Décaler les éléments du tableau pour supprimer le livre
            for (int j = i; j < *nb_livres - 1; j++) {
                livres[j] = livres[j + 1];
            }

            (*nb_livres)--;

            printf("Le livre a été supprimé avec succès.\n");
            return;
        }
    }

    printf("Livre non trouvé.\n");
}

//================= Fonction pour Rechercher des Livres par (Titre, Auteur) ========================

void rechercherLivres(Livre *livres, int nb_livres) {
    char recherche[100];
    printf("Entrez le titre ou l'auteur à rechercher : ");
    scanf(" %s", recherche);

    int trouve = 0;
    for (int i = 0; i < nb_livres; i++) {
        if (strstr(livres[i].titre, recherche) != NULL || strstr(livres[i].auteur, recherche) != NULL) {
            printf("Livre trouvé !\n");
            printf("ID : %s\n", livres[i].id);
            printf("Titre : %s\n", livres[i].titre);
            printf("Description : %s\n", livres[i].description);
            printf("Nom utilisateur : %s\n", livres[i].nom_utilisateur);
            printf("Catégorie : %s\n", livres[i].categorie);
            printf("Prix : %.2f\n", livres[i].prix);
            printf("Auteur : %s\n", livres[i].auteur);
            printf("Année de publication : %d\n", livres[i].annee);
            printf("Disponibilité : %d\n", livres[i].disponibilite);
            printf("\n");
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun livre trouvé.\n");
    }
}


//================= Fonction pour Trier des livres par (Titre, Catégorie) ========================
void trierLivres(Livre *livres, int nb_livres) {
    // Trier par titre
    for (int i = 0; i < nb_livres - 1; i++) {
        for (int j = 0; j < nb_livres - i - 1; j++) {
            if (strcmp(livres[j].titre, livres[j + 1].titre) > 0) {
                Livre temp = livres[j];
                livres[j] = livres[j + 1];
                livres[j + 1] = temp;
            }
        }
    }

    // Trier par catégorie
    for (int i = 0; i < nb_livres - 1; i++) {
        for (int j = 0; j < nb_livres - i - 1; j++) {
            if (strcmp(livres[j].categorie, livres[j + 1].categorie) > 0) {
                Livre temp = livres[j];
                livres[j] = livres[j + 1];
                livres[j + 1] = temp;
            }
        }
    }

    printf("Les livres ont été triés par titre et catégorie.\n");
}

Livre *loadFromFile(Livre *livres, int *nb_livres) {
    FILE *fichier = fopen("bibliotheque.txt", "r"); // Ouvrir le fichier en mode lecture
    char id[30];
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }


    while (fscanf(fichier, "%s", id) != EOF) {

        if (!livres) livres = malloc(sizeof(Livre));
        else livres = realloc(livres, sizeof(Livre) * (*nb_livres + 1));

        strcpy(livres[*nb_livres].id, id);

        fscanf(fichier, "%s", livres[*nb_livres].titre);
        fscanf(fichier, "%s", livres[*nb_livres].description);
        fscanf(fichier, "%s", livres[*nb_livres].nom_utilisateur);
        fscanf(fichier, "%s", livres[*nb_livres].categorie);
        fscanf(fichier, "%f", &livres[*nb_livres].prix);
        fscanf(fichier, "%s", livres[*nb_livres].auteur);
        fscanf(fichier, "%d", &livres[*nb_livres].annee);
        fscanf(fichier, "%d", &livres[*nb_livres].disponibilite);
        (*nb_livres)++;
    }

    fclose(fichier); // Fermer le fichier
    return livres;
}

void saveToFile(Livre *livres, int nb_livres) {
    FILE *fichier = fopen("bibliotheque.txt", "w"); // Ouvrir le fichier en mode écriture
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < nb_livres; i++) {
        fprintf(fichier, "%s\n", livres[i].id);
        fprintf(fichier, "%s\n", livres[i].titre);
        fprintf(fichier, "%s\n", livres[i].description);
        fprintf(fichier, "%s\n", livres[i].nom_utilisateur);
        fprintf(fichier, "%s\n", livres[i].categorie);
        fprintf(fichier, "%.2f\n", livres[i].prix);
        fprintf(fichier, "%s\n", livres[i].auteur);
        fprintf(fichier, "%d\n", livres[i].annee);
        fprintf(fichier, "%d\n", livres[i].disponibilite);
    }

    fclose(fichier); // Fermer le fichier
}

int main() {
    
    Livre *bibliotheque = NULL;
    int nb_livres = 0;
    int choix;
    char nom[30];

    saisir_nom(nom);

    bibliotheque = loadFromFile(bibliotheque, &nb_livres);

    do {
        printf("Menu :\n");
        printf("******************\n");
        printf("1. Ajouter un livre\n");
        printf("2. Supprimer un livre\n");
        printf("3. Modifier un livre\n");
        printf("4. Rechercher des livres par (Titre, Auteur)\n");
        printf("5. Trier des livres par (Titre, Catégorie)\n");
        printf("6. Quitter\n");
        printf("******************\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                bibliotheque = ajouterLivre(bibliotheque, &nb_livres);
                break;
            case 2:
                supprimerLivre(bibliotheque, &nb_livres);
                afficherLivre(bibliotheque, nb_livres);
                break;
            case 3:
                modifierLivre(bibliotheque, &nb_livres);
                break;
            case 4:
                rechercherLivres(bibliotheque, nb_livres);
                break;
            case 5:
                trierLivres(bibliotheque, nb_livres);
                afficherLivre(bibliotheque, nb_livres);
                break;
            case 6:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

        
    } while (choix != 6);

    saveToFile(bibliotheque, nb_livres);
    free(bibliotheque);
        return 0;
}
