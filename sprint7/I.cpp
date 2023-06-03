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

    for (int j = 0; j < m+1; ++j) {
        field[0][j] = -1;
    }
    for (int i = 0; i < n+1; ++i) {
        field[i][0] = -1;
    }

    int steps = n+m-2;
    std::vector<char> dirs(steps);
    int i = n, j = m;
    for (int st = 0; st < steps; ++st) {
        if (field[i-1][j] > field[i][j-1]) {
            dirs[st] = 'U';
            --i;
        } else {
            dirs[st] = 'R';
            --j;
        }
    }

    std::reverse(dirs.begin(), dirs.end());
    
    std::cout << field[n][m] << std::endl;
    for (char dir : dirs) {
        std::cout << dir;
    }
    std::cout << std::endl;

    return 0;
}