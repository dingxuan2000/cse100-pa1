/**
 * TODO: add file header
 * T
 */
#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <queue>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

/**
 * TODO: add class header
 * Used BST class's insert method to build a BST, and through find method to
 * check
 *
 */
template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // // number of Data items stored in this BST.
    unsigned int isize;

    // // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /**
     * Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {
        // PART 2
    }

    /** TODO */
    ~BST() { deleteAll(this->root); }

    /** TODO */
    bool insert(const Data& item) {
        BSTNode<Data>* newNode = new BSTNode<Data>(item);
        if (this->root == 0) {  // 0 is same as NULL
            this->root = newNode;
            isize = isize + 1;
            iheight = iheight + 1;
            return true;
        }
        int height = 0;
        BSTNode<Data>* currentptr = this->root;  // start at root
        while (currentptr != NULL) {
            if (currentptr->getData() < item) {
                if (currentptr->right == NULL) {
                    currentptr->right = newNode;
                    newNode->parent =
                        currentptr;  // set the newNode's parent=currentptr
                    isize = isize + 1;
                    height = height +
                             1;  // when insert a newNode, the height must +1
                    if (height > this->iheight) {
                        this->iheight = height;
                    }
                    return true;
                } else {
                    currentptr = currentptr->right;
                    height = height + 1;  // to get the right-most node's height
                }
            } else if (item < currentptr->getData()) {
                if (currentptr->left == NULL) {
                    currentptr->left = newNode;
                    newNode->parent =
                        currentptr;  // set the newNode's parent=currentptr
                    isize = isize + 1;
                    height = height + 1;
                    if (height > this->iheight) {
                        this->iheight = height;
                    }
                    return true;
                } else {
                    currentptr = currentptr->left;
                    height = height + 1;  // to get the left-most node's height
                }
            } else {
                delete newNode;  // when the newNode is duplicate, must to
                                 // delete it.
                return false;
            }  // when the data of currentptr == item, appear
               // duplicate case
        }
    }

    /** TODO */
    // BSTIterator<Data>
    iterator find(const Data& item) const {
        BSTNode<Data>* ptr;  // create a pointer that points to root
        ptr = this->root;
        // when the current node is not empty, compare the data of node with
        // item
        while (ptr != NULL) {
            if (ptr->getData() < item) {
                ptr = ptr->right;
            } else if (item < ptr->getData())
                ptr = ptr->left;
            else {
                iterator iobj(ptr);  // Found it, return an iterator object
                return iobj;
            }
        }
        // Not Found it, return an iterator object contains NULL, now ptr is
        // NULL.
        iterator iobj(ptr);
        return iobj;
    }

    /** TODO */  // PART 2
    bool deleteNode(const Data& item) { return false; }

    /** TODO */
    unsigned int size() const { return this->isize; }

    /** TODO */
    int height() const {
        if (this->empty()) return -1;  // when it's an empty tree, return -1
        return this->iheight;
    }

    /** TODO */
    bool empty() const {
        if (this->root == 0)  // 0 is same as NULL
            return true;
        else
            return false;
    }

    /** TODO */
    iterator begin() const {
        // call first(), and create an object pointing to the smallest element
        // in BST
        iterator start(first(this->root));
        return start;
    }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    vector<Data> inorder() const {
        vector<Data> vtr;
        inorderpush(this->root, vtr);
        return vtr;
    }

    /**
     * DO NOT CHANGE THIS METHOD
     * Prints a tree, including its structure to an
     * output stream to help with grading and debugging.
     */
    void print(ostream* out) {
        if (empty()) {
            *out << "(Empty tree)" << endl;
            return;
        }

        // Using a queue to traverse a tree is otherwise
        // known as a breadth first traversal of the tree.
        // It's useful here to show which nodes are on which
        // level.
        queue<BSTNode<Data>*>
            toVisit;         // Create an empty queue for level order travrsal
        toVisit.push(root);  // Enqueue root and initialize height
        int nodesPerLevel = 1;
        int totalSpacing = 1 << iheight;

        for (int i = 0; i <= iheight; i++) {
            for (int j = 0; j < nodesPerLevel; j++) {
                BSTNode<Data>* curr =
                    toVisit.front();  // returns a reference to the next element
                                      // in the queue; The next element is the
                                      // oldest element in the queue
                                      // and the same element that is poped out
                                      // from the queue
                                      // when pop is called.
                toVisit.pop();        // removes the next element in the queue,
                                      // reducing its size by 1
                if (curr == nullptr) {
                    *out << "X";
                    // If we have an entire missing subtree, we
                    // would like to print X's in place of all
                    // nodes because it avoids ambiguity
                    toVisit.push(nullptr);
                    toVisit.push(nullptr);
                } else {
                    *out << curr->getData();
                    toVisit.push(curr->left);
                    toVisit.push(curr->right);
                }
                for (int k = 0; k < totalSpacing / nodesPerLevel; k++) {
                    *out << "\t";
                }
            }
            *out << endl;
            nodesPerLevel *= 2;
        }
    }

  private:
    /** TODO Helper function for begin() */
    // returns a pointer to the node with the samllest data(the left-most node)
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        while (root->left != NULL) {
            root = root->left;
        }
        return root;
    }

    /** TODO */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
        if (n == 0) return;
        deleteAll(n->left);
        deleteAll(n->right);
        delete n;
    }

    /** TODO */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        return 0;
    }

    // Add more helper functions below
    // private helper method to help inorder()
    static void inorderpush(BSTNode<Data>* root1, vector<Data>& storevtr) {
        if ((root1 != 0) && (root1->left != 0)) {
            inorderpush(root1->left, storevtr);
        }
        storevtr.push_back(root1->getData());
        if ((root1 != 0) && (root1->right != 0)) {
            inorderpush(root1->right, storevtr);
        }
    }
};

#endif  // BST_HPP
