#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> readArr(int n);
int readNum();
int maxTrianglePerimeter(std::vector<int> &arr);

int main() {
    auto n = readNum();
    auto arr = readArr(n);
    std::cout << maxTrianglePerimeter(arr) << std::endl;
    return 0;
}



int maxTrianglePerimeter(std::vector<int> &arr) {
    std::sort(arr.rbegin(), arr.rend()); // sort in descending order
    for (auto p = arr.begin(); p != (arr.end() - 2); ++p) {
        if (*p < (*(p + 1) + *(p + 2))) {
            return *p + *(p + 1) + *(p + 2);
        }
    }
    return -1;
}

std::vector<int> readArr(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    return arr;
}

int readNum() {
    int x;
    std::cin >> x;
    return x;
};