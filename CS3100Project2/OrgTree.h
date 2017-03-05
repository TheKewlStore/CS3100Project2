#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TreeNode.h"

#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL


using namespace std;


class OrgTree
{
private:
	void find_and_replace(string& source, const string& find, const string& replace) {
		for (string::size_type i = source.find(find, 0); i != string::npos; i = source.find(find, i)) {
			source.replace(i, find.length(), replace);
			i += replace.length();
		}
	}

	bool parseLineFromFile(string& inputLine, string& title, string& name) {
		find_and_replace(inputLine, ", ", ",");
		istringstream iss(inputLine);
		
		title = "";
		name = "";

		getline(iss, title, ',');
		getline(iss, name, ',');

		if (title == "") {
			return false;
		}
		else if (name == "") {
			return false;
		}

		return true;
	}

public:
	TREENODEPTR root;
	int size;

	OrgTree()
	{
		this->size = 0;
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

		this->size++;
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
		this->size++;
	}

	void hire(TREENODEPTR employer, TREENODEPTR employee) {
		employer->appendChild(employee);
		this->size++;
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

		if (childToFire == NULL) {
			return false;
		}

		childToFire->parent->fireChild(childToFire);
		this->size--;
		return true;
	}

	bool read(string filename) {
		ifstream infile(filename);
		if (!infile.good()) {
			// The file doesn't exist.
			return false;
		}

		string line;
		string title;
		string name;

		bool complete = false;

		getline(infile, line);

		if (line.empty()) {
			return false;
		}

		if (!this->parseLineFromFile(line, title, name)) {
			return false;
		}

		this->addRoot(title, name);
		TreeNode* currentRoot = this->root;

		while (getline(infile, line)) {
			if (complete) {
				// We've determined that the tree has ended, but there is still data in the file!
				delete this->root;
				return false;
			}
			if (line == ")") {
				if (currentRoot == this->root) {
					// We're back at the root node, so we're done with the tree.
					// Don't return right away, continue on to see if there are any other lines in the file
					// in which case the format is invalid.
					complete = true;
					continue;
				}

				currentRoot = currentRoot->getParent();
				continue;
			}

			if (!this->parseLineFromFile(line, title, name)) {
				// We couldn't parse this line of input, meaning the file is formatted incorrectly.
				delete this->root;
				return false;
			}

			TreeNode* newTreeNode = new TreeNode(title, name);
			this->hire(currentRoot, newTreeNode);
			currentRoot = newTreeNode;
		}

		return complete;
	}

	void write(string filename) {
		ofstream outputFile(filename);

		if (!outputFile.is_open()) {
			// We couldn't open the file for some reason.
			// Not sure what to do in this case.
			return;
		}

		string outputData = this->root->outputTree();
		outputFile << outputData;
	}

	unsigned int getSize() {
		return this->size;
	}

	void printSubTree(TREENODEPTR subTreeRoot) {
		subTreeRoot->printTree("", cout);
	}

	void printSubTree(TREENODEPTR subTreeRoot, ostream& os) {
		subTreeRoot->printTree("", os);
	}
};
