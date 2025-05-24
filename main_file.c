#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_ACCOUNTS 1000
#define MAX_TRANSACTIONS 100
#define FILENAME "bank_data.dat"
#define TRANSACTION_FILE "transactions.dat"

typedef struct {
    int acc_number;
    char name[100];
    char address[200];
    char phone[15];
    float balance;
    char created_date[20];
    int is_active;
} Account;

typedef struct {
    int acc_number;
    char type[20]; // "DEPOSIT", "WITHDRAWAL", "TRANSFER"
    float amount;
    char date[20];
    float balance_after;
} Transaction;

Account accounts[MAX_ACCOUNTS];
Transaction transactions[MAX_TRANSACTIONS * MAX_ACCOUNTS]; // Multiple transactions per account
int acc_count = 0;
int trans_count = 0;

// Utility functions
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int is_valid_phone(const char *phone) {
    int len = strlen(phone);
    if (len < 10 || len > 15) return 0;
    
    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i]) && phone[i] != '+' && phone[i] != '-' && phone[i] != ' ')
            return 0;
    }
    return 1;
}

float get_valid_amount(const char *prompt) {
    float amount;
    char input[100];
    int valid = 0;
    
    while (!valid) {
        printf("%s", prompt);
        fgets(input, sizeof(input), stdin);
        
        // Check if input is numeric
        valid = 1;
        for (int i = 0; input[i] != '\n' && input[i] != '\0'; i++) {
            if (!isdigit(input[i]) && input[i] != '.') {
                printf("Please enter a valid number.\n");
                valid = 0;
                break;
            }
        }
        
        if (valid) {
            amount = atof(input);
            if (amount <= 0) {
                printf("Amount must be greater than zero.\n");
                valid = 0;
            }
        }
    }
    
    return amount;
}

void get_current_date(char *date_str) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(date_str, 20, "%Y-%m-%d %H:%M:%S", t);
}

int generate_account_number() {
    // Generate a 6-digit account number that doesn't already exist
    int new_acc;
    int exists;
    
    do {
        exists = 0;
        new_acc = 100000 + rand() % 900000; // 6-digit number
        
        for (int i = 0; i < acc_count; i++) {
            if (accounts[i].acc_number == new_acc) {
                exists = 1;
                break;
            }
        }
    } while (exists);
    
    return new_acc;
}

void add_transaction(int acc_number, const char *type, float amount, float balance_after) {
    if (trans_count >= MAX_TRANSACTIONS * MAX_ACCOUNTS) {
        printf("Transaction limit reached.\n");
        return;
    }
    
    transactions[trans_count].acc_number = acc_number;
    strcpy(transactions[trans_count].type, type);
    transactions[trans_count].amount = amount;
    transactions[trans_count].balance_after = balance_after;
    get_current_date(transactions[trans_count].date);
    
    trans_count++;
}
void save_data() {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }
    
    fwrite(&acc_count, sizeof(int), 1, fp);
    fwrite(accounts, sizeof(Account), acc_count, fp);
    fclose(fp);
    
    // Save transactions
    fp = fopen(TRANSACTION_FILE, "wb");
    if (fp == NULL) {
        printf("Error: Could not open transaction file for saving.\n");
        return;
    }
    
    fwrite(&trans_count, sizeof(int), 1, fp);
    fwrite(transactions, sizeof(Transaction), trans_count, fp);
    fclose(fp);
    
    printf("Data saved successfully.\n");
}

