//
// Created by mo528 on 12/29/2023.
//

#ifndef PROJECT_FUND2_ACCOUNT_H
#define PROJECT_FUND2_ACCOUNT_H
#include "BankAccount.h"
class Account:public BankAccount {
    friend void SaveUserDataInToFile();
protected:
    string name;
    string username;
    string password;
    int age;
    int id;
public:
    string getName();
    int getId();
    void setId(int idd);
    Account(string name,string userName,string password,int age,int id,int balance=0);

    void printAccountData();
    bool CheckPassword(string pass);
    bool CheckUserName(string UserName);
    bool ChangePassword(string Opass,string Npass);
};

#endif //PROJECT_FUND2_ACCOUNT_H
