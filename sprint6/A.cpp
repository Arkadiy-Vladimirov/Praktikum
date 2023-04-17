#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <set>

template<class V>
class EdgeList {
    int vert_count, edge_count;
    std::list<std::pair<V,V>> list;

public:
    EdgeList(std::size_t vert_count, std::size_t edge_count) : 
            vert_count(vert_count), edge_count(edge_count), list(edge_count) {};
    auto  begin()       {return list.begin(); };
    auto cbegin() const {return list.cbegin();};
    auto  end()         {return list.end();   };
    auto cend()   const {return list.cend();  };

    int get_vert_count() const {return vert_count;};
    int get_edge_count() const {return edge_count;};    
};

template<class V>
std::istream& operator >> (std::istream &in, EdgeList<V> &edge_list);

template<class V>
class AdjacencyList {
    int vert_count, edge_count;
    std::map<V,std::set<V>> list;

public: 
    AdjacencyList(const EdgeList<V> &edge_list);
    auto  begin()       {return list.begin(); };
    auto cbegin() const {return list.cbegin();};
    auto  end()         {return list.end();   };
    auto cend()   const {return list.cend();  };

    int get_vert_count() const {return vert_count;};
    std::set<V>& operator[] (const V &vert) {return list[vert];};
};

template<class V>
std::ostream& operator << (std::ostream &out, const AdjacencyList<V> &adj_list);

std::ostream& operator << (std::ostream &out, AdjacencyList<int> &adj_list);

int main() {    
    int n, m;
    std::cin >> n >> m;

    EdgeList<int> edge_list(n, m);
    std::cin >> edge_list;

    AdjacencyList<int> adj_list(edge_list);
    std::cout << adj_list;

    return 0;
}

template<class V>
std::istream& operator >> (std::istream &in, EdgeList<V> &edge_list) {
    for (auto &pair : edge_list) {
        in >> pair.first >> pair.second;
    }
    return in;
}

template<class V>
AdjacencyList<V>::AdjacencyList(const EdgeList<V> &edge_list) {
    vert_count = edge_list.get_vert_count();
    edge_count = edge_list.get_edge_count();
    for (auto iter = edge_list.cbegin(); iter != edge_list.cend(); ++iter) {
        list[iter->first].insert(iter->second);
    }
}

template<class V>
std::ostream& operator << (std::ostream &out, const AdjacencyList<V> &adj_list) {
    for (auto iter = adj_list.cbegin(); iter != adj_list.cend(); ++iter) {
        const auto &set = iter->second; 
        out << set.size() << " ";
        for (const auto &x : set) {
            out << x << " ";
        }
        out << std::endl;
    }
    return out;
}

std::ostream& operator << (std::ostream &out, AdjacencyList<int> &adj_list) {
    for (int idx = 1; idx <= adj_list.get_vert_count(); ++idx) {
        out << adj_list[idx].size() << " ";
        for (int x : adj_list[idx]) {
            out << x << " ";
        }
        out << std::endl;
    }
    return out;
}