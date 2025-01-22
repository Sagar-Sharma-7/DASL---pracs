#include <iostream>
using namespace std;

class linearProbing {
public:
    int arr[10];

    linearProbing() {
        for (int j = 0; j < 10; j++) {
            arr[j] = -1;
        }
    }

    int reminder(int value) {
        return value % 10;
    }

    void insert(int value) {
        int rem = reminder(value);
        int loc = rem;

        if (arr[rem] == -1) {
            arr[rem] = value;
        } else {
            int i = rem + 1;
            while (true) {
                i = i % 10;
                if (i == loc) {
                    cout << "Array is full" << endl;
                    return;
                } else {
                    if (arr[i] == -1) {
                        arr[i] = value;
                        return;
                    }
                }
                i++;
            }
        }
    }

    void search(int value) {
        int rem = reminder(value);
        int loc = rem;

        if (arr[rem] == value) {
            cout << "found at: " << rem <<  endl;
            return;
        } else {
            int i = rem + 1;
            while (true) {
                i = i % 10;
                if (i == loc) {
                    cout << "NOT FOUND" << endl;
                    return;
                } else {
                    if (arr[i] == value) {
                        cout << "found at: " << i << endl;
                        return;
                    }
                }
                i++;
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
    linearProbing l;
    int choice, value;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Insert value\n";
        cout << "2. Search value\n";
        cout << "3. Display array\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                l.insert(value);
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                l.search(value);
                break;
            case 3:
                l.display();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
}
