#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "TreeNode.h"
#include "OrgTree.h"

using namespace std;


OrgTree::OrgTree() {
	this->size = 0;
	this->root = TREENULLPTR;
}


OrgTree::~OrgTree() {
	if (this->root) {
		delete root;
	}
}


bool OrgTree::parseLineFromFile(string& inputLine, string& title, string& name) {
	// Removing call to find_and_replace because it runs in T(n^2) time which is not acceptable.
	// find_and_replace(inputLine, ", ", ",");
	istringstream iss(inputLine);

	title = "";
	name = "";

	getline(iss, title, ',');
	iss.ignore(1); // Ignore the space character.
	getline(iss, name, ',');

	if (title == "") {
		return false;
	}
	else if (name == "") {
		return false;
	}

	return true;
}


void OrgTree::addRoot(string title, string name) {
	TreeNode* newRoot = new TreeNode(title, name);

	// Only set the leftmost child of the new TreeNode if we already have a root.
	if (this->root) {
		this->root->setParent(newRoot);
		newRoot->setLeftChild(this->root);
	}

	this->size++;
	this->root = newRoot;
}


TREENODEPTR OrgTree::getRoot() {
	return this->root;
}


void OrgTree::setRoot(TREENODEPTR newRoot) {
	this->root = newRoot;
}

TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node) {
	return node->getLeftChild();
}


TREENODEPTR OrgTree::rightSibling(TREENODEPTR node) {
	return node->getRightSibling();
}


TREENODEPTR OrgTree::find(string title) {
	return this->root->find(title);
}


void OrgTree::hire(TREENODEPTR employer, string newTitle, string newName) {
	TREENODEPTR newNode = new TreeNode(newTitle, newName);
	employer->appendChild(newNode);
	this->size++;
}


void OrgTree::hire(TREENODEPTR employer, TREENODEPTR employee) {
	employer->appendChild(employee);
	this->size++;
}


bool OrgTree::fire(string formerTitle) {
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

	childToFire->getParent()->fireChild(childToFire);
	this->size--;
	return true;
}


bool OrgTree::read(string filename) {
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

	// This parses out the line and sets the proper stuff into title and name.
	// Returns false if it fails.
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


void OrgTree::write(string filename) {
	ofstream outputFile(filename);

	if (!outputFile.is_open()) {
		// We couldn't open the file for some reason.
		// Not sure what to do in this case.
		return;
	}

	string outputData = this->root->outputTree();
	outputFile << outputData;
}


unsigned int OrgTree::getSize() {
	return this->size;
}


void OrgTree::printSubTree(TREENODEPTR subTreeRoot) {
	subTreeRoot->printTree("", cout);
}


void OrgTree::printSubTree(TREENODEPTR subTreeRoot, ostream& os) {
	subTreeRoot->printTree("", os);
}
