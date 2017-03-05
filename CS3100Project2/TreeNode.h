#pragma once
#include <string>
#include <iostream>

using namespace std;

class TreeNode
{
public:
	string title;
	string name;
	TreeNode* parent;
	TreeNode* rightSibling;
	TreeNode* leftChild;

	TreeNode() {
		this->title = "";
		this->name = "";
		this->parent = NULL;
		this->rightSibling = NULL;
		this->leftChild = NULL;
	}

	TreeNode(string title, string name) {
		TreeNode();
		this->title = title;
		this->name = name;
	}

	string getTitle() {
		return this->title;
	}

	string getName() {
		return this->name;
	}

	TreeNode* getParent() {
		return this->parent;
	}

	void setParent(TreeNode* newParent) {
		this->parent = newParent;
	}

	TreeNode* getRightSibling() {
		return this->rightSibling;
	}

	void setRightSibling(TreeNode* newSibling) {
		this->rightSibling = newSibling;
	}

	TreeNode* getLeftChild() {
		return this->leftChild;
	}

	TreeNode* getLastChild() {
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

	void appendChild(TreeNode* newChild) {
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

	void setLeftChild(TreeNode* newChild) {
		this->leftChild = newChild;
	}

	TreeNode* find(string title) {
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

	TreeNode* findLeftSibling() {
		if (!this->parent) {
			return NULL;
		}

		if (this->parent->getLeftChild() == this) {
			return NULL;
		}

		TreeNode* currentChild = this->parent->getLeftChild();
		if (!currentChild) {
			return NULL;
		}

		TreeNode* nextChild = currentChild->getRightSibling();

		while (nextChild && nextChild != this) {
			currentChild = nextChild;
			nextChild = nextChild->getRightSibling();
		}

		return currentChild;
	}

	void fireChild(TreeNode* child) {
		TreeNode* leftSibling = child->findLeftSibling();
		TreeNode* rightSibling = child->getRightSibling();

		if (leftSibling) {
			// This guy has a right sibling, so we have to link that up directly to what his left sibling was.
			// If he had a left sibling, we need to change the left sibling's rightSibling pointer to the guys right sibling
			// since he's moving on to bigger and better things (the unemployment line).
			// We don't check to see if rightSibling is a nullt pointer because we want to set the left sibling
			// to null if there isn't a right sibling anyway.
			leftSibling->setRightSibling(rightSibling);
		}
		else {
			// If he was our leftmost child, update our leftmost child pointer to be his old right sibling.
			// We don't check to see if rightSibling is a null pointer because we want to set our left child
			// to null if there isn't a right sibling anyway.
			this->setLeftChild(rightSibling);
		}

		// Add on all of the child's previous children as employees directly under me.
		// We didn't need him anyway.
		TreeNode* hisChild = child->getLeftChild();

		if (hisChild) {
			this->appendChild(hisChild);
		}
	}

	string formatString() {
		return this->title + ", " + this->name + "\n";
	}

	void printTree(string currentIndentation, ostream& os) {
		os << currentIndentation << this->title << ": " << this->name << "\n";

		if (this->leftChild) {
			string childIndentation = currentIndentation + "    ";
			this->leftChild->printTree(childIndentation, os);
		}

		if (this->rightSibling) {
			this->rightSibling->printTree(currentIndentation, os);
		}
	}

	string outputTree() {
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

	~TreeNode() {
		if (this->parent) {
			// I don't think we should delete our parent, it should delete us?
			// delete this->parent;
		}

		if (this->leftChild) {
			delete this->leftChild;
		}

		if (this->rightSibling) {
			delete this->rightSibling;
		}
	}
};

