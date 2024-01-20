#include<iostream>
#include <string>
using namespace std;
#include "Apartment.h"
#include "User.h"
Apartment::Apartment(std::string ApartmentName, int apartmentId, int ownerId, int price):
ApartmentName(ApartmentName),apartment_id(apartmentId),owner_account_id(ownerId),price(price){

}
Apartment::Apartment(string name,int price): ApartmentName(name), price(price){

}
void Apartment::set_username(string user_name)
{
    ApartmentName=user_name;
}
void Apartment::set_apartment_id(int app_id)
{
    apartment_id=app_id;
}
void Apartment::set_owner_account_id(int own_id)
{
    owner_account_id=own_id;
}
void Apartment::set_price(int pricee)
{
    price=pricee;
}
string Apartment::get_username()
{
    return ApartmentName;
}
int Apartment::get_apartment_id()
{
    return apartment_id;
}
int Apartment::get_owner_account_id()
{
    return owner_account_id ;
}
int Apartment::get_price()
{
    return price ;
}
void Apartment::set_info(int area, int room,int bathroom,string location,string advantages)
{
    cout<<"area = "<<area<<endl<<"Room = "<<room<<endl<<"bathroom = "<<bathroom<<endl<<"location = "<<location<<endl;
    cout<<"advantages"<<advantages<<endl;
}


void Apartment::print_All_Data(){
    cout << "Name: " << ApartmentName << " apartment id: " << apartment_id << " owner account id: " << owner_account_id << " Price: " << price << endl;
}

