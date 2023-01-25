#include <iostream>
#include <vector>
#include <string>

class StackMax {
    std::vector<int> stack;
    std::vector<int> max_stack;

public:
    void push(int x) {
        if (stack.size() == 0) {
            max_stack.push_back(x);
        } else {
            if (x > max_stack.back()) {
                max_stack.push_back(x);
            } else {
                max_stack.push_back(max_stack.back());
            }
        }
        stack.push_back(x);
    }

    int pop() {
        if (stack.size() == 0) {
            std::string error_message = "error";
            throw error_message;
        } else {
            int x = stack.back();
            stack.pop_back();
            max_stack.pop_back();

            return x;
        }
    }

    int get_max() {
        if (stack.size() == 0) {
            std::string error_message = "None";
            throw error_message;
        } else {
            return max_stack.back();
        }  
    }

    void read_command() {
        std::string command_name;
        std::cin >> command_name;
        if (command_name == "push") {
            int x;
            std::cin >> x;
            push(x);
        } else {
            try {
                if (command_name == "pop") {
                    pop();
                }
                if (command_name == "get_max") {
                    std::cout << get_max() << std::endl;
                }
            } catch (std::string &error_name) { std::cout << error_name << std::endl;}
        }

        return;
    }
};

int main() {
    StackMax stack;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        stack.read_command();
    }

    return 0;
}