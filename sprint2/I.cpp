#include <iostream>
#include <vector>

class MyQueueSized {
    std::vector <int> buff;
    int head;
    int tail;
    int max_size;
    int cur_size;

public:
    MyQueueSized(int max_size) : buff(max_size), head(0), tail(0), max_size(max_size), cur_size(0) {};

    void push(int x);
    int pop();
    int peek();
    int size();

    void read_command();
};



int main() {
    int n;
    std::cin >> n;

    int size;
    std::cin >> size;
    MyQueueSized queue(size);

    for (int i = 0; i < n; ++i) {
        queue.read_command();
    }

    return 0;
}



void MyQueueSized::push(int x) {
    if (cur_size < max_size) {
        buff[tail] = x;
        tail = (tail + 1) % max_size;
        cur_size++;
    } else {
        std::string err = "error";
        throw err;
    }
    return;
}

int MyQueueSized::pop() {
    if (cur_size != 0) {
        int head_element = buff[head];
        head = (head + 1) % max_size;
        cur_size--;
        return head_element;
    } else {
        std::string err = "None";
        throw err;
    }
}

int MyQueueSized::peek() {
    if (cur_size != 0) {
        return buff[head];
    } else {
        std::string err = "None";
        throw err;
    }
}

int MyQueueSized::size() {
    return cur_size;
}

void MyQueueSized::read_command() {
    std::string command_name;
    std::cin >> command_name;
        try {
            if (command_name == "push") {
                int x;
                std::cin >> x;
                push(x);
            } else if (command_name == "pop") {
                std::cout << pop() << std::endl;
            } else if (command_name == "peek") {
                std::cout << peek() << std::endl;
            } else if (command_name == "size") {
                std::cout << size() << std::endl;
            }
        } catch (std::string &error_name) { 
            std::cout << error_name << std::endl;
        }

    return;
}