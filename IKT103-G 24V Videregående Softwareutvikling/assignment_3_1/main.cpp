#include <iostream>
#include <string>
#include <SQLiteCpp/Database.h>
#include <sqlite3.h>

namespace sql = SQLite;

void SELECT_all_FROM_query(sql::Database *db, sql::Statement *query){
    bool student_not_found = true;

    while (query->tryExecuteStep() == SQLITE_ROW) {
        int id = query->getColumn("id");
        std::string name = query->getColumn("name");
        std::string email = query->getColumn("email");
        int year = query->getColumn("year");

        std::cout
            << "id: " << id
            << ", name: " << name
            << ", email: " << email
            << ", year: " << year
            << std::endl;

        student_not_found = false;
    }
    if (student_not_found){
        std::cout <<"No students found" <<std::endl;
    }


}

void print_all(sql::Database *db){
    sql::Statement query_all(*db, "SELECT * FROM students");

    SELECT_all_FROM_query(db, &query_all);
}

void print_by_id(sql::Database *db){
    int id = 0;
    std::cout <<"input id: ";
    std::cin>> id;

    sql::Statement query_id(*db, "SELECT * FROM students WHERE id = ?");
    query_id.bind(1, id);

    SELECT_all_FROM_query(db, &query_id);

}

void add_student(sql::Database *db){
    std::string name;
    std::string email;
    int year = 0;

    std::cout <<"input name: ";
        std::cin.ignore(1, '\n');
    std::getline(std::cin, name, '\n');
    std::cout <<"input email: ";
    std::cin>> email;
    std::cout <<"input year: ";
    std::cin>> year;

    sql::Statement insert(*db, "INSERT INTO students (name, email, year) VALUES (?, ?, ?)");
    insert.bind(1, name);
    insert.bind(2, email);
    insert.bind(3, year);

    sql::Statement query_inserted(*db,"SELECT * FROM students ORDER BY id DESC LIMIT 1");

    if (insert.exec() == 1){
        std::cout <<"Added student: ";
        SELECT_all_FROM_query(db, &query_inserted);
    } else{
        std::cout<<":("<<std::endl;
    }

}

void edit_student(sql::Database *db){
    int id = 0;


    std::cout <<"id of student to edit: ";
    std::cin>> id;

    sql::Statement valid_test(*db, "SELECT * FROM students WHERE id = ?");
    valid_test.bind(1, id);
    if (valid_test.tryExecuteStep() != SQLITE_ROW){
        std::cout <<"Student not found" <<std::endl;
        return;
    }

    std::string name;
    std::string email;
    int year = 0;
        std::cin.ignore(1, '\n');
    std::cout <<"new name: ";
    std::getline(std::cin, name, '\n');
    std::cout <<"new email: ";
    std::cin>> email;
    std::cout <<"new year: ";
    std::cin>> year;

    sql::Statement update(*db, "UPDATE students SET name = ?, email = ?, year = ? WHERE id = ?");
    update.bind(1, name);
    update.bind(2, email);
    update.bind(3, year);
    update.bind(4, id);

    if (update.exec() == 1){
        std::cout <<"Student was edited successfully" <<std::endl;
    } else{
        std::cout<<"Student not found"<<std::endl;
    }

}

void remove_student(sql::Database *db){
    int id = 0;
    std::cout <<"id of student to remove: ";
    std::cin>> id;

    sql::Statement update(*db, "DELETE FROM students WHERE id = ?");
    update.bind(1, id);

    if (update.exec() == 1){
        std::cout <<"Student was removed successfully" <<std::endl;
    } else{
        std::cout<<"Student not found"<<std::endl;
    }

}

void search(sql::Database *db){

    std::string name;
    std::cout <<"search by name: ";
        std::cin.ignore(1, '\n');
    std::getline(std::cin, name, '\n');

    sql::Statement query_id(*db, "SELECT * FROM students WHERE name LIKE ? OR name = ?");
    query_id.bind(1, name);
    query_id.bind(2, name);

    SELECT_all_FROM_query(db, &query_id);
}

void print_menu(){
    std::cout <<"Please choose:" <<std::endl;
    std::cout <<"1. Read all students" <<std::endl;
    std::cout <<"2. Get student by id" <<std::endl;
    std::cout <<"3. Add student" <<std::endl;
    std::cout <<"4. Edit student" <<std::endl;
    std::cout <<"5. Remove student" <<std::endl;
    std::cout <<"6. Search" <<std::endl;
    std::cout <<"7. Exit" <<std::endl;
}

void menu_selection(sql::Database *db){
    print_menu();

    int selection = 0;
    std::cout <<"Select:";
    std::cin>> selection;

    switch (selection) {
        case 1:
            print_all(db);
            break;
        case 2:
            print_by_id(db);
            break;
        case 3:
            add_student(db);
            break;
        case 4:
            edit_student(db);
            break;
        case 5:
            remove_student(db);
            break;
        case 6:
            search(db);
            break;
        case 7:
            exit(0);
            break;
        default:
            return;
            break;
    }

}

int main() {

    sql::Database db("school.sqlite", sql::OPEN_READWRITE);

    while (true){
        menu_selection(&db);
    }

}


