#ifndef PROJECT_FUND2_USER_H
#define PROJECT_FUND2_USER_H
#include "Apartment.h"
#include "BankAccount.h"
#include "Account.h"

class User:public Account{
    friend void SaveUserDataInToFile();
    friend void SaveApartmentData();
private:
    vector<Apartment>MyApartment;
    void ReSet();
public:
    User(string name,string userName,string password,int age,int id,int balance=0);
    int getNumOfApartment();
    void add_apartment(Apartment lms);
    void remove_appartment(int id);
    bool sell(User& buyer,int app_id);
    void print_all_myapartment();

};
#endif
