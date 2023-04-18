#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adjacency_matrix(n, std::vector<int>(n, 0));

    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        adjacency_matrix[u-1][v-1] = 1;
    }

    for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        std::cout << adjacency_matrix[i][j] << " ";
    }
    std::cout << std::endl;
    }

    return 0;
}