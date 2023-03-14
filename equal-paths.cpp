#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

/*
* Gets the left-most path height
*/
int get_base_h(int h, Node * curr_node);

/*
* Recursive path height counter (from root to a leaf)
* Compares heights; base_h to a current curr_h
*/
bool comp(int base_h, Node * curr_node, int curr_h);


bool equalPaths(Node * root)
{
    // Add your code below

		if (root == nullptr){
			return true;
		}
		// otherwise, set left-most base path length
		int base_h = get_base_h(0, root);
		return comp(base_h, root, 0);
}


int get_base_h(int h, Node * curr_node)
{
	if (curr_node == nullptr){
		return 0;
	}
	if (curr_node->left == nullptr && curr_node->right == nullptr){
		return h;
	}
	if (curr_node->left != nullptr){
		return get_base_h(h+1, curr_node->left);
	}
	else{
		return get_base_h(h+1, curr_node->right);
	}
}


bool comp(int base_h, Node * curr_node, int curr_h)
{
	// if curr_node == nullptr
	if (curr_node == nullptr){
		return true;
	}
	// if left child exists but not right child, move to left child and recall
	if (curr_node->left != nullptr && curr_node->right == nullptr){
		return comp(base_h, curr_node->left, curr_h + 1);
	}
	// if right child exsists but not left child, move to right and recall
	else if (curr_node->right != nullptr && curr_node->left == nullptr){
		return comp(base_h, curr_node->right, curr_h + 1);
	}
	// if both children exist, recurse through both sides
	else if (curr_node->right != nullptr && curr_node->left != nullptr){
		return comp(base_h, curr_node->left, curr_h + 1) && 
		comp(base_h, curr_node->right, curr_h + 1);
	}
	// if at a leaf, check if the path height is the the same as the base height
	else if (curr_node->right == nullptr && curr_node->left == nullptr){
		return base_h == curr_h;
	}
	return false;
}


