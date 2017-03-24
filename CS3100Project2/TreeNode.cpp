#include "stdafx.h"
#include <string>
#include <iostream>
#include "TreeNode.h"


TreeNode::TreeNode() {
	this->title = "";
	this->name = "";
	this->parent = NULL;
	this->rightSibling = NULL;
	this->leftChild = NULL;
}

TreeNode::TreeNode(string title, string name) {
	TreeNode();
	this->title = title;
	this->name = name;
}

string TreeNode::getTitle() {
	return this->title;
}

string TreeNode::getName() {
	return this->name;
}

TreeNode* TreeNode::getParent() {
	return this->parent;
}

TreeNode* TreeNode::getRightSibling() {
	return this->rightSibling;
}

TreeNode* TreeNode::getLeftChild() {
	return this->leftChild;
}

void TreeNode::setParent(TreeNode* newParent) {
	this->parent = newParent;
}

void TreeNode::setRightSibling(TreeNode* newSibling) {
	this->rightSibling = newSibling;
}

void TreeNode::setLeftChild(TreeNode* newChild) {
	this->leftChild = newChild;
}

TreeNode* TreeNode::getLastChild() {
	if (!this->leftChild) {
		return NULL;
	}

	// Keep a reference to the current child node and the next one.
	TreeNode* currentChild = this->leftChild;
	TreeNode* nextChild = this->leftChild->getRightSibling();

	while (nextChild) {
		// Loop through, incrementing current and next child until next child is equal to null.
		// Then return currentChild.
		currentChild = nextChild;
		nextChild = nextChild->getRightSibling();
	}

	return currentChild;
}

void TreeNode::appendChild(TreeNode* newChild) {
	// T(n) <- worst
	TreeNode* currentLastChild = this->getLastChild();

	if (!currentLastChild) {
		// If we don't have a child yet, we need to set it as our left, not as a right sibling.
		this->setLeftChild(newChild);
	}
	else {
		// We have at least one child, so just point the last child to this new one.
		currentLastChild->setRightSibling(newChild);
	}

	// Set the parent pointer to ourselves for the new node.
	newChild->setParent(this);
}

TreeNode* TreeNode::find(string title) {
	if (this->title == title) {
		return this;
	}

	if (this->rightSibling) {
		// If we're not the node, and we have a sibling, we'll tell them to check themselves and their children/sibling.
		// If they find it, return it, otherwise we'll check our children and give up if we don't find it.
		TreeNode* theirNode = this->rightSibling->find(title);

		if (theirNode) {
			return theirNode;
		}

	}

	if (this->leftChild) {
		return this->leftChild->find(title);
	}

	return NULL;
}

TreeNode* TreeNode::findLeftSibling() {
	if (!this->parent) {
		// We don't have a parent, so no way we have a left sibling.
		return NULL;
	}

	if (this->parent->getLeftChild() == this) {
		// We're the left child, so we can't have a left sibling.
		return NULL;
	}

	TreeNode* currentChild = this->parent->getLeftChild();

	if (!currentChild) {
		// Somehow our parent doesn't have a left child. 
		// Not sure that this check is worth it, but i'd rather not find out.
		return NULL;
	}

	TreeNode* nextChild = currentChild->getRightSibling();

	while (nextChild && nextChild != this) {
		// Keep a reference to the currentChild, which will be used as a reference to our
		// leftSibling, and check the rightSibling to see if it is us.
		// If it is, currentChild will be our leftSibling.
		currentChild = nextChild;
		nextChild = nextChild->getRightSibling();
	}

	if (nextChild == NULL) {
		// Somehow we're not in the sibling chain?
		// Again, not something that should ever happen, but let's play it safe 
		// and err on the side of less weird behavior of returning an incorrect node.
		return NULL;
	}

	return currentChild;
}

void TreeNode::fireChild(TreeNode* child) {
	// T(n) <- Worst
	TreeNode* leftSibling = child->findLeftSibling();
	// T(1)
	TreeNode* rightSibling = child->getRightSibling();

	if (leftSibling) {
		// This guy has a right sibling, so we have to link that up directly to what his left sibling was.
		// If he had a left sibling, we need to change the left sibling's rightSibling pointer to the guys right sibling
		// since he's moving on to bigger and better things (the unemployment line).
		// We don't check to see if rightSibling is a null pointer because we want to set the left sibling
		// to null if there isn't a right sibling anyway.
		// T(1)
		leftSibling->setRightSibling(rightSibling);
	}
	else {
		// If he was our leftmost child, update our leftmost child pointer to be his old right sibling.
		// We don't check to see if rightSibling is a null pointer because we want to set our left child
		// to null if there isn't a right sibling anyway.
		// T(1)
		this->setLeftChild(rightSibling);
	}

	// Add on all of the child's previous children as employees directly under me.
	// We didn't need him anyway.
	// T(1)
	TreeNode* hisChild = child->getLeftChild();

	if (hisChild) {
		// T(1)
		this->appendChild(hisChild);
	}

	// Clear up the memory reference for the child we just fired.
	// Set all of his pointers to null first, so we don't end up trying to delete his previous nodes.
	child->setParent(nullptr);
	child->setLeftChild(nullptr);
	child->setRightSibling(nullptr);
	delete child;
}

string TreeNode::formatString() {
	return this->title + ", " + this->name + "\n";
}

void TreeNode::printTree(string currentIndentation, ostream& os) {
	os << currentIndentation << this->title << ": " << this->name << "\n";

	if (this->leftChild) {
		string childIndentation = currentIndentation + "    ";
		this->leftChild->printTree(childIndentation, os);
	}

	if (this->rightSibling) {
		this->rightSibling->printTree(currentIndentation, os);
	}
}

string TreeNode::outputTree() {
	string outputData = this->formatString();

	if (this->leftChild) {
		outputData += this->leftChild->outputTree();
	}

	if (this->rightSibling) {
		outputData += ")\n";
		outputData += this->rightSibling->outputTree();
	}
	else {
		outputData += ")\n";
	}

	return outputData;
}

TreeNode::~TreeNode() {
	if (this->parent) {
		// I don't think we should delete our parent, it should delete us?
		// delete this->parent;
	}

	if (this->leftChild) {
		// Recursive destructor, T(n) <- worst
		delete this->leftChild;
	}

	if (this->rightSibling) {
		// Recursive destructor, T(n)
		delete this->rightSibling;
	}
}