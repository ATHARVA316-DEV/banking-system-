..// File operations
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

void load_data() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No existing data file found. Starting with empty database.\n");
        return;
    }
    
    fread(&acc_count, sizeof(int), 1, fp);
    fread(accounts, sizeof(Account), acc_count, fp);
    fclose(fp);
    
    // Load transactions
    fp = fopen(TRANSACTION_FILE, "rb");
    if (fp == NULL) {
        printf("No existing transaction file found.\n");
        return;
    }
    
    fread(&trans_count, sizeof(int), 1, fp);
    fread(transactions, sizeof(Transaction), trans_count, fp);
    fclose(fp);
    
    printf("Loaded %d accounts and %d transactions.\n", acc_count, trans_count);
}

//Functions
void create_account() {
    if (acc_count >= MAX_ACCOUNTS) {
        printf("Account limit reached.\n");
        return;
    }
    
    Account new_account;
    
    // Generate a new account number
    new_account.acc_number = generate_account_number();
    printf("Generated Account Number: %d\n", new_account.acc_number);
    
    printf("Enter Full Name: ");
    clear_input_buffer();
    fgets(new_account.name, sizeof(new_account.name), stdin);
    new_account.name[strcspn(new_account.name, "\n")] = 0; // Remove newline
    
    printf("Enter Address: ");
    fgets(new_account.address, sizeof(new_account.address), stdin);
    new_account.address[strcspn(new_account.address, "\n")] = 0;
    
    do {
        printf("Enter Phone Number: ");
        fgets(new_account.phone, sizeof(new_account.phone), stdin);
        new_account.phone[strcspn(new_account.phone, "\n")] = 0;
        
        if (!is_valid_phone(new_account.phone)) {
            printf("Invalid phone number format. Please try again.\n");
        }
    } while (!is_valid_phone(new_account.phone));
    
    new_account.balance = get_valid_amount("Enter Initial Deposit: ");
    new_account.is_active = 1;
    get_current_date(new_account.created_date);
    
    accounts[acc_count] = new_account;
    acc_count++;
    
    // Add transaction record
    add_transaction(new_account.acc_number, "DEPOSIT", new_account.balance, new_account.balance);
    
    printf("Account created successfully!\n");
    save_data();
}

void view_accounts() {
    if (acc_count == 0) {
        printf("No accounts to display.\n");
        return;
    }
    
    printf("\n%-10s %-20s %-15s %-10s %-20s\n", 
           "Acc No", "Name", "Phone", "Balance", "Created On");
    printf("---------------------------------------------------------------------\n");
    
    for (int i = 0; i < acc_count; i++) {
        if (accounts[i].is_active) {
            printf("%-10d %-20s %-15s %-10.2f %-20s\n", 
                   accounts[i].acc_number, 
                   accounts[i].name, 
                   accounts[i].phone,
                   accounts[i].balance,
                   accounts[i].created_date);
        }
    }
    printf("---------------------------------------------------------------------\n");
}

int find_account_index(int acc_number) {
    for (int i = 0; i < acc_count; i++) {
        if (accounts[i].acc_number == acc_number && accounts[i].is_active)
            return i;
    }
    return -1;
}

void deposit() {
    int acc_number;
    float amount;
    
    printf("Enter Account Number: ");
    scanf("%d", &acc_number);
    
    int index = find_account_index(acc_number);
    if (index == -1) {
        printf("Account not found or inactive.\n");
        return;
    }
    
    clear_input_buffer();
    amount = get_valid_amount("Enter Deposit Amount: ");
    
    accounts[index].balance += amount;
    add_transaction(acc_number, "DEPOSIT", amount, accounts[index].balance);
    
    printf("Amount deposited successfully.\n");
    printf("New Balance: %.2f\n", accounts[index].balance);
    save_data();
}

void withdraw() {
    int acc_number;
    float amount;
    
    printf("Enter Account Number: ");
    scanf("%d", &acc_number);
    
    int index = find_account_index(acc_number);
    if (index == -1) {
        printf("Account not found or inactive.\n");
        return;
    }
    
    clear_input_buffer();
    amount = get_valid_amount("Enter Withdrawal Amount: ");
    
    if (amount > accounts[index].balance) {
        printf("Insufficient balance. Available balance: %.2f\n", accounts[index].balance);
    } else {
        accounts[index].balance -= amount;
        add_transaction(acc_number, "WITHDRAWAL", amount, accounts[index].balance);
        
        printf("Amount withdrawn successfully.\n");
        printf("New Balance: %.2f\n", accounts[index].balance);
        save_data();
    }
}

void transfer_funds() {
    int from_acc, to_acc;
    float amount;
    
    printf("Enter Source Account Number: ");
    scanf("%d", &from_acc);
    
    int from_index = find_account_index(from_acc);
    if (from_index == -1) {
        printf("Source account not found or inactive.\n");
        return;
    }
    
    printf("Enter Destination Account Number: ");
    scanf("%d", &to_acc);
    
    if (from_acc == to_acc) {
        printf("Cannot transfer to the same account.\n");
        return;
    }
    
    int to_index = find_account_index(to_acc);
    if (to_index == -1) {
        printf("Destination account not found or inactive.\n");
        return;
    }
    
    clear_input_buffer();
    amount = get_valid_amount("Enter Transfer Amount: ");
    
    if (amount > accounts[from_index].balance) {
        printf("Insufficient balance. Available balance: %.2f\n", accounts[from_index].balance);
    } else {
        accounts[from_index].balance -= amount;
        accounts[to_index].balance += amount;
        
        char transfer_desc[50];
        sprintf(transfer_desc, "TRANSFER TO %d", to_acc);
        add_transaction(from_acc, transfer_desc, amount, accounts[from_index].balance);
        
        sprintf(transfer_desc, "TRANSFER FROM %d", from_acc);
        add_transaction(to_acc, transfer_desc, amount, accounts[to_index].balance);
        
        printf("Transfer completed successfully.\n");
        printf("New Balance in Account %d: %.2f\n", from_acc, accounts[from_index].balance);
        save_data();
    }
}

void search_account() {
    int acc_number;
    
    printf("Enter Account Number: ");
    scanf("%d", &acc_number);
    
    int index = find_account_index(acc_number);
    if (index == -1) {
        printf("Account not found or inactive.\n");
    } else {
        printf("\n==== Account Details ====\n");
        printf("Account Number: %d\n", accounts[index].acc_number);
        printf("Name: %s\n", accounts[index].name);
        printf("Address: %s\n", accounts[index].address);
        printf("Phone: %s\n", accounts[index].phone);
        printf("Balance: %.2f\n", accounts[index].balance);
        printf("Created On: %s\n", accounts[index].created_date);
    }
}

void modify_account() {
    int acc_number;
    
    printf("Enter Account Number to modify: ");
    scanf("%d", &acc_number);
    
    int index = find_account_index(acc_number);
    if (index == -1) {
        printf("Account not found or inactive.\n");
        return;
    }
    
    printf("\nCurrent Account Details:\n");
    printf("1. Name: %s\n", accounts[index].name);
    printf("2. Address: %s\n", accounts[index].address);
    printf("3. Phone: %s\n", accounts[index].phone);
    
    int choice;
    printf("\nWhat would you like to modify?\n");
    printf("1. Name\n2. Address\n3. Phone\n4. Cancel\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    clear_input_buffer();
    
    switch(choice) {
        case 1:
            printf("Enter New Name: ");
            fgets(accounts[index].name, sizeof(accounts[index].name), stdin);
            accounts[index].name[strcspn(accounts[index].name, "\n")] = 0;
            printf("Name updated successfully.\n");
            break;
        case 2:
            printf("Enter New Address: ");
            fgets(accounts[index].address, sizeof(accounts[index].address), stdin);
            accounts[index].address[strcspn(accounts[index].address, "\n")] = 0;
            printf("Address updated successfully.\n");
            break;
        case 3:
            do {
                printf("Enter New Phone: ");
                fgets(accounts[index].phone, sizeof(accounts[index].phone), stdin);
                accounts[index].phone[strcspn(accounts[index].phone, "\n")] = 0;
                
                if (!is_valid_phone(accounts[index].phone)) {
                    printf("Invalid phone number format. Please try again.\n");
                }
            } while (!is_valid_phone(accounts[index].phone));
            printf("Phone updated successfully.\n");
            break;
        case 4:
            printf("Modification cancelled.\n");
            return;
        default:
            printf("Invalid choice.\n");
            return;
    }
    
    save_data();
}

void delete_account() {
    int acc_number;
    char confirm;
    
    printf("Enter Account Number to delete: ");
    scanf("%d", &acc_number);
    
    int index = find_account_index(acc_number);
    if (index == -1) {
        printf("Account not found or already inactive.\n");
        return;
    }
    
    printf("\nAccount Details:\n");
    printf("Name: %s\n", accounts[index].name);
    printf("Balance: %.2f\n", accounts[index].balance);
    
    clear_input_buffer();
    printf("Are you sure you want to delete this account? (y/n): ");
    scanf("%c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        // Soft delete - just mark as inactive
        accounts[index].is_active = 0;
        printf("Account deleted successfully.\n");
        save_data();
    } else {
        printf("Account deletion cancelled.\n");
    }
}

void view_transactions() {
    int acc_number;
    
    printf("Enter Account Number: ");
    scanf("%d", &acc_number);
    
    int index = find_account_index(acc_number);
    if (index == -1) {
        printf("Account not found or inactive.\n");
        return;
    }
    
    printf("\n==== Transaction History for Account %d ====\n", acc_number);
    printf("%-20s %-15s %-12s %-12s\n", "Date", "Type", "Amount", "Balance");
    printf("----------------------------------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < trans_count; i++) {
        if (transactions[i].acc_number == acc_number) {
            printf("%-20s %-15s $%-11.2f $%-11.2f\n", 
                   transactions[i].date, 
                   transactions[i].type, 
                   transactions[i].amount,
                   transactions[i].balance_after);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No transactions found for this account.\n");
    }
    printf("----------------------------------------------------------------\n");
}

void generate_statement() {
    int acc_number;
    
    printf("Enter Account Number: ");
    scanf("%d", &acc_number);
    
    int index = find_account_index(acc_number);
    if (index == -1) {
        printf("Account not found or inactive.\n");
        return;
    }
    
    char filename[50];
    sprintf(filename, "statement_%d.txt", acc_number);
    
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not create statement file.\n");
        return;
    }
    
    fprintf(fp, "=====================================================\n");
    fprintf(fp, "                   BANK STATEMENT                   \n");
    fprintf(fp, "=====================================================\n\n");
    
    fprintf(fp, "Account Number: %d\n", accounts[index].acc_number);
    fprintf(fp, "Account Holder: %s\n", accounts[index].name);
    fprintf(fp, "Address: %s\n", accounts[index].address);
    fprintf(fp, "Phone: %s\n\n", accounts[index].phone);
    
    char current_date[20];
    get_current_date(current_date);
    fprintf(fp, "Statement Date: %s\n", current_date);
    fprintf(fp, "Current Balance: $%.2f\n\n", accounts[index].balance);
    
    fprintf(fp, "Transaction History:\n");
    fprintf(fp, "%-20s %-20s %-12s %-12s\n", "Date", "Description", "Amount", "Balance");
    fprintf(fp, "---------------------------------------------------------------------\n");
    
    for (int i = 0; i < trans_count; i++) {
        if (transactions[i].acc_number == acc_number) {
            fprintf(fp, "%-20s %-20s $%-11.2f $%-11.2f\n", 
                   transactions[i].date, 
                   transactions[i].type, 
                   transactions[i].amount,
                   transactions[i].balance_after);
        }
    }
    
    fprintf(fp, "---------------------------------------------------------------------\n");
    fprintf(fp, "\nThank you for banking with us!\n");
    
    fclose(fp);
    printf("Statement generated successfully: %s\n", filename);
}

void search_by_name() {
    char search_name[100];
    int found = 0;
    
    printf("Enter name to search (partial name is okay): ");
    clear_input_buffer();
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = 0; // Remove newline
    
    // Convert search string to lowercase for case-insensitive search
    for (int i = 0; search_name[i]; i++) {
        search_name[i] = tolower(search_name[i]);
    }
    
    printf("\nSearch Results:\n");
    printf("%-10s %-20s %-15s %-10s\n", "Acc No", "Name", "Phone", "Balance");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < acc_count; i++) {
        if (accounts[i].is_active) {
            // Make a lowercase copy of the account name for comparison
            char temp_name[100];
            strcpy(temp_name, accounts[i].name);
            for (int j = 0; temp_name[j]; j++) {
                temp_name[j] = tolower(temp_name[j]);
            }
            
            if (strstr(temp_name, search_name) != NULL) {
                printf("%-10d %-20s %-15s %-10.2f\n", 
                       accounts[i].acc_number, 
                       accounts[i].name, 
                       accounts[i].phone,
                       accounts[i].balance);
                found = 1;
            }
        }
    }
    
    if (!found) {
        printf("No matching accounts found.\n");
    }
}

int main() {
    // Seed random number generator
    srand(time(NULL));
    
    // Load data from file if it exists
    load_data();
    
    int choice;
    
    do {
        printf("\n============================================\n");
        printf("        ADVANCED BANKING SYSTEM MENU        \n");
        printf("============================================\n");
        printf("1.  Create New Account\n");
        printf("2.  View All Accounts\n");
        printf("3.  Deposit\n");
        printf("4.  Withdraw\n");
        printf("5.  Transfer Funds\n");
        printf("6.  Search Account\n");
        printf("7.  Modify Account\n");
        printf("8.  Delete Account\n");
        printf("9.  View Transactions\n");
        printf("10. Generate Account Statement\n");
        printf("11. Search by Name\n");
        printf("0.  Exit\n");
        printf("--------------------------------------------\n");
        printf("Choose an option (0-11): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: create_account(); break;
            case 2: view_accounts(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: transfer_funds(); break;
            case 6: search_account(); break;
            case 7: modify_account(); break;
            case 8: delete_account(); break;
            case 9: view_transactions(); break;
            case 10: generate_statement(); break;
            case 11: search_by_name(); break;
            case 0: 
                printf("Saving data before exit...\n");
                save_data();
                printf("Thank you for using the banking system!\n");
                break;
            default: 
                printf("Invalid choice. Please try again.\n");
        }
        
    } while (choice != 0);
    
    return 0;
}