#include <iostream>
#include <vector>
#include <map>

std::vector<int> readArr(int n);
int readNum();
void printArr(const std::vector<int> &arr);

std::vector<int> rankedIDList(const std::vector<int> &arr, int k);

int main() {
    auto n = readNum();
    auto arr = readArr(n);
    auto k = readNum();

    printArr(rankedIDList(arr, k));

    return 0;
}



std::vector<int> rankedIDList(const std::vector<int> &arr, int k) {
    std::map<int,int> id_rate;
    for (const auto &val : arr) {
        if (id_rate.find(val) == id_rate.end()) {
            id_rate[val] = 0;
        } else {
            id_rate[val]++;
        }
    }

    std::multimap<int,int, std::greater<int>> rate_id;
    for (const auto &[id, rate] : id_rate) {
        rate_id.insert(std::pair(rate, id));
    }

    std::vector<int> top_k_id;
    for (auto const &[rate, id] : rate_id) {
        if (k == 0) {
            break;
        } else {
        top_k_id.push_back(id);
        k--;
        }
    }

    return top_k_id;
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

void printArr(const std::vector<int> &arr) {
    for (const auto &val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}