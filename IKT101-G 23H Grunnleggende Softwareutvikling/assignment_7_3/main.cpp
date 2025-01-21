#include <iostream>
#include <vector>

class Student{ //cpp do not need typedef
private:
    std::string _name;
    std::vector<std::string> _course;
    std::vector<char> _grades;
//innser at map kanskje ville vært bedre

public:
    Student() = default;
    Student(std::string *name){ //konstruktør. Ingen returverdi. Må hete samme som class. Må være public
        _name = *name;
    };
    void input_vector(std::string *course, char *grades){
//        if (course->empty() || *grades == 0){
//            return;
//        }
            _course.push_back(*course);
            _grades.push_back(*grades);
    }
    int course_size(){
        return _course.size();
    }
    std::string return_name(){
        return _name;
    }
    std::string return_course(int j){
        return _course[j];
    }
    char return_grades(int j){
        return _grades[j];
    }
};

void input_student(std::vector<Student> *object_vector) {
    std::string buffer_name;
    std::string buffer_course;
    char buffer_grade = {0};

//    Student new_object = new Student();

    for (int i = 0; true; ++i) {

        std::cout << "Input name:" << std::endl;
        std::getline(std::cin, buffer_name);
        if (buffer_name == "stop") { // ville brukt toUpper, men er i cstring
            break;
        }
        Student new_object(&buffer_name);

        while (true) {
            std::cout << "Input course:" << std::endl;
            std::getline(std::cin, buffer_course);
            if (buffer_course == "stop") { // ville brukt toUpper, men er i cstring
                break;
            }
            std::cout << "Input grade:" << std::endl;
            std::cin >> buffer_grade;
            new_object.input_vector(&buffer_course, &buffer_grade);

            std::cin.ignore(); //clear input buffer
        };

        object_vector->push_back(new_object);
    };
}

void print_class(std::vector<Student> *object_vector){
    for (int i = 0; i < object_vector->size(); ++i) {

        for (int j = 0; j < (*object_vector)[i].course_size(); ++j) {

           std::cout <<(*object_vector)[i].return_name() <<" - ";
           std::cout  <<(*object_vector)[i].return_course(j) <<" - ";
           std::cout  <<(*object_vector)[i].return_grades(j) <<std::endl;

        }


    }

}

int main() {
    std::vector<Student> object_vector;

    input_student(&object_vector);
    print_class(&object_vector);
}
