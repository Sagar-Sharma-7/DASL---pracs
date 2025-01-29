#include <bits/stdc++.h>
using namespace std;

void insert(int val, int arr[]) {
    int idx = val % 10;
    if (arr[idx] == -1) {
        arr[idx] = val;
        cout << "Successfully inserted the value" << endl;
    } else {
        int step = 1;
        while (step < 10) {
            if (arr[(idx + step) % 10] == -1) {
                arr[(idx + step) % 10] = val;
                cout << "Successfully inserted the value" << endl;
                break;
            }
            step++;
        }
        if (step == 10) {
            cout << "Table is full" << endl;
        }
    }
}

void display(int arr[]) {
    for (int i = 0; i < 10; i++) {
        cout << "Bucket" << i  << ": " << arr[i] << endl;
    }
}

void search(int val, int arr[]) {
    int comp = 0;
    int idx = val % 10;
    int step = 0;
    
    while (step < 10) {
        comp++;
        if (arr[(idx + step) % 10] == val) {
            cout << "Value found at location: " << (idx + step) % 10 << endl;
            cout << "Number of comparisons: " << comp << endl;
            break;
        } else if (arr[(idx + step) % 10] == -1) {
            cout << "Value is not present in table" << endl;
            cout << "Number of comparisons: " << comp << endl;
            break;
        }
        step++;
        if (step == 10) {
            cout << "Value is not present in table" << endl;
            cout << "Number of comparisons: " << comp << endl;
        }
    }
}

int main() {
    int arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = -1;
    }

    int menu;
    while (menu != 4) {
        cout << "Enter your choice: " << "\n";
        cout << "1. Insert\n2.Display\n3.Search\n4.exit\n";
        cin >> menu;
        
        if (menu == 1) {
            int n;
            cout << "Enter value you want to insert: ";
            cin >> n;
            insert(n, arr);
        }
        else if (menu == 2) {
            cout << "Displaying the hash table" << endl;
            display(arr);
        }
        else if (menu == 3) {
            int n;
            cout << "Enter value you want to search: ";
            cin >> n;
            search(n, arr);
        }
        else if (menu == 4) {
            cout << "Successfully exited from program!" << endl;
        }
        else {
            cout << "Enter a valid option!" << endl;
        }
    }
}
