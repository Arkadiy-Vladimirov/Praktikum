// prints all combinations of characters that may occur with a number dialed

#include <iostream>
#include <string>
#include <map>

std::map<char, std::string> letters = {
    {'1', ""},
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"},
    {'0', ""}
};

void print_all_combinations(std::string numbers, std::string prefix = "") {
    if (numbers == "") {
        std::cout << prefix << " ";
    } else {
        char number = numbers.front(); //get the first character of the string
        numbers = numbers.substr(1);   //pop the first character of the string
        for (auto letter : letters[number]) {
            print_all_combinations(numbers, prefix + letter);
        }
    }
}

int main() {
    std::string numbers;
    std::getline(std::cin, numbers);
    print_all_combinations(numbers);
    std::cout << std::endl;
    return 0;
}