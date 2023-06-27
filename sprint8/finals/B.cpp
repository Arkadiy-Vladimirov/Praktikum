#include <fstream>
#include <string>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>


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

    std::list<std::string::const_iterator> find_prefixes(
                                            std::string::const_iterator first, 
                                            std::string::const_iterator last );
};

int main() {
    std::ifstream fin;
    fin.open("input.txt");

    std::string str, word;
    fin >> str;

    int n;
    fin >> n;

    Trie trie;
    for (int i = 0; i < n; ++i) {
        fin >> word;
        trie.add_word(word);
    }
    fin.close();

    // is_sentence[pos] = true iff str[pos, end) is a sentence i.e. concat of words
    std::vector<bool> is_sentence(str.size() + 1, false);
    is_sentence[str.size()] = true;

    for (int pos = str.size() - 1; pos >= 0; --pos) {

        auto pref_ends = trie.find_prefixes(str.begin() + pos, str.end());

        for (auto end_it : pref_ends) {
            int count = std::distance(str.cbegin() + pos, end_it);
            is_sentence[pos] = is_sentence[pos] || is_sentence[pos + count];
        }
    }

    std::ofstream fout;
    fout.open("output.txt");

    if (is_sentence[0] == true) {
        fout << "YES\n";
    } else {
        fout << "NO\n";
    }
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

std::list<std::string::const_iterator> Trie::find_prefixes(
                                            std::string::const_iterator first, 
                                            std::string::const_iterator last ) {

    std::list<std::string::const_iterator> end_list;
    Node* node_ptr = root;

    for (auto it = first; it != last; ++it) {

        if (node_ptr->has_child(*it)) {

            node_ptr = node_ptr->get_child(*it);

            if (node_ptr->is_terminal) {
                end_list.push_back(it + 1);
            }

        } else {
            break;
        }
    }
    return end_list;
}
