#include "festival.h"
#include <stdio.h>
#include <stdlib.h>

void initialisation_festival(Festival *festival) {
    festival->nbr_salles = 0;
}

void donner_festival(Festival *festival) {
    FILE *fichier = fopen("donnees_festival.dat", "rb");
    if (fichier) {
        fread(festival, sizeof(Festival), 1, fichier);
        fclose(fichier);
    } else {
        printf("Impossible de charger les données du festival.\n");
    }
}

void donner_sauvegarder(Festival *festival) {
    FILE *fichier = fopen("donnees_festival.dat", "wb");
    if (fichier) {
        fwrite(festival, sizeof(Festival), 1, fichier);
        fclose(fichier);
    } else {
        printf("Impossible de sauvegarder les données du festival.\n");
    }
}
