#include <iostream>
#include <cstdio>


class Node{
private:
    int _value;
    Node *_next;

public:
    Node(){
            _value = 0;
            _next = nullptr;
    };
    explicit Node(int value){
        _value = value;
        _next = nullptr;
    };
    Node* return_next_mem(){
        return _next;
    }
    void push_next_mem(Node *next_node_adress){
        _next = next_node_adress;
    }
    int& return_value(){
        return _value;
    }
};


class Link_list{
private:
    Node *_start;

public:
//    Link_list() = default; ikke deafult fordi konstruktør ikke har noe i ()?
    Link_list(){
    //kall uten argument gjøres uten ()
        _start = nullptr;
    };

//~Link_list()
//{
//    int i = 0;
//}
    void push_back(const int value){

        Node *new_node = new Node(value);
        //lager ny node. Resten av pushback finner hvor i listen den skal plasseres

        if (_start == nullptr){
            //Hvis adresse til første node (_start) er NULL, finnes ingen nodes, og adressen til den første noden blir satt som _start
            _start = new_node;
            return;
        }

        Node* node_n = _start;
        // setter adresse til node_n som den første noden

        while (true) {
            if (node_n->return_next_mem() != nullptr){
                // test om node nr n sin adresse er NULL (NULL=siste node)
                node_n = node_n->return_next_mem(); //ikke siste node. Går videre
            } else{
                // _next pointer = NULL. Siste node i listen

                    node_n->push_next_mem(new_node);
                    // Nest siste node får adressen til siste. Siste node får adressen NULL i konstruktør
                break;
            }
        }
    }
    size_t size(){
        size_t size = 0;
        Node* node_n = _start;
        if (_start == nullptr){
            return size;
        }
        // setter adresse til node_n som den første noden
        while (true) {
            if (node_n->return_next_mem() != nullptr){
                // test om node nr n sin adresse er NULL (NULL=siste node)
                node_n = node_n->return_next_mem(); //ikke siste node. Går videre
                size++;
            } else{
                // _next pointer = NULL. Siste node i listen
                size++;
                return size;
            }
        }
    }
    int& at(size_t index){
        size_t node_count = 0;
        Node* node_n = _start;
        // setter adresse til node_n som den første noden
        while (node_count != index) {
            if (node_n->return_next_mem() != nullptr){
                // test om node nr n sin adresse er NULL (NULL=siste node)
                node_n = node_n->return_next_mem(); //ikke siste node. Går videre
                node_count++;
            } else{
                // _next pointer = NULL. Siste node i listen
                node_count++;
            }
        }
        return node_n->return_value();
    };
    void remove(size_t index){
        size_t node_count = 0;
        Node* node_before_n = _start;
        Node* node_n;
        Node* node_after_n;

        while (node_count != index -1) {
            if (index == 0){
                node_n = _start;
                node_after_n = node_n->return_next_mem();
                _start = node_after_n;
                delete node_n;
                return;
            }
            // finner node med index før den som skal slettes. Node_before_n er node som peker til den som skal slettes
            if (node_before_n->return_next_mem() != nullptr){
                node_before_n = node_before_n->return_next_mem(); //ikke siste node. Går videre
                node_count++;
            } else{
                // _next pointer = NULL. Siste node i listen
                node_count++;
            }
        }
        node_n = node_before_n->return_next_mem();
        // node_n er noden med adressen som ligger i peker til node_before_n.
        node_after_n = node_n->return_next_mem();
        node_before_n->push_next_mem(node_after_n);
        delete node_n;
    };
};



int main() {
//    std::cout << "1. Add integer" << std::endl;
//    std::cout << "2. Show integer at index" << std::endl;
//    std::cout << "3. Remove integer at index" << std::endl;
//    std::cout << "4. Print information" << std::endl;
//    std::cout << "5. Exit" << std::endl;
//    std::cout << std::endl;
    Link_list new_list;
    int choice = 0;

    while (true){
        std::cout <<"input choice: ";
        std::cin>> choice;


        if (choice == 1) {
            int value = 0;
            std::cout << "Input value:";
            std::cin >> value;
            new_list.push_back(value);
        } else if(choice == 2){
            int index = 0;
            std::cout <<"Input index:";
            std::cin>> index;
            printf("Integer at index %d: %d\n", index, new_list.at(index));
        } else if(choice == 3){
            int index = 0;
            std::cout << "Input index to be removed:";
            std::cin >> index;
            new_list.remove(index);
        } else if(choice == 4){
            if (new_list.size() == 0){
                std::cout <<"List contains no integers" <<std::endl;
            } else {
                printf("List contains %zu integers: ", new_list.size());
                for (int i = 0; i < new_list.size(); ++i) {
                    printf("%d ", new_list.at(i));
                }
            }
            std::cout <<std::endl;
        } else if(choice == 5){
            exit(0);
        }
    }






}
