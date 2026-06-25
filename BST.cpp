#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}


bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


int BST::height(BTNode* node) 
{
	if (node == NULL)return 0;
	return 1 + max(height(node->left), height(node->right));// To find the total height of the tree
}


void BST::printLevel(BTNode* node, int level)
{
	if (node == NULL)return;
	if (level == 1) //print the bottom node
		cout << node->item.id << "\t";
	
	else if (level>1)//recursive if not reach the bottom node
	{
		printLevel(node->left, level - 1);
		printLevel(node->right, level - 1);
	}
}


bool BST::deepestNodes() // main fuction to print the deepest node
{
	if (root == NULL)return false;

	int h = height(root);
	cout << "Deepest nodes: ";
	printLevel(root, h);
	cout << endl;
	return true;
}


void BST::displayAscending(BTNode* cur, ostream& out) {
	if (cur == NULL)return;
	displayAscending(cur->left, out);
	cur->item.print(out); // Check left and print the left first than print right,
						  //because L<C<R
	displayAscending(cur->right, out);
}


void BST::displayDescending(BTNode* cur, ostream& out)
{
	if (cur == NULL)return;
	displayDescending(cur->right, out);
	cur->item.print(out);// Check right and print the right first then print left
						 //because R>C>L
	displayDescending(cur->left, out);
}


//Main function to display the student info
bool BST::display(int order, int source)
{
	if (root == NULL)return false;

	ostream* out;

	//Determine the source
	if (source == 2) {
		out = new ofstream("student_info.txt");
	}
	else {
		out = &cout;
	}

	//Determine the order
	if (order == 1) {
		displayAscending(root, *out);
	}
	else {
		displayDescending(root, *out);
	}

	//Close the file after write
	if (source == 2) {
		((ofstream*)out)->close();
		delete out;
		cout << "Data written to student_info.txt" << endl;
	}
	return true;	
}


BTNode* BST::findNode(BTNode* node, type item) {
	if (node == NULL) return NULL;
	if (node->item.compare2(item)) return node;//node equal
	if (node->item.compare1(item))// node not equal to id insert, then continue search
		return findNode(node->left, item); // node >id given
	else
		return findNode(node->right, item);// node <id given
}


BTNode* BST::CloneSubtree2(BTNode* node) {
	if (node == NULL) return NULL;

	//Create new nodes using the item given to clone
	BTNode* newNode = new BTNode(node->item);

	//Copy the left right item of the node given
	newNode->left = CloneSubtree2(node->left);
	newNode->right = CloneSubtree2(node->right);
	return newNode;
}


// Main function for clone a subtree
bool BST::CloneSubtree(BST t1, type item) {
	//Empty tree case
	if (root != NULL) {
		cout << "Current tree not empty! Cannot clone." << endl;
		return false;
	}

	//Find the node
	BTNode* found = findNode(t1.root, item);
	if (found == NULL) {
		cout << "Cannot clone subtree. Item not found." << endl;
		return false;
	}

	root = CloneSubtree2(found);
	count = countNode();

	return true;
}


bool BST::printLevelNode() {
	if (root == NULL) return false;

	int h = height(root);
	for (int i = 1;i <= h;i++) {
		cout << "Level " << i << " nodes: ";
		printLevel(root, i);
		cout << endl;
	}
	return true;
}

void BST::printPath2(BTNode *node,string path) {
	if (node == NULL) return;

	path += to_string(node->item.id) + " ";

	if (node->left == NULL && node->right == NULL) {
		cout << path << endl;
	}
	else {
		printPath2(node->left, path);
		printPath2(node->right, path);
	}
}


bool BST::printPath() {
	if (root == NULL) return false;

	cout << "Below are all the external paths for the tree:" << endl;
	printPath2(root,"");
	return true;
}


