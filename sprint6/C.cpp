#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <list>

typedef std::vector<std::set<int>> AdjacencyList;

std::list<int> DFS(int start, AdjacencyList &graph);

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

    int start;
    std::cin >> start;

    auto visit_order = DFS(start, graph);

    for (int x : visit_order) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}

std::list<int> DFS(int start, AdjacencyList &graph) {
    std::stack<int> stack;
    std::vector<bool> not_visited(graph.size(), true);
    std::list<int> visit_order;

    stack.push(start);

    while (!stack.empty()) {

        int vert = stack.top();
        stack.pop();

        if (not_visited[vert]) {
            //color the vertex
            visit_order.push_back(vert);
            not_visited[vert] = false;

            //add unvisited neighbours to stack
            auto &neighbours = graph[vert];
            for (auto p = neighbours.rbegin(); p != neighbours.rend(); ++p) {
                int neib = *p;
                if (not_visited[neib]) {
                    stack.push(neib);
                }
            }
        }
        //proceed untill there are no more unvisited vertices
    }

    return visit_order;
}