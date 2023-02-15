// accepted parcel ID: 82197509
//
// Standard in-place quicksort realisation
//
// The program describes in-place sort of a range following Hoare's algorithm.
//
// The algorithm is performed recursively. At each step a pivot element is 
// chosen and the range is being divided into two parts: one contains all 
// elements less or equal to the pivot, and another - those that are strictly 
// greater. The parts are sorted again than, and are merged by simple 
// concatenation which, obviously, would save the correct order.
//
// In order of being in-place this particular algorithm divides the range by the
// following procedure: two iterators traverse through the range from both ends.
// The left iterator proceeds to the right till it reaches an element greater 
// than the pivot. The right iterator goes in the opposite direction till it 
// stops at an element that is less or equal to the pivot. When both iterators
// are stuck the pair of elements they point at is swapped and the procedure 
// proceeds. The traverse will end when iterators jump over each other. At this
// point everything to the left of the left iterator is less or equal to the 
// pivot, and everything right to the right iterator is greater. Now the range 
// is splitted and the algorihm is ready to be repeated over the left and
// the right subranges separately.
//
// Couple of pecularities worth to mention. The pivot may be chosen randomly, 
// still in this particular realisation the middle element is taken as one.
// Unfortunately, this may result into an infinite loop: in case of middle 
// element is the maximum, the left subrange (elements less or equal) would 
// coincide with the whole range and the algorithm would constantly repeat over 
// it. In order to avoid this, after the traverse the pivot is placed in 
// beetween of the left and the right subranges and is taken out of further 
// sorting.
// 
// The recursion depth of the Hoare algorithm is n in the worst case and log n 
// on average. At each level of the recursion O(n) operations are performed 
// (range traverse) and O(1) of memory space is used. Thus, the time {space} 
// complextiy of the algorithm is O(n^2) {O(n)} in the worst case, and O(nlog n)
// {O(log n)} on average.
//
// For additional info see e.g.
//      https://contest.yandex.ru/contest/23815/problems/B/ (rus)
//      https://en.wikipedia.org/wiki/Quicksort
//
// P.S. In this task a special type of data is sorted - records. It is described
// as Record structure and has its own relational operator. As having one is the
// only significant requirement of the sorting algorithm, it is being executed 
// normally and without any special adjustments.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Record {
    std::string name;
    int score;
    int penalty;
};

struct RecordComparator { //defines which record goes first on the list
    bool operator() (const Record &lhs, const Record &rhd) const;
};

int readNum();
Record readRecord();
std::vector<Record> readTable(int n);
void printNames(const std::vector<Record> &table);

template <class RandomIt, class Compare>
void qsort(RandomIt first, RandomIt last, Compare comp);



int main() {
    int n = readNum();
    auto table = readTable(n);
    qsort(table.begin(), table.end(), RecordComparator());
    printNames(table);
    return 0;
}



template <class RandomIt, class Compare>
void qsort(RandomIt first, RandomIt last, Compare comp) {
    if (std::distance(first, last) <= 1) {
        return;
    }

    auto pivot = (first + (last-first)/2); //or any other pivot choice strategy
    auto left = first;
    auto right = last - 1;

    auto pivot_val = *pivot;
    while (std::distance(left, right) != -1) {
        if (!comp(pivot_val, *left) && !comp(*left, pivot_val)){ //*left == pivot_val 
            pivot = left; //save pivot location
            left++;
        } else if (comp(*left,  pivot_val)) {                    //*left  < pivot_val
            left++;
        } else if (comp(pivot_val, *right)) {                    //*right > pivot_val
            right--;
        } else {
            std::swap(*left, *right);
        }
    }

    //[first, last) = [first, left-1) + [pivot] + (right, last)
    std::swap(*(left-1), *pivot);
    qsort(first    , left-1, comp);
    qsort(right + 1, last  , comp);
    return;
}


bool RecordComparator::operator() (const Record &lhs, const Record &rhs) const {
    if (lhs.score > rhs.score)
        return true;
    if (lhs.score < rhs.score)
        return false;

    if (lhs.penalty < rhs.penalty)
        return true;
    if (lhs.penalty > rhs.penalty)
        return false;

    if (lhs.name < rhs.name)
        return true;
    if (lhs.name > rhs.name)
        return false;

    return false;        
}


// read/write functions

int readNum() {
    int x;
    std::cin >> x;
    return x;
}

Record readRecord() {
    Record rec;
    std::cin >> rec.name >> rec.score >> rec.penalty;
    return rec;
}

std::vector<Record> readTable(int n) {
    std::vector<Record> table(n);
    for (auto &record : table) {
        record = readRecord();
    }
    return table;
}

void printNames(const std::vector<Record> &table) {
    for (const auto &record : table) {
        std::cout << record.name << std::endl;
    }
    return;
}