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
