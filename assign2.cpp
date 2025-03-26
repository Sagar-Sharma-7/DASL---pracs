#include <iostream>
#include <string>
using namespace std;


class node {
    public:
        string data;
        node* next;

        node(string data){
            this->data = data;
            next = nullptr;
        }
};

class sc{
    node** arr;
    int size;

    public:
        sc(int tsize){
            size = tsize;
            arr = new node*[size];
            for(int i = 0; i < size; i++){
                arr[i] = nullptr;
            }
        }

        int findIndex(string name){
            int index = 0;
            int step = 1;
            for(int i = 0; i < name.size(); i++){
                index += step * (name[name.size() - i - 1]);
                step = step * 10;
            }
            return index;
        }

        void insert(string name) {
            int index = findIndex(name) % 10;
            node* newnode = new node(name);
            if(arr[index] == nullptr){
                arr[index] = newnode;
            }else{
                newnode->next = arr[index];
                arr[index] = newnode;
            }
        }

        void display() {
            for(int i =0; i < size; i++){
                cout << "Bucket " << i << ": ";
                node* temp = arr[i];
                while(temp != nullptr){
                    cout << temp->data << "->";
                    temp = temp ->next;
                }
                cout << endl;
            }
        }

        bool search(string name) {
        int index = findIndex(name) % size;
        node* temp = arr[index];
        while (temp != nullptr) {
            if (temp->data == name) {
                cout << "\"" << name << "\" found in bucket " << index << endl;
                return true;
            }
            temp = temp->next;
        }
        cout << "\"" << name << "\" not found in the hash table." << endl;
        return false;
    }
};

int main() {
    int tableSize = 10;  // Size of the hash table
    sc hashTable(tableSize);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a word\n";
        cout << "2. Search for a word\n";
        cout << "3. Display the hash table\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string word;
            cout << "Enter the word to insert: ";
            cin.ignore();  // Clear input buffer
            getline(cin, word);
            hashTable.insert(word);
            break;
        }
        case 2: {
            string word;
            cout << "Enter the word to search: ";
            cin.ignore();  // Clear input buffer
            getline(cin, word);
            hashTable.search(word);
            break;
        }
        case 3:
            hashTable.display();
            break;
        case 4:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
