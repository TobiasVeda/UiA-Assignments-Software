//
// Created by Tobias on 20.02.2024.
//

#ifndef ASSIGNMENT_2_2_STUDENT_H
#define ASSIGNMENT_2_2_STUDENT_H

#include <string>

class Student {
private:
    int _id;
    std::string _name;
    int _age;
    int _attendance;

public:
    Student();
    Student(int id, std::string _name, int _age, int _attendance);
    [[nodiscard]] int get_id() const;
    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] int get_age() const;
    [[nodiscard]] int get_attendance() const;
};


#endif //ASSIGNMENT_2_2_STUDENT_H
