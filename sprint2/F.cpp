#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class StackMax {
    std::vector<int> data;
public:
    void push(int x) {
        data.push_back(x);
    }

    int pop() {
        if (data.size() == 0) {
            std::string error_message = "error";
            throw error_message;
        } else {
            int x = data.back();
            data.pop_back();
            return x;
        }
    }

    int get_max() {
        if (data.size() == 0) {
            std::string error_message = "None";
            throw error_message;
        } else {
            auto max_ptr = std::max_element(data.begin(), data.end());
            return *max_ptr;
        }  
    }
};

int main() {
    StackMax stack;

    int n;
    std::cin >> n;

    std::string command_name;
    for (int i = 0; i < n; ++i) {
        std::cin >> command_name;
        if (command_name == "push") {
            int x;
            std::cin >> x;
            stack.push(x);
        } else {
            try {
                if (command_name == "pop") {
                    stack.pop();
                }
                if (command_name == "get_max") {
                    std::cout << stack.get_max() << std::endl;
                }
            } catch (std::string &error_name) { std::cout << error_name << std::endl;}
        }
    }

    return 0;
}