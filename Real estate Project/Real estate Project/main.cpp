#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
#include "Apartment.h"
#include "User.h"
#ifdef _WIN32
//for windows
#define ClearScreen system("cls");
#define StopScreen  system("pause");

const int space = 70;
#else
// for linux
    #define ClearScreen system("clear");
    #define StopScreen  system("echo press any key ; read");
#endif
//store users in vector
vector<User>UserData;
//there is no user
User* CurrentLoginAccount= nullptr;
string adminName,adminPassword;
void printMyApartment(){
    CurrentLoginAccount->print_all_myapartment();
}

///================Data Base with Files ====================
const string UserSaveLocation{"UserSaveData.txt"};
const string ApartmentSaveLocation{"ApartmentSaveData.txt"};
void SaveUserDataInToFile(){
    ofstream outUserDataOut(UserSaveLocation);
    outUserDataOut<<UserData.size()<<endl;
    for (auto x:UserData) {
        outUserDataOut<<x.balance<<" "<<x.name<<" "<<x.username<<" "<<x.password<<" "<<x.age<<endl;
    }
    outUserDataOut.close();
}
void SaveApartmentData(){
    ofstream outUserDataOut(ApartmentSaveLocation);
    for (auto x:UserData) {
        outUserDataOut<<" "<<x.getNumOfApartment()<<endl;
        for (auto xA:x.MyApartment) {
            outUserDataOut<<xA.ApartmentName<<" "<<xA.apartment_id<<" "<<xA.owner_account_id<<" "<<xA.price<<endl;
        }
    }
    outUserDataOut.close();
}
void loadData(){
    UserData.clear();
    ifstream UserIn(UserSaveLocation);
    ifstream AppIn(ApartmentSaveLocation);


    if (UserIn.fail()||AppIn.fail()||UserIn.peek() == std::ifstream::traits_type::eof()||AppIn.peek() == std::ifstream::traits_type::eof()){return;}

    int NumOfUsers;UserIn>>NumOfUsers;
    while (NumOfUsers--){
        int balance,age;
        string name,userName,password;
        UserIn>>balance>>name>>userName>>password>>age;
        UserData.push_back({name,userName,password,age,(int)UserData.size(),balance});

        string ApartmentName;
        int apartmentId,ownerId,price,NumOfApartment;

        AppIn>>NumOfApartment;
        while (NumOfApartment--){
            AppIn>>ApartmentName>>apartmentId>>ownerId>>price;
            UserData.back().add_apartment({ApartmentName,apartmentId,ownerId,price});
        }

    }
    UserIn.close();
}
void clearFile(string FileLocation){
    fstream File(FileLocation,ios::in);
    if (File.fail()){return;}
    else{
        File.close();
        File.open(FileLocation,ios::out);
        File.close();
    }
}
void ClearAllDataInFile(){
    clearFile(UserSaveLocation);
    clearFile(ApartmentSaveLocation);
}
void ExitProgram(){
    SaveUserDataInToFile();
    SaveApartmentData();
    exit(0);
}



///=====================================================================


//======================================Add Apartment======================================================//
void addApartment(){

    string ApartmentName;
   int ApartmentPrice;

    cout<<"Apartment Name:";
    cin>>ApartmentName;
    cout<<"Apartment price:";
    cin>>ApartmentPrice;
    CurrentLoginAccount->add_apartment({ApartmentName,ApartmentPrice});
    //put any added apartment to file called apartment_data
    ofstream outFile("apartment_data.txt", ios::app);


    if (!outFile.is_open()) {
        cout << "Error opening apartment file for writing.\n";
        return;
    }

    // Write apartment data to the file
    outFile << CurrentLoginAccount->getId() << " " << ApartmentName << " " << ApartmentPrice << "\n";
    outFile.close();

    SaveUserDataInToFile();
    SaveApartmentData();
    cout << "Apartment added successfully!\n";

}
//=====================================================================================================//

//==============================================================
int IsUserNameExistById(const string& name){
    for (auto& x:UserData) {
        if (x.CheckUserName(name)){
            return x.getId();
        }
    }
    return -1;
}
void PrintFiles(const string& FileName) {
    ifstream inputFile(FileName);

    if (!inputFile.is_open()) {
        cout << "Error opening file: " << FileName << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close();
}
void PrintLogFile() {
    int choice;
    cout << "Choose a file to print:\n";
    cout << "1. user_data.txt\n";
    cout << "2. apartment_data.txt\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            ClearScreen
            PrintFiles("user_data.txt");
                cout<<endl;
            break;
        case 2:
            ClearScreen
            PrintFiles("apartment_data.txt");
            cout<<endl;
            break;
        default:
            cout << "Invalid choice\n";
    }
}
void clearLogFiles(){
    clearFile("user_data.txt");
    clearFile("apartment_data.txt");
}
/*
    name(name),ApartmentName(userName),password(password),age(age),id(id){
 * */
bool isValidUserName(const string& username) {

    if (username.length() >= 3) {
        return true;
    } else {
        cout << "Invalid username. It should be at least 3 characters long.\n";
        return false;
    }
}
bool isValidPassword(const string& password) {
    // Check if the password is at least 8 characters long
    if (password.length() < 8) {
        cout << "Invalid password. It should be at least 8 characters long.\n";
        return false;
    }

    // Check if the password contains at least one uppercase letter, one lowercase letter, and one digit
    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
// check the upperCase
    for (char ch : password) {
        if (isupper(ch)) {
            hasUppercase = true;
        } else if (islower(ch)) {
            hasLowercase = true;
        } else if (isdigit(ch)) {
            hasDigit = true;
        }
    }
    //if something wrong in password
    if (!hasUppercase || !hasLowercase || !hasDigit) {
        cout << "Invalid password. It should contain at least one uppercase letter, one lowercase letter, and one digit.\n";
        return false;
    }

    // If the password passed all checks, it is valid
    return true;
};

bool addAccount(){
    cout<<setw(space)<<"SignUp\n";
    string userName,FullName,Password;
    int age;
    cout<<"Your Account Must have letters and digits\n";
    cout<<"Enter Your userName:";cin>>userName;
    if (IsUserNameExistById(userName)!=-1|| !isValidUserName(userName)){
        cout<<"Account Name Not Valid\n";
        return false;
    }
    cout<<"Enter Your FullName:";cin>>FullName;
    cout<<"Your Password must have 8 letters and Caps\n\n";
    cout<<"Enter Your Password:";cin>>Password;
    if (!isValidPassword(Password)){
        cout<<"Password not Valid\n";
        return false;
    }
    cout<<"Enter Your age:";cin>>age;

    ofstream outFile("user_data.txt", std::ios::app);


    if (!outFile.is_open()) {
        cout << "Error opening file for writing.\n";
        return false;
    }


    outFile << userName << " " << FullName << " " << Password << " " << age << " " << UserData.size() << "\n";


    outFile.close();


    UserData.push_back({FullName, userName, Password, age, (int)UserData.size()});

    SaveUserDataInToFile();
    SaveApartmentData();
    return true;
}
void resetId(){
    for (int i = 0; i < UserData.size(); ++i) {
        UserData.at(i).setId(i);
    }
}
bool removeAccountById(int id){
    if (UserData.size()<=id){
        return false;
    }
    UserData.erase(UserData.begin()+id);
    resetId();
    SaveUserDataInToFile();
    SaveApartmentData();
    return true;
}
bool login(){
    cout<<setw(space)<<"Login\n";
    string userName,Password;
    cout<<"enter Your UserName: ";cin>>userName;
    int idRes=IsUserNameExistById(userName);
    if (idRes==-1){
        cout<<"User Name Does not Exist";
        return false;
    }
    cout<<"enter Your Password: ";cin>>Password;
    if (UserData.at(idRes).CheckPassword(Password)){
        CurrentLoginAccount=&UserData.at(idRes);
        return true;
    }else{
        cout<<"password Doesn't correct\n";
        return false;
    }
}
void logout(){
    cout<<"Good bye "<<CurrentLoginAccount->getName()<<endl;
    CurrentLoginAccount= nullptr;
}
void HomePage(int ExciptPoss=-1){
    for (int i = 0; i <UserData.size(); ++i) {
        if (i==ExciptPoss)continue;
        UserData.at(i).print_all_myapartment();
    }
}

void Deposit(){
    int amount;
    cout<<"enter amount to deposit:";cin>>amount;
    *(CurrentLoginAccount)+=amount;

    SaveUserDataInToFile();
    SaveApartmentData();
}
bool withdraw(){
    int amount;
    cout<<"enter amount to withdraw:";cin>>amount;

    if (CurrentLoginAccount->withdraw(amount)){
        cout<<"-="<<amount<<endl;

        SaveUserDataInToFile();
        SaveApartmentData();

        return true;
    }
    cout<<"there's not enough money\n";
        return false;
}
bool Buy(){
    int OwnerId,ApartmentId;
    cout<<"Enter Owner Id:";cin>>OwnerId;
    if (CurrentLoginAccount->getId()==OwnerId){
        cout<<"You can't buy form your self\n";
        return false;
    }else if (UserData.size()<=OwnerId){
        cout<<"id Doesn't Exist\n";
        return false;
    }
    cout<<"Enter Apartment Id:";cin>>ApartmentId;
    if (UserData.at(OwnerId).getNumOfApartment()<=ApartmentId){
        cout<<"id Doesn't Exist\n";
        return false;
    }
    bool res= UserData.at(OwnerId).sell(*CurrentLoginAccount,ApartmentId);
    if (res){
        SaveUserDataInToFile();
        SaveApartmentData();
    }
    return res;
}
void removeApartment(){
    int id;
    cout<<"Enter Apartment Id:";cin>>id;
    if (CurrentLoginAccount->getNumOfApartment()<=id){
        cout<<"Id doesn't exist\n";
        return;
    }
    CurrentLoginAccount->remove_appartment(id);
    SaveUserDataInToFile();
    SaveApartmentData();


    SaveUserDataInToFile();
    SaveApartmentData();
}
void printAllAccountsData(){
    if (UserData.empty())cout<<"there's no Accounts\n";
    else
        for (auto &x:UserData) {
            x.printAccountData();
        }
}
void ChangeAdminPass() {
    cout<<setw(space)<<"Change password\n";
    string oldPassword, newPassword;

    cout << "Enter Old Admin Password: ";
    cin >> oldPassword;

    // Check if the old password is correct
    if (adminPassword == oldPassword) {
        cout << "Enter New Admin Password: ";
        cin >> newPassword;

        // Update the admin password
        adminPassword = newPassword;
        ClearScreen
        StopScreen
        cout << "Admin Password changed successfully\n";
    } else {
        cout << "Incorrect Old Password\n";
    }
}
void ChangeAdminUserName() {
    cout<<setw(space)<<"Change Admin User\n";
    string newAdminName;

    cout << "Enter New Admin User Name: ";
    cin >> newAdminName;

    // Update the admin username
    adminName = newAdminName;

    cout << "Admin User Name changed successfully\n";
}

int adminList(){
    cout<<"1.Add New Account\n"
          "2.Remove Account\n"
          "3.Show Log File\n"
          "4.Print All Account Data\n"
          "5.logout\n"
          "6.Change Admin UserName\n"
          "7.Change Admin Password\n"
          "8.Clear Saved Data\n"
          "0.Exit\n";
    int ch;cin>>ch;
    return ch;
}
void loginAsAdmin(){
    cout<<setw(space)<<"Login As Admin\n";
    string UserName,Password;
    cout<<"Admin UserName:";cin>>UserName;
    cout<<"Admin Password:";cin>>Password;
    if (UserName==adminName&&Password==adminPassword){
        while (true){
            switch (adminList()) {
                case 0:
                    ExitProgram();
                    break;
                case 1:
                    ClearScreen
                    addAccount();
                    StopScreen
                    ClearScreen
                    break;
                case 2:
                    ClearScreen
                    int id;
                    cout<<"enter Account's ID you want to delete: ";cin>>id;
                    if (removeAccountById(id)){
                        cout<<"Account Deleted \n";
                    }else{
                        cout<<"Id doesn't Exist\n";
                    }
                    StopScreen
                    ClearScreen
                    break;
                case 3:
                    ClearScreen
                    PrintLogFile();
                    StopScreen
                    ClearScreen
                    break;
                 case 4:
                     ClearScreen
                     printAllAccountsData();
                    StopScreen
                    ClearScreen
                    break;
                 case 5:
                     return;
                case 6:
                    ClearScreen
                    ChangeAdminUserName();
                    StopScreen
                    ClearScreen
                    return;
                case 7:
                    ClearScreen
                    ChangeAdminPass();
                    StopScreen
                    ClearScreen
                case 8:
                    clearFile(UserSaveLocation);
                    clearFile(ApartmentSaveLocation);
                    break;
                default:
                    ClearScreen
                    cout<<"Wrong Choice\n";
                    StopScreen
                    ClearScreen
            }

        }

    }else{
        ClearScreen
        cout<<"wrong password or User Name\n";
        StopScreen
        ClearScreen
    }
}

int AfterLoginList(){
    cout<<"Welcome "<<CurrentLoginAccount->getName()<<"\t\t"<<CurrentLoginAccount->getBalance()<<"$\t\tId:"<<CurrentLoginAccount->getId()<<endl;
    cout<<"1.add Apartments For Sell\n"
          "2.Show My Apartments\n"
          "3.Remove Apartment\n"
          "4.logout\n"
          "5.Show All Available Apartment\n"
          "6.Buy Apartment\n"
          "7.Deposit Money\n"
          "8.WithDraw Money\n"
          "9.Show Account Money\n"
          "10.Change Account Password\n"
          "0.Exit\n";
    int ch;cin>>ch;
    return ch;
}
int StartList(){
    cout<<setw(space)<<"Home Page\n";
    cout<<"1.Login:\n"
          "2.SignUp:\n"
          "3.Login As Admin:\n"
          "4.Show Apartment for sell:\n"
          "0.Exit\n";
    int ch;cin>>ch;
    return ch;
}
void ChangePassword(){
    cout<<setw(space)<<"Change Password\n";
    string Old_pass,New_pass;
    cout<<"Enter Old Password:";cin>>Old_pass;
    cout<<"Enter New Password:";cin>>New_pass;
    if (CurrentLoginAccount->ChangePassword(Old_pass,New_pass)){
        cout<<"Password changed Successfully"<<endl;
        StopScreen
    }else{
        cout<<"Wrong Password"<<endl;
        StopScreen
    }

    SaveUserDataInToFile();
    SaveApartmentData();
}
void StartingMenu(){

    while (true){
        if (CurrentLoginAccount== nullptr) {
            switch (StartList()) {
                case 0:
                    ExitProgram();
                case 1:
                    ClearScreen
                    login();
                    StopScreen
                    ClearScreen
                    break;
                case 2:
                    ClearScreen
                    addAccount();
                    StopScreen
                    ClearScreen
                    break;
                case 3:
                    ClearScreen
                    loginAsAdmin();
                    StopScreen
                   ClearScreen
                    break;
                case 4:
                    ClearScreen
                    HomePage();
                    StopScreen
                    ClearScreen

                    break;
                default:
                cout<<"Wrong\n";
            }
        }else{
            switch (AfterLoginList()) {
                case 0:
                    ExitProgram();
                case 1:
                    StopScreen
                    addApartment();
                    StopScreen
                    ClearScreen

                    break;
                case 2:
                    ClearScreen
                    printMyApartment();
                    StopScreen
                    ClearScreen
                    break;
                case 3:
                    ClearScreen
                    removeApartment();
                    StopScreen
                    ClearScreen
                    break;
                case 4:
                    ClearScreen
                    StopScreen
                    logout();
                    StopScreen
                    ClearScreen
                    break;
                case 5:
                    ClearScreen
                    HomePage(CurrentLoginAccount->getId());
                    StopScreen
                    ClearScreen
                    break;
                case 6:
                    ClearScreen
                    if(Buy()){
                        cout<<"successful Buy Done";
                    }else{
                        cout<<"Failed Buy\n";
                    }
                    StopScreen
                    ClearScreen
                    break;
                case 7:
                    ClearScreen
                    Deposit();
                    StopScreen
                    ClearScreen
                    break;
                case 8:
                    ClearScreen
                    withdraw();
                    StopScreen
                    ClearScreen
                    break;
                    case 9:
                    ClearScreen
                    cout<<"Your Balance: "<<CurrentLoginAccount->getBalance()<<endl;
                    StopScreen
                    ClearScreen
                    break;
                case 10:
                    ClearScreen
                    ChangePassword();
                    ClearScreen
                    StopScreen
                    break;
                default:
                    cout<<"Wrong Choice\n";
                    StopScreen
            }
        }
    }

}

int main(){
//    clearLogFiles();
    system("Color 0B");
    cout<<"Do You Want to Load Saved Data:(Y,N)";
    if (tolower(cin.get())=='y')
        loadData();
        ClearScreen
    system("Color 03");
    cout<<setw(space)<<"Welcome to Real estate System\n";
    cout<<"Enter Admin User Name:";cin>>adminName;
    cout<<"Enter Admin User Password:";cin>>adminPassword;
    ClearScreen
    system("Color 09");
    StartingMenu();

    return 0;
}