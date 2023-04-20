#include <iostream>
#include <vector>
#include <set>
#include <stack>


typedef std::set<int> Vertices;
bool operator < (const Vertices &lhs, const Vertices &rhs) {
    return *lhs.cbegin() < *rhs.cbegin();
}

typedef std::set<Vertices> Components;
typedef std::vector<Vertices> AdjacencyList;

Components get_components(AdjacencyList &graph);
Vertices DFS(int start, AdjacencyList &graph);

int main() {
    int n, m;
    std::cin >> n >> m;

    AdjacencyList graph(n+1);

    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    auto components = get_components(graph);

    std::cout << components.size() << std::endl;
    for (const auto &comp : components) {
        for (int v : comp) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

Components get_components(AdjacencyList &graph) {
    std::vector<bool> not_visited(graph.size(), true);
    Components components;

    for (int v = 1; v < graph.size(); ++v) {
        if (not_visited[v]) {   //if not traversed through yet
            //get another component
            auto comp = DFS(v, graph);
            components.insert(comp);

            //update what is visitied
            for (int v : comp) {
                not_visited[v] = false;
            }
        }
    }

    return components;

}

Vertices DFS(int start, AdjacencyList &graph) {
    std::vector<bool> not_visited(graph.size(), true);
    std::stack<int> stack;
    Vertices visited_vertices;

    stack.push(start);
    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();

        if (not_visited[v]) {
            visited_vertices.insert(v);
            not_visited[v] = false;
            for (int u : graph[v]) {
                stack.push(u);
            }
        }       
    }

    return visited_vertices;
}