// check if two strings are equal up to renaming of chars

#include <iostream>
#include <string>
#include <unordered_map>

std::string universal_mapping(const std::string &str);

int main() {
    std::string str_a, str_b;
    std::cin >> str_a >> str_b;
    if (universal_mapping(str_a) == universal_mapping(str_b)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;

}

std::string universal_mapping(const std::string &str) {
    std::unordered_map<char, int> code;
    int next_code = 0;
    std::string str_image = "";
    for (char c : str) {
        if (code.find(c) == code.end()) { // if not encoded yet
            code[c] = next_code;
            next_code++;
        }
        str_image += code[c];
    }
    return str_image;
}