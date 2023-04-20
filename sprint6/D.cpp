#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>

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

    auto traverse_log = BFS(start, neighbours);

    for (int x : traverse_log) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}

std::vector<int> BFS(int start, AdjacencyList &neighbours) {
    std::vector<int> traverse_log;
    std::queue<int> queue;
    std::vector<bool> visited(neighbours.size(), false);

    queue.push(start);

    while (not queue.empty()) {

        int v = queue.front(); queue.pop();

        if (not visited[v]) {
            traverse_log.push_back(v);
            for (int x : neighbours[v]) {
                queue.push(x); 
            }
            visited[v] = true;
        }
    }

    return traverse_log;
}