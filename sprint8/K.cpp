#include <iostream>
#include <string>
#include <algorithm>

std::string del_odd(const std::string &str) {
    std::string out;
    for (char x : str) {
        if (((x - 'b') % 2) == 0) {
            out.push_back(x);
        }
    }
    return out;
}

int main() {
    std::string a, b;
    std::cin >> a >> b;

    a = del_odd(a);
    b = del_odd(b);

    if (std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end())){
        std::cout << -1 << std::endl;
        return 0;
    }
    if (std::lexicographical_compare(b.begin(), b.end(), a.begin(), a.end())){
        std::cout << 1 << std::endl;
        return 0;
    }

    std::cout << 0 << std::endl;
    return 0;
}