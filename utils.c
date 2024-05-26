#include "utils.h"
#include <stdio.h>

void lib_place() {
    printf("\033[H\033[J"); 
}

void pause() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
    getchar();
    
}
