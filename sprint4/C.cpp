// compute hash of requested substrings with O(1) time and O(n) additional data

#include <iostream>
#include <string>
#include <vector>

class substrHash {
    std::string str;
    int base, modulus;
    std::vector<long long> base_pow;
    std::vector<long long> prefix_hash;
public:
    substrHash(std::string str, int base, int modulus);
    int operator() (int first, int last);
};

int main() {
    int base, modulus;
    std::cin >> base >> modulus;
    std::string str;
    std::cin >> str;

    substrHash substr_hash(str, base, modulus);

    int n, l, r;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> l >> r;
        std::cout << substr_hash(l-1,r) << std::endl;
    }
    return 0;
}

substrHash::substrHash(std::string str, int base, int modulus) :
    str(str), base(base), modulus(modulus),
    base_pow(std::vector<long long> (str.size())),
    prefix_hash(std::vector<long long> (str.size()+1))
{
    base_pow[0] = 1;
    for (int i = 1; i < base_pow.size(); ++i) {
        base_pow[i] = base_pow[i-1]*base % modulus;
    }

    prefix_hash[0] = 0;
    for (int i = 1; i < str.size()+1; ++i) {
        prefix_hash[i] = (prefix_hash[i-1] * base + str[i-1]) % modulus;
    }

    return;
}

int substrHash::operator() (int first, int last) {
    return  (modulus + 
        prefix_hash[last] - (prefix_hash[first]*base_pow[last-first] % modulus))
            % modulus;
}