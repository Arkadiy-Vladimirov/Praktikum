#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string a, b;
    std::cin >> a >> b;

    std::size_t pos = 0;
    while ((pos < a.size()) && (pos < b.size())) {
        if (a[pos] != b[pos]) {
            break;
        }
        pos++;
    }

    bool is_equal;
    if (a.size() < b.size()) {
        is_equal = a.substr(pos) == b.substr(pos + 1);
    }
    if (a.size() > b.size()) {
        is_equal = a.substr(pos + 1) == b.substr(pos);   
    }
    if (a.size() == b.size()) {
        pos = std::min(pos + 1, a.size());
        is_equal = a.substr(pos) == b.substr(pos);
    }

    if (is_equal) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }

    return 0;
}