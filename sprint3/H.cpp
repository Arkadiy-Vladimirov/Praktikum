// finds the greatest concatination of given numbers

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

bool cmp(const std::string &a, std::string &b) {
    return (b + a) < (a + b);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::sort(arr.begin(), arr.end(), cmp);
    for (auto num : arr) {
        std::cout << num;
    }
    std::cout << std::endl;
    return 0;
}
