#ifndef MANAGER_H
#define MANAGER_H

#include "festival.h"

void creation_salle(Festival *festival);
void assigner_concert_a_salle(Festival *festival);
void modifier_salle(Salle *salle);
void afficher_statut_salle(Festival *festival);
void menu_manager(Festival *festival);

#endif // MANAGER_H


