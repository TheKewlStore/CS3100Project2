#pragma once
#include <string>
#include <iostream>

using namespace std;


/*  Represent a single TreeNode of an OrgTree, which contains information about itself, 
	and its relation to its parent, sibling and child.

	Worst-case timing information (Best-case included in docstring of individual functions):
	getLastChild(): T(n)
	appendChild(): T(n)
	find(string): T(n)
	findLeftSibling(): T(n)
	fireChild(TreeNode): T(n)
	~TreeNode(): T(n)

	TreeNode(): T(1)
	TreeNode(string, string): T(1)

	getTitle(): T(1)
	getName(): T(1)
	getParent(): T(1)
	getRightSibling(TreeNode*): T(1)

	setParent(): T(1)
	setLeftChild(): T(1)
	setRightSibling(TreeNode*): T(1)
	getLeftChild(): T(1)
*/
class TreeNode
{
public:
	string title;
	string name;

	TreeNode* parent;
	TreeNode* rightSibling;
	TreeNode* leftChild;

	/*  Empty constructor.
		Set all instance variables to null or empty string.
	*/
	TreeNode() {
		this->title = "";
		this->name = "";
		this->parent = NULL;
		this->rightSibling = NULL;
		this->leftChild = NULL;
	}

	/*  Basic constructor taking the title and name of the new TreeNode.
		Sets pointers to parent, child and sibling to null.
	*/
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

	/*  Follow the linked list of my children, and return the last active TreeNode in the children chain.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	TreeNode* getLastChild() {
		if (this->leftChild == NULL) {
			return NULL;
		}

		// Keep a reference to the current child node and the next one.
		TreeNode* currentChild = this->leftChild;
		TreeNode* nextChild = this->leftChild->getRightSibling();

		while (nextChild != NULL) {
			// Loop through, incrementing current and next child until next child is equal to null.
			// Then return currentChild.
			currentChild = nextChild;
			nextChild = nextChild->getRightSibling();
		}

		return currentChild;
	}

	void setLeftChild(TreeNode* newChild) {
		this->leftChild = newChild;
	}

	/*  Append a TreeNode at the end of my linked list of children.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	void appendChild(TreeNode* newChild) {
		// T(n) <- worst
		TreeNode* currentLastChild = this->getLastChild();

		if (currentLastChild == NULL) {
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

	/*  Find a given title in this TreeNode's subtree, returning a pointer to a matching node.

		Returns TREENULLPTR if the title was not found.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
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

	/*  Find this TreeNode's left sibling by iterating through the parent's children linked list.

		Since we don't keep track of our left sibling as an instance variable, 
		we have to iterate through the right sibling chain to find ourselves, keeping a reference to the previous node.

		Returns null if this TreeNode has no parent, is the left child, 
		or if we're somehow not in the sibling chain (should not happen).

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	TreeNode* findLeftSibling() {
		if (this->parent == NULL) {
			// We don't have a parent, so no way we have a left sibling.
			return NULL;
		}

		if (this->parent->getLeftChild() == this) {
			// We're the left child, so we can't have a left sibling.
			return NULL;
		}

		TreeNode* currentChild = this->parent->getLeftChild();

		if (currentChild == NULL) {
			// Somehow our parent doesn't have a left child. 
			// Not sure that this check is worth it, but i'd rather not find out.
			return NULL;
		}

		TreeNode* nextChild = currentChild->getRightSibling();

		while (nextChild != NULL && nextChild != this) {
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

	/*  Fire a given TreeNode who is a child of us, and move all of his children up to be siblings of us.
		
		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	void fireChild(TreeNode* child) {
		// T(n) <- Worst
		TreeNode* leftSibling = child->findLeftSibling();
		// T(1)
		TreeNode* rightSibling = child->getRightSibling();

		if (leftSibling != NULL) {
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

		if (hisChild != NULL) {
			// T(1)
			this->appendChild(hisChild);
		}
	}

	/*  TreeNode Destructor, free up all the pointers.

		This is recursive, which seems to work fine currently, but I'm not positive this isn't an issue.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	~TreeNode() {
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
};

