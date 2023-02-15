#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> readArr(int n);
int maxPurchases(std::vector<int> &arr, int limit);

int main() {
    int n, k;
    std::cin >> n >> k;
    auto arr = readArr(n);
    std::cout << maxPurchases(arr, k) << std::endl;
    return 0;
}

int maxPurchases(std::vector<int> &arr, int limit) {
    int purchases = 0;
    std::sort(arr.rbegin(), arr.rend()); //sort in descending order
    while (!arr.empty()) {
        if (limit >= arr.back()) {
            limit = limit - arr.back();
            arr.pop_back();
            purchases++;
        } else {
            return purchases;
        }
    }
    return purchases;
}

std::vector<int> readArr(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    return arr;
}