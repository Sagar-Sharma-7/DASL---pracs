#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;


class Node {
public:
    char ch;          
    int freq;          
    Node* left, *right; 

    Node(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        left = right = nullptr;
    }
};


class Compare {
public:
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq; 
    }
};


bool isLeaf(Node* node) {
    return !node->left && !node->right;
}

// Generate the Huffman Codes for each character by traversing the tree
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr) return;

    // If it's a leaf node, store its code
    if (isLeaf(root)) {
        huffmanCode[root->ch] = code;
    }

    // Traverse left and right subtrees
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Decode the encoded string using the Huffman tree
void decode(Node* root, int& index, const string& encodedString) {
    if (root == nullptr) return;

    // If it's a leaf node, print the character
    if (isLeaf(root)) {
        cout << root->ch;
        return;
    }

    // Move to the left or right child based on the encoded bit
    index++;
    if (encodedString[index] == '0') {
        decode(root->left, index, encodedString);
    } else {
        decode(root->right, index, encodedString);
    }
}

// Build the Huffman Tree and encode/decode the input text
void buildHuffmanTree(const string& text) {
    if (text.empty()) {
        cout << "Empty string provided!" << endl;
        return;
    }

    // Step 1: Calculate the frequency of each character
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    // Step 2: Create a priority queue (min-heap) to store nodes
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Step 3: Create a leaf node for each character and insert into the heap
    for (auto& pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Step 4: Build the Huffman Tree
    while (minHeap.size() > 1) {
        // Take two nodes with the smallest frequencies
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        // Create a new internal node with these two nodes as children
        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        // Insert the new node back into the heap
        minHeap.push(newNode);
    }

    // The remaining node is the root of the Huffman tree
    Node* root = minHeap.top();

    // Step 5: Generate Huffman Codes
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // Display the Huffman Codes
    cout << "Huffman Codes:\n";
    for (auto& pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Step 6: Encode the text
    string encodedString = "";
    for (char ch : text) {
        encodedString += huffmanCode[ch];
    }

    cout << "\nEncoded String:\n" << encodedString << endl;

    // Step 7: Decode the encoded string
    cout << "\nDecoded String:\n";
    int index = -1;
    while (index < (int)encodedString.size() - 1) {
        decode(root, index, encodedString);
    }
    cout << endl;
}

int main() {
    string text;
    cout << "Enter the text to be encoded: ";
    getline(cin, text); // Take the input text from the user
    buildHuffmanTree(text);
    return 0;
}
