// accepted parcel ID: 83684115
//
// Node by key removal in BST of height h realization.
//
// The algortihm basically consists of two steps:
//  - search of a node by key (removal() function main body, O(h))
//  - if not found do nothing, otherwise replace found node with the rigthest 
//    node in the left subtree (new_root() function O(h))
//
// The algorithm uses O(1) of additional memory space and is of O(h) time 
// complexity: O(h) for deleted node search and O(h) for traversing to the 
// rightest node in the left subtree.
//

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
#include <cassert>


Node* new_root(Node* root) {
    Node* left_child = root->left;
    Node* right_child = root->right;

    if (left_child == nullptr) {
        delete root;
        return right_child;
    }

    if (left_child->right == nullptr) {
        left_child->right = right_child;
        delete root;
        return left_child;
    }
    
    // traversing to the rightest node in left subtree, called here corner_node
    Node* pre_corner_node = left_child;
    while (pre_corner_node->right->right != nullptr) {
        pre_corner_node = pre_corner_node->right;
    }

    Node* corner_node = pre_corner_node->right;
    pre_corner_node->right = corner_node->left;
    corner_node->left = left_child;
    corner_node->right = right_child;
    delete root;
    return corner_node;
}

Node* remove(Node* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (root->value == key) {
        return new_root(root);
    }

    if (key < root->value) {
        root->left  = remove(root->left,  key);
    } else {
        root->right = remove(root->right, key);
    }
    return root;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}

int main() {
  test();
}
#endif
