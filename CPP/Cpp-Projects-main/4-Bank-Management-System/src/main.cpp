#include "BankAccount.hpp"
#include <iostream>

using namespace std;

// Main entry point for the bank management system.
int main() {
    BankAccount acc; // Create a default BankAccount object

    // Interactive account creation and display
    acc.createAccount();
    acc.displayAccount();

    // Perform operations
    acc.deposit(1000);
    
    // Call withdraw and display updated balance
    acc.withdraw(500);
    acc.displayAccount();

    return 0; // Indicate successful program execution
}