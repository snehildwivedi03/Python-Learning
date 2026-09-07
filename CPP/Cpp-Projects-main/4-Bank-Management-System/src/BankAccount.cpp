#include"BankAccount.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

// Default constructor: Initializes all members to safe defaults.
BankAccount::BankAccount() : accountNumber(0), holderName(""), balance(0.0), accountType("Savings") {}

// Parameterized constructor: Used for creating accounts with initial values.
BankAccount::BankAccount(int accNo, const string& name, const string& type, double initialBalance)
    : accountNumber(accNo), holderName(name), balance(initialBalance), accountType(type) {}

// Deposit method: Adds amount to balance if valid.
void BankAccount::deposit(double amount) {
    if (amount <= 0) {
        cout << "❌ Invalid deposit amount.\n";
        return;
    }
    balance += amount;
    cout << "✅ Deposited ₹" << amount << " successfully.\n";
}

// Withdraw method: Subtracts amount if valid and sufficient balance exists. Returns boolean status.
bool BankAccount::withdraw(double amount) {
    if (amount <= 0) {
        cout << "❌ Invalid withdrawal amount.\n";
        return false; // Return false on invalid amount
    }
    if (amount > balance) {
        cout << "⚠️ Insufficient balance.\n";
        return false; // Return false on insufficient funds
    }
    balance -= amount;
    cout << "✅ Withdrawn ₹" << amount << " successfully.\n";
    return true; // Return true on successful withdrawal
}

// Display method: Formats and prints all account details.
void BankAccount::displayAccount() const {
    cout << fixed << setprecision(2); // Set output to two decimal places
    cout << "\n--- Account Details ---\n";
    cout << "Account No: " << accountNumber << endl;
    cout << "Holder Name: " << holderName << endl;
    cout << "Type: " << accountType << endl;
    cout << "Balance: ₹" << balance << endl;
}

// Interactive helper function to read account details from user.
void BankAccount::createAccount() {
    cout << "\nEnter Account Number: ";
    cin >> accountNumber;
    cin.ignore(); // Consume the newline left by cin >> accountNumber

    cout << "Enter Account Holder Name: ";
    getline(cin, holderName);

    cout << "Enter Account Type (Savings/Current): ";
    getline(cin, accountType);

    cout << "Enter Initial Deposit Amount: ₹";
    cin >> balance;

    // Validate input and reset if invalid
    if (!isValid()) {
        cout << "❌ Invalid account details. Account not created.\n";
        accountNumber = 0;
        balance = 0;
    } else {
        cout << "✅ Account created successfully!\n";
    }
}

// Validation check: Ensures account number is positive, balance is non-negative, and name is not empty.
bool BankAccount::isValid() const {
    return (accountNumber > 0 && balance >= 0 && !holderName.empty());
}

// Getter implementations
int BankAccount::getAccountNumber() const { return accountNumber; }
double BankAccount::getBalance() const { return balance; }
string BankAccount::getHolderName() const { return holderName; }
string BankAccount::getAccountType() const { return accountType; }