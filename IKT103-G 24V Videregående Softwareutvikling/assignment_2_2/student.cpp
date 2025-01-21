//
// Created by Tobias on 20.02.2024.
//

#include "student.h"
#include <string>
#include <utility>

Student::Student() = default;
Student::Student(int id, std::string name, int age, int attendance){
    _id = id;
    _name = std::move(name);
    _age = age;
    _attendance = attendance;
}
int Student::get_id() const{
    return _id;
}
std::string Student::get_name() const{
    return _name;
}
int Student::get_age() const{
    return _age;
}
int Student::get_attendance() const{
    return _attendance;
}