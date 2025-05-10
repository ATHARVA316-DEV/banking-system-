#include <stdio.h>
#include <stdlib.h>
// #include "user.h"
// #include "transaction.h"
#include "security.h"
// #include "filemanager.h"
// #include "utils.h"


void displayMainMenu();
void handleAdminMenu();
void handleUserMenu();

int main() {
    int choice;

    printf("=====================================\n");
    printf(" Welcome to Silly Savings Banking System \n");
    printf("=====================================\n");

    if (!authenticateUser()) {
        printf(" Authentication failed. Exiting...\n");
        return EXIT_FAILURE;
    }

    printf(" Authentication successful. Welcome!\n");

    while (1) {
        displayMainMenu();
        choice = getValidatedIntegerInput("Enter your choice: ");

        switch (choice) {
            case 1: handleAdminMenu(); break;
            case 2: handleUserMenu(); break;
            case 3:
                printf(" Thank you for using Silly Savings. Goodbye!\n");
                return EXIT_SUCCESS;
            default:
                printf(" Invalid choice. Please try again.\n");
        }
    }
}

void displayMainMenu() {
    printf("\n========== Main Menu ==========\n");
    printf("1. Admin Module\n");
    printf("2. User Module\n");
    printf("3. Exit\n");
    printf("================================\n");
}

void handleAdminMenu() {
    int adminChoice;

    while (1) {
        printf("\n========== Admin Menu ==========\n");
        printf("1. Create User Account\n");
        printf("2. Update User Account\n");
        printf("3. Delete User Account\n");
        printf("4. View All Accounts\n");
        printf("5. Back to Main Menu\n");
        printf("================================\n");

        adminChoice = getValidatedIntegerInput("Enter your choice: ");

        switch (adminChoice) {
            case 1: createUserAccount(); break;
            case 2: updateUserAccount(); break;
            case 3: deleteUserAccount(); break;
            case 4: viewAllAccounts(); break;
            case 5: return;
            default: printf(" Invalid choice. Please try again.\n");
        }
    }
}

void handleUserMenu() {
    int userChoice;

    while (1) {
        printf("\n========== User Menu ==========\n");
        printf("1. Deposit Funds\n");
        printf("2. Withdraw Funds\n");
        printf("3. Transfer Funds\n");
        printf("4. View Transaction History\n");
        printf("5. Back to Main Menu\n");
        printf("================================\n");

        userChoice = getValidatedIntegerInput("Enter your choice: ");

        switch (userChoice) {
            case 1: depositFunds(); break;
            case 2: withdrawFunds(); break;
            case 3: transferFunds(); break;
            case 4: viewTransactionHistory(); break;
            case 5: return;
            default: printf(" Invalid choice. Please try again.\n");
        }
    }
}
