#include <iostream>
using namespace std;

class HashTable {
public:
    int arr[10][2];  

    HashTable() {
        for (int j = 0; j < 10; j++) {
            arr[j][0] = -1;  
            arr[j][1] = -1;  
        }
    }

    int reminder(int value) {
        return value % 10;  
    }

    void insert(int n) {
        int idx = reminder(n);  

        if (arr[idx][0] == -1) {
            arr[idx][0] = n;
            cout << "Inserted " << n << " at index " << idx << endl;
        } else if (arr[idx][0]%10 != idx){
        for(int i = idx; i < idx + 10; i++){
            int j = i % 10; 
            if(arr[j][0] == -1){
                arr[j][0] = arr[idx][0];
                arr[j][1] = arr[idx][1];
                for(int i=0;i<10;i++){
                    if(arr[i][1]==idx){
                        arr[i][1]=j;
                    }
                }
                break;
            }
        }
        arr[idx][0]=n;
        arr[idx][1]=-1;
        return;
    }else if(arr[idx][0]%10 == idx){
        while(arr[idx][1]!=-1){
            idx=arr[idx][1];
        }    
        for(int i = idx; i < idx + 10; i++){
            int j = i % 10; 
            if(arr[j][0] == -1){
                arr[j][0] = n;
                arr[idx][1]=j;
                return;
                }
            }
        
    }   
    }

    void display() {
        for (int i = 0; i < 10; i++) {
            cout << "Index " << i << ": Value = " << arr[i][0] << ", Next = " << arr[i][1] << endl;
        }
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
