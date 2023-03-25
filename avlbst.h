 #ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    AVLNode<Key, Value>* getLeaf(const Key& key, AVLNode<Key, Value>* p);
    void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void rotateRight(AVLNode<Key, Value>* parent);
    void rotateLeft(AVLNode<Key, Value>* parent);
    void removeFix(AVLNode<Key, Value>* n, int diff);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // if tree is empty, insert
    if (this->empty()){
        AVLNode<Key, Value>* mynode = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        this->root_ = mynode;
        mynode->setBalance(0);
    }
    // if the value alread in key
    else if (this->internalFind(new_item.first)){
        this->internalFind(new_item.first)->setValue(new_item.second);
    }
    else {
        AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
        AVLNode<Key, Value>* parent = getLeaf(new_item.first, temp);
        // create and insert new node
        AVLNode<Key, Value>* mynode = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
        if (mynode->getKey() < parent->getKey()){
            parent->setLeft(mynode);
						parent->updateBalance(-1);
						// if parent's previous balance was 0
						if (parent->getBalance() + 1 == 0){
							insertFix(parent, mynode);
						}
        }
        else{
            parent->setRight(mynode);
						parent->updateBalance(1);
						// if parent's previous balance was 0
						if (parent->getBalance() - 1 == 0){
							insertFix(parent, mynode);
						}
        }
    }
}


/*
 * insert() helper function
 * returns leaf node
 * Note: returned node will be the parent of the inserted node
 * Note 2: p = parent
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::getLeaf(const Key& key, AVLNode<Key, Value>* p)
{
    // traverse to left child
    if (key < p->getKey()){
        // base case:
        if (!p->getLeft()){
            return p;
        }
        return getLeaf(key, p->getLeft());
    }
    // traverse to right child
    else {
        // base case:
        if (!p->getRight()){
            return p;
        }
        return getLeaf(key, p->getRight());
    }
}


/*
 * insert() helper function
 * Called when parent leaf node balance = 0 before insertion
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n)
{
    // if p is null or p's parent is null
    if (!p || !p->getParent()) return;
		// g = p's parent
		AVLNode<Key,Value>* g = p->getParent();

		// if p is left child of g
		if (g->getLeft() == p){
				g->updateBalance(-1);
				// 3 cases:
				if (g->getBalance() == 0) 
				{
					return;
				}
				else if (g->getBalance() == -1){
						insertFix(g, p);
				}
				else if (g->getBalance() == -2){
						// if zig zig: 
						if (p->getBalance() == -1){
								rotateRight(g);
								p->setBalance(0);

								if (g->getLeft() && !g->getRight()){
									g->setBalance(-1);
								}
								else if (!g->getLeft() && g->getRight()){
									g->setBalance(1);
								}
								else{
									g->setBalance(0);
								}
						}
						// if zig zag:
						else if (p->getBalance() == 1){
								rotateLeft(p);
								rotateRight(g);

								// 3 sub-cases:
								if (n->getBalance() == -1){
										p->setBalance(0);
										g->setBalance(1);
										n->setBalance(0);
								}
								else if (n->getBalance() == 0){
										p->setBalance(0);
										g->setBalance(0);
										n->setBalance(0);
								}
								else if (n->getBalance() == 1){
										p->setBalance(-1);
										g->setBalance(0);
										n->setBalance(0);
								}
						}
				}
		}
		// if p is right child of g
		else if (g->getRight() == p){
				g->updateBalance(1);
				// 3 cases:
				if (g->getBalance() == 0) 
				{
					return;
				}
				else if (g->getBalance() == 1){
						insertFix(g, p);
				}
				else if (g->getBalance() == 2){
						// if zag zag: 
						if (p->getBalance() == 1){
								rotateLeft(g);
								p->setBalance(0);

								if (g->getLeft() && !g->getRight()){
									g->setBalance(-1);
								}
								else if (!g->getLeft() && g->getRight()){
									g->setBalance(1);
								}
								else{
									g->setBalance(0);
								}
						}
						// if zag zig:
						else if (p->getBalance() == -1){
								rotateRight(p);
								rotateLeft(g);

								// 3 sub-cases:
								if (n->getBalance() == 1){
										p->setBalance(0);
										g->setBalance(-1);
										n->setBalance(0);
								}
								else if (n->getBalance() == 0){
										p->setBalance(0);
										g->setBalance(0);
										n->setBalance(0);
								}
								else if (n->getBalance() == -1){
										p->setBalance(1);
										g->setBalance(0);
										n->setBalance(0);
								}
						}
				}
		}
}


/*
 * Balancing helper, right rotation
 */
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode< Key, Value>* parent)
{
    AVLNode<Key, Value>* child = parent->getLeft();
		AVLNode<Key, Value>* c = child->getRight();

		// checking if grandparent exists or if parent is root_
		if (this->root_ == parent){
			child->setParent(nullptr);
			this->root_ = child;
		}
		else {
			AVLNode<Key, Value>* grandparent = parent->getParent();
			child->setParent(grandparent);
			if (grandparent->getLeft() == parent){
				grandparent->setLeft(child);
			}
			else{
				grandparent->setRight(child);
			}
		}

		// handling child's original right child
		parent->setLeft(c);
        if (c){
		    c->setParent(parent);
        }
        
		child->setRight(parent);
		parent->setParent(child);

}


/*
 * Balancing helper, left rotation
 */
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* parent)
{
    AVLNode<Key, Value>* child = parent->getRight();
		AVLNode<Key, Value>* c = child->getLeft();

		// checking if grandparent exists or if parent is root_
		if (this->root_ == parent){
			child->setParent(nullptr);
			this->root_ = child;
		}
		else {
			AVLNode<Key, Value>* grandparent = parent->getParent();
			child->setParent(grandparent);
			if (grandparent->getLeft() == parent){
				grandparent->setLeft(child);
			}
			else{
				grandparent->setRight(child);
			}
		}

		// handling child's original left child
		parent->setRight(c);
		if (c){
      c->setParent(parent);
    }

		child->setLeft(parent);
		parent->setParent(child);

}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    // base case: empty tree
    if (this->empty()) return;
    
    AVLNode<Key, Value>* n = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
		if (!n) return;
    
    // check if taget has 2 nodes
    if (n->getLeft() && n->getRight()){
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(n));
        nodeSwap(n, pred);
				// because now n can ONLY have at most one child, handle remove later

        // handling when root_ is removed
        if (this->root_ == n){
            this->root_ = pred;
        }
				
    }

    AVLNode<Key, Value>* p = n->getParent();
    // if p exists
    if (p){
      if (p->getLeft() == n){
				// handling n's children, updating pointers
				if (n->getLeft()){
						p->setLeft(n->getLeft());
						p->getLeft()->setParent(p);
				}
				else if (n->getRight()){
						p->setLeft(n->getRight());
						p->getLeft()->setParent(p);
				}
				else {
					p->setLeft(nullptr);
				}

        delete n;
        removeFix(p, 1);
      }
			else if (p->getRight() == n){
				// handling n's children, updating pointers
				if (n->getLeft()){
						p->setRight(n->getLeft());
						p->getRight()->setParent(p);
				}
				else if (n->getRight()){
						p->setRight(n->getRight());
						p->getRight()->setParent(p);
				}
				else{
					p->setRight(nullptr);
				}

				delete n;
				removeFix(p, -1);
      }
    }
}


/*
 * remove() helper function
 */
template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int diff)
{
    // base case
    if (!n) return;
		AVLNode<Key, Value>* p = n->getParent();
		
    // calculations for next recursive call
    int ndiff = diff;
    if (p){
        if (p->getLeft() == n){
            ndiff = 1;
        }
        else{
            ndiff = -1;
        }
		}
	
    if (diff == -1){
			// case 1
			if (n->getBalance() + diff == -2){
					AVLNode<Key, Value>* c = n->getLeft();
					// 3 cases:
					// 1a - zig zig:
					if (c->getBalance() == -1){
							rotateRight(n);
							n->setBalance(0);
							c->setBalance(0);
							removeFix(p, ndiff);
					}
					// 1b - zig zig:
					else if (c->getBalance() == 0){
							rotateRight(n);
							n->setBalance(-1);
							c->setBalance(1);
					}
					// 1c- zig zag:
					else if (c->getBalance() == 1){
							AVLNode<Key, Value>* g = c->getRight();
							rotateLeft(c);
							rotateRight(n);
							// 3 cases
							// case 1ca
							if (g->getBalance() == 1){
									n->setBalance(0);
									c->setBalance(-1);
									g->setBalance(0);
							}
							// case 1cb
							else if (g->getBalance() == 0){
									n->setBalance(0);
									c->setBalance(0);
									g->setBalance(0);
							}
							// case 1cc
							else if (g->getBalance() == -1){
									n->setBalance(1);
									c->setBalance(0);
									g->setBalance(0);
							}
							removeFix(p, ndiff);
					}
			}
			// case 2
			else if (n->getBalance() + diff == -1){
				n->setBalance(-1);
			}
			// case 3
			else if (n->getBalance() + diff == 0){
				n->setBalance(0);
				removeFix(p, ndiff);
			}	
		}
		else if (diff == 1){
			// case 1
			if (n->getBalance() + diff == 2){
					AVLNode<Key, Value>* c = n->getRight();
					// 3 cases:
					// 1a - zig zig:
					if (c->getBalance() == 1){
							rotateLeft(n);
							n->setBalance(0);
							c->setBalance(0);
							removeFix(p, ndiff);
					}
					// 1b - zig zig:
					else if (c->getBalance() == 0){
							rotateLeft(n);
							n->setBalance(1);
							c->setBalance(-1);
					}
					// 1c- zig zag:
					else if (c->getBalance() == -1){
							AVLNode<Key, Value>* g = c->getLeft();
							rotateRight(c);
							rotateLeft(n);
							// 3 cases
							// case 1ca
							if (g->getBalance() == -1){
									n->setBalance(0);
									c->setBalance(1);
									g->setBalance(0);
							}
							// case 1cb
							else if (g->getBalance() == 0){
									n->setBalance(0);
									c->setBalance(0);
									g->setBalance(0);
							}
							// case 1cc
							else if (g->getBalance() == 1){
									n->setBalance(-1);
									c->setBalance(0);
									g->setBalance(0);
							}
							removeFix(p, ndiff);
					}
			}
			// case 2
			else if (n->getBalance() + diff == 1){
				n->setBalance(1);
			}
			// case 3
			else if (n->getBalance() + diff == 0){
				n->setBalance(0);
				removeFix(p, ndiff);
			}
		}
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
