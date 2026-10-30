// LinkedList Object class
// methods- create new Linked List, add element, delete element, search element, print linked list,modify element
#pragma once
#include <string>
#include <iostream>
#include "DataStructure.h"

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

class LinkedList : public DataStructure {
public:
	Node* head;
	Node* tail;
	int Listsize = 0;

	LinkedList() {
		head = NULL;
		tail = NULL;
	}

	~LinkedList() {
		Node* temp = head;
		while (temp != NULL) {
			Node* next = temp->next;
			delete temp;
			temp = next;
		}
	}

	std::string typeName() override { return "LinkedList"; }
	int size() override { return Listsize; }
	void add(std::string data) override { insertNodeTail(data); }
	void view() override { printLL(); }
	bool removeNeedsValue() override { return true; }
	bool canEdit() override { return true; }


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

	//replace the first node holding oldData with newData
	bool edit(std::string oldData, std::string newData) override {
		Node* temp = head;
		while (temp != NULL) {
			if (temp->data == oldData) {
				temp->data = newData;
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	//return true if any node holds data, otherwise false
	bool search(std::string data) override {
		Node* temp = head;
		while (temp != NULL) {
			if (temp->data == data) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	//delete the first node holding data and return true, return false if it isn't in the list
	bool remove(std::string data) override {
		Node* previous = NULL;
		Node* temp = head;

		//walk the list until temp is the node to delete, previous stays one node behind it
		while (temp != NULL && temp->data != data) {
			previous = temp;
			temp = temp->next;
		}

		if (temp == NULL) {
			return false;
		}

		//unlink the node, if there is no previous node then it was the head
		if (previous == NULL) {
			head = temp->next;
		}
		else {
			previous->next = temp->next;
		}

		//if it was the last node then the node before it is the new tail
		if (temp == tail) {
			tail = previous;
		}

		delete temp;
		Listsize--;
		return true;
	}

};
