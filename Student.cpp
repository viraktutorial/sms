#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

class Student {
protected:
    std::string name;
    int id;
public:
    Student(){}
    Student(int id, std::string name):id(id),name(name){}
    int getId(){
        return id;
    }
    std::string getName(){
        return name;
    }
    void setId(int id){
        this->id=id;
    }
    void setName(std::string name){
        this->name=name;
    }
    virtual std::string getType() const = 0;
    virtual void display() const {
        std::cout << "Name: " << name << ", ID: " << id << ", Type: " << getType() << std::endl;
    }
    virtual ~Student() = default;
};
