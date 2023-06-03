#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n,m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> field(n+1, std::vector<int>(m+1,0));
    for (int i = n; i > 0; --i) {
    for (int j = 1; j < m+1; ++j) {
        char c;
        std::cin >> c;
        field[i][j] = c - '0';
    }
    }

    for (int i = 1; i < (n+1); ++i) {
        for (int j = 1; j < (m+1); ++j) {
            field[i][j] = field[i][j] + std::max(field[i-1][j], field[i][j-1]);
        }
    }

    std::cout << field[n][m] << std::endl;
    
    return 0;
}