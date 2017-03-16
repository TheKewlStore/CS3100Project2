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

		Worst-case asymptotic run-time: T(1)
		Best-case asymptotic run-time: T(1)
	*/
	TreeNode();

	/*  Basic constructor taking the title and name of the new TreeNode.
		Sets pointers to parent, child and sibling to null.

		Worst-case asymptotic run-time: T(1)
		Best-case asymptotic run-time: T(1)
	*/
	TreeNode(string title, string name);

	string getTitle();
	string getName();

	TreeNode* getParent();
	TreeNode* getRightSibling();
	TreeNode* getLeftChild();

	void setParent(TreeNode* newParent);
	void setRightSibling(TreeNode* newSibling);
	void setLeftChild(TreeNode* newChild);

	/*  Follow the linked list of my children, and return the last active TreeNode in the children chain.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	TreeNode* getLastChild();

	/*  Append a TreeNode at the end of my linked list of children.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	void appendChild(TreeNode* newChild);

	/*  Find a given title in this TreeNode's subtree, returning a pointer to a matching node.

		Returns TREENULLPTR if the title was not found.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	TreeNode* find(string title);

	/*  Find this TreeNode's left sibling by iterating through the parent's children linked list.

		Since we don't keep track of our left sibling as an instance variable, 
		we have to iterate through the right sibling chain to find ourselves, keeping a reference to the previous node.

		Returns null if this TreeNode has no parent, is the left child, 
		or if we're somehow not in the sibling chain (should not happen).

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	TreeNode* findLeftSibling();

	/*  Fire a given TreeNode who is a child of us, and move all of his children up to be siblings of us.
		
		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	void fireChild(TreeNode* child);

	/*  Print a human-readable representation of this tree.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	void printTree(string currentIndentation, ostream& os);

	/*  Helper function to return a string representation of this TreeNode object.

		Worst-case asymptotic run-time: T(1)
		Best-case asymptotic run-time: T(1)
	*/
	string formatString();

	/*  Create a string representation of the complete subtree that this TreeNode points to.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	string outputTree();

	/*  TreeNode Destructor, free up all the pointers.

		This is recursive, which seems to work fine currently, but I'm not positive this isn't an issue.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	~TreeNode();
};

