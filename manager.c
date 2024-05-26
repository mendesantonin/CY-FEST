#include "festival.h"
#include "manager.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include "festivalier.h"

void creation_salle(Festival *festival) {
    if (festival->nbr_salles >= MAX_SALLE) {
        printf("Nombre maximum de salles atteint.\n");
        return;
    }

    Salle *salle = &festival->salles[festival->nbr_salles++];
    printf("Entrez le nom de la salle : ");
    scanf("%s", salle->nom);
    printf("Entrez le nombre de rangées : ");
    scanf("%d", &salle->rangee);

    int rangees_A, rangees_B;
    printf("Entrez le nombre de rangées en catégorie A : ");
    scanf("%d", &rangees_A);
    printf("Entrez le nombre de rangées en catégorie B : ");
    scanf("%d", &rangees_B);

    if (rangees_A + rangees_B > salle->rangee) {
        printf("Erreur : Le total des rangées pour les catégories A et B dépasse le nombre total de rangées.\n");
        return;
    }

    for (int i = 0; i < salle->rangee; i++) {
        printf("Entrez le nombre de sièges pour la rangée %d : ", i + 1);
        scanf("%d", &salle->place_rangee[i]);
        int categorie = 3; // Catégorie C par défaut
        if (i < rangees_A) {
            categorie = 1; // Catégorie A
        } else if (i < rangees_A + rangees_B) {
            categorie = 2; // Catégorie B
        }

        for (int j = 0; j < salle->place_rangee[i]; j++) {
            salle->places[i][j].categorie = categorie;
            salle->places[i][j].reserver = 0;
        }
    }

    salle->concert_actif = 0;
    salle->fosse = 0;
    salle->capacite_fosse = rangees_A * salle->place_rangee[0] * 2; // Exemple de calcul
    salle->categorie_A_rows = rangees_A; // Nombre de rangées de catégorie A
    salle->place_fosse = 0;
    salle->prix[0] = 50.0f; // Prix pour la catégorie A
    salle->prix[1] = 30.0f; // Prix pour la catégorie B
    salle->prix[2] = 20.0f; // Prix pour la catégorie C

    donner_sauvegarder(festival);
}

void assigner_concert_a_salle(Festival *festival) {
    char nom_salle[MAX_TAILLE_NOM];
    printf("Entrez le nom de la salle pour le concert : ");
    scanf("%s", nom_salle);

    for (int i = 0; i < festival->nbr_salles; i++) {
        if (strcmp(festival->salles[i].nom, nom_salle) == 0) {
            Salle *salle = &festival->salles[i];
            salle->concert_actif = 1;

            printf("Le concert a-t-il une fosse ? (1 = Oui, 0 = Non) : ");
            scanf("%d", &salle->fosse);

            if (salle->fosse) {
                printf("Entrez le prix pour les places en fosse : ");
                scanf("%f", &salle->prix_fosse);

                // Calcul du nombre de places en catégorie A et conversion en fosse
                int total_places_A = 0;
                for (int j = 0; j < salle->rangee; j++) {
                    for (int k = 0; k < salle->place_rangee[j]; k++) {
                        if (salle->places[j][k].categorie == 1) {
                            total_places_A++;
                        }
                    }
                }

                salle->capacite_fosse = total_places_A * 2;
                salle->categorie_A_rows = 0;
                for (int j = 0; j < salle->rangee; j++) {
                    if (salle->places[j][0].categorie == 1) {
                        salle->categorie_A_rows++;
                    }
                }
            }

            printf("Entrez le prix pour les sièges de catégorie A : ");
            scanf("%f", &salle->prix[0]);
            printf("Entrez le prix pour les sièges de catégorie B : ");
            scanf("%f", &salle->prix[1]);
            printf("Entrez le prix pour les sièges de catégorie C : ");
            scanf("%f", &salle->prix[2]);

            // Sauvegarde des données du festival pour refléter les modifications
            donner_sauvegarder(festival);

            // Affichage du plan de la salle pour que l'utilisateur puisse voir les changements
            afficher_plan_salle(salle);

            return;
        }
    }

    printf("Salle non trouvée.\n");
}

void modifier_salle(Salle *salle) {
    int choix;
    do {
        printf("Modifier la salle %s :\n", salle->nom);
        printf("1. Changer le nombre de rangées et de sièges\n");
        printf("2. Changer les prix des sièges\n");
        printf("3. Activer/Désactiver la fosse\n");
        printf("4. Changer le prix des places en fosse\n");
        printf("5. Retour\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                printf("Entrez le nombre de rangées : ");
                scanf("%d", &salle->rangee);

                int rangees_A, rangees_B;
                printf("Entrez le nombre de rangées en catégorie A : ");
                scanf("%d", &rangees_A);
                printf("Entrez le nombre de rangées en catégorie B : ");
                scanf("%d", &rangees_B);

                if (rangees_A + rangees_B > salle->rangee) {
                    printf("Erreur : Le total des rangées pour les catégories A et B dépasse le nombre total de rangées.\n");
                    return;
                }

                for (int i = 0; i < salle->rangee; i++) {
                    printf("Entrez le nombre de sièges pour la rangée %d : ", i + 1);
                    scanf("%d", &salle->place_rangee[i]);
                    int categorie = 3; // Catégorie C par défaut
                    if (i < rangees_A) {
                        categorie = 1; // Catégorie A
                    } else if (i < rangees_A + rangees_B) {
                        categorie = 2; // Catégorie B
                    }

                    for (int j = 0; j < salle->place_rangee[i]; j++) {
                        salle->places[i][j].categorie = categorie;
                        salle->places[i][j].reserver = 0; // Réinitialiser la réservation
                    }
                    salle->capacite_fosse = rangees_A * salle->place_rangee[0] * 2; // Exemple de calcul
                    salle->categorie_A_rows = rangees_A; // Nombre de rangées de catégorie A
                }
                break;
            }
            case 2: {
                printf("Entrez le nouveau prix pour les sièges de catégorie A : ");
                scanf("%f", &salle->prix[0]);
                printf("Entrez le nouveau prix pour les sièges de catégorie B : ");
                scanf("%f", &salle->prix[1]);
                printf("Entrez le nouveau prix pour les sièges de catégorie C : ");
                scanf("%f", &salle->prix[2]);
                break;
            }
            case 3: {
                printf("Le concert a-t-il une fosse ? (1 = Oui, 0 = Non) : ");
                scanf("%d", &salle->fosse);

                if (salle->fosse) {
                    printf("Entrez le prix pour les places en fosse : ");
                    scanf("%f", &salle->prix_fosse);

                    // Calcul du nombre de places en catégorie A et conversion en fosse
                    int total_places_A = 0;
                    for (int j = 0; j < salle->rangee; j++) {
                        for (int k = 0; k < salle->place_rangee[j]; k++) {
                            if (salle->places[j][k].categorie == 1) {
                                total_places_A++;
                            }
                        }
                    }

                    salle->capacite_fosse = total_places_A * 2;
                    salle->categorie_A_rows = 0;
                    for (int j = 0; j < salle->rangee; j++) {
                        if (salle->places[j][0].categorie == 1) {
                            salle->categorie_A_rows++;
                        }
                    }
                }
                break;
            }
            case 4: {
                if (salle->fosse) {
                    printf("Entrez le nouveau prix pour les places en fosse : ");
                    scanf("%f", &salle->prix_fosse);
                } else {
                    printf("La fosse n'est pas activée dans cette salle.\n");
                }
                break;
            }
            case 5:
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    } while (choix != 5);
}

void afficher_etat_salle(Festival *festival) {
    for (int i = 0; i < festival->nbr_salles; i++) {
        Salle *salle = &festival->salles[i];
        printf("Salle : %s, Concert en cours : %s\n", salle->nom, salle->concert_actif ? "Oui" : "Non");
        for (int j = 0; j < salle->rangee; j++) {
            int nombre_reserve = 0;
            for (int k = 0; k < salle->place_rangee[j]; k++) {
                if (salle->places[j][k].reserver) {
                    nombre_reserve++;
                }
            }
            printf("Rangée %d : %d/%d sièges réservés\n", j + 1, nombre_reserve, salle->place_rangee[j]);
        }
        if (salle->fosse) {
            printf("Fosse : %d/%d places réservées\n", salle->place_fosse, salle->capacite_fosse);
        }
    }
}

void menu_gestionnaire(Festival *festival) {
    int choix;
    do {
        lib_place();
        printf("=== Menu Gestionnaire ===\n");
        printf("1. Créer une nouvelle salle\n");
        printf("2. Assigner un concert à une salle\n");
        printf("3. Modifier une salle existante\n");
        printf("4. Voir l'état des salles\n");
        printf("5. Retour au menu principal\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creation_salle(festival);
                break;
            case 2:
                assigner_concert_a_salle(festival);
                break;
            case 3: {
                char nom_salle[MAX_TAILLE_NOM];
                printf("Entrez le nom de la salle à modifier : ");
                scanf("%s", nom_salle);
                for (int i = 0; i < festival->nbr_salles; i++) {
                    if (strcmp(festival->salles[i].nom, nom_salle) == 0) {
                        modifier_salle(&festival->salles[i]);
                        donner_sauvegarder(festival);  // Sauvegarder les modifications
                        break;
                    }
                }
                break;
            }
            case 4:
                afficher_etat_salle(festival);
                break;
            case 5:
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
        pause();
    } while (choix != 5);
}
