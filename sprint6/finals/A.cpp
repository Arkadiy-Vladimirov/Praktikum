// accepted parcel ID: 86219022	
//
// Maximum Spanning Tree extraction.
// Particularly, the Prim's algorithm is implemented. 
// The description may be found at e.g. 
//                              https://en.wikipedia.org/wiki/Prim%27s_algorithm
//
// In a nutshell, this is a greedy algorithm that costructs a tree gradually by 
// adding reachable vertices with maximum edge weight one by one. 
// 
// A step of an algorithm works as follows:
// Assume we have added i vertices, v_i is the last added.
//  - push all vertices from adjacent(v_i) with weights into the heap
//  - pop the heap untill we get an unvisited one - this would be the next 
//  vertice v_{i+1}
//
// Throughout the algorithm we would add O(E) vertices with weights into heap 
// giving us O(E) space complexity and O(ElogE) = O(E 2logV) = O(ElogV) time.
// We proceed untill the heap is empty, so the extraction complexity may be 
// estimated similarly.
//
// All the other procedures are of O(V) or O(E), hence we get:
// Time complexity: O(ElogV)
// Space complexity: O(E).
//

#include <iostream>
#include <vector>
#include <list>
#include <queue>

struct Arc {
    int to;
    int weight;
};

struct CompareWeigths {
    bool operator() (const Arc &lhs, const Arc &rhs) {
        return (lhs.weight < rhs.weight);
    }
};

class Graph {
    std::list<int> vertices;
    std::vector<std::list<Arc>> adjacency_list;

public:
    Graph(int n) : adjacency_list(n), vertices() {
        for (int v = 0; v < n; ++v) {
            vertices.push_back(v);
        }
    };

    void add_arc (int from, int to, int weight);
    void add_edge(int from, int to, int weight);

    size_t size() const;
    const std::list<int>& get_vertices() const;
    const std::list<Arc>& adjacent(int v) const;
};

class MST {
    int total_weight;
    std::priority_queue<Arc, std::vector<Arc>, CompareWeigths> heap;
    std::vector<bool> visited;

private:
    void setup(const Graph &G);
    bool all_connected();

public:
    int operator() (const Graph &G);
};



int main() {
    int n, m;
    std::cin >> n >> m;

    Graph G(n);

    int u, v, weight;
    for (int i = 0; i < m; ++i){
        std::cin >> u >> v >> weight;
        G.add_edge(u-1, v-1, weight);
    }

    MST mst;

    try {
        std::cout << mst(G) << std::endl;
    } catch(const char* err_msg) {
        std::cout << err_msg;
    }

    return 0;
}



int MST::operator() (const Graph &G) {

    setup(G);

    while(not heap.empty()) {
        auto [vertex, weight] = heap.top();
        heap.pop();

        if (not visited[vertex]) {
            for (const auto &arc : G.adjacent(vertex)) {
                heap.push(arc);
            }
            total_weight += weight;
            visited[vertex] = true;            
        }
    }

    if (not all_connected()) { throw "Oops! I did it again\n"; }

    return total_weight;
}

void MST::setup(const Graph &G) {
    total_weight = 0;
    visited.clear();
    visited.resize(G.size(), false);
    heap.push(Arc{0,0});
}

bool MST::all_connected() {
    for (bool t : visited) {
        if (not t) {
            return false;
        }
    }
    return true;
}



void Graph::add_arc(int from, int to, int weight) {
    adjacency_list[from].push_back(Arc({to, weight}));
}
void Graph::add_edge(int u, int v, int weight) {
    add_arc(u, v, weight);
    add_arc(v, u, weight);
}

size_t Graph::size() const {
    return vertices.size();
}
const std::list<int>& Graph::get_vertices() const {
    return vertices;
}
const std::list<Arc>& Graph::adjacent(int v) const {
    return adjacency_list[v];
}