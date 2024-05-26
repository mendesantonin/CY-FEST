#include "festival.h"
#include "manager.h"
#include "festivalier.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>


int main() {
    Festival festival;
    initialisation_festival(&festival);

    int choix;
    do {
        lib_place();  
        printf("===BIENVENU SUR CY'FEST===\n");
        printf("===choissisez votre mode===\n");
        printf("1. Mode Manager\n");
        printf("2. Mode Festivalier\n");
        printf("3. Quitter\n");    
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                menu_gestionnaire(&festival);
                break;
            case 2:
                festivalier_menu(&festival);
                break;
            case 3:
                printf("Sortie...\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
        pause();
    } while (choix != 3);

    return 0;
}