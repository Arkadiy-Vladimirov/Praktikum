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
// The idea of the algorithm is to iterate through the vertices in reverse 
// order and for each vertice v_i compare R and B reachibility of all the 
// others from it.
//
// def. We denote the set of all reachable from x vertices as reachable(x).
//
// As vertices are sorted topologically, we know that reachable(v_i) may be 
// derived from higher reachables in O(n). Hence, by iterating from 
// v_{n-1} to v_0 we may construct reachable sets one by one in O(n) each, 
// resulting in O(n^2).
//
// We need to store reachables that are of O(n^2) size.
// To compare obtained reachables we need O(n^2) time.
//
// Therefore we get:
// O(n^2) time complexity
// O(n^2) additional memory consumption
//
// The algorithm itself is described below.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <map>

template <class V>
class DiGraph { 
    // Directed Graph class implemented on adjacency list
    size_t vertices_count;
    std::unordered_map<V, std::list<V>> adjacency_list;

public:
    DiGraph(size_t n) : vertices_count(n) {};

    void add_arc(const V &from, const V &to);

    size_t get_vertices_count();
    std::list<V>& get_adjacent(const V &from);
};


bool is_optimal(DiGraph<int> &R, DiGraph<int> &B);
void update_reachable(int u, std::vector<bool> &reachable , DiGraph<int> &G);
bool zero_overlay(const std::vector<bool> &lhs, const std::vector<bool> &rhs);


int main() {
    int n;
    std::cin >> n;

    DiGraph<int> R(n), B(n);

    std::map<char, DiGraph<int>*> get_graph { {'R', &R}, {'B', &B} };
    char edge_class; // R or B

    for (int i = 0; i < (n - 1); ++i) {
        for (int j = (i + 1); j < n; ++j) {
            std::cin >> edge_class;
            get_graph[edge_class]->add_arc(i, j);
        }
    }

    std::map<bool, std::string> cli_response {{false, "NO\n"}, {true, "YES\n"}};
    std::cout << cli_response[is_optimal(R, B)];

    return 0;
}


bool is_optimal(DiGraph<int> &R, DiGraph<int> &B) {
    size_t n = R.get_vertices_count();
    std::map<char, std::vector<bool>> reachable {
                                        {'R', std::vector<bool>(n, false)}, 
                                        {'B', std::vector<bool>(n, false)}
                                    };

    for (int u = (n-2); u >= 0; --u) {

        update_reachable(u, reachable['R'], R);
        update_reachable(u, reachable['B'], B);

        if (not zero_overlay(reachable['R'], reachable['B'])) {
            return false;
        }
    }

    return true;
}

void update_reachable(int u, std::vector<bool> &reachable , DiGraph<int> &G) {
    for (int v : G.get_adjacent(u)) {
        
    }
    return;
}   

bool zero_overlay(const std::vector<bool> &lhs, const std::vector<bool> &rhs) {
    for (int i = 0; i < lhs.size(); ++i) {
        if ((lhs[i] == true) && (rhs[i] == true)) {
            return false;
        }
    }
    return true;
}

template <class V>
void DiGraph<V>::add_arc(const V &from, const V& to) {
    adjacency_list[from].push_back(to);
    return;
}

template <class V>
std::list<V>& DiGraph<V>::get_adjacent(const V &from) {
    return adjacency_list[from];
}

template <class V>
size_t DiGraph<V>::get_vertices_count() {
    return vertices_count;
}