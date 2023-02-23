// 4-sum problem
#include <iostream>
#include <vector>
#include <tuple>
#include <set>
//#include <unordered_set>
#include <unordered_map>
#include <algorithm>

std::vector<int> readArr(int n);
void printSet4(const std::set<std::tuple<int,int,int,int>> &set4);

std::set<std::tuple<int,int,int,int>> find4Sum(int sum, std::vector<int> arr);

int main() {
    int n, s;
    std::cin >> n >> s;
    auto arr = readArr(n);
    printSet4(find4Sum(s, arr));
}

// O(n^2) time, O(n^2) space complexity
std::set<std::tuple<int,int,int,int>> find4Sum(int sum, std::vector<int> arr) {
    std::set<std::tuple<int,int,int,int>> ans;
    std::unordered_map<long long, std::vector<std::pair<int,int>>> seen_pairs;
    std::sort(arr.begin(), arr.end());
    int n = arr.size();

    for (int j = 0; j < n; ++j) {
        for (int k = j+1; k < n; ++k) {
            long long res = (long long)sum - ((long long)arr[j] + (long long)arr[k]);
            if (seen_pairs.find(res) != seen_pairs.end()) {
                for (auto pair : seen_pairs[res]) {
                    ans.insert(std::make_tuple(pair.first, pair.second, arr[j], arr[k]));
                }
            }
        }

        for (int i = 0; i < j; ++i) {
            seen_pairs[(long long)arr[i] + (long long)arr[j]].push_back(std::make_pair(arr[i], arr[j]));
        }
    }

    return ans;
}

// O(n^3) time, O(n) space complexity
/*std::set<std::tuple<int,int,int,int>> find4Sum(int sum, std::vector<int> arr) {
    std::set<std::tuple<int,int,int,int>> ans;
    std::unordered_set<int> seen_elements;
    std::sort(arr.begin(), arr.end());
    int n = arr.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            for (int k = j+1; k < n; ++k) {
                int res = sum - (arr[i] + arr[j] + arr[k]);
                if (seen_elements.find(res) != seen_elements.end()) {
                    ans.insert(std::make_tuple(res, arr[i], arr[j], arr[k]));
                }
            }
        }
        seen_elements.insert(arr[i]); 
    }

    return ans;
}*/

std::vector<int> readArr(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    return arr;
}

void printSet4(const std::set<std::tuple<int,int,int,int>> &set4) {
    std::cout << set4.size() << std::endl;
    for (const auto &t : set4) {
        std::cout << std::get<0>(t) << " "
                  << std::get<1>(t) << " "
                  << std::get<2>(t) << " " 
                  << std::get<3>(t) << " " << std::endl;
    }
    return;
}