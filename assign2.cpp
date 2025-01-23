#include <iostream>
#include <string>
using namespace std;

class node {
public:
    string data;
    node* next;

    node(string data) {
        this->data = data;  
        next = nullptr;
    }
};

class separateChaining {
    node** arr;  
    int size;

public:
    separateChaining(int tableSize) {
        size = tableSize;
        arr = new node*[size];  
        for (int i = 0; i < size; i++) {
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
        if (arr[index] == nullptr) { 
            arr[index] = newnode;
        } else {
            newnode-> next = arr[index];
            arr[index] = newnode;
        }
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << "Bucket " << i << ": ";
            node* temp = arr[i];
            while (temp != nullptr) {
                cout << temp->data << "->";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

int main() {
    separateChaining hashTable(10);  

   
    hashTable.insert("sagar");  
    hashTable.insert("sagar"); 
    hashTable.insert("sharma");  
    hashTable.insert("sagarji");   


   
    hashTable.display();

    return 0;
}
