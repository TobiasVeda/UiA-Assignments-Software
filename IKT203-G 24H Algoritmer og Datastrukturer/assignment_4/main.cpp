#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct Node{
    std::string name;
    int priority;
};


class Heap{

private:
    // For the math to work out, index should start at 1.
    // Only for math logic, when interacting with vector, 1 is subtracted
    std::vector<Node> _tree;


    bool duplicate_job(std::string &name){
        for (auto &i : _tree) {
            if (i.name == name){
                std::cout <<"Error: Duplicate job name." <<std::endl;
                return true;
            }
        }
        return false;
    }
    bool null_priority(int pri){
        if (pri <= 0){
            return true;
        }
        return false;
    }


    int get_child_1_index(int i_parent){
    // The index of the first child node is the double of
    // the index of the parent
        int index = i_parent * 2;
        if (index > _tree.size()){
            //This child doesn't exist
            return -1;
        }
        return index;
    }
    int get_child_2_index(int i_parent){
    // The index of the second child node is the double of
    // the index of the parent plus 1
        int index = (i_parent * 2) +1;
        if (index > _tree.size()){
            //this child doesn't exist
            return -1;
        }
        return index;
    }
    void swap_nodes(int i1, int i2){
    // Swaps places(indices) of two elements in vector
        Node temp = _tree[i1 -1];

        _tree[i1 -1] = _tree[i2 -1];
        _tree[i2 -1] = temp;
    }

    void max_heapify(){
    // Starts from halfway into the vector, checks if each child has greater. If it is, it swaps
    // place with the parent. Index then counted down 1 and process repeated until it reaches the
    // top of the heap/start of the vector

        // .size() counts number of elements, in practice converts first index (first i=0) to 1 (first i=1)
        // Must subtract 1 from index when interacting with vector (ex: pushback(), erase(), vector[])
        int midpoint = floor((float)_tree.size()/2.f);

        for (int i = midpoint; i >= 1; i--) {

            if (_tree.empty()){
                break;
            }

            int i_child_1 = get_child_1_index(i);
            int i_child_2 = get_child_2_index(i);

            if (_tree[i_child_1 -1].priority > _tree[i -1].priority){
                // First child priority greater than parent,
                // swaps places.
                swap_nodes(i_child_1, i);
            }

            if (i_child_2 == -1){
                // Child node number 2 doesn't exist
                continue;
            }

            if (_tree[i_child_2 -1].priority > _tree[i -1].priority){
                // Second child priority greater than parent,
                // swaps places.
                swap_nodes(i_child_2, i);
            }
        }
    }



public:

    Heap() = default;

    void add_job(std::string name, int priority){
    // Checks for user input error, then pushes to heap

        if (duplicate_job(name)){
            std::cout <<"Error: Job \"" <<name <<"\" already exist" <<std::endl;
            return;
        }
        if (null_priority(priority)){
            std::cout <<"Error: Priority must be greater than 0" <<std::endl;
            return;
        }

        _tree.push_back(Node{name, priority});
    }

    void edit_job(std::string name, int priority){

        for (auto &i : _tree) {
            if (i.name == name){
                i.priority = priority;
                max_heapify();
                return;
            }
        }
        std::cout <<"Error: Job \"" <<name <<"\" does not exist" <<std::endl;
    }

    void print_top_job(){
    // When the heap is max-heapified, the topmost node has the highest priority.
    // The top node represented by first index in vector.
    // Prints first node in vector
        if (_tree.empty()){
            std::cout <<"Queue empty" <<std::endl;
            return;
        }

        max_heapify();
        std::cout <<"Name: " <<_tree[0].name <<", Priority: " <<_tree[0].priority <<std::endl;
    }
    void process_top(){
    // When the heap is max-heapified, the topmost node has the highest priority.
    // The top node represented by first index in vector
    // Erases first node in vector
        if (_tree.empty()){
            std::cout <<"Queue empty" <<std::endl;
            return;
        }
        max_heapify();
        _tree.erase(_tree.begin());
        std::cout <<"Job Successfully Processed" <<std::endl;
    }

};


void display_menu(){
    std::cout <<"==========================================" <<std::endl;
    std::cout <<"1) Insert Print Job" <<std::endl;
    std::cout <<"2) Update Job Priority" <<std::endl;
    std::cout <<"3) Display Job With Highest Priority" <<std::endl;
    std::cout <<"4) Process Next Job" <<std::endl;
    std::cout <<"5) Exit Application" <<std::endl;
}

Node user_input(){
// Floats will be floored

    std::cout <<"Input Job Name: ";
    std::string name;
    std::cin>> name;

    std::cout <<"Input Job Priority: ";
    std::string pri;
    std::cin>> pri;

    return Node{name, atoi(pri.c_str())};
}


int main(){
    auto heap = new Heap;
    bool loop = true;

//    heap->add_job("one", 1);
//    heap->add_job("two", 2);
//    heap->add_job("three", 3);
//    heap->add_job("four", 4);
//    heap->add_job("five", 5);
//    heap->add_job("six", 6);
//    heap->add_job("seven", 7);
//    heap->add_job("eight", 8);

    while (loop){

        display_menu();

        auto node = new Node;
        int option = 0;
        std::cin>> option;


        switch(option) {
            case 1:
                std::cout <<"--Add Print Job--" <<std::endl;
                *node = user_input();
                heap->add_job(node->name, node->priority);
                break;

            case 2:
                std::cout <<"--Change Job Priority--" <<std::endl;
                *node = user_input();
                heap->edit_job(node->name, node->priority);
                break;

            case 3:
                std::cout <<"--Job With Highest Priority--" <<std::endl;
                heap->print_top_job();
                break;

            case 4:
                heap->process_top();
                break;

            case 5:
                loop = false;
                break;

            default:
            std::cout <<"Error: Invalid choice" <<std::endl;
        }

        delete node;
    }

    delete heap;
    return 0;
}