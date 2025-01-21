#include "rapidcsv/rapidcsv.h"
#include <iostream>
#include <vector>
#include <string>

namespace csv = rapidcsv;

template<typename T, typename U>
void print_width_two(std::string type, std::vector<T> *first, std::vector<U> *second){
    for (int i = 0; i < first->size(); ++i) {
        std::cout
        <<type
        <<": "
        <<(*first)[i]
        <<", "
        <<(*second)[i]
        <<std::endl;
    }
}

void print_amount_per_product(std::string type, std::vector<int> *product_id, std::vector<std::string> *product_name, std::vector<int> *order_p_id, std::vector<int> *order_amount,
                              std::vector<int> product_price = {}){

    if (product_price.empty()){
        for (int i = 0; i < product_id->size(); ++i) {
            product_price.push_back(1);
        }
    }

    for (int i = 0; i < product_id->size(); ++i) {
        int amount = 0;
        for (int j = 0; j < order_p_id->size(); ++j) {
            if ((*product_id)[i] == (*order_p_id)[j]){
                amount += (*order_amount)[j] * (product_price)[i];
            }
        }
        std::cout
            <<(*product_name)[i]
            <<type
            <<amount
        <<std::endl;
    }

}

void print_money_spent(std::vector<int> *customer_id, std::vector<std::string> *customer_name,
                       std::vector<int> *product_id,std::vector<int> *product_price,
                       std::vector<int> *order_c_id, std::vector<int> *order_p_id, std::vector<int> *order_amount
                       ){


    for (int k = 0; k < customer_id->size(); ++k) {
        int money_spent = 0;

        for (int i = 0; i < product_id->size(); ++i) {
        int money_per_product = 0;

            for (int j = 0; j < order_p_id->size(); ++j) {
                if ((*customer_id)[k] == (*order_c_id)[j] && (*product_id)[i] == (*order_p_id)[j]){
                    money_spent += (*order_amount)[j] * (*product_price)[i];
                }


            }

        }

        std::cout
            <<(*customer_name)[k]
            <<" money spent: "
            <<money_spent
        <<std::endl;

    }

}

int main(){
    csv::Document customer("customers.csv");
    std::vector<int> customer_id = customer.GetColumn<int>("id");
    std::vector<std::string> customer_name = customer.GetColumn<std::string>("name");
    std::vector<std::string> customer_address = customer.GetColumn<std::string>("address");

    csv::Document product("products.csv");
    std::vector<int> product_id = product.GetColumn<int>("id");
    std::vector<std::string> product_name = product.GetColumn<std::string>("name");
    std::vector<int> product_price = product.GetColumn<int>("price");

    csv::Document order("orders.csv");
    std::vector<int> order_id = order.GetColumn<int>("id");
    std::vector<int> order_c_id = order.GetColumn<int>("customerid");
    std::vector<int> order_p_id = order.GetColumn<int>("productid");
    std::vector<int> order_amount = order.GetColumn<int>("amount");

    print_width_two("Customer", &customer_name, &customer_address);
    print_width_two("Product", &product_name, &product_price);
    print_amount_per_product(" amount: ", &product_id, &product_name, &order_p_id, &order_amount);
    print_amount_per_product(" gross income: ", &product_id, &product_name, &order_p_id, &order_amount, product_price);
    print_money_spent(&customer_id, &customer_name, &product_id, &product_price, &order_c_id, &order_p_id, &order_amount);
}