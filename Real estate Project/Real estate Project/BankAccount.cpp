//
// Created by mo528 on 12/29/2023.
//

#include "BankAccount.h"

BankAccount::BankAccount(double initialBalance ) : balance(initialBalance) {}
void BankAccount::deposit(double amount) {
    balance += amount;
    ofstream outfile("Money_Transaction.txt",ios::app);
    outfile<<BankAccountName<<" Deposit +"<<amount<<" Current Balance:"<<balance<<endl;
    outfile.close();
}
BankAccount& BankAccount::operator+=(double amount) {
    deposit(amount);
    return *this;
}
bool BankAccount::withdraw(double amount) {
    if (amount > balance) {
        return false;
    } else {
        balance -= amount;
        ofstream outfile("Money_Transaction.txt",ios::app);
        outfile<<BankAccountName<<" withdraw -"<<amount<<" Current Balance:"<<balance<<endl;
        outfile.close();

        return true;

    }
}
BankAccount& BankAccount::operator-=(double amount) {
    withdraw(amount);
    return *this;
}
double BankAccount::getBalance() const {
    return balance;
}