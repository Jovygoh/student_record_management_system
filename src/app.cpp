#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"../include/BST.h"
#include    "../include/Student.h"

using namespace std;

bool readFile(const char *, BST *);
int menu();
void clearScreen();
void clearInput();

int main() {
    BST t1, t2;
    Student student;
    int choice;
    const char* filename = "student.txt";

    do {
        choice = menu();
        switch (choice) {
        case 1:
            clearScreen();
            if (readFile(filename, &t1)) {
                t1.preOrderPrint();
            }
            else
                cout<<"Student record failed!"<<endl;
            break;
        case 2:
            clearScreen();
            if (!t1.deepestNodes())
                cout << "Failed to print or no record!"<<endl;
            break;
        case 3: {
            clearScreen();
            int order, source;
            cout << "Enter order (1 for ascending, 2 for descending): ";
            cin >> order;
            while (cin.fail()||order<1||order>2) {
                clearInput();
                cout << "Invalid input! Please enter (1 for ascending, 2 for descending): ";
                cin >> order;
            }
            cout << "Enter source (1 for screen, 2 for file): ";
            cin >> source;
            while (cin.fail()||source<1||source>2) {
                clearInput();
                cout << "Invalid input! Please enter (1 for screen, 2 for file): ";
                cin >> source;
            }
            if (!t1.display(order, source))
                cout << "Display failed or no record!"<<endl;
            break;
        }
        case 4: {
            clearScreen();
            int id;
            cout << "Enter the student ID to clone subtree: ";
            cin >> id;
            while (cin.fail()) {
                clearInput();
                cout << "Invalid input! Please enter a valid integer: ";
                cin >> id;
            }
            t2 = BST(); // reset t2
            Student s;
            s.id = id;
            if (t2.CloneSubtree(t1, s))
            {
                cout << "Original Tree (PreOrder):" << endl;
                t1.preOrderPrint();
                cout << "Cloned Subtree (PreOrder):" << endl;
                t2.preOrderPrint();
            }
            break;
        }
        case 5:
            clearScreen();
            if (!t1.printLevelNode())
                cout << "Failed to print or no record!" << endl;
            break;
        case 6:
            clearScreen();
            if (!t1.printPath())
                cout << "Failed to print or no record!" << endl;
            break;
        case 7:
            clearScreen();
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        if (choice != 7) {
            cout << "\nPress <ENTER> to continue...";
            cin.ignore();
            cin.get();
        }
        clearScreen();
    } while (choice != 7);

	system("pause");
	return 0;
}

int menu() {
    int choice;
    cout << "\nMenu:\n";
    cout << "(1) Read data to BST\n";
    cout << "(2) Print deepest nodes\n";
    cout << "(3) Display student\n";
    cout << "(4) Clone Subtree\n";
    cout << "(5) Print Level Nodes\n";
    cout << "(6) Print Path\n";
    cout << "(7) Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    while (cin.fail()) {
        clearInput();
        cout << "Invalid input! Please enter a valid integer: ";
        cin >> choice;
    }
    return choice;
}
bool readFile(const char* filename, BST* t1) {
	ifstream inFile(filename);
	if (!inFile) {
		cout << "Error opening file: " << filename << endl;
		return false;
	}

	int recordsRead = 0;

	Student s;
	string line;
	char skip[30];
	while (inFile >> skip >> skip >> skip >> s.id)
    {
		inFile >> skip >> skip;
        inFile.ignore();
		inFile.getline(s.name, 256);
        inFile >> skip >> skip;
        inFile.getline(s.address, 256);
        inFile >> skip >> skip >> s.DOB;
		inFile >> skip >> skip >> skip >> s.phone_no;
		inFile >> skip >> skip >> s.course;
		inFile >> skip >> skip >> s.cgpa;

		t1->insert(s);
		recordsRead++;
	}

	cout << recordsRead << " student records successfully read." << endl;
	inFile.close();
	return true;
}

void clearScreen() {
    system("cls");
}

void clearInput() {
    cin.clear(); // clear the error flags
    cin.ignore(1000, '\n'); // ignore invalid input
}
