//
// Created by mo528 on 12/29/2023.
//

#ifndef PROJECT_FUND2_BANKACCOUNT_H
#define PROJECT_FUND2_BANKACCOUNT_H
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class BankAccount {
    friend void SaveUserDataInToFile();
private:
    double balance;
protected:
    string BankAccountName;
public:

    BankAccount(double initialBalance = 0.0);
    void deposit(double amount);
    BankAccount& operator+=(double amount);
    bool withdraw(double amount);
    BankAccount& operator-=(double amount);
    double getBalance() const;
};



#endif //PROJECT_FUND2_BANKACCOUNT_H
