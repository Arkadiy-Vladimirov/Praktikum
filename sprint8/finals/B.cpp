// accepted parcel ID: 88612726
//
// Problem:
//  Given a text of size m and a dictionary of n words of size no more than l 
// each, define if the text is a sentence, i.e. may be constructred with these 
// words. The text and the words consist of symbols of fixed alphabet of size s.
// ( m >> n, l >> s) 
//
// Solution:
//  We would look at each suffix of the text - text[pos, end) from the smallest
// one text[end-1, end) to the whole text - text[0, end), and evaluate whether 
// it is a sentence. To do that we assume that an empty sentence is a sentence, 
// and observe that text[pos, end) is a sentence iff there exists a word, s.t.
//          text[pos, end) = word + text[pos + word.size(), end),
//          where text[pos + word.size(), end) is a sentence.                (1)
//
//  Hence, for each suffix we only need to look at any word that is a prefix of 
// it and check whether there is one that satisfies condition (1). In order to 
// make the search of words effective we would construct a trie out of the 
// dictionary in advance.
//
//  The trie would take O(l s^2) memory and it's construction would cost O(nl) 
// time. It would take only O(l) each time to find all prefix words. The 
// memoization array is_sentence would take O(m) memory. Given the prefix 
// search we would traverse through it in O(ml) time.
//
//  Memory: O(m + l*s^2) ~ O(m)
//  Time: O(ml)
// 

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
