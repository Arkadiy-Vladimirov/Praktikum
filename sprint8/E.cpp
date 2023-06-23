#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct Insertion {
    std::string str;
    int count;
};

bool operator < (const Insertion &lhs, const Insertion &rhs) {
    return lhs.count < rhs.count;
}   

int main() {
    std::string input;
    std::cin >> input;

    int n;
    std::cin >> n;

    std::vector<Insertion> insertions(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> insertions[i].str >> insertions[i].count;
    }

    std::sort(insertions.begin(), insertions.end());

    int pos = 0;
    std::ostringstream oss;
    for (const auto &insertion : insertions) {
        oss << input.substr(pos, insertion.count - pos) << insertion.str;
        pos = insertion.count;
    }
    oss << input.substr(pos, input.size() - pos);

    std::cout << oss.str() << std::endl;

    return 0;
}