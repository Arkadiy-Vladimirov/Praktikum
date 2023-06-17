// accepted parcel ID: -
//
// Problem description  
//
// Solution
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {

    // input
    std::string s, t;
    std::getline(std::cin, s);
    std::getline(std::cin, t);

    // initialization
    // i = 0..n, j = 0..m - sizes of t and s prefixes corresp.
    int n = s.size(), m = t.size();
    std::vector<std::vector<int>> dist(n+1, std::vector<int>(m+1));

    // base case -- Levenstein distance between the empty string and a string
    // equals to the length of the latter.
    for (int i = 0; i < n+1; ++i) {
        dist[i][0] = i;
    }
    for (int j = 0; j < m+1; ++j) {
        dist[0][j] = j;
    }

    // computation
    for (int i = 1; i < n+1; ++i) {
        for (int j = 1; j < m+1; ++j) {
            dist[i][j] = std::min({
                dist[i-1][ j ] + 1,                    // "append s_i"
                dist[ i ][j-1] + 1,                    // "delete t_j"
                dist[i-1][j-1] + int(s[i-1] != t[j-1]) // "replace s_i with t_j"
            }); // note that indexing in strings is shifted here and starts at 0
        }
    }

    // output
    std::cout << dist[n][m] << std::endl;

    return 0;
}