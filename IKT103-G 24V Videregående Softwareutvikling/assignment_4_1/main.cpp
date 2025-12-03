#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <string>
#include <thread>
#include <chrono>

class sleep;

using namespace web;
using namespace web::http;
using namespace web::http::client;



auto GET_all(http_client client){

    auto request = client.request(methods::GET, uri_builder(U("students")).to_string())
            .then([](const http_response& response){

                if(response.status_code() != 200){
                    throw std::runtime_error("Request failed: " + std::to_string(response.status_code()));
                }
                return response.extract_json();

            }).then([](json::value root){

                for (int i = 0; i < root.size(); ++i) {
                    auto id = root[i][U("id")].as_integer();
                    auto name = root[i][U("name")].as_string();
                    auto email = root[i][U("email")].as_string();
                    auto year = root[i][U("year")].as_integer();

                    ucout
                    <<std::endl
                    <<"id: " <<id
                    <<", name: " <<name
                    <<", email: " <<email
                    <<", year: " <<year
                    <<std::endl;
                }
            });
    return request;
}


auto GET_one(http_client client){

    std::string id;
    std::cout <<"Input ID to retrieve:";
    std::cin>> id;

//    id used immediatly in request, variable is lost when out of scope, but wont matter

    auto request = client.request(methods::GET, uri_builder(U("students"))
    .append_path(utility::conversions::to_string_t(id))
    .to_string())
            .then([](const http_response& response){

              if(response.status_code() != 200){
                    std::cout <<std::endl <<"Student not found" <<std::endl;
                    throw std::runtime_error("Request failed: " + std::to_string(response.status_code()));
                }
                return response.extract_json();

            }).then([](json::value root){

                    auto id = root[U("id")].as_integer();
                    auto name = root[U("name")].as_string();
                    auto email = root[U("email")].as_string();
                    auto year = root[U("year")].as_integer();

                    ucout
                    <<std::endl
                    <<"id: " <<id
                    <<", name: " <<name
                    <<", email: " <<email
                    <<", year: " <<year
                    <<std::endl;
            });
    return request;
}

auto POST_one(http_client client){

    std::string name;
    std::string email;
    int year = 0;

    std::cout <<"Input name:";
    std::cin.ignore(1, '\n');
    std::getline(std::cin, name);
    std::cout <<"Input email: ";
    std::cin>> email;
    std::cout <<"Input year: ";
    std::cin>> year;

    json::value json_object;
    json_object[U("name")] = json::value::string(utility::conversions::to_string_t(name));
    json_object[U("email")] = json::value::string(utility::conversions::to_string_t(email));
    json_object[U("year")] = year;

    auto request = client.request(methods::POST, uri_builder(U("students/")).to_string(),
                                  json_object.serialize(), U("application/json"))

      .then([](const http_response& response){

        if(response.status_code() != 201){
            std::cout <<std::to_string(response.status_code()) <<std::endl;
            throw std::runtime_error("Request failed: " + std::to_string(response.status_code()));
        }
        return response.extract_json();


    }).then([](json::value root){

        auto id = root[U("id")].as_integer();
        auto name = root[U("name")].as_string();
        auto email = root[U("email")].as_string();
        auto year = root[U("year")].as_integer();

        ucout
        <<std::endl
        <<"Added student: "
        <<"id: " <<id
        <<", name: " <<name
        <<", email: " <<email
        <<", year: " <<year
        <<std::endl;

    });
    return request;
}

auto PUT_one(http_client client){
    int id = 0;
    std::string Lid;
    std::string name;
    std::string email;
    int year = 0;

    std::cout <<"Input ID: ";
    std::cin>> id;
    Lid = std::to_string(id);
    std::cout <<"Input name:";
    std::cin.ignore(1, '\n');
    std::getline(std::cin, name);
    std::cout <<"Input email: ";
    std::cin>> email;
    std::cout <<"Input year: ";
    std::cin>> year;

    json::value json_object;
    json_object[U("email")] = json::value::string(utility::conversions::to_string_t(email));
    json_object[U("id")] = id;
    json_object[U("name")] = json::value::string(utility::conversions::to_string_t(name));
    json_object[U("year")] = year;

    auto request = client.request(methods::PUT,uri_builder(U("students"))
    .append_path(utility::conversions::to_string_t(Lid)).to_string(),
    json_object.serialize(),
    U("application/json")

    ).then([](const http_response& response){

                if(response.status_code() != 200){
                    std::cout <<std::to_string(response.status_code()) <<std::endl;
                    std::cout <<std::endl <<"Student not found" <<std::endl;
                    throw std::runtime_error("Request failed: " + std::to_string(response.status_code()));
                }else if(response.status_code() == 200){
                    std::cout <<std::endl <<"Student was edited successfully" <<std::endl;
                }


            });
    return request;
}

auto DEL_one(http_client client){
    std::string id;
    std::cout <<"Input ID to delete:";
    std::cin>> id;

    auto request = client.request(methods::DEL, uri_builder(U("students"))
    .append_path(utility::conversions::to_string_t(id)).to_string())
            .then([](const http_response& response){

                if(response.status_code() != 204){
                    std::cout <<std::endl <<"Student not found" <<std::endl;
                    throw std::runtime_error("Request failed: " + std::to_string(response.status_code()));
                }else if(response.status_code() == 204){
                    std::cout <<std::endl <<"Student was removed successfully" <<std::endl;
                }

            });
    return request;

}

void print_menu(){
    std::cout <<"Please choose:" <<std::endl;
    std::cout <<"1. Read all students" <<std::endl;
    std::cout <<"2. Get student by id" <<std::endl;
    std::cout <<"3. Add student" <<std::endl;
    std::cout <<"4. Edit student" <<std::endl;
    std::cout <<"5. Remove student" <<std::endl;
    std::cout <<"6. Exit" <<std::endl;
}


void menu_selection(http_client client){
    print_menu();

//    auto needs initializer

    int selection = 0;
    std::cout <<"Select:";
    std::cin>> selection;

    while (true){
        if(selection == 1) {
            GET_all(client);
            break;
        }
            if(selection == 2) {
                GET_one(client);
                break;
            }
            if(selection == 3) {
                POST_one(client);
                break;
            }
            if(selection == 4) {
                PUT_one(client);
                break;
            }
            if(selection == 5) {
               DEL_one(client);
                break;
            }
            if(selection == 6) {
                std::cout << "Waiting for response..." << std::endl;
                std::this_thread::sleep_for (std::chrono::seconds(1));
                exit(0);
                break;
            }

        }
    }





int main() {

    http_client client(U("http://localhost:5000"));
//    int a;
//    std::cin>> a;
//    auto request = POST_one(client);
//    request.wait();
    while (true){
        menu_selection(client);
    }



}
