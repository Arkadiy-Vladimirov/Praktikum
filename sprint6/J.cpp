#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>

typedef enum {NOT_VISITED, VISITED, FINISHED} State;

struct Node {
    State state = NOT_VISITED; 
    std::set<int> neighbours;
};

typedef std::vector<Node> AdjacencyList;

std::vector<int> top_sort(AdjacencyList &graph);
std::vector<int> DFS(int start, AdjacencyList &graph);

int main() {
    int n, m;
    std::cin >> n >> m;

    AdjacencyList graph(n+1);

    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        graph[u].neighbours.insert(v);
    }

    auto vertex_order = top_sort(graph);

    for (auto iter = vertex_order.rbegin(); iter != vertex_order.rend(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    return 0;
}

std::vector<int> top_sort(AdjacencyList &graph) {
    std::vector<int> vertex_order;
    
    for (int start = 1; start < graph.size(); ++start) {
        auto vert_ord_piece = DFS(start, graph);
        vertex_order.insert(vertex_order.end(), vert_ord_piece.begin(), vert_ord_piece.end());
    }

    return vertex_order;
}

std::vector<int> DFS(int start, AdjacencyList &graph) {
    std::vector<int> vertex_order;
    std::stack<int> stack;

    stack.push(start);
    while (!stack.empty()) {
        int vert = stack.top();
        
        if (graph[vert].state == FINISHED) {
            stack.pop();            
        }
        
        if (graph[vert].state == VISITED) {
            stack.pop();
            graph[vert].state = FINISHED;
            vertex_order.push_back(vert);
        }

        if (graph[vert].state == NOT_VISITED) {
            graph[vert].state = VISITED;
            for (int neib : graph[vert].neighbours) {
                if (graph[neib].state == NOT_VISITED) {
                    stack.push(neib);
                }                
            }
        }
    }

    return vertex_order;
}