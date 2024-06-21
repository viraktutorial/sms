

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "PartTimeStudent.cpp"
#include "FullTimeStudent.cpp"
#include "Student.cpp"
#include "DataValidInput.cpp"
#include "StudentRepository.cpp"

class StudentManager : public StudentRepository{
private:
    std::vector<Student*> students;

    Student* findStudentById(int id) {
        auto it = std::find_if(students.begin(), students.end(), [id](Student* student) {
            return student->getId() == id;
        });
        return (it != students.end()) ? *it : nullptr;
    }

public:
    ~StudentManager() {
        for (auto student : students) {
            delete student;
        }
    }

    void addStudent(int id, std::string name, int type) {

        if (type == 1) {
            students.push_back(new PartTimeStudent(name, id));
        } else if (type == 2) {
            students.push_back(new FullTimeStudent(name, id));
        } else {
            throw std::invalid_argument("Invalid student type.");
        }

        std::cout << "Student added successfully.\n";
    }

    void updateStudent(int id) {
        Student* student = findStudentById(id);
        if (student == nullptr) {
            throw std::invalid_argument("Student not found");
            return;
        }

        std::string newName;
        newName = DataValidInput::getStringInput("Enter student name: ");

        student->setName(newName);
        std::cout << "Student updated successfully.\n";
    }

    void deleteStudent(int id) {
        auto it = std::remove_if(students.begin(), students.end(), [id](Student* student) {
            if (student->getId() == id) {
                delete student;
                return true;
            }
            return false;
        });

        if (it != students.end()) {
            students.erase(it, students.end());
            std::cout << "Student deleted successfully.\n";
        } else {
            throw std::invalid_argument("Student not found");
        }
    }

    void viewStudents() {
        if (students.empty()) {
            throw std::invalid_argument("No student available");
            return;
        }

        for (const auto& student : students) {
            student->display();
        }
    }
};