#include<iostream>
#include<iomanip>
using namespace std;

class Node {

public:
	int data;
	Node* next;
	Node* prev;

	Node(int value)
	{
		this->data = value;
		this->next = nullptr;
		this->prev = nullptr;

	}
	~Node() {
		// Destructor
		cout << "Node with value " << data << " is being deleted." << endl;

	}



};

class DLL
{

public:

	Node* head;
	Node* tail;


	DLL()
	{
		head = nullptr;
		tail = nullptr;
	}
	~DLL() {
		Node* current = head;
		while (current != nullptr) {
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
		cout << "DLL Deleted." << endl;
	}

	//Task 1: Create a destructor DONE



	/*
	* display(): This function is used to display the linked list elements.
	* It will also check if the list is empty
	*/
	void display()
	{
		Node* current = head;

		if (current == nullptr)
		{
			cout << "List is Empty" << endl;
			return;
		}

		while (current != nullptr)
		{
			cout << current->data << endl;
			current = current->next;
		}
	}

	/*Display():
	*	This function is used to display the nodes.
	*	Prev Address: Contains the Address to the Previous Node
	*	Data: Contains the Values
	*	Next Address: Contians the Address of the Next Node
	*	Node Address: Address of the Complete Node
	*/
	void Display() {
		Node* temp = head;
		cout << "\n------------------------------------------------------\n";
		cout << "     Prev Address        |   Data   |     Next Address |   Node Address\n";
		cout << "------------------------------------------------------\n";

		while (temp != nullptr) {
			cout << setw(20) << temp->prev   // shows prev pointer address
				<< " | " << setw(7) << temp->data   // data field
				<< " | " << setw(18) << temp->next  // shows next pointer address
				<< " | " << setw(20) << temp
				<< endl;
			temp = temp->next;
		}
		cout << endl << "Tail: " << tail << endl;
		cout << "------------------------------------------------------\n";
	}



	/*
	* insertAtBegin():
	*	This function is used to insert the Node at the begining.
	*/
	void insertAtBegin(int value)
	{
		Node* newNode = new Node(value);

		newNode->next = head;

		if (head != nullptr)
		{
			head->prev = newNode;
		}
		head = newNode;

		if (head->next == nullptr)
		{
			tail = newNode;
		}
	}

	/* insertAtPos()
	*	This function is used to insert values at specific position
	*	This function will contains your task 2.
	*/
	void insertAtPos(int position, int value)
	{

		if (head == nullptr)
		{
			if (position != 1)
			{
				cout << "Invalid Index..!!" << endl;
				return;
			}
			else
			{
				insertAtBegin(value);
			}
		}

		Node* current = head;
		Node* newNode = new Node(value);
		//node to be inserted at the end
		


		//Move Current to One Node Before the desired Location
		for (int i = 1; i < position - 1; i++)
		{
			if(current == nullptr){
				cout << "Invalid Index..!!" << endl;
				return;
			}
			current = current->next;


		}

		cout << "Traversed: " << current << endl;

		newNode->prev = current;
		newNode->next = current->next;
		if(current->next != nullptr){
			current->next->prev = newNode;
		}
		// current->next->prev = newNode;
		current->next = newNode;


		/*Task 2
		* Add four items in the linked list
		* And try to add the 5th Item in the linked List.
		* Do you see all the 5 element?
		* If No Fix the code segement.
		*/

	}

	/*
	* deleteFB()
	*	This function is used to delete the node from the front.
	*/

	void deleteFB() {


		if (head == nullptr)
		{
			cout << "List is Empty" << endl;
			return;
		}
		else if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
		}
		else
		{
			Node* temp = head;
			Node* nextNode = head->next;
			nextNode->prev = nullptr;
			head = head->next;
			delete temp;

			/*Task 3:
			* This code delete the elements from the begining of the list
			* Run this function you will see the first the node is deleted.
			* Can you see the problem with the head pointing to the new node?
			* Fix the code segement if you see the problem
			*/

		}
	}
	/*DisplayNode()
	*	The purpose of this function to display the content of the single node.
	*	Run this function you will see the content of more then one node.
	*	Task 4: Fix this.
	*/
	void DisplayNode(Node* node) {
		Node* temp = node;
		cout << "\n------------------------------------------------------\n";
		cout << "     Prev Address        |   Data   |     Next Address |   Node Address\n";
		cout << "------------------------------------------------------\n";

		while (temp != nullptr) {
			cout << setw(20) << temp->prev   // shows prev pointer address
				<< " | " << setw(7) << temp->data   // data field
				<< " | " << setw(18) << temp->next  // shows next pointer address
				<< " | " << setw(20) << temp
				<< endl;
			temp = temp->next;
		}
		cout << "------------------------------------------------------\n";
	}
	void search(int value)
	{
		Node* current = head;

		while (current != nullptr)
		{
			if (current->data == value)
			{
				cout << "Node found...";
				DisplayNode(current);
			}
			current = current->next;
		}
	}

	void insertAtEnd(int value)
	{
		if (tail == nullptr)
		{
			insertAtBegin(value);
		}
		else
		{
			Node* current = tail;
			Node* newNode = new Node(value);


			current->next = newNode;
			newNode->prev = current;
			newNode->next = nullptr;
			tail = newNode;

		}
	}


};

int main()
{
	/*
	* You need to complete the four task today.
	*
	*/
	DLL list;
	list.insertAtBegin(10);
	list.insertAtBegin(20);
	list.insertAtBegin(30);
	list.insertAtBegin(40);
	list.insertAtBegin(50);
	list.insertAtEnd(5);
	list.insertAtPos(6, 255);


	list.Display();
	list.deleteFB();

	//Add four elements to the Linked List to Solve Task 2


	//Delete the element from the begining, call the function to Solve Task 3





}