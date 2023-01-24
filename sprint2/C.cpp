#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

#ifndef REMOTE_JUDGE
#include <cassert>
#include <string>

struct Node {  
    std::string value;  
    Node* next;  
    Node(const std::string &value, Node* next) : value(value), next(next) {
        
    }
};
#endif


Node* solution(Node* head, int idx) {
    if (idx == 0) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
        return head;
    }

    Node* prev_ptr = head;
    while (idx != 1) {
        prev_ptr = prev_ptr->next;
        idx--;
    }

    Node* cur_ptr = prev_ptr->next;
    prev_ptr->next = cur_ptr->next;
    free(cur_ptr);
    return head;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node3("node3", nullptr);
    Node node2("node2", &node3);
    Node node1("node1", &node2);
    Node node0("node0", &node1);
    Node* new_head = solution(&node0, 1);
    assert(new_head == &node0);
    assert(new_head->next == &node2);
    assert(new_head->next->next == &node3);
    assert(new_head->next->next->next == nullptr);
    // result is : node0 -> node2 -> node3
}

int main() {
    test();
}
#endif