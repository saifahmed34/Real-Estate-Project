#include<iostream>
#include <string>
using namespace std;
#ifndef PROJECT_FUND2_APARTMENT_H
#define PROJECT_FUND2_APARTMENT_H
class Apartment{
    friend void SaveApartmentData();
private:
    string ApartmentName;
    int apartment_id;
    int owner_account_id;
    int price;
public:

    Apartment(string name,int price);
    Apartment(string ApartmentName,int apartmentId,int ownerId,int price);
    void set_username(string user_name);
    void set_apartment_id(int app_id);
    void set_owner_account_id(int own_id);
    void set_price(int pricee);
    void set_info(int area,int room,int bathroom,string location,string advantages);
    string get_username();
    int get_apartment_id();
    int get_owner_account_id();
    int get_price();
    void print_All_Data();



};


#endif
