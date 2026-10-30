// Heap Object class, min heap stored in a vector so the smallest value is always at the root
// methods- insert element, remove root, search element, modify element, print heap
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include "DataStructure.h"

class Heap : public DataStructure {
public:
	std::vector<std::string> items;

	std::string typeName() override { return "Heap"; }
	int size() override { return (int)items.size(); }
	bool canEdit() override { return true; }

	void add(std::string data) override {
		items.push_back(data);
		siftUp((int)items.size() - 1);
	}

	//remove the root, data isn't used because a heap can only remove its root
	bool remove(std::string data) override {
		if (items.empty()) {
			return false;
		}
		std::cout << "Removed root " << items[0] << "\n";
		items[0] = items.back();
		items.pop_back();
		siftDown(0);
		return true;
	}

	bool search(std::string data) override {
		return indexOf(data) != -1;
	}

	//change the value then move it to wherever it belongs now
	bool edit(std::string oldData, std::string newData) override {
		int i = indexOf(oldData);
		if (i == -1) {
			return false;
		}
		items[i] = newData;
		siftUp(i);
		siftDown(i);
		return true;
	}

	void view() override {
		if (items.empty()) {
			std::cout << "Empty Heap\n";
			return;
		}
		std::cout << "Array: [ ";
		for (int i = 0; i < items.size(); i++) {
			std::cout << items[i] << " ";
		}
		std::cout << "]\n";
		std::cout << "Tree:\n" << items[0] << "\n";
		printChildren(0, "");
	}

private:
	int indexOf(std::string data) {
		for (int i = 0; i < items.size(); i++) {
			if (items[i] == data) {
				return i;
			}
		}
		return -1;
	}

	//swap with the parent until the parent is no bigger
	void siftUp(int i) {
		while (i > 0) {
			int parent = (i - 1) / 2;
			if (!valueLess(items[i], items[parent])) {
				return;
			}
			std::swap(items[i], items[parent]);
			i = parent;
		}
	}

	//swap with the smaller child until neither child is smaller
	void siftDown(int i) {
		int count = (int)items.size();
		while (true) {
			int left = 2 * i + 1;
			int right = 2 * i + 2;
			int smallest = i;

			if (left < count && valueLess(items[left], items[smallest])) {
				smallest = left;
			}
			if (right < count && valueLess(items[right], items[smallest])) {
				smallest = right;
			}
			if (smallest == i) {
				return;
			}
			std::swap(items[i], items[smallest]);
			i = smallest;
		}
	}

	void printChildren(int i, std::string prefix) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int count = (int)items.size();

		if (left < count) {
			bool hasRight = right < count;
			std::cout << prefix << (hasRight ? "|-- " : "`-- ") << items[left] << "\n";
			printChildren(left, prefix + (hasRight ? "|   " : "    "));
		}
		if (right < count) {
			std::cout << prefix << "`-- " << items[right] << "\n";
			printChildren(right, prefix + "    ");
		}
	}
};
