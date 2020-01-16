/**
 * TODO: add file header
 * This file implements BSTiterator class to the BST class.
 * Xuan Ding, xding@ucsd.edu
 * Qilong Li, qil009@ucsd.edu
 */
#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"

using namespace std;

/**
 * TODO: add class header
 * This class contains field of BSTNode<Data> pointer which allows user to
 * create iterator object to iterate through the BST in ascsending order.
 * Iterator is overloaded with ++ operator for increment.
 */
template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /**
     * Constructor that initialize the current BSTNode
     * in this BSTIterator.
     */
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}

    /** Dereference operator. */
    Data operator*() const { return curr->getData(); }

    /** Pre-increment operator. */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    /** Post-increment operator. */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /** TODO
     * Parameter: an constant BSTIterator<Data> type reference Iterator object
     * returns true if two objects' ptr points at the same address
     */
    bool operator==(BSTIterator<Data> const& other) const {
        return (this->curr == other.curr);
    }

    /** TODO
     * Parameter: an constant BSTIterator<Data> type reference Iterator object
     *  returns true if two object's ptr points at the different address
     */
    bool operator!=(BSTIterator<Data> const& other) const {
        return (this->curr != other.curr);
    }
};

#endif  // BSTITERATOR_HPP
