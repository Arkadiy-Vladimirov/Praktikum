// given a list of minimum acceptable number for each player and a list of 
// numbers, find out the maximum amount of accepted nmumbers.

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> readArr(int n);
int readNum();

int maxAccepted(std::vector<int> &arr, std::vector<int> &min_acceptable);

int main() {
    auto n = readNum();
    auto min_acceptable = readArr(n);
    auto m = readNum();
    auto arr = readArr(m);
    std::cout << maxAccepted(arr, min_acceptable) << std::endl;
    return 0;
}




int maxAccepted(std::vector<int> &arr, std::vector<int> &min_acceptable) {
    std::sort(arr.begin(), arr.end());
    std::sort(min_acceptable.begin(), min_acceptable.end());
    int max_accepted = 0;
    while (min_acceptable.size() != 0) {
        if (min_acceptable.back() <= arr.back()) { // accepted!
            min_acceptable.pop_back();
            arr.pop_back();
            max_accepted++;
        } else {
            min_acceptable.pop_back();             // not accepted
        }
    }
    return max_accepted;
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