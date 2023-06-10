#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // input
    int n;
    std::cin >> n;

    std::vector<int> r(n+1);
    for (int i = 1; i < n+1; ++i) {
        std::cin >> r[i];
    }

    // forward go
    std::vector<int> v(n+1);
    v[0] = 0;

    for (int i = 1; i < n+1; ++i) {
        int max_val = v[0];
        for (int j = 1; j < i; ++j) {
            if (r[j] < r[i]) {
                max_val = std::max(max_val, v[j]);
            }
        }
        v[i] = 1 + max_val;
    }

    // find ans
    std::vector<int> ans_idx;
    int fin_idx = std::distance(v.begin(), std::max_element(v.begin(), v.end()));

    // backward go
    ans_idx.push_back(fin_idx);
    int i = fin_idx;
    int j = i-1;

    while (j > 0) {
        if ((r[j] < r[i]) && (v[j] + 1 == v[i])) {
            ans_idx.push_back(j);
            i = j;
        }
        j--;
    }

    // output
    std::reverse(ans_idx.begin(), ans_idx.end());

    std::cout << ans_idx.size() << std::endl;
    for (int i: ans_idx) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}