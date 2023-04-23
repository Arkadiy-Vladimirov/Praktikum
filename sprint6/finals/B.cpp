// accepted parcel ID: 86308288
//
//
// _Problem_
//
// An oriented graph G = (V,E) is given. The vertices are sorted in topological 
// order, each vertice is connected with all the subsequent, i.e v_i whith 
// v_{i+1}, ..., v_{n-1} (i = 0, ... n-1; |V| = n).
//
// Edges in the graph are divided into two classes: E = E_b v E_r, giving two
// subgraphs of the graph G : B = (V,E_b), R = (V, E_r).
//
// def. Say that a vertice v is G-reachable from a vertice u is u->v in the 
// sense of graph G. 
// 
// def. Say that a partition R,B of a given graph G is optimal if there are no
// such a pair of vertices (u,v) that v is both R-reachable and B-reachable.
//
// The goal is to detect if a partition provided is optimal.
//
//
// _Solution_
//
// To get the answer we have to look through all the pairs of vertices and 
// check for R and B reachibility. Or, equivalently, for each vertice v we may 
// look at set of all R reachable and B reachable vertices. A partition is not
// optimal iff there exists such v that the intersection of such sets is not 
// empty.
//
// To obtain reachability sets DFS is used. By definition, when returned from 
// another vertex traversal the DFS has passed through all the reachable 
// vertices. Explicitely DFS is done as follows:
//
// - All the vertices start whith lists of reachibility preset as adjacency 
// lists that would be updated during the algorithm (i.e. done in-place).
// - When DFS pushes another vertex into the stack, previous vertx is stored.
// - When DFS returns from another vertex, it updates the reachibility list 
// of the previous, adding what is reached from the finished vertex.
//
// By definition by the end of DFS all reachibility lists would be up-to-date.
//
// In our particular problem, as the graph is almost full (full in the sense of 
// oriented, topologically sorted graph), and the partition is tight, detecting 
// a new reachable vertex (i.e. not defined in the adjacecy list already) in 
// sense of, say, R, automatically implies that there is a reachibility 
// coincidence in R and B and the answer is found - (R,B) is not optimal. 
// Therefore, the breakpoint of the program is set as follows - the DFS founds 
// a new reachibility list entry.
//
// The complexity of the program is all defined by the DFS and thus is O(n^2) 
// both in time and memory.
//


#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>

class Graph {
    std::vector<std::vector<char>> adj;

public:
    Graph(int n);
    size_t size() const;
    void print();

    friend class DFS;
};

class DFS {
    typedef enum {NOT_DETECTED, IN_PROCESS, FINISHED} State;

    Graph &G;
    std::vector<State> state;
    std::vector<int> prev;

private:
    void traverse(int v, char color);
    void update_adj(int v, char color);
    void reset();

public:
    DFS(Graph &G) : G(G), state(G.size(), NOT_DETECTED), prev(G.size(), -1) {};

    void operator() (char color);
};


int main() {
    int n;
    std::cin >> n;

    Graph G(n);

    DFS dfs(G);

    try {
        dfs('R');
        dfs('B');
        std::cout << "YES\n";
    } catch (const char* err_msg) {
        std::cout << "NO\n";
    }

    return 0;
}


//________________________________DFS_methods___________________________________
void DFS::operator() (char color) {
    for (int v = 0; v < G.size(); ++v) {
        traverse(v, color);
    }

    reset();
}

void DFS::traverse(int v, char color) {
    std::stack<int> stack;
    stack.push(v);

    while (not stack.empty()) {
        v = stack.top();
        if (state[v] == FINISHED) {
            stack.pop();
        }
        if (state[v] == IN_PROCESS) {
            state[v] = FINISHED;
            if (prev[v] != -1) {
                update_adj(v, color);
            }
            stack.pop();
        }
        if (state[v] == NOT_DETECTED) {
            state[v] = IN_PROCESS;
            for (int i = (G.size()-v-2); i >= 0; --i) {
                if (G.adj[v][i] == color) {
                    prev[v+1+i] = v;
                    stack.push(v+1+i);
                }
            }
        }
    }    
}

void DFS::update_adj(int v, char color) {
    int u = prev[v];
    for (int i = 0; i < (G.size()-v-1); ++i) {
        // check if we found a new reachable vertex
        if ((G.adj[v][i] == color) && (G.adj[u][v-u+i] != color)) {
            throw "coincidence found";
        }
    }
}

void DFS::reset() {
    for (int i = 0; i < G.size(); ++i) {
        state[i] = NOT_DETECTED;
        prev[i] = -1;
    }
}


//________________________________Graph_methods_________________________________
Graph::Graph(int n) : adj(n) {
    char color;
    for (int i = 0; i < (n - 1); ++i) {
        adj[i].resize(n-i-1);
        for (int j = 0; j < (n-i-1); ++j) {
            std::cin >> color;
            adj[i][j] = color;
        }
    }
}

void Graph::print() {
    for (const auto& list : adj) {
        for (char col : list) {
            std::cout << col;
        }
        std::cout << '\n';
    }
}


size_t Graph::size() const {
    return adj.size();
}

