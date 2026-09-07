#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

#include<string>

class BankAccount {
  // Encapsulated Data Members (Private)
  private:
  int accountNumber;
  std::string holderName;
  double balance;
  std::string accountType;

  public:
  // Constructors
  BankAccount();
  BankAccount(int accNo, const std::string &name,const std::string& type, double initialBalance=0.0);

  // Core Operations (Public Interface)
  void deposit(double amount);
  bool withdraw(double amount);  // Returns true on success, false otherwise.
  void displayAccount() const;   // Prints account details to console.

  // Getter Methods (Read-only access)
  int getAccountNumber() const;
  double getBalance() const;
  std::string getHolderName() const;
  std::string getAccountType() const;

  // Utility Methods
  void createAccount();
  bool isValid() const;
};

#endif