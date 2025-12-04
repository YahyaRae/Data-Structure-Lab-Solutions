#include <iostream>
#include <string>
using namespace std;

struct TimeCapsule {
    int year;
    string eventName;
    TimeCapsule* left;
    TimeCapsule* right;
    
    TimeCapsule(int y, const string& name) : year(y), eventName(name), left(nullptr), right(nullptr) {}
};

class TimeStreamStabilizer {
private:
    TimeCapsule* root;
    
    
    TimeCapsule* findMin(TimeCapsule* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
    
    
    TimeCapsule* deleteNode(TimeCapsule* node, int year) {
        if (!node) return nullptr;
        
        if (year < node->year) {
            node->left = deleteNode(node->left, year);
        } else if (year > node->year) {
            node->right = deleteNode(node->right, year);
        } else {
            
            if (!node->left) {
                TimeCapsule* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TimeCapsule* temp = node->left;
                delete node;
                return temp;
            }
            
            
            TimeCapsule* successor = findMin(node->right);
            node->year = successor->year;
            node->eventName = successor->eventName;
            node->right = deleteNode(node->right, successor->year);
        }
        return node;
    }
    
   
    TimeCapsule* insertNode(TimeCapsule* node, int year, const string& eventName) {
        if (!node) {
            return new TimeCapsule(year, eventName);
        }
        
        if (year < node->year) {
            node->left = insertNode(node->left, year, eventName);
        } else if (year > node->year) {
            node->right = insertNode(node->right, year, eventName);
        }
        
        return node;
    }
    
    
    TimeCapsule* searchNode(TimeCapsule* node, int year) {
        if (!node || node->year == year) {
            return node;
        }
        
        if (year < node->year) {
            return searchNode(node->left, year);
        } else {
            return searchNode(node->right, year);
        }
    }
    
    
    void inOrderTraversal(TimeCapsule* node) {
        if (!node) return;
        
        inOrderTraversal(node->left);
        cout << node->year << ": " << node->eventName << endl;
        inOrderTraversal(node->right);
    }
    
    
    int findMinYear(TimeCapsule* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node ? node->year : -1;
    }
    
    int findMaxYear(TimeCapsule* node) {
        while (node && node->right) {
            node = node->right;
        }
        return node ? node->year : -1;
    }
    
public:
    TimeStreamStabilizer() : root(nullptr) {}
    
    void INJECT(int year, const string& eventName) {
        cout << "> System: Injecting " << year << "... Timeline stable." << endl;
        
        TimeCapsule* existing = searchNode(root, year);
        if (existing) {
           
            return;
        }
        
        root = insertNode(root, year, eventName);
    }
    
    void PARADOX(int year) {
        TimeCapsule* node = searchNode(root, year);
        if (!node) {
            cout << "> Alert: Paradox detected at " << year << "!" << endl;
            cout << "> System: Year " << year << " not found. Timeline stable." << endl;
            return;
        }
        
        cout << "> Alert: Paradox detected at " << year << "!" << endl;
        root = deleteNode(root, year);
        cout << "> System: Year " << year << " removed. Timeline stabilized." << endl;
    }
    
    void SEARCH(int year) {
        cout << "> Query: Searching for " << year << "..." << endl;
        
        TimeCapsule* node = searchNode(root, year);
        if (node) {
            cout << "> Result: Event Found! [" << node->year << ": " << node->eventName << "]" << endl;
        } else {
            cout << "> Result: Year " << year << " not found in current timeline." << endl;
        }
    }
    
    void REPORT() {
        cout << "> COMMAND: CHRONOLOGICAL REPORT" << endl;
        cout << "-------------------------------" << endl;
        
        if (!root) {
            cout << "Timeline is empty." << endl;
        } else {
            inOrderTraversal(root);
        }
        
        cout << "-------------------------------" << endl;
    }
    
    
    int CalculateTimeSpan() {
        if (!root) return 0;
        
        int earliest = findMinYear(root);
        int latest = findMaxYear(root);
        
        return latest - earliest;
    }
    
    
    TimeCapsule* getRoot() { return root; }
};

int main() {
    TimeStreamStabilizer stabilizer;
    string command;
    
    
    cout << "=== TIME-STREAM STABILIZER ACTIVATED ===" << endl << endl;
    
   
    stabilizer.INJECT(2050, "Mars Colony Established");
    stabilizer.INJECT(1969, "Moon Landing");
    stabilizer.INJECT(2100, "Warp Drive Invented");
    stabilizer.INJECT(2000, "Y2K Bug");
    
    stabilizer.INJECT(1800, "Industrial Revolution");
    
    cout << endl;
    stabilizer.SEARCH(1969);
    
    cout << endl;
    stabilizer.INJECT(1990, "World Wide Web");
    
    cout << endl;
    stabilizer.PARADOX(2000);
    
    cout << endl;
    stabilizer.REPORT();
    
    cout << endl;
    stabilizer.SEARCH(2000);
    
    
    cout << endl;
    cout << "> BONUS: Time Span Calculation" << endl;
    int timeSpan = stabilizer.CalculateTimeSpan();
    cout << "> Time Span: " << timeSpan << " years" << endl;
    
    return 0;
}