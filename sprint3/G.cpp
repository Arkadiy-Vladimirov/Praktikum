// counting sort, elemnts are in {0,1,2}

#include <iostream>
#include <vector>
#include <map>
#include <set>

std::set<int> VALUES = {0, 1, 2};  // the set of values known from the problem statement
std::map<int,int> value_counts = { // the corresponding map
    {0, 0},
    {1, 0},
    {2, 0}
};

std::vector<int> readArr(int n);
void printArr(const std::vector<int> &arr);

std::vector<int> countingSort(const std::vector<int> &arr);

int main() {
    int n;
    std::cin >> n;
    auto arr = readArr(n);
    auto sorted_arr = countingSort(arr);
    printArr(sorted_arr);
    return 0;
}


std::vector<int> countingSort(const std::vector<int> &arr) {
    for (auto val : arr) {
        value_counts[val]++;
    }

    std::vector<int> sorted_arr;
    for (auto val : VALUES) {
        for (int i = 0; i < value_counts[val]; ++i) {
            sorted_arr.push_back(val);
        }
    }

    return sorted_arr;
}

std::vector<int> readArr(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    return arr;
}

void printArr(const std::vector<int> &arr) {
    for (auto val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}