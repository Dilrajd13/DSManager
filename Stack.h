// Stack Object class, last in first out
// methods- push element, pop element, search element, print stack
#pragma once
#include <string>
#include <iostream>
#include "DataStructure.h"
#include "LinkedList.h"

class Stack : public DataStructure {
public:
	Node* top;
	int Stacksize = 0;

	Stack() {
		top = NULL;
	}

	~Stack() {
		while (top != NULL) {
			Node* next = top->next;
			delete top;
			top = next;
		}
	}

	std::string typeName() override { return "Stack"; }
	int size() override { return Stacksize; }

	//push onto the top
	void add(std::string data) override {
		Node* toAdd = new Node(data);
		toAdd->next = top;
		top = toAdd;
		Stacksize++;
	}

	//pop off the top, data isn't used because a stack can only remove its top
	bool remove(std::string data) override {
		if (top == NULL) {
			return false;
		}
		Node* toDelete = top;
		std::cout << "Popped " << toDelete->data << "\n";
		top = top->next;
		delete toDelete;
		Stacksize--;
		return true;
	}

	bool search(std::string data) override {
		Node* temp = top;
		while (temp != NULL) {
			if (temp->data == data) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	void view() override {
		if (top == NULL) {
			std::cout << "Empty Stack\n";
			return;
		}
		Node* temp = top;
		std::cout << "TOP\n";
		while (temp != NULL) {
			std::cout << "| " << temp->data << "\n";
			temp = temp->next;
		}
		std::cout << "BOTTOM\n";
	}
};
