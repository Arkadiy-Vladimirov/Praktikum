// UNSOLVED
// the problem does not require code. Given the hash funciton, find two strings 
// that have the same hash

#include <iostream>

int polyHash(std::string str, int base, int modulus);

int main() {
    std::string str;
    while(true) {
        std::getline(std::cin, str);
        std::cout << polyHash(str, 1000, 123987123) << std::endl;
    }
    return 0;
}

int polyHash(std::string str, int base, int modulus) {
    long long hash = 0;
    for (char c : str) { // Horner's method
        hash = (hash*base + c) % modulus;
    }
    return hash;
}