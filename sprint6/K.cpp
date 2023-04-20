#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>

constexpr int INF = std::numeric_limits<int>::max();

struct Arrow {
    int to;
    int weight;
};

typedef std::vector<std::list<Arrow>> AdjacencyList;

std::vector<std::vector<int>> Dijkstra(AdjacencyList &edges);
std::vector<int> Dijkstra(int s, AdjacencyList &edges);

int main() {
    int n, m;
    std::cin >> n >> m; 

    AdjacencyList edges(n);

    int u, v, dist;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> dist;
        edges[u-1].push_back(Arrow({v-1, dist}));
        edges[v-1].push_back(Arrow({u-1, dist}));
    }

    auto dist_mat = Dijkstra(edges);

    for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        std::cout << dist_mat[i][j] << " ";
    }
    std::cout << std::endl;
    }

    return 0;
}

std::vector<std::vector<int>> Dijkstra(AdjacencyList &edges) {
    std::vector<std::vector<int>> dist_mat;

    for (int s = 0; s < edges.size(); ++s) {
        auto dist = Dijkstra(s, edges);
        dist_mat.push_back(dist);
    }

    return dist_mat;
}

std::vector<int> Dijkstra(int s, AdjacencyList &edges) {
    std::vector<int> dist(edges.size(), INF);
    std::vector<bool> visited(edges.size(), false);

    int min_dist = 0;
    dist[s] = min_dist;

    while (min_dist != INF) { // while there are still not visited vertices

        // relaxation
        for (const auto &edge : edges[s]) { 
            dist[edge.to] = std::min(dist[s] + edge.weight, dist[edge.to]);
        }
        visited[s] = true;

        // find min, i.e. next s
        min_dist = INF;
        for (int v = 0; v < edges.size(); ++v) {
            if ((not visited[v]) && (min_dist > dist[v])){
                min_dist = dist[v]; 
                s = v;
            }
        }
    }

    // change infs to -1
    for (int i = 0; i < edges.size(); ++i) {
        if (dist[i] == INF) {
            dist[i] = -1;
        }
    }
    
    return dist;
}
