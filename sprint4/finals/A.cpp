// accepted parcel ID: 83264610
//
// Model Search Engine realisation. 
// 
// The engine constructs searching index related to a given corpus as 
// a map : word -> collections of docs id with their relevance.
//
// To find the most relevant document the relevance_table is constructed i.e. 
// a map doc_id -> sentence relevance. To do that we go through all unique words
// in a sentence and sum up their relevances for each doc. The table is sorted 
// then, and top 5 results are given.
//
// Say we have n unique words in a corpus of m documents.
// The index contains a collection of documents with their relevance for each 
// unique word. Hence, to maintain the index O(nm) data has to be stored.
// To respond to a request with k unique words we would need O(km) operations to
// construct a relevance table of size O(m) and then sort it in O(mlog m) time.
// Therefore, time complexity of a request processing is O(km) + O(m log m), and
// O(nm) of addittional memory is used for the index.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>

typedef std::string Word;
typedef int ID;
typedef int Relevance;

int readNum();
void printArr(const std::vector<int> &arr);

class SearchEngine {
    std::unordered_map<Word, std::unordered_map<ID, Relevance>> index;

    void             readDocument  (const std::string &doc, int doc_id);
    std::vector<int> processRequest(const std::string &request);

    struct HigherOnList {
    bool operator() 
    (const std::pair<ID, Relevance> &l, const std::pair<ID, Relevance> &r) const;
    };

public:
    void readCorpus(int corpus_size);
    void runSession(int session_length);
};

int main() {
    SearchEngine search_engine;

    int n = readNum();
    search_engine.readCorpus(n);

    int m = readNum();
    search_engine.runSession(m);

    return 0;
}



//_________________SearchEngine_class_methods_implementation____________________

void SearchEngine::readCorpus(int corpus_size) {
    for (int doc_id = 1; doc_id <= corpus_size; ++doc_id) {
        std::string document;
        std::getline(std::cin, document);
        readDocument(document, doc_id);
    }   
    return;
}

void SearchEngine::runSession(int session_length) {
    for (int i = 0; i < session_length; ++i) {
        std::string request;
        std::getline(std::cin, request);
        auto se_results = processRequest(request);
        printArr(se_results);
    }
    return;
}

void SearchEngine::readDocument(const std::string &doc, int doc_id) {
    auto iss = std::istringstream(doc);
    std::string word;

    while (iss >> word) {
        if (index[word].find(doc_id) == index[word].end()) {
            index[word][doc_id] = 1;
        } else {
            index[word][doc_id]++;
        }
    }
    return;
}

std::vector<int> SearchEngine::processRequest(const std::string &request) {
    auto iss = std::istringstream(request);
    std::unordered_set<std::string> word_set;
    std::string word;
    while (iss >> word) {
        word_set.insert(word);
    }
    
    std::unordered_map<ID, Relevance> relevance_table;
    for (const auto &word : word_set) {
        for (const auto &[doc_id, relevance] : index[word]) {
            if (relevance_table.find(doc_id) == relevance_table.end()) {
                relevance_table[doc_id] = relevance;
            } else {
                relevance_table[doc_id] += relevance;
            }
        }
    }

    std::set<std::pair<ID, Relevance>, HigherOnList> ranked_list;
    for (const auto &pair : relevance_table) {
        ranked_list.insert(pair);
    }
    
    std::vector<ID> top5docs;
    auto last = std::next(ranked_list.begin(), std::min(5, (int)ranked_list.size()));
    for (auto p = ranked_list.begin(); p != last; ++p) {
        top5docs.push_back(p->first);
    } 

    return top5docs;
}


bool SearchEngine::HigherOnList::operator() 
(const std::pair<ID, Relevance> &l, const std::pair<ID, Relevance> &r) const {
    if (l.second > r.second) {
        return true;
    }
    if (l.second < r.second) {
        return false;
    }
    
    if (l.first < r.first) {
        return true;
    }
    if (l.first > r.first) {
        return false;
    }
    return false;
}
//______________________________________________________________________________


//_____________________________IO_functions_____________________________________

int readNum() {
    int x;
    std::cin >> x;
    std::cin.ignore();
    return x;
}

void printArr(const std::vector<int> &arr) {
    for (auto x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}
//______________________________________________________________________________