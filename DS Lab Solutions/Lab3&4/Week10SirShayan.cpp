#include <iostream>
using namespace std;

class Queue {
private:
    int* arr;
    int capacity;
    int frontIdx;
    int rearIdx;
    int currentSize;

    
    void resize() {
        int newCapacity = capacity * 2;     
        int* newArr = new int[newCapacity]; 

        
        for (int i = 0; i < currentSize; i++) {
            newArr[i] = arr[(frontIdx + i) % capacity];
        }

        delete[] arr;        
        arr = newArr;        
        capacity = newCapacity;

        frontIdx = 0;        
        rearIdx = currentSize; 
    }

public:
    // Constructor
    Queue(int initialCapacity = 4) {
        capacity = initialCapacity;
        arr = new int[capacity];
        frontIdx = 0;
        rearIdx = 0;
        currentSize = 0;
    }

    // Destructor
    ~Queue() {
        delete[] arr;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    int size() const {
        return currentSize;
    }

    void enqueue(int value) {
        if (currentSize == capacity) {
            cout << "Queue is full, resizing..." << endl;
            resize();
        }

        arr[rearIdx] = value;
        rearIdx = (rearIdx + 1) % capacity;
        currentSize++;
    }

    void dequeue() {
        if (currentSize == 0) {
            cout << "Queue Underflow" << endl;
            return;
        }
        frontIdx = (frontIdx + 1) % capacity;
        currentSize--;
    }

    int front() const {
        if (currentSize == 0) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return arr[frontIdx];
    }

    void print() const {
        cout << "Queue elements: ";
        for (int i = 0; i < currentSize; i++) {
            cout << arr[(frontIdx + i) % capacity] << " ";
        }
        cout << endl;
    }
};

int main(){
    Queue q;
    cout<<"Enqueue 10, 20, 30, 40"<<endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);

    q.print();
    cout<<"front element: "<<q.front()<<endl;
    cout<<"Dequeue two elements"<<endl;
    q.dequeue();  
    q.dequeue(); 
    q.print();
    cout<<"Front elements no: "<<q.front()<<endl;

    cout<<"Enqueue 50, 60, 70"<<endl;
    q.enqueue(50);
    q.enqueue(60);
    q.enqueue(70); // This should call a resize
    q.print();

    cout<<"Dequeuing all elements"<<endl;
    while (!q.isEmpty()) {
        cout<<"Front: "<<q.front()<<" -> dequeued\n";
        q.dequeue();}

    q.dequeue();
    



    return 0;
}

    
