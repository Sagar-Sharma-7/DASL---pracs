#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

// Node class to represent characters and their frequencies
class Node {
public:
    char character;      // The character
    int frequency;       // Frequency of the character
    Node* left;          // Left child
    Node* right;         // Right child

    // Constructor to initialize the node
    Node(char ch, int freq) {
        character = ch;
        frequency = freq;
        left = nullptr;
        right = nullptr;
    }
};

// Comparator class for the priority queue
class Compare {
public:
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency; // Smaller frequency has higher priority
    }
};

// Function to check if a node is a leaf
bool isLeaf(Node* node) {
    return node->left == nullptr && node->right == nullptr;
}

// Function to generate Huffman codes
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return; // Base case: empty node

    if (isLeaf(root)) {
        huffmanCodes[root->character] = code; // Store the code for the character
    }

    generateCodes(root->left, code + "0", huffmanCodes);  // Traverse left
    generateCodes(root->right, code + "1", huffmanCodes); // Traverse right
}

// Function to decode the encoded string
void decodeString(Node* root, const string& encodedString) {
    Node* current = root; // Start from the root of the tree

    for (char bit : encodedString) {
        if (bit == '0') {
            current = current->left;  // Move to the left child
        } else {
            current = current->right; // Move to the right child
        }

        if (isLeaf(current)) { // If it's a leaf node, print the character
            cout << current->character;
            current = root; // Go back to the root for the next character
        }
    }
    cout << endl;
}

// Function to build the Huffman Tree and perform encoding/decoding
void huffmanEncoding(const string& text) {
    if (text.empty()) {
        cout << "The input text is empty!" << endl;
        return;
    }

    // Step 1: Calculate the frequency of each character
    unordered_map<char, int> frequencyMap;
    for (char ch : text) {
        frequencyMap[ch]++;
    }

    // Step 2: Create a priority queue (min-heap) to store the nodes
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Create a leaf node for each character and add it to the heap
    for (auto pair : frequencyMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Step 3: Build the Huffman Tree
    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop(); // Node with smallest frequency
        Node* right = minHeap.top(); minHeap.pop(); // Node with second smallest frequency

        // Create a new internal node with the combined frequency
        Node* newNode = new Node('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode); // Add the new node to the heap
    }

    Node* root = minHeap.top(); // The root of the Huffman Tree

    // Step 4: Generate Huffman codes
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    // Step 5: Encode the input text
    string encodedString = "";
    for (char ch : text) {
        encodedString += huffmanCodes[ch];
    }

    // Display the Huffman codes
    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Display the encoded string
    cout << "\nEncoded String:\n" << encodedString << endl;

    // Step 6: Decode the encoded string
    cout << "\nDecoded String:\n";
    decodeString(root, encodedString);
}

int main() {
    string text;
    cout << "Enter the text to be encoded: ";
    getline(cin, text);

    huffmanEncoding(text);
    return 0;
}
