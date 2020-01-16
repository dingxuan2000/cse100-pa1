/**
 * TODO: add file header
 * This file provides BSTNODE class to the BST class.
 * Xuan Ding, xding@ucsd.edu
 * Qilong Li, qil009@ucsd.edu
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * TODO: add class header
 * the field of BSTNODE class contains private member: data.
 * left, right and parent pointer of the node.
 * The class includes public mutator and accessor which allows user to
 * read and write to data. It also contains successor method which returns the
 * address of node that contains next smallest data.
 */
template <typename Data>
class BSTNode {
  private:
    Data data;

  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    /** TODO */
    BSTNode(const Data& d) : data(d) {
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }

    /** Set the value of data */
    void setData(const Data& d) { data = d; }

    /** Get the value of data */
    Data getData() { return data; }

    /** TODO
     * returns the address of next smallest data
     */
    BSTNode<Data>* successor() {
        // First case: the current node has the right child, and then traverse
        // the right-subtree to get the smallest element in that sub-tree.
        BSTNode<Data>* smallest;
        if (this->right != NULL) {
            smallest = this->right;
            while (smallest->left != NULL) {
                smallest = smallest->left;
            }
            return smallest;
        } else {
            smallest = this;
            // Traverse its parent nodes recursively
            while (smallest->parent != NULL) {
                if (smallest == smallest->parent->left)
                    return smallest->parent;
                else
                    smallest = smallest->parent;
            }
            return NULL;
        }
    }
};

/**
 * DO NOT CHANGE THIS METHOD
 * Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
