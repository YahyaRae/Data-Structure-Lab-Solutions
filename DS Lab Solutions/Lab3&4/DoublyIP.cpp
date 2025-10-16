#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


struct Node {
    string ip;
    Node* prev;
    Node* next;


    Node(const string& ip_addr) : ip(ip_addr), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    
    ~DoublyLinkedList() {
        freeList();
    }

   
    void insertAtEnd(const string& ip_addr) {
        Node* newNode = new Node(ip_addr);

        if (head == nullptr) {
            // List is empty
            head = newNode;
            tail = newNode;
        } else {
            // Insert at the end
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    
    void displayForward() const {
        cout << "Forward traversal:" << endl;
        Node* current = head;

        if (current == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        while (current != nullptr) {
            cout << current->ip;
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }

    
    void displayBackward() const {
        cout << "Backward traversal:" << endl;
        Node* current = tail;

        if (current == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        while (current != nullptr) {
            cout << current->ip;
            if (current->prev != nullptr) {
                cout << " -> ";
            }
            current = current->prev;
        }
        cout << endl;
    }

   
    void freeList() {
        Node* current = head;
        Node* nextNode = nullptr;
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
    }
};


int main() {
    DoublyLinkedList ip_list;
    ifstream file("Readme Text.txt"); 

    
    if (!file.is_open()) {
        cerr << "Error: Could not open the file 'ips.txt'. Please ensure it exists." << endl;
        return 1;
    }

    string line;

    if (getline(file, line)) {
   
        stringstream ss(line);
        string ip_token;

        
        while (getline(ss, ip_token, ',')) {
            
            if (!ip_token.empty()) {
                
                ip_list.insertAtEnd(ip_token);
            }
        }
    }

    file.close(); 
    ip_list.displayForward();

   
    cout << "\n----------------------------------------\n" << endl;


    ip_list.displayBackward();

  
    return 0;
}