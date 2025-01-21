#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "student.h"
#include <iostream>
#include <list>
#include <algorithm>

namespace json = rapidjson;

bool comp_asc(Student * student1, Student* student2){
    return student1->get_age() < student2->get_age();
}

int main() {
    int average_age = 0;

    FILE *file = fopen("students.json", "r");
    char readBuffer[65536];
    json::FileReadStream json(file, readBuffer, sizeof(readBuffer));
    json::Document doc;
    doc.ParseStream(json);
    fclose(file);

    std::list<Student*> student_list;

    for (int i = 0; i < doc.Size(); ++i) {
        json::Value &a = doc[i]["id"];
        int id = a.GetInt();
        json::Value &b = doc[i]["name"];
        std::string name = b.GetString();
        json::Value &c = doc[i]["age"];
        int age = c.GetInt();
        json::Value &d = doc[i]["attendance"];
        int attendance = d.GetInt();

        Student *new_student = new Student(id, name, age, attendance);
        student_list.push_back(new_student);
        average_age += new_student->get_age();
    }

    student_list.sort(comp_asc);

        std::cout
            <<"Youngest: "
            <<student_list.front()->get_name()
            <<std::endl;

        std::cout
            <<"Oldest: "
            <<student_list.back()->get_name()
            <<std::endl;

        average_age = average_age / (student_list.size());
        std::cout
            <<"Average age: "
            <<average_age
            <<std::endl;

        for (int i = 0; i < student_list.size(); ++i) {
            std::list<Student*>::iterator iterator = student_list.begin();
            std::advance(iterator, i);

            if((*iterator)->get_attendance() < 30){
                std::cout
                        <<"Bad student: "
                        <<(*iterator)->get_name()
                        <<std::endl;
            }
        }
}
