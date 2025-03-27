#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    bool isLeftThreaded, isRightThreaded;

    Node(int value)
        : data(value), left(nullptr), right(nullptr),
          isLeftThreaded(false), isRightThreaded(false) {}
};

class FullyThreadedBST {
private:
    Node* root;

    // Standard BST insertion.
    Node* insert(Node* node, int value) {
        if (!node)
            return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        return node;
    }

    // Convert the BST to a fully threaded BST.
    // During an inorder traversal, set threads for nodes without a genuine child.
    void convertFullyThreaded(Node* curr, Node*& prev) {
        if (!curr)
            return;

        // Process left subtree first.
        convertFullyThreaded(curr->left, prev);

        // If current node does not have a left child, thread it to its inorder predecessor.
        if (curr->left == nullptr) {
            curr->left = prev;
            curr->isLeftThreaded = true;
        }
        
        // For the previously visited node, if it doesn't have a right child,
        // then thread its right pointer to the current node.
        if (prev != nullptr && prev->right == nullptr) {
            prev->right = curr;
            prev->isRightThreaded = true;
        }

        // Update the previous node to the current node.
        prev = curr;

        // Process right subtree.
        convertFullyThreaded(curr->right, prev);
    }

    // Helper: Get the leftmost node from a given node.
    Node* leftMost(Node* node) {
        if (!node) return nullptr;
        // Move to left child until a thread or NULL is encountered.
        while (!node->isLeftThreaded && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Inorder traversal using the threaded pointers.
    void inorderTraversal() {
        Node* cur = leftMost(root);
        while (cur != nullptr) {
            cout << cur->data << " ";
            // If the right pointer is a thread, simply follow it.
            if (cur->isRightThreaded)
                cur = cur->right;
            else
                // Otherwise, go to the leftmost node in the right subtree.
                cur = leftMost(cur->right);
        }
    }

    // Preorder traversal (recursive) that avoids following thread pointers.
    void preorderTraversal(Node* node) {
        if (!node)
            return;
        cout << node->data << " ";
        if (!node->isLeftThreaded) {
            preorderTraversal(node->left);
        }
        if (!node->isRightThreaded) {
            preorderTraversal(node->right);
        }
    }

public:
    FullyThreadedBST() : root(nullptr) {}

    // Public method to insert a new node.
    void insert(int value) {
        root = insert(root, value);
    }

    // Convert the BST into a fully threaded BST.
    void convert() {
        Node* prev = nullptr;
        convertFullyThreaded(root, prev);
    }

    // Inorder traversal (using threads).
    void inorder() {
        cout << "Inorder Traversal (Fully Threaded): ";
        inorderTraversal();
        cout << endl;
    }

    // Preorder traversal (recursive, avoiding threads).
    void preorder() {
        cout << "Preorder Traversal (Fully Threaded): ";
        preorderTraversal(root);
        cout << endl;
    }
};

int main() {
    FullyThreadedBST tree;
    
    // Insert nodes into the BST.
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    // Convert the BST into a fully threaded BST.
    tree.convert();
    
    // Display traversals.
    tree.inorder();
    tree.preorder();
    
    return 0;
}
