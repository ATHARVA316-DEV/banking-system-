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
