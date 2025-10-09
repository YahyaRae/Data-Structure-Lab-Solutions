#include <iostream>
#include <string>
using namespace std;

// Node for singly linked list
struct Node {
    string name;
    int id;
    Node* next;

    Node(const string& n, int i) : name(n), id(i), next(nullptr) {}
};

// Queue class
class Queue {
private:
    Node* front;
    Node* back;
    int count;

public:
    Queue() : front(nullptr), back(nullptr), count(0) {}

    // Add student to the queue (enqueue)
    void addstudent(const string& name, int id) {
        Node* newNode = new Node(name, id);
        if (front == nullptr) {
            front = back = newNode;
        } else {
            back->next = newNode;
            back = newNode;
        }
        count++;
        cout << "Added: " << name << " (ID: " << id << ") to the queue.\n";
    }

    // Serve student from the queue (dequeue)
    void servestudent() {
        if (front == nullptr) {
            cout << "Queue is empty. No one to serve.\n";
            return;
        }
        Node* temp = front;
        cout << "Served: " << temp->name << " (ID: " << temp->id << "). Enjoy the T-shirt!\n";
        front = front->next;
        if (front == nullptr) back = nullptr;
        delete temp;
        count--;
    }

    // Student leaves from the middle (remove by id)
    void leavestudent(int id) {
        if (front == nullptr) {
            cout << "Queue is empty.\n";
            return;
        }

        if (front->id == id) {
            Node* temp = front;
            front = front->next;
            if (front == nullptr) back = nullptr;
            cout << "Removed: " << temp->name << " (ID: " << temp->id << ") from the queue.\n";
            delete temp;
            count--;
            return;
        }

        Node* current = front;
        while (current->next != nullptr && current->next->id != id) {
            current = current->next;
        }

        if (current->next == nullptr) {
            cout << "Student with ID " << id << " not found.\n";
            return;
        }

        Node* temp = current->next;
        current->next = current->next->next;
        if (temp == back) back = current;
        cout << "Removed: " << temp->name << " (ID: " << temp->id << ") from the queue.\n";
        delete temp;
        count--;
    }

    // Display the queue
    void display() const {
        if (front == nullptr) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Current queue (front -> back):\n";
        Node* current = front;
        int pos = 1;
        while (current != nullptr) {
            cout << pos++ << ". Name: " << current->name << "  ID: " << current->id << "\n";
            current = current->next;
        }
    }

    int getcount() const {
        return count;
    }
};

int main() {
    Queue q;
    int choice;

    while (true) {
        cout << "\n=== Code-a-Thon T-Shirt Queue ===\n";
        cout << "1. Add Student\n";
        cout << "2. Serve Student (front of queue)\n";
        cout << "3. Student Leaves (remove by ID)\n";
        cout << "4. Display Queue\n";
        cout << "5. Count Students\n";
        cout << "6. Exit\n";
        cout << "Choose an option (1-6): ";

        if (!(cin >> choice)) {
            cin.clear();       // clear fail flag
            cin.ignore(10000, '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(); // remove leftover newline after integer input

        if (choice == 1) {
            string name;
            int id;

            cout << "Enter student name: ";
            getline(cin, name);

            cout << "Enter unique student ID (integer): ";
            while (!(cin >> id)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid ID. Enter an integer: ";
            }
            cin.ignore(); // remove newline

            q.addstudent(name, id);

        } else if (choice == 2) {
            q.servestudent();

        } else if (choice == 3) {
            int id;
            cout << "Enter the student ID to remove: ";
            while (!(cin >> id)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid ID. Enter an integer: ";
            }
            cin.ignore();
            q.leavestudent(id);

        } else if (choice == 4) {
            q.display();

        } else if (choice == 5) {
            cout << "Students waiting: " << q.getcount() << "\n";

        } else if (choice == 6) {
            cout << "Goodbye!\n";
            break;

        } else {
            cout << "Please select a valid option (1-6).\n";
        }
    }

    return 0;
}
