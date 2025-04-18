/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    string department;

public:
    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Department: ";
        getline(cin, department);
    }

    void display() const {
        cout << "Roll No: " << rollNo << "\n";
        cout << "Name: " << name << "\n";
        cout << "Department: " << department << "\n";
        cout << "------------------------\n";
    }

    int getRollNo() const {
        return rollNo;
    }
};

void addStudent() {
    ofstream file("students.dat", ios::binary | ios::app);
    Student s;
    s.input();
    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();
    cout << "Student record added successfully.\n";
}

void displayAll() {
    ifstream file("students.dat", ios::binary);
    Student s;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        s.display();
    }
    file.close();
}

void searchStudent(int roll) {
    ifstream file("students.dat", ios::binary);
    Student s;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRollNo() == roll) {
            cout << "Student Found:\n";
            s.display();
            found = true;
            break;
        }
    }
    file.close();
    if (!found) {
        cout << "Student with Roll No " << roll << " not found.\n";
    }
}

void deleteStudent(int roll) {
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    Student s;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRollNo() != roll) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student record deleted successfully.\n";
    else
        cout << "Student with Roll No " << roll << " not found.\n";
}

int main() {
    int choice, roll;
    do {
        cout << "\n===== Student Record Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Delete Student by Roll No\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            cout << "Enter Roll No to search: ";
            cin >> roll;
            searchStudent(roll);
            break;
        case 4:
            cout << "Enter Roll No to delete: ";
            cin >> roll;
            deleteStudent(roll);
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
