#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> str(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> str[i];
    }

    int m;
    std::cin >> m;
    std::vector<int> temp(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> temp[i];
    }

    std::vector<int> ans;
    for (int start = 0; start < (n - m + 1); ++start) {
        int c = str[start] - temp[0];
        bool fits = true;
        for (int i = 0; i < m; ++i) {
            if (str[start + i] != (temp[i] + c)) {
                fits = false;
            }
        }
        
        if (fits) {
            ans.push_back(start + 1);
        }
    }

    for (int x : ans) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}