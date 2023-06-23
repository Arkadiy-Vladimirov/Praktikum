#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main() {
    std::string line, word;
    std::getline(std::cin, line);
    
    std::vector<std::string> words;
    auto iss = std::istringstream(line);
    while (iss >> word) {
        words.push_back(word);
    }

    for (auto p = words.rbegin(); p != words.rend(); ++p) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;

    return 0;
}