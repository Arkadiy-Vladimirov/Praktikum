// accepted parcel ID: 85410675
//
// HeapSort
//
// We are provided with a range of comparable elements (contestants in our case)
// of size N. The sorting is done as follows:
//      - fill a heap with elements of the range;
//      - refill the range retrieving elements from the heap one by one.
//
// A heap object is an object of the class Heap, a container class that 
// maintains heap structure, i.e. a binary tree such that each node has the key 
// that is greater or equal to such of the children. The class supports two 
// interface methods insert() and pop() that insert an element to the heap and 
// pops the top element correspondingly. In order to save the heap structure:
//      - each time an element is inserted the sift up* is called; (log N)
//      - each time the element is popped the sift down* is called. (log N)
//
// Retrieving elements from a heap one be one would provide us with a 
// sorted range and the suggested sorting algorithm would take
//      - O(NlogN) time complexity (NlogN to fill the heap + NlogN to drain it);
//      - O(N) space complexity to store the heap.
//
// *More about the heap and heapsort at
//                      - https://en.wikipedia.org/wiki/Heap_(data_structure)
//                      - https://en.wikipedia.org/wiki/Heapsort
//

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>


struct Contestant {
    std::string login;
    int score;
    int penalty;
};

struct ContestantComp {
    bool operator() (const Contestant& lhs, const Contestant& rhs);
};

template<>
struct std::less<Contestant> {
    bool operator() (const Contestant& lhs, const Contestant& rhs) {
        return ContestantComp()(lhs, rhs);}
};


template<class T, class Compare = std::less<T>>
class MaxHeap {
    std::vector<T> arr;
    Compare comp;

    void siftDown(size_t idx);
    void siftUp(size_t idx);

public:
    MaxHeap() : arr(1) {}; 
    T pop();
    void insert(const T& x);
    size_t size();
};


template<class T, class Compare = std::less<T>>
MaxHeap<T, Compare> make_max_heap(const T&);

template<class RandomIt>
void heapSort(RandomIt first, RandomIt last);

template<class T, class Compare>
MaxHeap<T, Compare> make_max_heap(const T&, Compare comp);

template<class RandomIt, class Compare>
void heapSort(RandomIt first, RandomIt last, Compare comp);


std::istream& operator >> (std::istream &in , Contestant& c);
std::ostream& operator << (std::ostream &out, const Contestant& c);

template<class T>
std::istream& operator >> (std::istream &in , std::vector<T>& arr);
template<class T>
std::ostream& operator << (std::ostream &out, const std::vector<T>& arr);


//_________________________________MAIN_________________________________________
int main() {
    int n;
    std::cin >> n;
    std::vector<Contestant> contestants(n);
    std::cin >> contestants;

    heapSort(contestants.begin(), contestants.end());
    //heapSort(contestants.begin(), contestants.end(), ContestantComp());

    std::cout << contestants;
    return 0;
}
//______________________________________________________________________________


bool ContestantComp::operator() (const Contestant& lhs, const Contestant& rhs) {
    if (lhs.score < rhs.score)
        return true;
    if (lhs.score > rhs.score)
        return false;
    
    if (lhs.penalty > rhs.penalty)
        return true;
    if (lhs.penalty < rhs.penalty)
        return false;

    if (lhs.login > rhs.login)
        return true;
    if (lhs.login < rhs.login)
        return false;

    return false;
}


//______________________make_sort_function_templates____________________________
template<class T, class Compare = std::less<T>>
MaxHeap<T, Compare> make_max_heap(const T&) {
    MaxHeap<T, Compare> max_heap;
    return max_heap;
}

template<class RandomIt>
void heapSort(RandomIt first, RandomIt last) {
    if (first == last) {
        return;
    }

    auto heap = make_max_heap(*first);

    for (auto p = first; p != last; ++p) {
        heap.insert(*p);
    }
    for (auto p = first; p != last; ++p) {
        *p = heap.pop();
    }
    return;
}

template<class T, class Compare>
MaxHeap<T, Compare> make_max_heap(const T&, Compare comp) {
    MaxHeap<T, Compare> max_heap;
    return max_heap;
}

template<class RandomIt, class Compare>
void heapSort(RandomIt first, RandomIt last, Compare comp) {
    if (first == last) {
        return;
    }

    auto heap = make_max_heap(*first, comp);

    for (auto p = first; p != last; ++p) {
        heap.insert(*p);
    }
    for (auto p = first; p != last; ++p) {
        *p = heap.pop();
    }
    return;
}
//______________________________________________________________________________


//_____________________________Heap_Methods_____________________________________
template<class T, class Compare>
T MaxHeap<T, Compare>::pop() {
    if (size() == 0) {
        throw "error: pop call for an empty heap";
    }
    auto top_value = arr[1];
    std::swap(arr[1], arr[size()]);
    arr.pop_back();
    
    siftDown(1);
    return top_value;
}

template<class T, class Compare>
void MaxHeap<T, Compare>::insert(const T &x) {
    arr.push_back(x);
    siftUp(size());
    return;
}

template<class T, class Compare>
void MaxHeap<T, Compare>::siftDown(size_t idx) {
    if ((2*idx + 1) <= size()) { // two children
        auto max_it = std::max_element(arr.begin() + 2*idx, arr.begin() + 2*idx + 2, comp);
        size_t max_idx = std::distance(arr.begin(), max_it);
        if (comp(arr[idx], arr[max_idx])) {
            std::swap(arr[idx], arr[max_idx]);
            siftDown(max_idx);
        }
    }

    if (2*idx == size()) {       // one child
        if (comp(arr[idx], arr[2*idx])) {
            std::swap(arr[idx], arr[2*idx]);
        }
    }

    //no children or no changes
    return;
}

template<class T, class Compare>
void MaxHeap<T, Compare>::siftUp(size_t idx) {
    if (idx == 1) {
        return;
    }
    if (comp(arr[idx/2], arr[idx])) {
        std::swap(arr[idx/2], arr[idx]);
        siftUp(idx/2);
    }
    return;
}

template<class T, class Compare>
size_t MaxHeap<T, Compare>::size() {
    return arr.size() - 1;
}
//______________________________________________________________________________


//____________________________IO_operators______________________________________
std::istream& operator >> (std::istream &in , Contestant& c) {
    in >> c.login >> c.score >> c.penalty;
    return in;
}
std::ostream& operator << (std::ostream &out, const Contestant& c) {
    out << c.login;
    return out;
}

template<class T>
std::istream& operator >> (std::istream &in , std::vector<T>& arr) {
    for (auto &x : arr) {
        in >> x;
    }
    return in;
}
template<class T>
std::ostream& operator << (std::ostream &out, const std::vector<T>& arr) {
    for (const auto &x : arr) {
        out << x << std::endl;
    }
    return out;
}
//______________________________________________________________________________