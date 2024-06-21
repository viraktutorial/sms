#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include<iomanip>
#include "StudentApplication.cpp"
#include "DataValidInput.cpp"
#include "User.cpp"
using namespace std;


class AuthSystem {
private:
    vector<User> users;
    string usersFile = "users.dat";

public:
    AuthSystem() {
        loadUsers();
    }

    void loadUsers() {
        ifstream file(usersFile, ios::binary);
        if (file.is_open()) {
            User user;
            while (file.read((char*)&user, sizeof(User))) {
                users.push_back(user);
            }
            file.close();
        }
    }

    void saveUsers() {
        ofstream file(usersFile, ios::binary | ios::trunc);
        if (file.is_open()) {
            for (const auto& user : users) {
                file.write((char*)&user, sizeof(User));
            }
            file.close();
        }
    }

    void addUser() {
        string username, password, role;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter role (admin/user): ";
        cin >> role;

        users.push_back(User(username, password, role));
        saveUsers();
        cout << "User added successfully!" << endl;
    }

    bool authenticate(const string& username, const string& password, User& authenticatedUser) {
        for (const auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                authenticatedUser = user;
                return true;
            }
        }
        return false;
    }

    void login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        User authenticatedUser;
        if (authenticate(username, password, authenticatedUser)) {
            cout << "Login successful! Role: " << authenticatedUser.getRole() << endl;
            if (authenticatedUser.getRole() == "admin") {
                adminMenu();
            } else {
                userMenu();
            }
        } else {
            cout << "Invalid username or password." << endl;
        }
    }
       void regis() {
        string username, password, role;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter role (admin/user): ";
        cin >> role;

        users.push_back(User(username, password, role));
        saveUsers();
        cout << "User added successfully!" << endl;
    }

    void adminMenu() {
         enum MainMenu {EXIT, STUDENT, USER};
        int choice;
        cout.setf(ios::fixed|ios::showpoint);
        cout<<setprecision(2); 

        do{
            std::cout << "\nMain Menu:\n";
            std::cout << "1. Student Management\n";
            std::cout << "2. User Management\n";
            std::cout << "0. Exit\n";
            choice = DataValidInput::getIntInput("Enter your choice: ");
            switch(choice){
                case STUDENT: 
                StudentApplication studentApp;
                studentApp.run();
                break;
                case USER: 
                cout<<"User Management"<<endl;
                break;
                case EXIT:
                cout<<"Exit Program"<<endl;
                break;
                default :
                cout<<"Invalid input"<<endl;
                cout<<"\a";
            }
            }while(choice!=EXIT);
    }

    void userMenu() {
        int choice;
        do {
            cout << "\nUser Menu\n";
            cout << "1. View Profile\n";
            cout << "2. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Viewing user profile..." << endl;
                // Add profile viewing logic here
                break;
            case 2:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
            }
        } while (choice != 2);
    }

    void viewUsers() {
        cout << "\nRegistered Users:\n";
        for (const auto& user : users) {
            cout << "Username: " << user.getUsername() << ", Role: " << user.getRole() << endl;
        }
    }

    void menu() {
        int choice;
        do {
            cout << "\nMain Menu\n";
            cout << "1. Login\n";
            cout << "2. Register\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                login();
                break;
            case 2:
                regis();
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
            }
        } while (choice != 0);
    }
};


