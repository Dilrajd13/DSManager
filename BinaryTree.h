// BinaryTree Object class, binary search tree so smaller values go left and bigger values go right
// methods- insert element, delete element, search element, modify element, print tree
#pragma once
#include <string>
#include <iostream>
#include "DataStructure.h"

class TreeNode {
public:
	std::string data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(std::string data) {
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
};

class BinaryTree : public DataStructure {
public:
	TreeNode* root;
	int Treesize = 0;

	BinaryTree() {
		root = NULL;
	}

	~BinaryTree() {
		deleteAll(root);
	}

	std::string typeName() override { return "BinaryTree"; }
	int size() override { return Treesize; }
	bool removeNeedsValue() override { return true; }
	bool canEdit() override { return true; }

	//duplicates are ignored since each value has one spot in the tree
	void add(std::string data) override {
		if (search(data)) {
			std::cout << data << " is already in the tree\n";
			return;
		}
		root = insertNode(root, data);
		Treesize++;
	}

	bool remove(std::string data) override {
		if (!search(data)) {
			return false;
		}
		root = deleteNode(root, data);
		Treesize--;
		return true;
	}

	bool search(std::string data) override {
		TreeNode* temp = root;
		while (temp != NULL) {
			if (temp->data == data) {
				return true;
			}
			temp = valueLess(data, temp->data) ? temp->left : temp->right;
		}
		return false;
	}

	//the new value may belong somewhere else so remove the old one and insert again
	bool edit(std::string oldData, std::string newData) override {
		if (!search(oldData)) {
			return false;
		}
		if (search(newData)) {
			std::cout << newData << " is already in the tree\n";
			return false;
		}
		remove(oldData);
		add(newData);
		return true;
	}

	void view() override {
		if (root == NULL) {
			std::cout << "Empty Binary Tree\n";
			return;
		}
		std::cout << root->data << "\n";
		printChildren(root, "");
		std::cout << "In order: ";
		printInOrder(root);
		std::cout << "\n";
	}

private:
	TreeNode* insertNode(TreeNode* node, std::string data) {
		if (node == NULL) {
			return new TreeNode(data);
		}
		if (valueLess(data, node->data)) {
			node->left = insertNode(node->left, data);
		}
		else {
			node->right = insertNode(node->right, data);
		}
		return node;
	}

	TreeNode* deleteNode(TreeNode* node, std::string data) {
		if (node == NULL) {
			return NULL;
		}
		if (data != node->data) {
			if (valueLess(data, node->data)) {
				node->left = deleteNode(node->left, data);
			}
			else {
				node->right = deleteNode(node->right, data);
			}
			return node;
		}

		//zero or one child, the child takes this node's place
		if (node->left == NULL || node->right == NULL) {
			TreeNode* child = (node->left != NULL) ? node->left : node->right;
			delete node;
			return child;
		}

		//two children, copy in the next biggest value then delete it from the right side
		TreeNode* next = node->right;
		while (next->left != NULL) {
			next = next->left;
		}
		node->data = next->data;
		node->right = deleteNode(node->right, next->data);
		return node;
	}

	void deleteAll(TreeNode* node) {
		if (node == NULL) {
			return;
		}
		deleteAll(node->left);
		deleteAll(node->right);
		delete node;
	}

	void printChildren(TreeNode* node, std::string prefix) {
		if (node->left != NULL) {
			bool hasRight = node->right != NULL;
			std::cout << prefix << (hasRight ? "|-- " : "`-- ") << "L: " << node->left->data << "\n";
			printChildren(node->left, prefix + (hasRight ? "|   " : "    "));
		}
		if (node->right != NULL) {
			std::cout << prefix << "`-- " << "R: " << node->right->data << "\n";
			printChildren(node->right, prefix + "    ");
		}
	}

	void printInOrder(TreeNode* node) {
		if (node == NULL) {
			return;
		}
		printInOrder(node->left);
		std::cout << node->data << " ";
		printInOrder(node->right);
	}
};
