#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

typedef std::vector<std::set<int>> AdjacencyList;

std::vector<int> BFS(int start, AdjacencyList &neighbours);

int main() {
    int n, m;
    std::cin >> n >> m;

    AdjacencyList neighbours(n+1);

    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        neighbours[u].insert(v);
        neighbours[v].insert(u);
    }

    int start;
    std::cin >> start;

    auto distances = BFS(start, neighbours);

    std::cout << *std::max_element(distances.begin(), distances.end()) << std::endl;

    return 0;
}

std::vector<int> BFS(int start, AdjacencyList &neighbours) {
    std::vector<int> dist(neighbours.size(), -1);
    std::vector<int> prev(neighbours.size());
    std::vector<bool> visited(neighbours.size(), false);
    std::vector<bool> bonded(neighbours.size(), false);
    std::queue<int> queue;

    prev[start] = 0;
    bonded[start] = true;
    queue.push(start);

    while (not queue.empty()) {
        int v = queue.front(); queue.pop();
        
        if (not visited[v]) {

            dist[v] = dist[prev[v]] + 1;

            for (int x : neighbours[v]) {
                if (not bonded[x]) {
                    prev[x] = v;
                    queue.push(x);
                    bonded[x] = true;
                }
            }
            
            visited[v] = true;
        }
    }

    return dist;
}