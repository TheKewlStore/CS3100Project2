// CS3100Project2.cpp : Defines the entry point for the console application.
//
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "OrgTree.h"

using namespace std;


TREENODEPTR president;
TREENODEPTR vpSales;
TREENODEPTR directorPR;
TREENODEPTR directorMarketing;
TREENODEPTR digitalMediaSpecialist;
TREENODEPTR headTVPrintAdvertising;
TREENODEPTR vpOperations;
TREENODEPTR vpSoftwareDevelopment;
TREENODEPTR cloudDevelopment;
TREENODEPTR magicBagLeader;
TREENODEPTR softwareEngineerI;
TREENODEPTR softwareEngineerII;


void setupTree(OrgTree& tree) {
	president = new TreeNode("President", "George Orwell");
	vpSales = new TreeNode("VP Sales", "Mark Zuckerberg");
	directorPR = new TreeNode("Director of Public Relations", "Kurt Vonnegut");
	directorMarketing = new TreeNode("Director of Marketing", "George Lucas");
	digitalMediaSpecialist = new TreeNode("Digital Media Specialist", "Al Gore");
	headTVPrintAdvertising = new TreeNode("Head of Television and Print Advertising", "George R.R Martin");
	vpOperations = new TreeNode("VP Operations", "Bill Gates");
	vpSoftwareDevelopment = new TreeNode("VP Software Development", "Ayn Rand");
	cloudDevelopment = new TreeNode("Cloud Development", "Bob Ross");
	magicBagLeader = new TreeNode("MagicBag Team Leader", "Will Wheaton");
	softwareEngineerI = new TreeNode("Software Engineer I", "Donald Knuth");
	softwareEngineerII = new TreeNode("Software Engineer II", "Marvin Minsky");

	president->setLeftChild(vpSales);
	vpSales->setRightSibling(vpOperations);
	vpOperations->setRightSibling(vpSoftwareDevelopment);
	vpSales->setParent(president);
	vpOperations->setParent(president);
	vpSoftwareDevelopment->setParent(president);

	vpSales->setLeftChild(directorMarketing);
		directorMarketing->setParent(vpSales);
		directorPR->setParent(vpSales);
		directorMarketing->setRightSibling(directorPR);
		directorMarketing->setLeftChild(digitalMediaSpecialist);
			digitalMediaSpecialist->setParent(directorMarketing);
			headTVPrintAdvertising->setParent(directorMarketing);
			digitalMediaSpecialist->setRightSibling(headTVPrintAdvertising);

	vpSoftwareDevelopment->setLeftChild(magicBagLeader);
		magicBagLeader->setParent(vpSoftwareDevelopment);
		cloudDevelopment->setParent(vpSoftwareDevelopment);
		magicBagLeader->setRightSibling(cloudDevelopment);
		magicBagLeader->setLeftChild(softwareEngineerI);
			softwareEngineerI->setParent(magicBagLeader);
			softwareEngineerII->setParent(magicBagLeader);
			softwareEngineerI->setRightSibling(softwareEngineerII);

	tree.root = president;
}


void setupTreeWithHire(OrgTree& tree) {
	tree.addRoot("President", "George Orwell");

	president = tree.getRoot();

	tree.hire(president, "VP Sales", "Mark Zuckerberg");
	tree.hire(president, "VP Operations", "Bill Gates");
	tree.hire(president, "VP Software Development", "Ayn Rand");

	vpSales = tree.find("VP Sales");
	vpOperations = tree.find("VP Operations");
	vpSoftwareDevelopment = tree.find("VP Software Development");

	tree.hire(vpSales, "Director of Marketing", "George Lucas");
	tree.hire(vpSales, "Director of Public Relations", "Kurt Vonnegut");

	tree.hire(vpOperations, "MagicBag Team Leader", "Will Wheaton");
	tree.hire(vpOperations, "Cloud Development", "Bob Ross");

	magicBagLeader = tree.find("MagicBag Team Leader");
	directorMarketing = tree.find("Director of Marketing");
	directorPR = tree.find("Director of Public Relations");

	tree.hire(magicBagLeader, "Software Engineer I", "Donald Knuth");
	tree.hire(magicBagLeader, "Software Engineer II", "Marvin Minsky");

	tree.hire(directorMarketing, "Digital Media Specialist", "Al Gore");
	tree.hire(directorMarketing, "Head of Television and Print Advertising", "George R.R Martin");

	cloudDevelopment = tree.find("Cloud Development");
	digitalMediaSpecialist = tree.find("Digital Media Specialist");
	headTVPrintAdvertising = tree.find("Head of Television and Print Advertising");
	softwareEngineerI = tree.find("Software Engineer I");
	softwareEngineerII = tree.find("Software Engineer II");

}


bool testGetLastChild() {
	TREENODEPTR parent = new TreeNode("President", "George Orwell");
	
	if (parent->getLastChild() != TREENULLPTR) {
		cout << "TreeNode::getLastChild() fails to return a null pointer on a node with no children!" << endl;
		return false;
	}

	TREENODEPTR firstChild = new TreeNode("VP Sales", "Somebody");
	parent->setLeftChild(firstChild);

	if (parent->getLastChild() != firstChild) {
		cout << "TreeNode::getLastChild() fails to return the right child with one child!" << endl;
		return false;
	}

	TREENODEPTR secondChild = new TreeNode("VP Operations", "Someone else");
	firstChild->setRightSibling(secondChild);

	if (parent->getLastChild() != secondChild) {
		cout << "TreeNode::getLastChild() fails to return the right child with two children!" << endl;
		return false;
	}

	
	return true;
}


bool testAppendChild() {
	TREENODEPTR parent = new TreeNode("Parent Title", "Parent Name");
	TREENODEPTR firstChild = new TreeNode("First Child Title", "First Child Name");
	TREENODEPTR secondChild = new TreeNode("Second Child Title", "Second Child Name");

	parent->appendChild(firstChild);

	if (parent->getLastChild() != firstChild) {
		cout << "TreeNode::appendChild() fails to return the right last child after one appendChild!" << endl;
		return false;
	}
	else if (firstChild->parent != parent) {
		cout << "TreeNode::appendChild() fails to set the parent pointer for the first child!" << endl;
		return false;
	}

	parent->appendChild(secondChild);

	if (parent->getLastChild() != secondChild) {
		cout << "TreeNode::appendChild() fails to return the right last child after two appendChilds!" << endl;
		return false;
	}
	else if (secondChild->parent != parent) {
		cout << "TreeNode::appendChild() fails to set the parent pointer for the second child!" << endl;
		return false;
	}

	
	return true;
}


bool testConstructor() {
	OrgTree myTree = OrgTree();

	if (myTree.root != TREENULLPTR) {
		cout << "OrgTree::OrgTree() didn't initialize the root pointer to null properly!" << endl;
		return false;
	} 
	
	
	return true;
}


bool testAddRoot() {
	OrgTree myTree = OrgTree();

	myTree.addRoot("VP Software Development", "Ayn Rand");

	TREENODEPTR rootPtr = myTree.root;

	if (rootPtr == TREENULLPTR) {
		cout << "OrgTree::addRoot() did not set the root attribute properly!" << endl;
		return false;
	}

	TreeNode& root = *rootPtr;

	if (root.title != "VP Software Development") {
		cout << "OrgTree::addRoot() did not create a TreeNode with the proper title" << endl;
		cout << "OrgTree::addRoot() - Expected title: President Actual title: " << root.title << endl;
		return false;
	}
	else if (root.name != "Ayn Rand") {
		cout << "OrgTree::addRoot() did not create a TreeNode with the proper name" << endl;
		cout << "OrgTree::addRoot() - Expected name: Ayn Rand Actual title: " << root.name << endl;
		return false;
	}

	myTree.addRoot("President", "George Orwell");

	TREENODEPTR newRootPtr = myTree.root;

	if (newRootPtr == TREENULLPTR) {
		cout << "OrgTree::addRoot() sets a nullptr as root after first addRoot!" << endl;
		return false;
	}

	TreeNode& newRoot = *newRootPtr;

	if (newRoot.title == "VP Software Development" || newRoot.name == "Ayn Rand") {
		cout << "OrgTree::addRoot() did not update the root ptr, it's still Ayn Rand" << endl;
		return false;
	}
	else if (newRoot.title != "President" || newRoot.name != "George Orwell") {
		cout << "OrgTree::addRoot() sets us to a totally random TreeNode after second call!" << endl;
		cout << "OrgTree::addRoot() - Title: " << newRoot.title << " Name: " << newRoot.name << endl;
		return false;
	}
	else if (newRoot.getLeftChild() != rootPtr) {
		cout << "OrgTree::addRoot() doesn't update the leftChild attribute of the new root TreeNode!" << endl;
		return false;
	}
	else if (root.parent != newRootPtr) {
		cout << "OrgTree::addRoot() doesn't update the parent attribute of the old root TreeNode!" << endl;
		return false;
	}
	
	
	return true;
}


bool testGetRoot() {
	OrgTree myTree = OrgTree();

	TREENODEPTR initialRoot = myTree.getRoot();

	if (initialRoot != TREENULLPTR) {
		cout << "OrgTree::getRoot() does not give a null pointer when no root has been added!" << endl;
		return false;
	}

	myTree.root = president;

	if (myTree.getRoot() != president) {
		cout << "OrgTree::getRoot() does not return the root attribute pointer!" << endl;
		return false;
	}

	
	return true;
}


bool testLeftmostChild() {
	OrgTree& myTree = *(new OrgTree());
	setupTree(myTree);

	if (myTree.leftmostChild(president) != vpSales) {
		cout << "OrgTree::leftmostChild() does not return the proper child from the root node!" << endl;
		return false;
	}

	if (myTree.leftmostChild(vpSales) != directorMarketing) {
		cout << "OrgTree::leftmostChild() does not return the proper child of the root's leftmost child!" << endl;
		return false;
	}

	if (myTree.leftmostChild(vpOperations) != TREENULLPTR) {
		cout << "OrgTree::leftmostChild() on a leaf does not return null pointer!" << endl;
	}

	
	return true;
}


bool testRightSibling() {
	OrgTree& myTree = *(new OrgTree());
	setupTree(myTree);

	if (myTree.rightSibling(president) != TREENULLPTR) {
		cout << "OrgTree::rightSibling() does not return null on the root node!" << endl;
		return false;
	}

	if (myTree.rightSibling(vpSales) != vpOperations) {
		cout << "OrgTree::rightSibling() does not return the VP of Operations given the VP of Sales!" << endl;
		return false;
	}

	if (myTree.rightSibling(directorMarketing) != directorPR) {
		cout << "OrgTree::rightSibling() does not return the Director of Public Relations given the Director of Marketing!" << endl;
		return false;
	}

	if (myTree.rightSibling(digitalMediaSpecialist) != headTVPrintAdvertising) {
		cout << "OrgTree::rightSibling() does not return a Head of TV and Print Advertising given digital media specialist!" << endl;
		return false;
	}

	if (myTree.rightSibling(headTVPrintAdvertising) != TREENULLPTR) {
		cout << "OrgTree::rightSibling() does not return a null pointer given Head of TV and Print Advertising!" << endl;
		return false;
	}

	
	return true;
}


bool testFind() {
	OrgTree& myTree = *(new OrgTree());
	setupTree(myTree);

	if (myTree.find("Invalid") != TREENULLPTR) {
		cout << "OrgTree::find() does not return a null pointer given an invalid name" << endl;
		return false;
	}
	else if (myTree.find("President") != president) {
		cout << "OrgTree::find() does not find the President!" << endl;
		return false;
	}
	else if (myTree.find("VP Sales") != vpSales) {
		cout << "OrgTree::find() does not find the VP Sales" << endl;
		return false;
	}
	else if (myTree.find("VP Operations") != vpOperations) {
		cout << "OrgTree::find() does not find the VP Operations" << endl;
		return false;
	}
	else if (myTree.find("VP Software Development") != vpSoftwareDevelopment) {
		cout << "OrgTree::find() does not find the VP Software Development" << endl;
		return false;
	}
	else if (myTree.find("Director of Marketing") != directorMarketing) {
		cout << "OrgTree::find() does not find the Director of Marketing" << endl;
		return false;
	}
	else if (myTree.find("Director of Public Relations") != directorPR) {
		cout << "OrgTree::find() does not find the Director of Public Relations" << endl;
		return false;
	}
	else if (myTree.find("MagicBag Team Leader") != magicBagLeader) {
		cout << "OrgTree::find() does not find the MagicBag Team Leader" << endl;
		return false;
	}
	else if (myTree.find("Cloud Development") != cloudDevelopment) {
		cout << "OrgTree::find() does not find the Cloud Development" << endl;
		return false;
	}
	else if (myTree.find("Digital Media Specialist") != digitalMediaSpecialist) {
		cout << "OrgTree::find() does not find the Digital Media Specialist" << endl;
		return false;
	}
	else if (myTree.find("Head of Television and Print Advertising") != headTVPrintAdvertising) {
		cout << "OrgTree::find() does not find the Head of TV and Print Advertising" << endl;
		return false;
	}
	else if (myTree.find("Software Engineer I") != softwareEngineerI) {
		cout << "OrgTree::find() does not find the Software Engineer I" << endl;
		return false;
	}
	else if (myTree.find("Software Engineer II") != softwareEngineerII) {
		cout << "OrgTree::find() does not find the Software Engineer II" << endl;
		return false;
	}

	
	return true;
}


bool testHire() {
	OrgTree& myTree = *(new OrgTree());
	setupTreeWithHire(myTree);

	TreeNode* foundNode = myTree.find("President");

    if (myTree.find("President") != president) {
		cout << "OrgTree::hire() does not add the President!" << endl;
		return false;
	}
	else if (myTree.find("VP Sales") != vpSales) {
		cout << "OrgTree::hire() does not add the VP Sales" << endl;
		return false;
	}
	else if (myTree.find("VP Operations") != vpOperations) {
		cout << "OrgTree::hire() does not add the VP Operations" << endl;
		return false;
	}
	else if (myTree.find("VP Software Development") != vpSoftwareDevelopment) {
		cout << "OrgTree::hire() does not add the VP Software Development" << endl;
		return false;
	}
	else if (myTree.find("Director of Marketing") != directorMarketing) {
		cout << "OrgTree::hire() does not add the Director of Marketing" << endl;
		return false;
	}
	else if (myTree.find("Director of Public Relations") != directorPR) {
		cout << "OrgTree::hire() does not add the Director of Public Relations" << endl;
		return false;
	}
	else if (myTree.find("MagicBag Team Leader") != magicBagLeader) {
		cout << "OrgTree::hire() does not add the MagicBag Team Leader" << endl;
		return false;
	}
	else if (myTree.find("Cloud Development") != cloudDevelopment) {
		cout << "OrgTree::hire() does not add the Cloud Development" << endl;
		return false;
	}
	else if (myTree.find("Digital Media Specialist") != digitalMediaSpecialist) {
		cout << "OrgTree::hire() does not add the Digital Media Specialist" << endl;
		return false;
	}
	else if (myTree.find("Head of Television and Print Advertising") != headTVPrintAdvertising) {
		cout << "OrgTree::hire() does not add the Head of TV and Print Advertising" << endl;
		return false;
	}
	else if (myTree.find("Software Engineer I") != softwareEngineerI) {
		cout << "OrgTree::hire() does not add the Software Engineer I" << endl;
		return false;
	}
	else if (myTree.find("Software Engineer II") != softwareEngineerII) {
		cout << "OrgTree::hire() does not add the Software Engineer II" << endl;
		return false;
	}
	else if (softwareEngineerII->getParent() != magicBagLeader) {
		cout << "OrgTree::hire() does not setup the parent hierarchy properly!" << endl;
		return false;
	}

	return true;
}


bool testFire() {
	OrgTree& myTree = *(new OrgTree());

	bool success = myTree.fire("President");

	if (success) {
		cout << "OrgTree::fire() reports successful deletion when no nodes have been added!" << endl;
		return false;
	}

	setupTreeWithHire(myTree);

	success = myTree.fire("President");

	if (success) {
		cout << "OrgTree::fire() reports successful deletion of the root node! Not Allowed!" << endl;
		return false;
	}
	else if (myTree.root != president) {
		cout << "OrgTree::fire() reports failure on deletion of root but the root node was still modified!" << endl;
		return false;
	}


	success = myTree.fire("Nobody");

	if (success) {
		cout << "OrgTree::fire() reports successful deletion of a title that doesn't exist!" << endl;
		return false;
	}

	success = myTree.fire("Software Engineer II");

	if (!success) {
		cout << "OrgTree::fire() reports failure to delete Software Engineer II" << endl;
		return false;
	}
	else if (myTree.find("Software Engineer II") != TREENULLPTR) {
		cout << "OrgTree::fire() deleted Software Engineer II but it still exists in tree" << endl;
		return false;
	}
	else if (softwareEngineerI->getRightSibling() != TREENULLPTR) {
		cout << "OrgTree::fire() delete Software Engineer II but Software Engineer I's right sibling was not reset!" << endl;
		return false;
	}

	success = myTree.fire("Director of Marketing");

	if (!success) {
		cout << "OrgTree::fire() reports failure to delete Director of Marketing" << endl;
		return false;
	}
	else if (myTree.find("Director of Marketing") != TREENULLPTR) {
		cout << "OrgTree::fire() deleted Director of Marketing but it still exists in tree" << endl;
		return false;
	}
	else if (vpSales->getLeftChild() != directorPR) {
		cout << "OrgTree::fire() does not update the left child of vpSales when firing director of marketing" << endl;
		return false;
	}

	success = myTree.fire("VP Operations");

	if (!success) {
		cout << "OrgTree::fire() reports failure to delete VP Operations" << endl;
		return false;
	}
	else if (myTree.find("VP Operations") != TREENULLPTR) {
		cout << "OrgTree::fire() deleted VP Operations but it still exists in tree" << endl;
		return false;
	}
	else if (vpSales->getRightSibling() != vpSoftwareDevelopment) {
		cout << "OrgTree::fire() does not update rightSibling pointer of VP Sales" << endl;
		return false;
	}

	return true;
}


bool testGetSize() {
	OrgTree& myTree = *(new OrgTree());

	if (myTree.getSize() != 0) {
		cout << "OrgTree::getSize() not equal to 0 on a brand new tree" << endl;
		return false;
	}

	myTree.addRoot("Test", "Just 1");

	if (myTree.getSize() != 1) {
		cout << "OrgTree::getSize() not equal to 1 after setting root" << endl;
		return false;
	}

	myTree.hire(myTree.getRoot(), "Test2", "Just 2");

	if (myTree.getSize() != 2) {
		cout << "OrgTree::getSize() not equal to 2 after hiring one employee" << endl;
		return false;
	}

	myTree = *(new OrgTree());

	setupTreeWithHire(myTree);

	if (myTree.getSize() != 12) {
		cout << "OrgTree::getSize() not equal to 12 after setting up entire tree" << endl;
		return false;
	}

	return true;
}


bool testRead() {
	OrgTree& myTree = *(new OrgTree());

	bool success = myTree.read("C:\\Users\\ian\\Documents\\Visual Studio 2015\\Projects\\CS3100Project2\\test_proper.txt");

	if (!success) {
		cout << "OrgTree::read() fails with test_proper.txt" << endl;
		return false;
	}
	else if (myTree.getSize() != 12) {
		cout << "OrgTree::read() did not add the proper amount of nodes from file test_proper.txt" << endl;
		return false;
	}

	TREENODEPTR president = myTree.getRoot();

	if (president == TREENULLPTR || president->getTitle() != "President") {
		cout << "OrgTree::read() did not set the root to President" << endl;
		return false;
	}

	TREENODEPTR vpSales = president->getLeftChild();

	if (vpSales == TREENULLPTR || vpSales->getTitle() != "VP Sales") {
		cout << "OrgTree::read() did not set the root's leftmost child to VP Sales" << endl;
		return false;
	}

	TREENODEPTR vpOperations = vpSales->getRightSibling();

	if (vpSales == TREENULLPTR || vpSales->getTitle() != "VP Sales") {
		cout << "OrgTree::read() did not set the root's leftmost child to VP Sales" << endl;
		return false;
	}

	return true;
}


bool testMemoryLeaks() {
	for (int i = 0; i < 10000; i++) {
		OrgTree firstTree = OrgTree();
		OrgTree secondTree = OrgTree();
		setupTree(firstTree);
		setupTreeWithHire(secondTree);
	}

	return true;
}


void checkTestSuccess(bool success, int& passes, int& failures) {
	if (success) {
		cout << ".";
		passes++;
	}
	else {
		failures++;
	}
}


int main()
{
	int passes = 0;
	int failures = 0;

	checkTestSuccess(testGetLastChild(), passes, failures);
	checkTestSuccess(testAppendChild(), passes, failures);
	checkTestSuccess(testConstructor(), passes, failures);
	checkTestSuccess(testAddRoot(), passes, failures);
	checkTestSuccess(testGetRoot(), passes, failures);
	checkTestSuccess(testLeftmostChild(), passes, failures);
	checkTestSuccess(testRightSibling(), passes, failures);
	checkTestSuccess(testFind(), passes, failures);
	checkTestSuccess(testHire(), passes, failures);
	checkTestSuccess(testFire(), passes, failures);
	checkTestSuccess(testGetSize(), passes, failures);
	checkTestSuccess(testRead(), passes, failures);
	checkTestSuccess(testMemoryLeaks(), passes, failures);

	cout << endl;

	if (failures > 0) {
		cout << "Testcase finished with failures" << endl;
		cout << "Tests Passed: " << passes << " Tests Failed: " << failures << endl;
	}
	else {
		cout << "PASSED" << endl;
		cout << "Tests Ran: " << passes << endl;
	}

	_CrtDumpMemoryLeaks();

	system("pause");
    return 0;
}

