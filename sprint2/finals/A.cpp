// accepted parcel ID: 81606610
//
// Standard realisation of dequeue based on a circular buffer.
//
// The dequeue is incapsulated in a Dequeue class.
// The class stores the dequeue itself in a buffer of fixed capacity and 
// adresses through it via (mod capacity) arithmetic. 
// The class maintains the invariant of the head always pointing at the first 
// element and the tail pointing behind the last. (Empty dequeue is a corner 
// case and is handled separately)
// As the adresses of the first and the last elements are always at disposal, 
// all standard dequeue operations are of O(1) complexity.
// Under the assumption of correct operation with deque of size n, buffer 
// capacity has to be not less than n. Hence, the space complexity is O(n).
//
//  buffer addressing mode outline:
//
//  | unused |     | 1st element | | 2nd element |       | last element | | unused |     |   unused   |
//  ---------- ... --------------  ---------------  ...  ---------------- ---------- ... -------------
//  |    0   |     |    head    |  |   head+1    |       |    tail-1    | |  tail  |     | capacity-1 |.
//        
// For more info see e.g. https://en.wikipedia.org/wiki/Circular_buffer

#include <iostream>
#include <vector>
#include <string>

class Dequeue {
    std::vector <int> buff;
    int size;
    int capacity;
    int head;
    int tail;

public:
    Dequeue(int capacity) : buff(std::vector <int> (capacity)), size(0), capacity(capacity), head(0), tail(0) {};

    void push_back(int value);
    void push_front(int value);
    int pop_back();
    int pop_front();
};


int main() {
    int n, m;
    std::string command;
    int value;
    std::cin >> n >> m;
    Dequeue deq(m);

    for (int i = 0; i < n; ++i) {
        try {
            std::cin >> command;

                   if (command == "pop_front") {
                std::cout << deq.pop_front() << std::endl;
            } else if (command == "pop_back") {
                std::cout << deq.pop_back() << std::endl;
            } else if (command == "push_front") {
                std::cin >> value;
                deq.push_front(value);
            } else if (command == "push_back") {
                std::cin >> value;
                deq.push_back(value);
            }
        } catch(const std::string &error_msg) {
            std::cout << error_msg << std::endl;
        }
    }

    return 0;
}



void Dequeue::push_back(int value) {
    if (size == capacity) {
        std::string error_msg = "error";
        throw error_msg;
    } else {
        buff[tail] = value;
        tail = (tail + 1) % capacity;
        size++;
    }
    return;
}

void Dequeue::push_front(int value) {
    if (size == capacity) {
        std::string error_msg = "error";
        throw error_msg;
    } else {
        head = (head + capacity - 1) % capacity;
        buff[head] = value;
        size++;
    }
    return;
}

int Dequeue::pop_back() {
    if (size == 0) {
        std::string error_msg = "error";
        throw error_msg;
    } else {
        tail = (tail + capacity - 1) % capacity;
        size--;
        return buff[tail];
    }
    return 0;
}

int Dequeue::pop_front() {
    if (size == 0) {
        std::string error_msg = "error";
        throw error_msg;
    } else {
        int output = buff[head];
        head = (head + 1) % capacity;
        size--;
        return output;
    }
    return 0;
}