#include <iostream>
#include <string>

struct Node {
    int data;
    Node* next;

    Node(int x = 0, Node* ptr = NULL) : data(x), next(ptr) {};
};

class Queue {
    Node* head;
    Node* tail;
    int length;

public:
    Queue() : head(NULL), tail(NULL), length(0) {};
    int get();
    void put(int x);
    int size();
};

void read_and_apply_input(Queue &queue);



int main() {
    Queue queue;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        read_and_apply_input(queue);
    }

    return 0;
}



int Queue::get() {
    if (head == NULL) {
        std::string error_msg = "error";
        throw error_msg;
    } else {
        Node* tmp_ptr = head;
        int got_data = head->data;
        head = head->next;
        free(tmp_ptr);

        if (head == NULL) {
            tail = NULL;
        }

        length--;
        return got_data;
    }
}

void Queue::put(int x) {
    Node* new_node_ptr = new Node(x);
    length++;

    if (head == NULL) {
        head = new_node_ptr;
        tail = new_node_ptr;
    } else {
        tail->next = new_node_ptr;
        tail = tail->next;
    }

    return;
}

int Queue::size() {
    return length;
}

void read_and_apply_input(Queue &queue) {
    std::string command_name;
    std::cin >> command_name;

        try {
            if (command_name == "get") {
                std::cout << queue.get() << std::endl;
            } else if (command_name == "put") {
                int x;
                std::cin >> x;
                queue.put(x);
            } else if (command_name == "size") {
                std::cout << queue.size() << std::endl;
            }
        } catch (std::string &error_name) { 
            std::cout << error_name << std::endl;
        }

    return;
}