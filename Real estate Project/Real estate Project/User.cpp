#include "User.h"
#include "Apartment.h"
using namespace std;
#include <iostream>
#include <fstream>


User::User(string name,string userName,string password,int age,int id,int balance):
Account(name,userName,password,age,id,balance){

}
void User::add_apartment(Apartment NewApartment){
    NewApartment.set_apartment_id(MyApartment.size());
    NewApartment.set_owner_account_id(id);
    MyApartment.push_back(NewApartment);
}
void User::ReSet() {
    for (int i = 0; i < MyApartment.size(); ++i) {
        MyApartment.at(i).set_apartment_id(i);
    }
}
void User::remove_appartment(int id) {
    MyApartment.erase(MyApartment.begin()+id);
    ReSet();
}
int User::getNumOfApartment(){
    return MyApartment.size();
}

bool User::sell(User& buyer,int  app_id){
    string apartment= MyApartment.at(app_id).get_username();
    string ownerName =name;
    string buyerName = buyer.name;
    ofstream outfile("Sold_Apartment.txt");
    outfile<<apartment<<ownerName<<buyerName;
    Apartment& app=MyApartment.at(app_id);
    if (buyer.withdraw(app.get_price())){
        ofstream apartmentSellLogFile("apartmentSellLog.txt",ios::app);
        apartmentSellLogFile<<"apartment "<<apartment<<" Sold from "<<ownerName<<" to "<<buyerName<<endl;
        apartmentSellLogFile.close();
        //this accont Deposit
        deposit(app.get_price());
        //give appart to the buyer
        buyer.add_apartment(app);

        //remove the app from me
        remove_appartment(app.get_apartment_id());
        ReSet();
        return true;
    }else{
     return false;
    }
}

void User::print_all_myapartment() {
    for (auto &val:MyApartment) {
        val.print_All_Data();
    }

}
