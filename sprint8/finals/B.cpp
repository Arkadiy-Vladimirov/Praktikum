#include <fstream>
#include <string>
#include <unordered_map>
#include <list>
#include <queue>


struct Node {
    bool is_terminal = false;
    std::unordered_map<char, Node*> children;

    bool has_child(char c);
    Node* get_child(char c);
};

class Trie {
    Node* root;
public:
    Trie() : root(new(Node)) {};
    ~Trie();
    void add_word(const std::string &word);

    // fills list of end iteratrors of prefixes str[0, end) that are words
    void find_prefixes(std::string::const_iterator begin, 
                       std::string::const_iterator end,
                       std::list<std::string::const_iterator> &end_list);
    // returns true if str[begin, end) is a concat of words
    bool is_sentence(std::string::const_iterator begin, 
                     std::string::const_iterator end  );
};

int main() {
    std::ifstream fin;  fin.open ("input.txt" );
    std::ofstream fout; fout.open("output.txt");

    std::string str, word;
    fin >> str;

    int n;
    fin >> n;

    Trie trie;
    for (int i = 0; i < n; ++i) {
        fin >> word;
        trie.add_word(word);
    }

    if (trie.is_sentence(str.begin(), str.end())) {
        fout << "YES\n";
    } else {
        fout << "NO\n";
    }

    fin.close();
    fout.close();
    return 0;
}



bool Node::has_child(char c) {
    return children.find(c) != children.end();
}
    
Node* Node::get_child(char c) {
    if (children.find(c) == children.end()) {
        children[c] = new(Node);
    }
    return children[c];
}



Trie::~Trie() {
    std::queue<Node*> del_queue;
    del_queue.push(root);

    while (del_queue.size() != 0) {
        Node* ptr = del_queue.front(); del_queue.pop();
        for (const auto &[key, child_ptr] : ptr->children) {
            del_queue.push(child_ptr);
        }
        delete(ptr);
    }
}

void Trie::add_word(const std::string &word) {
    Node* node_ptr = root;
    for (char c : word) {
        node_ptr = node_ptr->get_child(c);
    }
    node_ptr->is_terminal = true;
}

void Trie::find_prefixes(std::string::const_iterator begin, 
                         std::string::const_iterator end  ,
                         std::list<std::string::const_iterator> &end_list) {

    Node* node_ptr = root;

    for (auto it = begin; it != end; ++it) {

        if (node_ptr->has_child(*it)) {

            node_ptr = node_ptr->get_child(*it);

            if (node_ptr->is_terminal) {
                end_list.push_back(it + 1);
            }
        } else {
            break;
        }
    }
}

bool Trie::is_sentence(std::string::const_iterator first,
                       std::string::const_iterator last ) {

    if (first == last) {
        return true;
    }

    std::list<std::string::const_iterator> prefix_ends;
    find_prefixes(first, last, prefix_ends);
    bool ans = false;

    for (auto end : prefix_ends) {

        ans = ans || is_sentence(end, last);
        if (ans == true) {
            return true;
        }
    }

    return false;
}