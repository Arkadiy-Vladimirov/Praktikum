#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> vol(n+1);
    for (int i = 1; i < n+1; ++i) {
        std::cin >> vol[i];
    }

    std::vector<std::vector<int>> pi(n+1, std::vector<int>(m+1, 0));

    for (int i = 1; i < n+1; ++i) {
        for (int j = 1; j < m+1; ++j) {
            if (j-vol[i] < 0) { // if ith item does not fit into the backpack
                pi[i][j] = pi[i-1][j];
            } else {
                pi[i][j] = std::max(pi[i-1][j], vol[i] + pi[i-1][j-vol[i]]);
            }
        }
    }

    std::cout << pi[n][m] << std::endl;

    return 0;
}