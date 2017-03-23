// CS3100Project2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <direct.h>
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


ifstream::pos_type filesize(const string filename) {
	ifstream in(filename, ifstream::ate | ifstream::binary);
	return in.tellg();
}


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

	tree.setRoot(president);
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


bool verifyCompleteTree(OrgTree& myTree, string functionName) {
	TREENODEPTR president = myTree.getRoot();

	if (president == TREENULLPTR || president->getTitle() != "President") {
		cout << functionName + " did not set the root to President" << endl;
		return false;
	}

	TREENODEPTR vpSales = president->getLeftChild();

	if (vpSales == TREENULLPTR || vpSales->getTitle() != "VP Sales") {
		cout << functionName + " did not set the root's leftmost child to VP Sales" << endl;
		return false;
	}

	TREENODEPTR vpOperations = vpSales->getRightSibling();

	if (vpSales == TREENULLPTR || vpOperations->getTitle() != "VP Operations") {
		cout << functionName + " did not set the root's leftmost child to VP Operations" << endl;
		return false;
	}

	TREENODEPTR vpSoftwareDev = vpOperations->getRightSibling();

	if (vpSoftwareDev == TREENULLPTR || vpSoftwareDev->getTitle() != "VP Software Development") {
		cout << functionName + " did not set the root's leftmost child to VP Software Development" << endl;
		return false;
	}

	TREENODEPTR directorMarketing = vpSales->getLeftChild();

	if (directorMarketing == TREENULLPTR || directorMarketing->getTitle() != "Director of Marketing") {
		cout << functionName + " did not set the root's leftmost child to Director of Marketing" << endl;
		return false;
	}

	TREENODEPTR directorPR = directorMarketing->getRightSibling();

	if (directorPR == TREENULLPTR || directorPR->getTitle() != "Director of Public Relations") {
		cout << functionName + " did not set the root's leftmost child to Director of PR" << endl;
		return false;
	}

	TREENODEPTR digitalMedia = directorMarketing->getLeftChild();

	if (digitalMedia == TREENULLPTR || digitalMedia->getTitle() != "Digital Media Specialist") {
		cout << functionName + " did not set the root's leftmost child to Digital Media Specialist" << endl;
		return false;
	}

	TREENODEPTR headOfAdvertising = digitalMedia->getRightSibling();

	if (headOfAdvertising == TREENULLPTR || headOfAdvertising->getTitle() != "Head of Television and Print Advertising") {
		cout << functionName + " did not set the root's leftmost child to Head of Advertising" << endl;
		return false;
	}

	TREENODEPTR magicBagLeader = vpSoftwareDev->getLeftChild();

	if (magicBagLeader == TREENULLPTR || magicBagLeader->getTitle() != "MagicBag Team Leader") {
		cout << functionName + " did not set the root's leftmost child to MagicBag Team Leader" << endl;
		return false;
	}

	TREENODEPTR cloudDevelopment = magicBagLeader->getRightSibling();

	if (cloudDevelopment == TREENULLPTR || cloudDevelopment->getTitle() != "Cloud Development") {
		cout << functionName + " did not set the root's leftmost child to Cloud Development" << endl;
		return false;
	}

	TREENODEPTR softwareEngineerI = magicBagLeader->getLeftChild();

	if (softwareEngineerI == TREENULLPTR || softwareEngineerI->getTitle() != "Software Engineer I") {
		cout << functionName + " did not set the root's leftmost child to Software Engineer I" << endl;
		return false;
	}

	TREENODEPTR softwareEngineerII = softwareEngineerI->getRightSibling();

	if (softwareEngineerII == TREENULLPTR || softwareEngineerII->getTitle() != "Software Engineer II") {
		cout << functionName + " did not set the root's leftmost child to Software Engineer II" << endl;
		return false;
	}

	return true;
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
	else if (firstChild->getParent() != parent) {
		cout << "TreeNode::appendChild() fails to set the parent pointer for the first child!" << endl;
		return false;
	}

	parent->appendChild(secondChild);

	if (parent->getLastChild() != secondChild) {
		cout << "TreeNode::appendChild() fails to return the right last child after two appendChilds!" << endl;
		return false;
	}
	else if (secondChild->getParent() != parent) {
		cout << "TreeNode::appendChild() fails to set the parent pointer for the second child!" << endl;
		return false;
	}

	
	return true;
}


bool testConstructor() {
	OrgTree myTree = OrgTree();

	if (myTree.getRoot() != TREENULLPTR) {
		cout << "OrgTree::OrgTree() didn't initialize the root pointer to null properly!" << endl;
		return false;
	} 
	
	
	return true;
}


bool testAddRoot() {
	OrgTree myTree = OrgTree();

	myTree.addRoot("VP Software Development", "Ayn Rand");

	TREENODEPTR rootPtr = myTree.getRoot();

	if (rootPtr == TREENULLPTR) {
		cout << "OrgTree::addRoot() did not set the root attribute properly!" << endl;
		return false;
	}

	TreeNode& root = *rootPtr;

	if (root.getTitle() != "VP Software Development") {
		cout << "OrgTree::addRoot() did not create a TreeNode with the proper title" << endl;
		cout << "OrgTree::addRoot() - Expected title: President Actual title: " << root.getTitle() << endl;
		return false;
	}
	else if (root.getName() != "Ayn Rand") {
		cout << "OrgTree::addRoot() did not create a TreeNode with the proper name" << endl;
		cout << "OrgTree::addRoot() - Expected name: Ayn Rand Actual title: " << root.getName() << endl;
		return false;
	}

	myTree.addRoot("President", "George Orwell");

	TREENODEPTR newRootPtr = myTree.getRoot();

	if (newRootPtr == TREENULLPTR) {
		cout << "OrgTree::addRoot() sets a nullptr as root after first addRoot!" << endl;
		return false;
	}

	TreeNode& newRoot = *newRootPtr;

	if (newRoot.getTitle() == "VP Software Development" || newRoot.getName() == "Ayn Rand") {
		cout << "OrgTree::addRoot() did not update the root ptr, it's still Ayn Rand" << endl;
		return false;
	}
	else if (newRoot.getTitle() != "President" || newRoot.getName() != "George Orwell") {
		cout << "OrgTree::addRoot() sets us to a totally random TreeNode after second call!" << endl;
		cout << "OrgTree::addRoot() - Title: " << newRoot.getTitle() << " Name: " << newRoot.getName() << endl;
		return false;
	}
	else if (newRoot.getLeftChild() != rootPtr) {
		cout << "OrgTree::addRoot() doesn't update the leftChild attribute of the new root TreeNode!" << endl;
		return false;
	}
	else if (root.getParent() != newRootPtr) {
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

	myTree.setRoot(president);

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
	else if (myTree.getRoot() != president) {
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

	myTree.fire("Software Engineer II");

	if (myTree.getSize() != 11) {
		cout << "OrgTree::getSize() not equal to 11 after firing one Software Engineer II" << endl;
		return false;
	}

	myTree.fire("VP Software Development");
	
	if (myTree.getSize() != 10) {
		cout << "OrgTree::getSize() not equal to 7 after firing VP Software Development" << endl;
		return false;
	}


	return true;
}


bool testWrite() {
	OrgTree& myTree = *(new OrgTree());

	string originalFilename = ".\\test_proper.txt";
	string outputFilename = ".\\test_proper_write.txt";
	string simpleOutputFilename = ".\\test_output_variant.txt";

	myTree.read(originalFilename);
	myTree.write(outputFilename);

	ifstream::pos_type originalFilesize = filesize(originalFilename);
	ifstream::pos_type outputFilesize = filesize(outputFilename);

	if (originalFilesize != outputFilesize) {
		cout << "Output file does not match original file!" << endl;
		return false;
	}

	myTree = *(new OrgTree());
	myTree.addRoot("President", "George Orwell");
	TREENODEPTR myRoot = myTree.getRoot();
	myTree.hire(myRoot, "VP Sales", "Mark Zuckerberg");
	myTree.hire(myRoot, "VP Operations", "Bill Gates");
	myTree.hire(myTree.find("VP Sales"), "Director of Marketing", "George Lucas");
	myTree.hire(myTree.find("Director of Marketing"), "Digital Media Specialist", "Al Gore");
	myTree.hire(myTree.find("Director of Marketing"), "Head of Advertising", "George R.R Martin");
	myTree.fire("VP Sales");

	myTree.write(simpleOutputFilename);

	myTree = *(new OrgTree());

	bool success = myTree.read(outputFilename);

	if (!success) {
		cout << "OrgTree::write() does not generate the proper format" << endl;
		return false;
	}
	else if (myTree.getSize() != 12) {
		cout << "OrgTree::write() does not generate all the proper nodes" << endl;
		return false;
	}
	else if (!verifyCompleteTree(myTree, "OrgTree::write()")) {
		return false;
	}

	return true;
}


bool testRead() {
	OrgTree& myTree = *(new OrgTree());
	string originalFilename = ".\\test_proper.txt";

	bool success = myTree.read(originalFilename);

	if (!success) {
		cout << "OrgTree::read() fails with test_proper.txt" << endl;
		return false;
	}
	else if (myTree.getSize() != 12) {
		cout << "OrgTree::read() did not add the proper amount of nodes from file test_proper.txt" << endl;
		return false;
	}

	if (!verifyCompleteTree(myTree, "OrgTree::read()")) {
		return false;
	}

	return true;
}


bool testPrintSubtree() {
	OrgTree myTree = *(new OrgTree());
	setupTreeWithHire(myTree);

	stringstream myStream;
	string expectedData = 
		"President: George Orwell\n"
		"    VP Sales: Mark Zuckerberg\n"
		"        Director of Marketing: George Lucas\n"
		"            Digital Media Specialist: Al Gore\n"
		"            Head of Television and Print Advertising: George R.R Martin\n"
		"        Director of Public Relations: Kurt Vonnegut\n"
		"    VP Operations: Bill Gates\n"
		"        MagicBag Team Leader: Will Wheaton\n"
		"            Software Engineer I: Donald Knuth\n"
		"            Software Engineer II: Marvin Minsky\n"
		"        Cloud Development: Bob Ross\n"
		"    VP Software Development: Ayn Rand\n";

	myTree.printSubTree(myTree.getRoot(), myStream);

	string actualData = myStream.str();

	if (actualData != expectedData) {
		cout << "OrgTree::printSubTree() does not print the expected formatted response to the ostream" << endl;
		return false;
	}

	return true;
}


bool testMemoryLeaks() {
	for (int i = 0; i < 100; i++) {
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
	OrgTree o1, o2;

	// Adding roots should make a linear tree
	o1.addRoot("R1", "R1");
	o1.addRoot("R2", "R2");
	o1.addRoot("R3", "R3");

	o1.printSubTree(o1.getRoot()); //printSubTree from root

	o1.hire(o1.getRoot(), "R3C1", "R3C1"); //add two children to root
	o1.hire(o1.getRoot(), "R3C2", "R3C2");

	o1.hire(o1.find("R3C1"), "R3C1C1", "R3C1C1");//test find on leaf node and hire to it

	cout << o1.getSize() << endl;
	o1.printSubTree(o1.getRoot()); //printSubTree from root

	o1.fire("R3C1"); //fire an internal node
	cout << o1.getSize() << endl;
	o1.printSubTree(o1.getRoot());

	// Write out a tree and read it back in to a new tree, then print
	o1.write("output.txt");
	o2.read("output.txt");
	o2.printSubTree(o2.getRoot()); //printSubTree from root

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
	checkTestSuccess(testWrite(), passes, failures);
	checkTestSuccess(testPrintSubtree(), passes, failures);
	checkTestSuccess(testMemoryLeaks(), passes, failures);

	cout << endl;

	if (failures > 0) {
		cout << "Testcase finished with failures" << endl;
		cout << "Tests Passed: " << passes << endl;
		cout << "Tests Failed: " << failures << endl;
	}
	else {
		cout << "PASSED" << endl;
		cout << "Tests Ran: " << passes << endl;
	}

	system("pause");
    return 0;
}
