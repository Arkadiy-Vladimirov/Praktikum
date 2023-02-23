// calculate polynomial hash of a string given the base and the modulus

#include <iostream>
#include <string>

int polyHash(std::string str, int base, int modulus);

int main() {
    int base, modulus;
    std::cin >> base >> modulus;
    std::string str;
    std::cin >> str;
    std::cout << polyHash(str, base, modulus) << std::endl;
    return 0;
}

int polyHash(std::string str, int base, int modulus) {
    long long hash = 0;
    for (char c : str) { // Horner's method
        hash = (hash*base + c) % modulus;
    }
    return hash;
}