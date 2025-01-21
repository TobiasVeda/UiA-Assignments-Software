#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>

static int id_student_counter = 0;
static int id_test_counter = 0;

class Students{
private:
    std::string _name;
    std::string _email;

public:
    Students() = default;
    Students(std::string *name, std::string *email){
        id_student_counter++;
        _name = *name;
        _email = *email;
    }
    void edit_student(std::string *name, std::string *email){
        _name = *name;
        _email = *email;
    }
    std::pair<std::string,std::string> return_student(){
        std::pair<std::string,std::string> student;
        student.first = _name;
        student.second = _email;
        return student;
    }
};

class Tests{
private:
    std::string _course_name;
    std::string _test_name;
    std::string _date;

public:
    Tests() = default;
    Tests(std::string *course_name, std::string *test_name, std::string *date){
        id_test_counter++;
        _course_name = *course_name;
        _test_name = *test_name;
        _date = *date;
    }
    void edit_test(std::string *course_name, std::string *test_name, std::string *date){
        _course_name = *course_name;
        _test_name = *test_name;
        _date = *date;
    }
    [[nodiscard]] std::string return_course_name() const{
        return _course_name;
    }
    [[nodiscard]] std::string return_test_name() const{
        return _test_name;
    }
    [[nodiscard]] std::string return_date() const{
        return _date;
    }
};

class Test_results{
private:
    int _student_id;
    int _test_id;
    int _grade;
public:
    Test_results() = default;
    Test_results(int *student_id, int *test_id, int *grade){
        _student_id = *student_id;
        _test_id = *test_id;
        _grade = *grade;
    }
    [[nodiscard]] std::pair<int,int> return_id() const{
        std::pair<int,int> id;
        id.first = _student_id;
        id.second = _test_id;
        return id;
    };
    [[nodiscard]] int return_grade() const{
        return _grade;
    }
    void edit_grade(int *grade){
        _grade = *grade;
    }
};
std::map<int, Students> student_map;
std::map<int, Tests> test_map;
std::vector<Test_results> result_vector;

void add_student(){
    std::string name;
    std::string email;

    std::cout <<"Name:";
//    std::cin.ignore(1, '\n'); Removes first letter of name and isn't needed to prevent newline bullshit
    std::getline(std::cin, name, '\n');
    std::cout <<"Email:";
    std::cin>> email;

    Students new_student(&name, &email);
    student_map[id_student_counter] = new_student;

}


void add_tests(){

    std::string course_name;
    std::string test_name;
    std::string date;

    std::cout <<"Course name:";
    std::cin>> course_name;
    std::cout <<"Test name:";
    std::cin.ignore(1, '\n');
    std::getline(std::cin, test_name, '\n');
    std::cout <<"Date:";
    std::cin>> date;

    Tests new_test(&course_name, &test_name, &date);
    test_map[id_test_counter] = new_test;
}
void add_edit_test_results(){
    int student_id = 0;
    int test_id = 0;
    int grade = {0};

    std::cout <<"Choose student by id:";
    std::cin>> student_id;
    if (student_map.count(student_id) == 0){
        return;
    }
    std::cout <<"Choose test by id:";
    std::cin>> test_id;
    if (test_map.count(test_id) == 0){
        return;
    }
    std::cout <<"Grade:";
    std::cin>> grade;

    for (int i = 0; i < result_vector.size(); ++i) {
        if(result_vector[i].return_id().first == student_id && result_vector[i].return_id().second == test_id){
            result_vector[i].edit_grade(&grade);
//              grade already exist, updates instead of creating new
            return;
        }
    }

    Test_results new_results(&student_id, &test_id, &grade);
    result_vector.push_back(new_results);
//    grade doesn't exist, creates new
}

void edit_student(){
    int student_id = 0;
    std::string name;
    std::string email;

    std::cout <<"Choose student by id:";
    std::cin>> student_id;
    if (student_map.count(student_id) == 0){
        return;
    }
    std::cout <<"Name:";
    std::cin.ignore(1, '\n');
    std::getline(std::cin, name, '\n');
    std::cout <<"Email:";
    std::cin>> email;

    student_map[student_id].edit_student(&name, &email);
}
void edit_test(){
    int test_id = 0;
    std::string course_name;
    std::string test_name;
    std::string date;

    std::cout <<"Choose test by id:";
    std::cin>> test_id;
    if (test_map.count(test_id) == 0){
        return;
    }
    std::cout <<"Course_name:";
    std::cin>> course_name;
    std::cout <<"Test name:";
    std::cin.ignore(1, '\n');
    std::getline(std::cin, test_name, '\n');
    std::cout <<"Date:";
    std::cin>> date;

    test_map[test_id].edit_test(&course_name, &test_name, &date);
}

void print_student(std::string *divider){
//    sett test slik at den ikke printer tom map
    std::cout <<"Student details:" <<std::endl;
    for (int i = 1; i < id_student_counter+1; ++i) { //i=1 and +1 because map starts at 1
        std::cout
        <<"student id" <<*divider <<i
        <<", name" <<*divider <<student_map[i].return_student().first
        <<", email" <<*divider <<student_map[i].return_student().second
        <<std::endl;
    }
}
void print_test(std::string *divider){
    std::cout <<"Test details:" <<std::endl;
    for (int i = 1; i < id_test_counter+1; ++i) { //i=1 and +1 because map starts at 1
        std::cout
        <<"test id" <<*divider <<i
        <<", course name" <<*divider <<test_map[i].return_course_name()
        <<", test name" <<*divider <<test_map[i].return_test_name()
        <<", date" <<*divider <<test_map[i].return_date()
        <<std::endl;
    }
}
void print_result(std::string *divider){
    std::cout <<"Test results:" <<std::endl;
    for (int i = 0; i < result_vector.size(); ++i) {
        int student_id = result_vector[i].return_id().first;
        int test_id = result_vector[i].return_id().second;
        std::cout
        <<"student id" <<*divider <<student_id
        <<", course name" <<*divider <<test_map[test_id].return_course_name()
        <<", test id" <<*divider <<test_id
        <<", test name" <<*divider <<test_map[test_id].return_test_name()
        <<", grade" <<*divider <<result_vector[i].return_grade()
        <<std::endl;
    }
}

void continue_remove_result(int *student_id, int *test_id){
    for (int i = 0; i < result_vector.size(); ++i) {
        if (
            result_vector[i].return_id().first == *student_id
//            || *student_id == 0
// supposed to be used for when removing test results when a test og student is removed. Issues where it removed more
//test results than supposed to. Fail test with, doesn't fail when excluded(???)
            &&
            result_vector[i].return_id().second == *test_id
//            || *test_id == 0
        ){
            result_vector.erase(result_vector.begin() + i);
        }
    }
}
void remove_student(){
    int student_id = 0;

    std::cout <<"Choose student id:";
    std::cin>> student_id;
    if (student_map.count(student_id) == 0){
        return;
    }

    student_map.erase(student_id);
    continue_remove_result(&student_id, 0);
//    0 as map key is invalid. id passed to continue can't be 0, caught in map.count check
}
void remove_test(){
    int test_id = 0;

    std::cout <<"Choose test id:";
    std::cin>> test_id;
    if (test_map.count(test_id) == 0){
        return;
    }

    test_map.erase(test_id);
    continue_remove_result(0, &test_id);
    //    0 as map key is invalid. id passed to continue can't be 0, caught in map.count check
}
void remove_result(){
    int student_id = 0;
    int test_id = 0;

    std::cout <<"Choose student id:";
    std::cin>> student_id;
    if (student_map.count(student_id) == 0){
        return;
    }
    std::cout <<"Choose test id:";
    std::cin>> test_id;
    if (test_map.count(test_id) == 0){
        return;
    }

    continue_remove_result(&student_id, &test_id);
}



void print_menu(){
    std::cout <<"Please choose:" <<std::endl;
    std::cout<<std::endl;
    std::cout <<"1. Add student" <<std::endl;
    std::cout <<"2. Edit student" <<std::endl;
    std::cout <<"3. Remove student" <<std::endl;
    std::cout<<std::endl;
    std::cout <<"4. Add test" <<std::endl;
    std::cout <<"5. Edit test" <<std::endl;
    std::cout <<"6. Remove test" <<std::endl;
    std::cout<<std::endl;
    std::cout <<"7. Add test result" <<std::endl;
    std::cout <<"8. Edit test result" <<std::endl;
    std::cout <<"9. Remove test result" <<std::endl;
    std::cout<<std::endl;
    std::cout <<"10. Show all info" <<std::endl;
    std::cout <<"11. Exit" <<std::endl;
}

void menu_selection(){
    print_menu();

    int selection = 0;
    std::string divider_equal = " = ";
    std::string divider_colon = " : ";
//    needed to pass test

    std::cout<<std::endl;
    std::cout <<"Select:";
    std::cin>> selection;
    std::cin.ignore(1, '\n'); //Only meant to remove a single newline


    switch (selection) {
        case 1:
            add_student();
            break;
        case 2:
            print_student(&divider_colon);
            edit_student();
            break;
        case 3:
            print_student(&divider_colon);
            remove_student();
            break;
        case 4:
            add_tests();
            break;
        case 5:
            print_test(&divider_colon);
            edit_test();
            break;
        case 6:
            print_test(&divider_colon);
            remove_test();
            break;
        case 7: case 8:
            print_student(&divider_colon);
            print_test(&divider_colon);
            print_result(&divider_colon);
            add_edit_test_results();
            break;
        case 9:
            print_result(&divider_colon);
            remove_result();
            break;
        case 10:
            print_student(&divider_equal);
            print_test(&divider_equal);
            print_result(&divider_equal);
            break;
        case 11:
            exit(0);
            break;
        default:
            return;
            break;
    }

}

int main() {
    while (true){
        menu_selection();
    }
}