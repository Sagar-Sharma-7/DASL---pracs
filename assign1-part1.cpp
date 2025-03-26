#include <bits/stdc++.h>
#include <string>
using namespace std;

class Student{
    int rollNo;
    string name;

    public:
        Student(){
            rollNo = -1;
            name = "";
        }

        void setDetails(int r, string n){
            rollNo = r;
            name = n;
        }

        int getRollNo(){
            return rollNo;
        }

        string getName(){
            return name;
        }

        void clear(){
            rollNo = -1;
            name = "";
        }

};

void insert(int rollNo, string name, Student arr[]){
    int idx = rollNo % 10;
    if(arr[idx].getRollNo() == -1){
        arr[idx].setDetails(rollNo, name);
        cout << "Successfully inserted" << endl;
    } else {
        int step = 1;
        while( step < 10){
            int newIdx = (idx + step) % 10;
            if(arr[newIdx].getRollNo() == -1){
                arr[newIdx].setDetails(rollNo, name);
                cout << "Successfully insert after collision" << endl;
                return;
            }
            step++;
        }
        if(step == 10){
            cout << "Table is full" << endl;
        }
    }
}

void search(int rollNo, Student arr[]){
    int idx = rollNo % 10;
    int step = 0, comparisons = 0;

    while(step < 10){
        comparisons++;
        int newIdx = (idx + step) % 10;
        if(arr[newIdx].getRollNo() == rollNo){
            cout << "Student found: " << arr[newIdx].getName()
                 << " (Roll No: " << arr[newIdx].getRollNo() << ").\n";
            cout << "Number of comparisons: " << comparisons << endl;
            return;
        }else if (arr[newIdx].getRollNo() == -1){
            cout << "Student not found.\n";
            cout << "Number of comparisons: " << comparisons << endl;
            return;
        }
        step++;
    }
    cout << "Student not found after checking entire table.\n";
    cout << "Number of comparisons: " << comparisons << endl;
}

void display(Student arr[]){
    for(int i = 0; i < 10; i++){
        if(arr[i].getRollNo() != -1){
            cout << "Bucket " << i << ": "
                 << "Roll No: " << arr[i].getRollNo()
                 << ", Name: " << arr[i].getName() << endl;
        } else {
            cout << "Bucket " << i << ": Empty\n";
        }
    }
}

int main(){
    Student arr[10];

    int menu;
    while (menu != 4) {
        cout << "\nEnter your choice:\n";
        cout << "1. Insert Student Details\n";
        cout << "2. Display Student Table\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Exit\n";
        cin >> menu;

        if (menu == 1) {
            int rollNo;
            string name;
            cout << "Enter Roll No: ";
            cin >> rollNo;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            insert(rollNo, name, arr);
        } else if (menu == 2) {
            cout << "Displaying the student table:\n";
            display(arr);
        } else if (menu == 3) {
            int rollNo;
            cout << "Enter Roll No to search: ";
            cin >> rollNo;
            search(rollNo, arr);
        } else if (menu == 4) {
            cout << "Exiting the program.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
