#include <bits/stdc++.h>
using namespace std;

class Student {
    int rollNo;
    string name;

public:
    Student() : rollNo(-1), name("") {}

    void setDetails(int r, string n) {
        rollNo = r;
        name = n;
    }

    int getRollNo() {
        return rollNo;
    }

    string getName() {
        return name;
    }

    void clear() {
        rollNo = -1;
        name = "";
    }
};

Student v[10][2]; // Hash table: v[i][0] stores student data, v[i][1] stores chaining link

void insert(int rollNo, string name) {
    int idx = rollNo % 10;

    if (v[idx][0].getRollNo() == -1) {
        // Insert if the bucket is empty
        v[idx][0].setDetails(rollNo, name);
        cout << "Successfully inserted the student details.\n";
    } else {
        // Check if the element at index belongs to another bucket
        if (v[idx][0].getRollNo() % 10 != idx) {
            for (int i = idx; i < idx + 10; i++) {
                int j = i % 10;
                if (v[j][0].getRollNo() == -1) {
                    v[j][0].setDetails(v[idx][0].getRollNo(), v[idx][0].getName());
                    v[j][1].setDetails(v[idx][1].getRollNo(), "");
                    
                    for(int i = 0; i < 10; i++){
                        if(v[i][1].getRollNo() == idx){
                            v[i][1].setDetails(j, "");
                        }
                    }
                    v[idx][0].setDetails(rollNo, name);
                    cout << "Successfully inserted the student details. (pointer changed)\n";
                    return;
                }
            }
            cout << "Hash table is full.\n";
            return;
        } else {
            // Handle collision using chaining
            while (v[idx][1].getRollNo() != -1) {
                idx = v[idx][1].getRollNo();
            }
            for (int i = 0; i < 10; i++) {
                int current = (idx + i) % 10;
                if (v[current][0].getRollNo() == -1) {
                    v[current][0].setDetails(rollNo, name);
                    v[idx][1].setDetails(current, ""); // Create chain link
                    cout << "Successfully inserted the student details.\n";
                    return;
                }
            }
            cout << "Hash table is full.\n";
        }
    }
}

void display() {
    for (int i = 0; i < 10; i++) {
        cout << "Bucket " << i << ": ";
        if (v[i][0].getRollNo() != -1) {
            cout << "Roll No: " << v[i][0].getRollNo() << ", Name: " << v[i][0].getName();
        } else {
            cout << "Empty";
        }
        if (v[i][1].getRollNo() != -1) {
            cout << " -> Points to: " << v[i][1].getRollNo();
        }
        cout << endl;
    }
}

void search(int rollNo) {
    int idx = rollNo % 10;
    int comparisons = 0;

    if (v[idx][0].getRollNo() == -1) {
        cout << "Student not found.\n";
        return;
    } else if (v[idx][0].getRollNo() % 10 != rollNo % 10) {
        for (int i = idx; i < idx + 10; i++) {
            comparisons++;
            int j = i % 10;
            if (v[j][0].getRollNo() == rollNo) {
                cout << "Student found: " << v[j][0].getName() << " (Roll No: " << v[j][0].getRollNo() << ")\n";
                cout << "Number of comparisons: " << comparisons << endl;
                return;
            }
        }
        cout << "Student not found.\n";
        cout << "Number of comparisons: " << comparisons << endl;
    } else {
        while (v[idx][0].getRollNo() != rollNo && v[idx][1].getRollNo() != -1) {
            comparisons++;
            idx = v[idx][1].getRollNo();
        }
        comparisons++;
        if (v[idx][0].getRollNo() == rollNo) {
            cout << "Student found: " << v[idx][0].getName() << " (Roll No: " << v[idx][0].getRollNo() << ")\n";
            cout << "Number of comparisons: " << comparisons << endl;
        } else {
            cout << "Student not found.\n";
            cout << "Number of comparisons: " << comparisons << endl;
        }
    }
}

int main() {
    // Initialize hash table
    for (int i = 0; i < 10; i++) {
        v[i][0].clear();
        v[i][1].clear();
    }

    int menu;
    while (menu != 4) {
        cout << "\nEnter your choice:\n1.Insert Student Details\n2.Display Table\n3.Search Student\n4.Exit\n";
        cin >> menu;

        if (menu == 1) {
            int rollNo;
            string name;
            cout << "Enter Roll No: ";
            cin >> rollNo;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            insert(rollNo, name);
        } else if (menu == 2) {
            cout << "Displaying the hash table:\n";
            display();
        } else if (menu == 3) {
            int rollNo;
            cout << "Enter Roll No to search: ";
            cin >> rollNo;
            search(rollNo);
        } else if (menu == 4) {
            cout << "Successfully exited the program.\n";
        } else {
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
