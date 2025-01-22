#include <iostream>
using namespace std;

class HashTable {
public:
    int arr[10];  

   
    HashTable() {
        for (int j = 0; j < 10; j++) {
            arr[j] = -1;
        }
    }

    
    int reminder(int value) {
        return value % 10;  
    }

    
    void insert(int value) {
        int index = reminder(value);  

        
        if (arr[index] == -1) {
            arr[index] = value;
            cout << "Inserted " << value << " at index " << index << endl;
        } else {  
                if (arr[index] % 10 == index) {
                    cout << "Slot " << index << " is correct for value " << arr[index] << endl;
                    int x = index;
                    int y = 0;
                    while(arr[x] != -1){
                        y = y + 1
                        x = (x + 1) % 10;
                        if(y==10){
                            cout << "table is full";
                            break;
                        }
                    }

                    if (arr[x] == -1) {
                        arr[x] = value;
                        cout << "Inserted " << value << " at index " << x << endl;
                    }
                } else {
                    int displaced_value = arr[index];
                    int displaced_index = reminder(displaced_value);  
                    
                    
                    while (arr[displaced_index] != -1) {
                        displaced_index = (displaced_index + 1) % 10;
                    }
                    arr[displaced_index] = displaced_value;
                    cout << "Moved displaced value " << displaced_value << " to correct position at index " << displaced_index << endl;
                    
                   
                    arr[index] = value;
                    cout << "Inserted " << value << " at index " << index << endl;
                    return;   
            }
            
            
        }
    }

   
    void display() {
        for (int i = 0; i < 10; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    HashTable table; 
    int choice, value;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Insert value\n";
        cout << "2. Display array\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                table.insert(value);  
                break;
            case 2:
                table.display(); 
                break;
            case 3:
                return 0;  
            default:
                cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}
