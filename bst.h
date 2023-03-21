#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <cmath>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    void insertHelp(Node<Key, Value>* newPairPtr, Node<Key, Value>* current);
		int getHeight(Node<Key, Value>* curr_node) const;
        bool isBalancedHelp(Node<Key, Value>* curr_node) const;
		Node<Key, Value> *getLargestNode() const;
        void clearHelp(Node<Key, Value>* current);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
	if (current_ == nullptr && rhs.current_ == nullptr) return true;
    // when one == nullptr and not the other (implied by bypassing first if)
    if (current_ == nullptr || rhs.current_ == nullptr) return false;
    return (current_->getKey() == rhs->first) && (current_->getValue() == rhs->second);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    // nullptr == nullptr
    if (current_ == nullptr && rhs.current_ == nullptr) return false;
    // when one == nullptr and not the other (implied by bypassing first if)
    if (current_ == nullptr || rhs.current_ == nullptr) return true;
    // if either keys do not match or values (or both), will return true
    return (current_->getKey() != rhs->first) || (current_->getValue() != rhs->second);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    // in-order sequencing: left, function call call, right
	if (this->current_ != nullptr){
	    this->current_ = successor(this->current_);
    }
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;

}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO

    // when root is null
    if (empty()){
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
    }
    // if key already in tree, update its value
    else if (internalFind(keyValuePair.first) != NULL){
        internalFind(keyValuePair.first)->setValue(keyValuePair.second);
    }
    // if not in tree
    else{
        // traverse > or < with helper function
        Node<Key, Value>* newnode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
		insertHelp(newnode, root_);
    }
}

/**
* An insert method helper functions
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insertHelp(Node<Key, Value>* newPairPtr, Node<Key, Value>* current)
{
	// base case: leaf node reached, val is < leaf
	if (current->getLeft() == NULL && newPairPtr->getKey() < current->getKey()){
        current->setLeft(newPairPtr);
		newPairPtr->setParent(current);
        return;
	}
	// base case 2: leaf node reached, val is > leaf
	else if (current->getRight() == NULL && newPairPtr->getKey() > current->getKey()){
        current->setRight(newPairPtr);
		newPairPtr->setParent(current);
        return;
	}
	// left traversal necesssary, left child exists
	else if (newPairPtr->getKey() < current->getKey()){
		insertHelp(newPairPtr, current->getLeft());
	}
	// right traversal necesssary, right child exists
	else if (newPairPtr->getKey() > current->getKey()){
		insertHelp(newPairPtr, current->getRight());
	}
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO

    Node<Key, Value>* target = internalFind(key);
    // if key exists
    if (target != NULL) {
        // if key has two children, swap with predecessor then remove
        if (target->getRight() != nullptr && target->getLeft() != nullptr) {
            Node<Key, Value>* pred = predecessor(target);
            nodeSwap(target, pred);
            if (root_ == target){
                root_ = pred;
            }
        }
        if (target->getRight() == nullptr && target->getLeft() == nullptr){
            // making sure root_ still exists if tree only has root_
            // because this is when the node to be removed specifically
            // has no children either
            if (root_ == target){
                root_ = NULL;
            }
            else {
                // target->setParent(nullptr);
								if (target->getParent()->getRight() == target){
									target->getParent()->setRight(nullptr);
								}
								else{
									target->getParent()->setLeft(nullptr);
								}
                delete target;
            }
        }
        // if key has only left child, remove key, promote single child
        else if (target->getLeft() != NULL && target->getRight() == NULL){
            // check if node has a partent, and thus is the root
            if (root_ == target){
                Node<Key, Value>* newTarget = target->getLeft();

                root_ = newTarget;
                newTarget->setParent(nullptr);
            }
            else {
                Node<Key, Value>* newTarget = target->getLeft();
                Node<Key, Value>* oldParent = target->getParent();
                
                newTarget->setParent(oldParent);

								if (newTarget->getKey() > oldParent->getKey()){
									oldParent->setRight(newTarget);
								}
								else{
									oldParent->setLeft(newTarget);
								}
            }
            delete target;
        }
        // if key has only right child
        else if (target->getLeft() == NULL && target->getRight() != NULL){
            // check if node has a partent, and thus is the root
            if (root_ == target){
                Node<Key, Value>* newTarget = target->getRight();

                root_ = newTarget;
                newTarget->setParent(nullptr);
            }
            else {
                Node<Key, Value>* newTarget = target->getRight();
                Node<Key, Value>* oldParent = target->getParent();

                newTarget->setParent(oldParent);
                
								if (newTarget->getKey() > oldParent->getKey()){
									oldParent->setRight(newTarget);
								}
								else{
									oldParent->setLeft(newTarget);
								}
            }
            delete target;
        }
    }
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if (current == nullptr){
        return nullptr;
    }
    // increment one left, then keep going right while exists
    else if (current->getLeft()){
        current = current->getLeft();
				while (current->getRight()){
            current = current->getRight();
        }
        return current;
    }
    // if no left child
    else {
			// if there is a parent and current is not the parent's right child
        while (current->getParent() != nullptr){
			// if successor found, once the parent's right child is the current
            if (current->getParent()->getRight() == current){
                return current->getParent();
            }
            else{
                // otherwise, keep moving up
                current = current->getParent();
            }
        }
		// if current is root node
		// thus, if (current->getParent() == nullptr){
		return nullptr;
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    if (current == nullptr){
        return nullptr;
    }
    // increment one right, then keep going left while exists
    else if (current->getRight()){
        current = current->getRight();
        while (current->getLeft()){
            current = current->getLeft();
        }
        return current;
    }
    // if no left child
    else {
        // if there is a parent and current is not the parent's left child
        while (current->getParent() != nullptr){
			// if successor found, once the parent's left child is the current
            if (current->getParent()->getLeft() == current){
                return current->getParent();
            }
            else{
                // otherwise, keep moving up
                current = current->getParent();
            }
        }
		// if current is root node
		// thus, if (current->getParent() == nullptr){
		return nullptr;
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clearHelp(root_);
    root_ = NULL;
}


/**
* clear() helper function
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelp(Node<Key, Value>* current)
{
    // base case: empty
    if (empty()) return;
    else if (current == nullptr) return;
    else if (current->getLeft() == nullptr && current->getRight() == nullptr){
        delete current;
    }
    else{
        clearHelp(current->getRight());
        clearHelp(current->getLeft());
    }
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    // if this is null
    if (root_ == nullptr) return nullptr;
    // if there is no left
    if (root_->getLeft() == NULL) return root_;
    // if there is a left
    Node<Key, Value>* temp = root_;
    while (temp->getLeft() != NULL){
        temp = temp->getLeft();
    }
    return temp;
}

/**
* A helper function to find the largest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getLargestNode() const
{
    // if this is null
    if (root_ == nullptr) return nullptr;
    // if there is no right
    if (root_->getRight() == NULL) return root_;
    // if there is a right
    Node<Key, Value>* temp = root_;
    while (temp->getRight() != NULL){
        temp = temp->getRight();
    }
    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO

    const Key& max = getLargestNode()->getKey();
    const Key& min = getSmallestNode()->getKey();
    
    if (empty() || key > max || key < min){
        return NULL;
    }

    Node<Key, Value>* temp = root_; 
    while (temp->getKey() != key){
		// traverse left
        if (key < temp->getKey()){
            temp = temp->getLeft();
        }
		// traverse right
        else if (key > temp->getKey()){
            temp = temp->getRight();
        }

        // check that the traversed temp is valid
        if (temp == nullptr) return NULL;
    }
	// when while loop exited: thus, key found
    return temp;
    
}


/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
		// base case: when no root_
		if (empty()) return true;
		// base case 2: only root_ exists
		else if (root_->getLeft() == NULL && root_->getRight() == NULL){
			return true;
		}
		else {
			return isBalancedHelp(root_);
		}
}


/**
 * isBalanced() recursive helper, gets height
 */
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getHeight(Node<Key, Value>* curr_node) const
{
	// base case: when leaf, return height
    if (curr_node == nullptr){
		return 0;
	}
    else if (curr_node->getLeft() == nullptr && curr_node->getRight() == nullptr){
		return 1;
	}
	else return std::max(getHeight(curr_node->getLeft()) + 1, getHeight(curr_node->getRight()) + 1);
}


/**
 * isBalanced() recursive helper
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelp(Node<Key, Value>* curr_node) const
{
    // if leaf node, return true
    if (curr_node->getLeft() == nullptr && curr_node->getRight() == nullptr){
        return true;
    }
    // check if height of left subtree is within 1 of height of right sub tree
    else if (std::abs(getHeight(curr_node->getLeft()) - getHeight(curr_node->getRight())) <= 1){
        return isBalancedHelp(curr_node->getLeft()) && isBalancedHelp(curr_node->getRight());
    }
    else {
        return false;
    }
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
