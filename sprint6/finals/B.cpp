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
#include <unordered_map>
#include <list>
#include <map>
#include <stack>

template <class V>
class Vertex;

//__________________________Graph_class_________________________________________
template <class V>
class Graph { 
    // Directed Graph class implemented on adjacency list
    typedef Vertex<V> Vert;

    std::list<Vert> vertices;
    std::unordered_map<V, std::list<Vert>> adjacency_list;
    std::unordered_map<V, std::list<Vert>> reachibility_list;

public:
    Graph(size_t n = 0) { 
        for (size_t i = 0; i < n; ++i) {
            vertices.push_back(Vert(V(i), *this));
        }
    }

    void add_arc(const V &from, const V &to) {
        adjacency_list[from].push_back(Vert(to, *this));
    }

    size_t size() const {
        return vertices.size(); 
    }

    std::list<Vert>& get_vertices() {
        return vertices;
    }

    std::list<Vert>& get_adjacent(const V &from) {
        return adjacency_list[from];
    }

    std::list<Vert>& get_reachable(const V &from) {
        return reachibility_list[from];
    }
};
//______________________________________________________________________________


//_______________________Vertex_class___________________________________________
template <class V>
class Vertex {
        V name;
        Graph<V> &G;
    public: 
        Vertex(V v, Graph<V> &G) : name(v), G(G) {};

        operator V() const {return name;};

        const Vertex<V>& operator= (const Vertex<V> &other) {
            name = other.name; G = other.G; return *this;
        }

        V get_name() const {
            return name;
        }
        
        friend std::ostream& operator << (std::ostream &out, const Vertex &v) {
            return out << v.name;
        }

        friend std::list<Vertex>& adj(Vertex &v) {
            return v.G.get_adjacent(v.name);
        }

        friend std::list<Vertex>& reach(Vertex &v) {
            return v.G.get_reachable(v.name);
        }
};

//______________________________________________________________________________


//______________________________DFS_class_______________________________________
template <class V>
class DFS {
    typedef enum {NEVER, ONCE, TWICE} State;

    std::unordered_map<V, State> visited;
    std::unordered_map<V, Vertex<V>> prev;
public: 
    DFS() {};

    void operator() (Graph<V> &G);
    void traverse (Vertex<V> &v);
};
//______________________________________________________________________________


//_______________________________MAIN___________________________________________
int main() {
    int n;
    std::cin >> n;

    Graph<int> R(n), B(n);

    std::map<char, Graph<int>*> get_graph { {'R', &R}, {'B', &B} };
    char edge_class; // R or B

    for (int i = 0; i < (n - 1); ++i) {
        for (int j = (i + 1); j < n; ++j) {
            std::cin >> edge_class;
            get_graph[edge_class]->add_arc(i, j);
        }
    }

    std::map<bool, std::string> cli_response {{false, "NO\n"}, {true, "YES\n"}};
    //std::cout << cli_response[is_optimal(R, B)];

    //test print

    DFS<int> dfs;

    dfs(R);
    
    /*
    for (auto v : R.get_vertices()) {
        for (auto u : adj(v)) {
            std::cout << u << " ";
        }
        std::cout << std::endl;
    }
    */

    return 0;
}
//______________________________________________________________________________


//________________________DFS_implementation____________________________________
template <class V>
void DFS<V>::operator() (Graph<V> &G) {

    for (auto &v : G.get_vertices()) {
        visited[v] = NEVER;
    }

    for (auto &v : G.get_vertices()) {
        traverse(v);
    }
    
    visited.clear();
    prev.clear();
    return;
}

template <class V>
void DFS<V>::traverse(Vertex<V> &v) {
    
    std::stack<Vertex<V>> stack;
    stack.push(v);
    
    while (not stack.empty()) {
        auto v = stack.top();
        stack.pop();

        prev[v.get_name()];
        
        if (visited[v] == ONCE) {
            reach(prev[v]).push_back(v);
            reach(prev[v]).insert(reach(prev[v]).end(), reach(v).begin(), reach(v).end());
            visited[v] = TWICE;
        }
        
        if (visited[v] == NEVER) {
            for (auto& u : adj(v)) {
                prev[u] = v;
                stack.push(u);
            }
            visited[v] = ONCE;
        }
    }
    
    return;
}
//______________________________________________________________________________