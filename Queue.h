// Queue Object class, first in first out
// methods- enqueue element, dequeue element, search element, print queue
#pragma once
#include <string>
#include <iostream>
#include "DataStructure.h"
#include "LinkedList.h"

class Queue : public DataStructure {
public:
	Node* front;
	Node* back;
	int Queuesize = 0;

	Queue() {
		front = NULL;
		back = NULL;
	}

	~Queue() {
		while (front != NULL) {
			Node* next = front->next;
			delete front;
			front = next;
		}
	}

	std::string typeName() override { return "Queue"; }
	int size() override { return Queuesize; }

	//enqueue at the back
	void add(std::string data) override {
		Node* toAdd = new Node(data);
		if (back == NULL) {
			front = toAdd;
			back = toAdd;
		}
		else {
			back->next = toAdd;
			back = toAdd;
		}
		Queuesize++;
	}

	//dequeue from the front, data isn't used because a queue can only remove its front
	bool remove(std::string data) override {
		if (front == NULL) {
			return false;
		}
		Node* toDelete = front;
		std::cout << "Dequeued " << toDelete->data << "\n";
		front = front->next;
		if (front == NULL) {
			back = NULL;
		}
		delete toDelete;
		Queuesize--;
		return true;
	}

	bool search(std::string data) override {
		Node* temp = front;
		while (temp != NULL) {
			if (temp->data == data) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	void view() override {
		if (front == NULL) {
			std::cout << "Empty Queue\n";
			return;
		}
		std::cout << "FRONT -> ";
		Node* temp = front;
		while (temp != NULL) {
			std::cout << "[" << temp->data << "] ";
			temp = temp->next;
		}
		std::cout << "<- BACK\n";
	}
};
