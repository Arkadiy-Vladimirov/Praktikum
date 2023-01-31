// accepted parcel ID: 81606627
//
// Standard reverse polish notation computation realisation.
//
// The algorithm computes an expression of size n represented in reverse polish 
// notation (https://en.wikipedia.org/wiki/Reverse_Polish_notation).
//
// In a nuthell, we process the expression linearly token by token (whether it 
// be an operand or an operator) till the end of it. If we got an operand, we 
// put it on the top of the stack. Otherwise, we reached an operator and we 
// execute it on the top two elements of the stack, pop them out, and put the 
// result back on the top.
//
// As long as the r.p.n. of an expression is correct, at the end of the 
// operation there would only be one element in the stack left - the value of 
// the expression. As the computations are done one-pass linearly through the 
// expression and at each step only a fixed number of operations is executed, 
// the complexity of computation is O(n). 
// 
// The main contributor to the space consumption of the algorithm is the stack. 
// Depending on whether we've reached an operand or an operator the stack size 
// is increased, or decresed by one correspondingly. Hence, the size is bounded 
// above with n, from the one hand, and is not less than n/2 from the other, as 
// in worst cases like "12345++++", we need a stack of at least n/2 elements. 
// Therefore, the space complexity is O(n).
//
// For additional info see e.g. https://en.wikipedia.org/wiki/Reverse_Polish_notation
// or https://contest.yandex.ru/contest/22781/problems/B/ (rus)


#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <algorithm>


inline void pop_twice(int &x, int &y, std::stack <int> &stack) {
    y = stack.top();
    stack.pop();
    x = stack.top();
    stack.pop();
}

int algebraic_division(int x, int y);

std::set<std::string> operators {"+", "-", "*", "/"};
    
std::map<std::string, std::function<int(int,int)>> execute_operator {
    {"+", std::plus<int>()},
    {"-", std::minus<int>()},
    {"*", std::multiplies<int>()},
    {"/", algebraic_division}
};



int main() {
    std::string input;
    std::string token;
    std::stack <int> stack;
    std::getline(std::cin, input);
    std::istringstream reverse_polish_notation(input);

    int x, y;
    while (reverse_polish_notation >> token) {
        if (operators.find(token) != operators.end()) { // if operator
            pop_twice(x,y, stack);
            stack.push(execute_operator[token](x,y));
        } else {                                       // otherwise
            stack.push(std::stoi(token));
        }
    }

    std::cout << stack.top() << std::endl;
    return 0;
}



int algebraic_division(int x, int y) {
    if (x >= 0) {
        return x / y;
    } else if ((x % y) == 0) {
        return -((-x) / y);
    } else {
        return -((-x) / y) - 1;
    }
}