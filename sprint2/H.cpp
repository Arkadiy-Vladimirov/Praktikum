#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <set>

std::set <char> open_brackets = {'(', '[', '{'};
std::map <char, char> open_one = {{')', '('}, {']','['}, {'}','{'}};

bool isCorrectBracketSeq(const std::string &bracket_seq);

int main() {
    std::string bracket_sequence;
    std::getline(std::cin, bracket_sequence);

    if (isCorrectBracketSeq(bracket_sequence)) {
        std::cout << "True" << std::endl;
    } else {
        std::cout << "False" << std::endl;
    }

    return 0;
}


bool isCorrectBracketSeq(const std::string &bracket_seq) {
    std::stack <char> stack;
    
    for (char bracket : bracket_seq) {
        if (open_brackets.find(bracket) != open_brackets.end()) {
            stack.push(bracket);
        } else if (!stack.empty() && (stack.top() == open_one[bracket])) {
            stack.pop();
        } else {
            return false;
        }
    }

    if (stack.empty()) {
        return true;
    } else {
        return false;
    }
}