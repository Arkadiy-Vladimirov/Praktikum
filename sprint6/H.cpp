#include <iostream>
#include <vector>
#include <set>
#include <stack>

struct Time {
    int in;
    int out;
};

typedef std::vector<Time> TimeRecord;
typedef std::vector<std::set<int, std::greater<int>>> AdjacencyList;
typedef enum {NOT_VISITED, VISITED, FINISHED} State;

TimeRecord DFS(int start, AdjacencyList &graph);

int main() {
    int n, m;
    std::cin >> n >> m;

    AdjacencyList graph(n+1);

    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        graph[u].insert(v);
    }

    auto time = DFS(1, graph);

    for (int i = 1; i <= n; ++i) {
        std::cout << time[i].in << " " << time[i].out << std::endl;
    }

    return 0;
}

TimeRecord DFS(int start, AdjacencyList &graph) {
    TimeRecord time_record(graph.size());
    std::vector<State> state(graph.size(), NOT_VISITED);
    std::stack<int> stack;

    int time = 0;
    stack.push(start);

    while (!stack.empty()) {
        int vert = stack.top();
        if (state[vert] == NOT_VISITED) {       // visit first time
            state[vert] = VISITED;
            time_record[vert].in = time;
            time++;

            auto &neighbours = graph[vert];
            for (int neib : neighbours) {
                if (state[neib] == NOT_VISITED) {
                    stack.push(neib);
                }
            }

        } else if (state[vert] == VISITED) {    // we've returned to it
            state[vert] = FINISHED;
            time_record[vert].out = time; 
            time++;
            stack.pop(); // remove the vertex from the stack
        } else {                                // the vertex is fully processed already
            stack.pop(); // remove the vertex from the stack
        }
    }

    return time_record;
}