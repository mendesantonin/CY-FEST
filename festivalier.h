#ifndef FESTIVALIER_H
#define FESTIVALIER_H

#include "festival.h"

// Définition des codes de couleur
#define COLOR_A "\033[1;32m" // Vert pour Catégorie A
#define COLOR_B "\033[1;33m" // Jaune pour Catégorie B
#define COLOR_C "\033[1;37m" // Blanc pour Catégorie C
#define COLOR_FAUSSE "\033[1;34m" // Bleu pour la fosse
#define COLOR_RESET "\033[0m" // Réinitialiser la couleur

void afficher_plan_salle(Salle *salle);
void reserver_place(Festival *festival);
void menu_festivalier(Festival *festival);

#endif // FESTIVALIER_H
