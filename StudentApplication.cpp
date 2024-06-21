
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "PartTimeStudent.cpp"
#include "FullTimeStudent.cpp"
#include "StudentManager.cpp"
#include "DataValidInput.cpp"

class StudentApplication{
private:
    void displayMenu() {
        std::cout << "\nStudent Manager Menu:\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Update Student\n";
        std::cout << "3. Delete Student\n";
        std::cout << "4. View Students\n";
        std::cout << "5. Back to Main Menu\n";
       
    }
public:
    void run(){
        StudentManager manager;
        int choice;

      bool done = false;
    while ( !done ) {
        displayMenu();
        choice = DataValidInput::getIntInput("Enter your choice: ");
        try {
            switch (choice) {
                case 1:{
                        std::string name;
                        int id;
                        int type;
                        id = DataValidInput::getIntInput("Enter student ID: ");
                        name = DataValidInput::getStringInput("Enter student name: ");
                        DataValidInput::validateId(id);
                        type = DataValidInput::getIntInput("Enter 1 for Part-Time, 2 for Full-Time: ");
                        manager.addStudent(id,name,type);
                    break;
                }
                case 2:{
                        int id;
                        id = DataValidInput::getIntInput("Enter student ID: ");
                        DataValidInput::validateId(id);

                        manager.updateStudent(id);
                        break;
                }
                case 3:{
                        int id;
                        id = DataValidInput::getIntInput("Enter student ID: ");
                        DataValidInput::validateId(id);
                        manager.deleteStudent(id);
                        break;
                }
                case 4:
                    manager.viewStudents();
                    break;
                case 5:
                    done = true;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    }
};
