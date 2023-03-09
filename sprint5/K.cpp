#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  Node* left = nullptr;  
  Node* right = nullptr;
  Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

void print_range(Node* root, int l, int r) {
    if (root == nullptr) {
        return;
    }
    if (root->value < l) {
       print_range(root->right, l, r);
       return;
    }
    if ((l <= root->value) && (root->value <= r)) {
        print_range(root->left, l, r);
        std::cout << root->value << std::endl;
        print_range(root->right, l, r);
        return;
    }
    if (root->value > r) {
        print_range(root->left, l, r);
        return;
    }
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({nullptr, &node1, 1});
    Node node3({nullptr, nullptr, 8});
    Node node4({nullptr, &node3, 8});
    Node node5({&node4, nullptr, 9});
    Node node6({&node5, nullptr, 10});
    Node node7({&node2, &node6, 5});
    print_range(&node7, 2, 8);
    // expected output: 2 5 8 8
}

int main() {
  test();
}
#endif