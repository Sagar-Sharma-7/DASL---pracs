#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    bool lThread;
    bool rThread;

    Node(int value) {
        data = value;
        left = right = nullptr;
        lThread = rThread = true;  // Initially both threads are true
    }
};

class ThreadedBST {
private:
    Node* root;

public:
    ThreadedBST() {
        root = nullptr;
    }

    // Insert into TBST
    void insert(int key) {
        Node* newNode = new Node(key);

        // First node becomes root
        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* curr = root;
        Node* parent = nullptr;

        while (curr != nullptr) {
            if (key == curr->data) {
                cout << "Duplicate not allowed\n";
                return;
            }

            parent = curr;

            if (key < curr->data) {
                if (!curr->lThread)
                    curr = curr->left;
                else
                    break;
            } else {
                if (!curr->rThread)
                    curr = curr->right;
                else
                    break;
            }
        }

        if (key < parent->data) {
            newNode->left = parent->left;
            newNode->right = parent;
            parent->lThread = false;
            parent->left = newNode;
        } else {
            newNode->right = parent->right;
            newNode->left = parent;
            parent->rThread = false;
            parent->right = newNode;
        }
    }

    // Find leftmost node
    Node* leftMost(Node* node) {
        if (node == nullptr) return nullptr;
        while (!node->lThread)
            node = node->left;
        return node;
    }

    // Inorder traversal using threads
    void inorder() {
        Node* curr = leftMost(root);
        cout << "Inorder Traversal: ";
        while (curr != nullptr) {
            cout << curr->data << " ";

            if (curr->rThread)
                curr = curr->right;
            else
                curr = leftMost(curr->right);
        }
        cout << endl;
    }
};

int main() {
    ThreadedBST tree;
    int choice, value;

    do {
        cout << "\n--- Threaded BST Menu ---\n";
        cout << "1. Insert Node\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            tree.inorder();
            break;
        case 3:
            cout << "Exiting.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
