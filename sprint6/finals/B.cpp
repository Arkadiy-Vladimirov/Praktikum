// accepted parcel ID: ---
//
// An oriented graph G = (V, E) (|V| = n, |E| = m) is given and is divided into 
// subgraphs: R = (V, E_r) and B = (V, E_b), E = E_r v E_b. Vertices V are 
// already topologically sorted w.r.t. both E_r and E_b.
//
// def. We will say that a vertice v is G-reachable from a vertice u if there 
// is a path u-->v in the graph G.
//
// def. We will say that (R, B) is an optimal partition of a graph G if there 
// is no such pair of vertices (u,v) that v is both R- and B- reachable from u.
//
// The goal is to detect whether the partition (R,B) is optimal for the graph G.
//
// The algortihm simply constructs reachable sets for each vertice in a graph 
// and compare them afterwards: iff there is a coincidence the partiaion is not 
// optimal
//
// In order to get reachable(v) we may run DFS(v) and collect all traversed 
// vertices O(n^2). When running through descendant vertices DFS automatically
// collects reachable sets for them. Hence, in one DFS, i.e. O(n^2) we may 
// collect all reachable sets for a graph.
//
// Therefore we get:
// O(n^2) time complexity (from DFS and reachables comparison)
// O(n^2) additional memory consumption (as we need to store reachables)
//
// The algorithm itself is described below.
//

//_________________________________Includes_____________________________________
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <numeric>

//_________________________________Graph_class__________________________________
class Graph {
    std::list<int> vertices;
    std::vector<std::list<int>> adjacency_list;
    std::vector<std::list<int>> reachibility_list;
public:
    Graph(int n) : adjacency_list(n), reachibility_list(n), vertices() {
        for (int v = 0; v < n; ++v) {
            vertices.push_back(v);
        }
    };

    void add_arc(int from, int to);

    const std::list<int>& get_vertices() const;
    const std::list<int>& adjacent(int v) const;
          std::list<int>& reachable(int v);
};

//___________________________________DFS_class__________________________________
class DFS {
    std::vector<int> times_visited;
    std::vector<int> previous;
    Graph* Gptr;

public:
    DFS(int n) : times_visited(n, 0), previous(n, -1), Gptr(nullptr) {};
    void operator() (Graph &G);

private:
    void clear();
    void traverse(int v);
    void update_reachable(int v);
};

//____________________________________Main______________________________________
bool is_optimal(int n, Graph &R, Graph &B);

int main() {
    int n;
    std::cin >> n;

    Graph R(n), B(n);

    std::map<char, Graph*> get_graph { {'R', &R}, {'B', &B} };
    char edge_class; // R or B

    for (int i = 0; i < (n - 1); ++i) {
        for (int j = (i + 1); j < n; ++j) {
            std::cin >> edge_class;
            get_graph[edge_class]->add_arc(i, j);
        }
    }

    std::map<bool, std::string> cli_response {{false, "NO\n"}, {true, "YES\n"}};
    std::cout << cli_response[is_optimal(n, R, B)];

    return 0;
}


//_______________________is_optimal_implementation______________________________
bool is_optimal(int n, Graph &R, Graph &B) {
    // obtain reachables
    DFS dfs(n);
    dfs(R); dfs(B);

    // reachables comparison
    for (int v = 0; v < n; ++v) {
        int r, b;
        while ((not R.reachable(v).empty()) &&  (not B.reachable(v).empty())) {
            r = R.reachable(v).front();
            b = B.reachable(v).front();
            if (r < b) {
                R.reachable(v).pop_front();
            }
            if (r > b) {
                B.reachable(v).pop_front();
            }
            if (r == b) {
                return false;
            }
        }
    }
    return true;
}

//_____________________________Graph_methods____________________________________
void Graph::add_arc(int from, int to) {
    adjacency_list[from].push_back(to);
}
const std::list<int>& Graph::get_vertices() const {
    return vertices;
}
const std::list<int>& Graph::adjacent(int v) const {
    return adjacency_list[v];
}
std::list<int>& Graph::reachable(int v) {
    return reachibility_list[v];
}

//______________________________DFS_methods_____________________________________
void DFS::operator() (Graph &G) {
    Gptr = &G;
    for (auto v : G.get_vertices()) {
        traverse(v);
    }
    clear();
}

void DFS::traverse(int v) {
    Graph& G = *Gptr;
    std::stack<int> stack;
    stack.push(v);

    while (not stack.empty()) {
        int v = stack.top();
        
        if (times_visited[v] == 2) {
            stack.pop();
        }
        if (times_visited[v] == 1) {
            update_reachable(v);
            times_visited[v]++;
            stack.pop();
        }
        if (times_visited[v] == 0) {
            for (auto u : G.adjacent(v)) {
                previous[u] = v;
                stack.push(u);                
            }           
            times_visited[v]++;
        }
        
    }
}

void DFS::update_reachable(int v) {
    Graph& G = *Gptr;
    if (previous[v] != -1) {
        G.reachable(previous[v]).push_back(v);
        G.reachable(previous[v]).insert(G.reachable(previous[v]).end(),
                                G.reachable(v).begin(), G.reachable(v).end());
    }
}

void DFS::clear() {
    std::fill(times_visited.begin(), times_visited.end(), 0);
    std::fill(previous.begin(), previous.end(), -1);
    Gptr = nullptr;
}