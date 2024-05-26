#include "festival.h"
#include "festivalier.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

void afficher_plan_salle(Salle *salle) {
    printf("Plan de la salle: %s\n", salle->nom);
    printf("            SCENE\n");

    for (int i = 0; i < salle->rangee; i++) {
        if (salle->fosse && salle->categorie_A_rows > 0 && i < salle->categorie_A_rows) {
            // Afficher la fosse pour les rangées de catégorie A
            if (i == 0) {
                printf("Nombre de places en fosse : %d\n", salle->capacite_fosse);
            }
        } else {
            printf("R %d ", i + 1);
            for (int j = 0; j < salle->place_rangee[i]; j++) {
                switch (salle->places[i][j].categorie) {
                    case 1:
                        printf(COLOR_A "0 " COLOR_RESET);
                        break;
                    case 2:
                        if (salle->places[i][j].reserver) {
                            printf("\033[1;31mX " COLOR_RESET);
                        } else {
                            printf(COLOR_B "0 " COLOR_RESET);
                        }
                        break;
                    case 3:
                        if (salle->places[i][j].reserver) {
                            printf("\033[1;31mX " COLOR_RESET);
                        } else {
                            printf(COLOR_C "0 " COLOR_RESET);
                        }
                        break;
                    default:
                        break;
                }
            }
            printf("\n");
        }
    }

    printf("Légende:\n");
    printf(COLOR_A "0" COLOR_RESET " - Catégorie A (%.2f euros)\n", salle->prix[0]);
    printf(COLOR_B "0" COLOR_RESET " - Catégorie B (%.2f euros)\n", salle->prix[1]);
    printf(COLOR_C "0" COLOR_RESET " - Catégorie C (%.2f euros)\n", salle->prix[2]);
    if (salle->fosse) {
        printf(COLOR_FAUSSE "[]" COLOR_RESET " - Fosse (%.2f euros)\n", salle->prix_fosse);
    }
    printf("\033[1;31mX\033[0m - Siège réservé\n");
}

void reserver_place(Festival *festival) {
    char nom_salle[MAX_TAILLE_NOM];
    printf("Entrez le nom de la salle pour la réservation: ");
    scanf("%s", nom_salle);

    for (int i = 0; i < festival->nbr_salles; i++) {
        if (strcmp(festival->salles[i].nom, nom_salle) == 0) {
            Salle *salle = &festival->salles[i];
            if (!salle->concert_actif) {
                printf("Aucun concert actif dans cette salle.\n");
                return;
            }

            afficher_plan_salle(salle);

            int reserver_autre = 1;
            while (reserver_autre) {
                if (salle->fosse) {
                    int reserver_fosse;
                    printf("Voulez-vous réserver une place en fosse ? (1 = Oui, 0 = Non): ");
                    scanf("%d", &reserver_fosse);

                    if (reserver_fosse) {
                        int places_fosse;
                        printf("Combien de places voulez-vous réserver en fosse ? ");
                        scanf("%d", &places_fosse);

                        if (salle->place_fosse + places_fosse <= salle->capacite_fosse) {
                            salle->capacite_fosse -= places_fosse;
                            salle->place_fosse += places_fosse;
                            printf("%d places réservées avec succès en fosse.\n", places_fosse);
                        } else {
                            printf("Il n'y a pas assez de places disponibles en fosse. Places disponibles: %d\n", salle->capacite_fosse - salle->place_fosse);
                        }
                    } else {
                        int rangée, siège;
                        printf("Entrez le numéro de rangée: ");
                        scanf("%d", &rangée);
                        printf("Entrez le numéro de siège: ");
                        scanf("%d", &siège);

                        // Vérifier si le numéro de rangée et le numéro de siège sont valides
                        if (rangée > 0 && rangée <= salle->rangee && siège > 0 && siège <= salle->place_rangee[rangée - 1]) {
                            if (!salle->places[rangée - 1][siège - 1].reserver) {
                                // Marquer le siège comme réservé dans la structure Hall
                                salle->places[rangée - 1][siège - 1].reserver = 1;
                                printf("Siège réservé avec succès.\n");
                            } else {
                                printf("Le siège est déjà réservé.\n");
                            }
                        } else {
                            printf("Sélection de siège invalide.\n");
                        }
                    }
                } else {
                    int rangée, siège;
                    printf("Entrez le numéro de rangée: ");
                    scanf("%d", &rangée);
                    printf("Entrez le numéro de siège: ");
                    scanf("%d", &siège);

                    // Vérifier si le numéro de rangée et le numéro de siège sont valides
                    if (rangée > 0 && rangée <= salle->rangee && siège > 0 && siège <= salle->place_rangee[rangée - 1]) {
                        if (!salle->places[rangée - 1][siège - 1].reserver) {
                            // Marquer le siège comme réservé dans la structure Hall
                            salle->places[rangée - 1][siège - 1].reserver = 1;
                            printf("Siège réservé avec succès.\n");
                        } else {
                            printf("Le siège est déjà réservé.\n");
                        }
                    } else {
                        printf("Sélection de siège invalide.\n");
                    }
                }

                donner_sauvegarder(festival);

                printf("Voulez-vous réserver une autre place ? (1 = Oui, 0 = Non): ");
                scanf("%d", &reserver_autre);
            }

            return;
        }
    }

    printf("Salle non trouvée.\n");
}

void festivalier_menu(Festival *festival) {
    int choix;
    do {
        lib_place();
        printf("=== Menu Festivalier ===\n");
        printf("1. Réserver un siège\n");
        printf("2. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                reserver_place(festival);
                break;
            case 2:
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
        pause();
    } while (choix != 2);
}
