/**
 * TODO: add file header
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
    ~BST() {}

    /** TODO */
    bool insert(const Data& item) {
        BSTNode<Data>* ptr = this->root;
        while (ptr != NULL) {
            if (*ptr < item)
                ptr = ptr->left;
            else if (item < *ptr)
                ptr = ptr->right;
            else
                return false;
        }
        BSTNode<data>* newNode = new BSTNode();
        newnode->data = item;
        newNode->left = 0;
        newNode->right = NULL;
        newNode->parent = ptr

            // ptr->getData() = item;  // Manybe grammer error
            return true;
    }

    /** TODO */
    // BSTIterator<Data>
    iterator find(const Data& item) const {
        // iterator iobj = new iterator(this->root);
        // // cout << *(ptr.curr) << endl;
        // int val = *(iobj.curr);  // cannot access the curr pointer, as curr
        // is a
        //                          // private member
        // while (iobj.curr != NULL) {
        //     if (item < val)
        //         iobj.curr = iobj.curr->left;
        //     else if (val < item)
        //         iobj.curr = iobj.curr->right;
        //     else
        //         return iobj;
        // }
        // iobj.curr = nullptr;
        // return iobj;
        return 0;
    }

    /** TODO */  // PART 2
    bool deleteNode(const Data& item) { return false; }

    /** TODO */
    unsigned int size() const { return this->isize; }

    /** TODO */
    int height() const {
        if (this->empty()) return -1;
        //
        return this->iheight;
    }

    /** TODO */
    bool empty() const {
        if (this->root == NULL)
            return true;
        else
            return false;
    }

    /** TODO */
    iterator begin() const {
        // iterator start = new iterator(
        //     first(this->root));  // Not sure, maybe the grammer error
        // return start;
        return 0;
    }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    vector<Data> inorder() const {}

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
    }

    /** TODO */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        return 0;
    }

    // Add more helper functions below
};

#endif  // BST_HPP
