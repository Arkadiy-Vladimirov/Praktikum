#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int readNum();
std::vector<std::string> readArr(int n);
void printArr(std::vector<std::string> const &arr);

std::vector<std::string> eraseRecs(std::vector<std::string> const &arr);

int main() {
    auto n = readNum();
    auto string_arr = readArr(n);
    printArr(eraseRecs(string_arr));
    return 0;
}



//____implementation____
std::vector<std::string> eraseRecs(std::vector<std::string> const &arr) {
    std::vector<std::string> norecs_arr;
    for (const auto &x : arr) {
        if (std::find(norecs_arr.begin(), norecs_arr.end(), x) == norecs_arr.end()) {
            norecs_arr.push_back(x);    
        }
    } 
    return norecs_arr;
}

int readNum() {
    int x;
    std::cin >> x;
    std::cin.ignore();
    return x;
}

std::vector<std::string> readArr(int n) {
    std::vector<std::string> arr;
    std::string input;

    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, input);
        arr.push_back(input);
    }
    return arr;
}

void printArr(std::vector<std::string> const &arr) {
    for (const auto &element : arr) {
        std::cout << element << std::endl;
    }
    return;
}