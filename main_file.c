// File operations
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