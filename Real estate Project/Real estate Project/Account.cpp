//
// Created by mo528 on 12/29/2023.
//

#include "Account.h"

void Account::setId(int idd){id=idd;}
Account::Account(string name,string userName,string password,int age,int id,int balance):
name(name),username(userName),password(password),age(age),id(id),BankAccount(balance){
    BankAccountName=name;
}
void Account::printAccountData(){
    cout<<name<<" "<<username<<" "<<age<<" "<<id<<endl;
}
bool Account::CheckPassword(string pass){
    return pass==password;
}
bool Account::CheckUserName(string UserName){
    return UserName==username;
}
bool Account::ChangePassword(string Opass,string Npass){
    if (Opass==password){
        password=Npass;
        return true;
    }
    return false;
}
string Account::getName(){return name;}
int Account::getId(){return id;}