//accepted parcel ID: 81521731
//
// Standard reverse polish notation computation realisation. Any comments seem to be superfluous here.
//
// For additional info see e.g. https://en.wikipedia.org/wiki/Reverse_Polish_notation
// or https://contest.yandex.ru/contest/22781/problems/B/

#include <iostream>
#include <sstream>
#include <string>
#include <stack>

inline int alg_div(int x, int y) {
    if (x >= 0) {
        return x / y;
    } else if ((x % y) == 0) {
        return -((-x) / y);
    } else {
        return -((-x) / y) - 1;
    }
}

inline void pop_twice(int &x, int &y, std::stack <int> &stack) {
    y = stack.top();
    stack.pop();
    x = stack.top();
    stack.pop();
}

int main() {
    std::string input;
    std::getline(std::cin, input);

    std::istringstream reverse_polish_notation(input);
    std::string token;

    std::stack <int> stack;
    int x, y;
    while (reverse_polish_notation >> token) {
               if (token == "+") {
            pop_twice(x, y, stack);
            stack.push(x + y);

        } else if (token == "-") {
            pop_twice(x, y, stack);
            stack.push(x - y);

        } else if (token == "/") {
            pop_twice(x, y, stack);
            stack.push(alg_div(x,y));

        } else if (token == "*") {
            pop_twice(x, y, stack);
            stack.push(x * y);

        } else { //if token is an operand
            stack.push(std::stoi(token));
        }
    }

    std::cout << stack.top() << std::endl;
    return 0;
}