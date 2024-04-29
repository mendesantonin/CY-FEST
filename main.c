#include <stdio.h>
#include "manager.h"
#include "festivalier.h"

int main() {
    int choice;
    
    do {
        printf("\n=== Welcome to Festival Management System ===\n");
        printf("1. Manager Mode\n");
        printf("2. Festivalier Mode\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                managerMenu();
                break;
            case 2:
                festivalierMenu();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 3);
    
    return 0;
}
