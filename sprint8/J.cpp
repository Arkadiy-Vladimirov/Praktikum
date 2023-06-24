#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <list>
#include <queue>

struct Node {
    std::list<std::string> word_list;
    std::unordered_map<char, Node*> children;

    Node* get_child(char c) {
        if (children.find(c) == children.end()) {
            children[c] = new(Node);
        }
        return children[c];
    }

    bool has_child(char c) {
        return (children.find(c) != children.end()); 
    }
};

struct SERP {
    std::multiset<std::string> word_list;
    void gather_words(Node* root);
};

class Trie {
    Node* root;
public:
    Trie() {root = new(Node);};
    ~Trie();
    void add(const std::string &word);
    SERP find(const std::string &request);
};



int main() {
    int n, m;
    std::string word, request;

    Trie trie;

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> word;
        trie.add(word);
    }

    std::cin >> m; 
    std::cin.ignore();

    for (int i = 0; i < m; ++i) {
        std::getline(std::cin, request);

        auto response = trie.find(request);
        for (const auto &word : response.word_list) {
            std::cout << word << std::endl;
        }
    }

    return 0;
}



Trie::~Trie() {
    std::queue<Node*> delete_queue;
    delete_queue.push(root);

    while (delete_queue.size() != 0) {
        Node* ptr = delete_queue.front(); delete_queue.pop();
        for (const auto &[key, child_ptr] : ptr->children) {
            delete_queue.push(child_ptr);
        }
        delete(ptr);
    }
}

void Trie::add(const std::string &word) {
    Node* node_ptr = root;
    for (char c : word) {
        if (std::isupper(c)) {
            node_ptr = node_ptr->get_child(c);
        }
    }
    node_ptr->word_list.push_back(word);
}

SERP Trie::find(const std::string &request) {
    SERP serp;

    Node* node_ptr = root;
    for (char c : request) {
        if (node_ptr->has_child(c)) {
            node_ptr = node_ptr->children[c];
        } else {
            return serp;
        }
    }

    serp.gather_words(node_ptr);
    return serp;
}

void SERP::gather_words(Node* root) {
    std::queue<Node*> gather_list;
    gather_list.push(root);

    while (gather_list.size() != 0) {
        Node* node_ptr = gather_list.front(); 
                         gather_list.pop();

        for (const auto &word : node_ptr->word_list) {
            word_list.insert(word);
        }
        for (const auto &[key, child_ptr] : node_ptr->children) {
            gather_list.push(child_ptr);
        }
    }
    
}