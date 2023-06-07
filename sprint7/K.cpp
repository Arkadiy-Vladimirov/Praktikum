#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    // input
    int n;
    std::cin >> n;
    std::vector<int> a(n+1);
    for (int i = 1; i < n+1; ++i) {
        std::cin >> a[i];
    }

    int m;
    std::cin >> m;
    std::vector<int> b(m+1);
    for (int j = 1; j < m+1; ++j) {
        std::cin >> b[j];
    }

    // forward go
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));
    for (int i = 1; i < n+1; ++i) {
        for (int j = 1; j < m+1; ++j) {
            if (a[i] == b[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    // backward go
    int i = n, j = m;
    std::vector<int> a_idx, b_idx;
    while (dp[i][j] != 0) {
        if (a[i] == b[j]) {
            a_idx.push_back(i);
            b_idx.push_back(j);
            i--; j--;
        } else {
            if (dp[i][j] == dp[i-1][j]) {
                i--;
            } else {
                j--;
            }
        } 
    }
    std::reverse(a_idx.begin(), a_idx.end());
    std::reverse(b_idx.begin(), b_idx.end());

    // output
    std::cout << dp[n][m] << std::endl;

    for (int i : a_idx) {
        std::cout << i << " ";
    
    }
    std::cout << std::endl;

    for (int j : b_idx) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    return 0;
}