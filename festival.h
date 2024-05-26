#ifndef FESTIVAL_H
#define FESTIVAL_H

#define MAX_SALLE 10
#define MAX_TAILLE_NOM 50

typedef struct {
    char nom[MAX_TAILLE_NOM]; // Nom de la salle
    int rangee; // Nombre de rangées
    int place_rangee[MAX_SALLE]; // Nombre de places par rangée
    int categorie_A_rows; // Nombre de rangées dans la catégorie A
    struct {
        int categorie; // Catégorie de la place
        int reserver; // Statut de réservation de la place
    } places[MAX_SALLE][MAX_SALLE]; // Tableau des places
    int concert_actif; // Indicateur de concert actif
    int fosse; // Indicateur de fosse (zone debout)
    float prix[3]; // Prix des places pour chaque catégorie
    float prix_fosse; // Prix des places en fosse
    int capacite_fosse; // Capacité de la fosse
    int place_fosse; // Nombre de places réservées en fosse
} Salle;

typedef struct {
    Salle salles[MAX_SALLE]; // Tableau des salles
    int nbr_salles; // Nombre de salles
} Festival;

void initialisation_festival(Festival *festival); // Initialiser le festival
void donner_festival(Festival *festival); // Afficher les informations du festival
void donner_sauvegarder(Festival *festival); // Sauvegarder les informations du festival

#endif /* FESTIVAL_H */