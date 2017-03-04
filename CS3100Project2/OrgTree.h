#pragma once
#include <string>
#include <iostream>
#include "TreeNode.h"

#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL


using namespace std;


class OrgTree
{
public:
	TREENODEPTR root;

	OrgTree()
	{
		this->root = TREENULLPTR;
	}

	~OrgTree()
	{
		if (this->root) {
			delete root;
		}
	}

	void addRoot(string title, string name) {
		TreeNode* newRoot = new TreeNode(title, name);
	
		// Only set the leftmost child of the new TreeNode if we already have a root.
		if (this->root) {
			this->root->setParent(newRoot);
			newRoot->setLeftChild(this->root);
		}

		this->root = newRoot;
	}

	TREENODEPTR getRoot() {
		return this->root;
	}

	TREENODEPTR leftmostChild(TREENODEPTR node) {
		return node->getLeftChild();
	}

	TREENODEPTR rightSibling(TREENODEPTR node) {
		return node->getRightSibling();
	}

	TREENODEPTR find(string title) {
		return this->root->find(title);
	}

	void hire(TREENODEPTR employer, string newTitle, string newName) {
		TREENODEPTR newNode = new TreeNode(newTitle, newName);
		employer->appendChild(newNode);
	}

	bool fire(string formerTitle) {
		if (this->root == TREENULLPTR) {
			// Can't fire anybody if there isn't even a root node
			return false;
		}

		if (formerTitle == this->root->getTitle()) {
			// Disallow firing the root node
			return false;
		}

		TreeNode* childToFire = this->find(formerTitle);
		childToFire->parent->fireChild(childToFire);
		return true;
	}

	bool read(string filename) {
		return false;
	}

	void write(string filename) {
	}

	unsigned int getSize() {
		return 0;
	}

	void printSubTree(TREENODEPTR subTreeRoot) {
		cout << "";
	}
};

