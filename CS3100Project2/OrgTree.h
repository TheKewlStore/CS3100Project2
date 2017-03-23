#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TreeNode.h"

#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL

/*  This OrgTree uses a binaryized tree of TreeNodes.

	Implementation of nodes in the tree are contained in the TreeNode class.
*/

using namespace std;


/*  Represent a single general tree of the hierarchy of an organization.

	Nodes in the tree represent an employee with a name and title.
*/
class OrgTree
{
private:
	TREENODEPTR root;
	int size;

	/*  Helper function for reading from a file.

		Parse name and title information from a single line of the file.

		Return false if either the title or name could not be read properly.

		Worst-case asymptotic run-time: T(1)
		Best-case asymptotic run-time: T(1)
	*/
	bool parseLineFromFile(string& inputLine, string& title, string& name);

public:
	/*  OrgTree constructor, set the root pointer to null and initialize size to 0.

		Worst-case asymptotic run-time: T(1)
		Best-case asymptotic run-time: T(1)
	*/
	OrgTree();

	/*  OrgTree destructor, release all memory allocation for TreeNode pointers for this OrgTree.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	~OrgTree();

	void addRoot(string title, string name);

	TREENODEPTR getRoot();
	TREENODEPTR leftmostChild(TREENODEPTR node);
	TREENODEPTR rightSibling(TREENODEPTR node);

	void setRoot(TREENODEPTR newRoot);

	/*  Find a TreeNode in our OrgTree with the given title.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	TREENODEPTR find(string title);

	/*  Hire a new employee under employer, adding it to our OrgTree as necessary.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	void hire(TREENODEPTR employer, string newTitle, string newName);

	/*  Helper overload of hire that uses an existing TreeNode object.

		This is mostly used in my test harness for thoroughness.

		Worst-case asymptotic run-time: T(1)
		Best-case asymptotic run-time: T(1)
	*/
	void hire(TREENODEPTR employer, TREENODEPTR employee);

	/*  Fire an employee with the given title from the OrgTree, moving any of his children up one.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	bool fire(string formerTitle);

	/*  Read in a string representation of the current tree from the given filename, and construct an OrgTree from it.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	bool read(string filename);

	/*  Write a string representation of the current tree to the given filename.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	void write(string filename);

	/*  Return the current size (i.e the number of nodes) of the current tree.

		Worst-case asymptotic run-time: T(1)
		Best-case asymptotic run-time: T(1)
	*/
	unsigned int getSize();

	/*  Print a string representation of the given sub tree root node to cout.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	void printSubTree(TREENODEPTR subTreeRoot);

	/*  Print a string representation of the given sub tree root node to the given output stream.

		Worst-case asymptotic run-time: T(n)
		Best-case asymptotic run-time: T(1)
	*/
	void printSubTree(TREENODEPTR subTreeRoot, ostream& os);
};
