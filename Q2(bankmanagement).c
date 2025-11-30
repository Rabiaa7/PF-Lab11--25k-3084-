#include <stdio.h>
#include <string.h>

struct Account {
    char name[50];
    int accountNumber;
    char type[20]; 
    float balance;
    float interestRate;
    float minBalance;
    char creationDate[15];
    char lastTransactionDate[15];
    char lastTransactionType[20]; 
};

void displayAccount(struct Account a) {
    printf("\nAccount Number: %d\n", a.accountNumber);
    printf("Name: %s\n", a.name);
    printf("Type: %s\n", a.type);
    printf("Balance: $%.2f\n", a.balance);
    printf("Interest Rate: %.2f%%\n", a.interestRate);
    printf("Minimum Balance: $%.2f\n", a.minBalance);
    printf("Account Creation Date: %s\n", a.creationDate);
    printf("Last Transaction: %s on %s\n", a.lastTransactionType, a.lastTransactionDate);
}

struct Account deposit(struct Account a, float amount, char date[]) {
    a.balance += amount;
    strcpy(a.lastTransactionType, "Deposit");
    strcpy(a.lastTransactionDate, date);
    printf("Deposited $%.2f successfully.\n", amount);
    return a;
}

struct Account withdraw(struct Account a, float amount, char date[]) {
    if (a.balance - amount < a.minBalance) {
        printf("Cannot withdraw $%.2f. Minimum balance requirement not met.\n", amount);
    } else {
        a.balance -= amount;
        strcpy(a.lastTransactionType, "Withdrawal");
        strcpy(a.lastTransactionDate, date);
        printf("Withdrawn $%.2f successfully.\n", amount);
    }
    return a;
}

struct Account initializeAccount(struct Account a) {
    if (strcmp(a.type, "Savings") == 0) {
        a.interestRate = 4.0;
        a.minBalance = 1000;
    } else if (strcmp(a.type, "Current") == 0) {
        a.interestRate = 0.0;
        a.minBalance = 5000;
    } else if (strcmp(a.type, "Fixed Deposit") == 0) {
        a.interestRate = 7.0;
        a.minBalance = 10000;
    } else {
        printf("Invalid account type!\n");
    }
    strcpy(a.lastTransactionType, "None");
    strcpy(a.lastTransactionDate, a.creationDate);
    return a;
}

int main() {
    struct Account account1;
    char date[15];
    int choice;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &account1.accountNumber);
    printf("Enter name: ");
    scanf(" %[^\n]", account1.name); 
    printf("Enter account type (Savings/Current/Fixed Deposit): ");
    scanf(" %[^\n]", account1.type);
    printf("Enter initial balance: ");
    scanf("%f", &account1.balance);
    printf("Enter account creation date (dd-mm-yyyy): ");
    scanf(" %[^\n]", account1.creationDate);

    account1 = initializeAccount(account1);

    do {
        printf("\n--- Bank Menu ---\n");
        printf("1. Display Account Info\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                displayAccount(account1);
                break;
            case 2:
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                printf("Enter transaction date (dd-mm-yyyy): ");
                scanf(" %[^\n]", date);
                account1 = deposit(account1, amount, date);
                break;
            case 3:
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                printf("Enter transaction date (dd-mm-yyyy): ");
                scanf(" %[^\n]", date);
                account1 = withdraw(account1, amount, date);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 4);

    return 0;
}