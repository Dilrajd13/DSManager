// LinkedList Object class
// methods- create new Linked List, add element, delete element, search element, print linked list,modify element
#pragma once
#include <string>
#include <iostream>
class Node {
public:
	 std::string data;
	 Node* next;


	 Node() {
		 data = ""; 
		 next = NULL;
	 }

	 Node(std::string data) {
		 this->data = data;
		 this->next = NULL;
	 }
};

class LinkedList {
public:
	Node* head;
	Node* tail;
	int Listsize = 0;

	LinkedList() {
		head = NULL;
		tail = NULL;
		std::cout << "New List Made!";
	}

	
	//insert node at the head
	void insertNodeHead(std::string data) {

		//create new node object
		Node* toAdd = new Node(data);

		if (head == NULL) {
			head=toAdd;
			tail = toAdd;
			Listsize++;
			return;
		}
		toAdd->next = this->head;
		this->head = toAdd;

		Listsize++;


	}
	void insertNodeTail(std::string data) {
		Node* toAdd = new Node(data);

		if (head == NULL) {
			head=toAdd;
			tail=toAdd;
			Listsize++;
			return;
		}

		toAdd->next = NULL;
		tail->next = toAdd;
		this->tail = toAdd;

		Listsize++;
	}

	void printLL() {
		Node* temp = head;
		if (temp == NULL) {
			std::cout << "Empty Linked List\n";
			return;
		}
		while (temp != NULL) {
			
			std::cout << temp->data;
			if (Listsize > 1 && temp->next!=NULL) {
				std::cout << "-->";
			}
			temp = temp->next;
		}

		std::cout << "-->NULL\n";

	}









	//delete

	//print







};