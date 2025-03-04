/**
 * TODO: add file header
 * This file implements the BST class. Source: stepik book
 * Xuan Ding, xding@ucsd.edu
 * Qilong Li, qil009@ucsd.edu
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
 * TODO: add class header:
 * This class uses protected fields of BSTNode<data>* inherted from
 * BSTNODE.hpp to create a binary search tree with no duplicates.
 * It contains protected fields include isize and height.
 * Besides, class default constructor creates an empty bst tree with root = 0,
 * isize = 0, iheight = -1. User is able to insert and search as well as
 * traversing the tree.
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

    /** TODO
     * Created a copy constructor, and calling buildSubtree to get a balanced
     * tree
     */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {
        vector<Data> vtr = bst.inorder();
        this->isize = bst.isize;
        this->root = buildSubtree(vtr, 0, bst.size() - 1, this->iheight);
    }

    /** TODO */
    ~BST() { deleteAll(this->root); }

    /** TODO
     * Parameter: a constant generic type variable's reference item.
     * Return true if insert the item correctly;
     * Return false if insert the item incorrectly.
     * If the tree is empty, we just created a node as the root, with value
     * "item". If the tree is nonempty, we should traverse the tree, find the
     * correct position to insert the node with value "item".
     */
    bool insert(const Data& item) {
        BSTNode<Data>* newNode = new BSTNode<Data>(item);
        // case1: empty tree, insert a node as root.(0 is same as NULL)
        if (this->root == 0) {
            this->root = newNode;
            isize = isize + 1;
            // Only insert a node, height become 0.
            iheight = iheight + 1;
            return true;
        }
        int height = 0;  // for us to record the height of BST
        BSTNode<Data>* currentptr = this->root;  // start at root
        // case2: when nonempty BST
        while (currentptr != NULL) {
            // go to right when the item is greater than current node
            if (currentptr->getData() < item) {
                // if the right is null, create a node
                if (currentptr->right == NULL) {
                    currentptr->right = newNode;
                    // set the newNode's parent=currentptr
                    newNode->parent = currentptr;
                    // when insert a newNode, the height and size must +1
                    isize = isize + 1;
                    height = height + 1;
                    // compare the height and the initial height, update height
                    if (height > this->iheight) {
                        this->iheight = height;
                    }
                    // sucessfully inserted the item
                    return true;
                } else {
                    // traverse the right-subtree
                    currentptr = currentptr->right;
                    // to get the right-most node's height
                    height = height + 1;
                }
                // go to left when the item is smaller than current node
            } else if (item < currentptr->getData()) {
                // if the left is null, create a node
                if (currentptr->left == NULL) {
                    currentptr->left = newNode;
                    // set the newNode's parent=currentptr
                    newNode->parent = currentptr;
                    isize = isize + 1;
                    height = height + 1;
                    // compare the height and the initial height, update height
                    if (height > this->iheight) {
                        this->iheight = height;
                    }
                    // sucessfully inserted the item
                    return true;
                } else {
                    // the left is not null, traverse the left tree.
                    currentptr = currentptr->left;
                    height = height + 1;  // to get the left-most node's height
                }
            } else {
                /**when the data of currentptr == item, appear duplicate case.
                 * when the newNode is duplicate, must to delete it.
                 */
                delete newNode;
                return false;
            }
        }
    }

    /** TODO
     * Parameter: a constant generic type variable's reference item.
     * Return an interator object when find the node with value "item",
     * Created a pointer to traverse the tree, and pass the correct pointer
     * to the iterator object, then return this iterator object.
     */
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

    /** TODO
     * To delete the node in BST
     * In general, there are three cases:
     *  1. when the node is a leaf node.
     * 2. when the node has only one child
     * 3. when the node has two children
     */
    // PART 2
    bool deleteNode(const Data& item) {
        BSTNode<Data>* curr = this->root;
        while (curr != NULL) {
            if (curr->getData() < item)
                curr = curr->right;
            else if (item < curr->getData())
                curr = curr->left;
            else {
                // case1: if curr is a leaf node
                if ((curr->left == NULL) && (curr->right == NULL)) {
                    // when the tree has only root node, set root to null, and
                    // delete it.
                    if (curr == this->root) {
                        curr = NULL;
                        delete curr;
                        this->isize = this->isize - 1;
                        this->iheight = finddepth(this->root);
                        return true;
                    } else {
                        // we have to set NULL pointer after deleting
                        if (curr == curr->parent->left) {
                            curr->parent->left = NULL;
                            delete curr;
                            this->isize = this->isize - 1;
                            this->iheight = finddepth(this->root);
                            return true;
                        } else {
                            curr->parent->right = NULL;
                            delete curr;
                            this->isize = this->isize - 1;
                            this->iheight = finddepth(this->root);
                            return true;
                        }
                    }

                }
                // case2:node has two child
                else if ((curr->left != NULL) && (curr->right != NULL)) {
                    // Set a pointer that points to curr node's successor
                    BSTNode<Data>* successorPtr = curr->successor();
                    // 1. when successorPtr doesn't have the right child, then
                    // just replace the curr node's data with its successorPtr's
                    // data.
                    if (successorPtr->right == NULL) {
                        curr->setData(successorPtr->getData());
                        // When the successorPtr = successorPtr->parent->right
                        /**        7
                         *        / \
                         *       5  20
                         */
                        if (successorPtr == successorPtr->parent->right) {
                            // Set the successorPtr as NULL, and delete it
                            successorPtr->parent->right = NULL;
                            delete successorPtr;
                            this->isize = this->isize - 1;
                            this->iheight = finddepth(this->root);
                            return true;

                        }
                        /**When successorPtr = successorPtr->parent->left
                         *                7
                         *               / \
                         *              5   20
                         *                  /
                         *                 15
                         */
                        else {
                            // When the successorPtr is on the left, set as
                            // NULL, and delete it.
                            successorPtr->parent->left = NULL;
                            delete successorPtr;
                            this->isize = this->isize - 1;
                            this->iheight = finddepth(this->root);
                            return true;
                        }
                    }
                    // 2. when the successorPtr has the right subtree, then we
                    // need the replace its data with curr node's data. And
                    // connect successorPtr's right subtree with its parent. In
                    // this case, the successorPtr can't have the left subtree.
                    else {
                        /**           7
                         *           / \
                         *          5   10
                         *              /
                         *             8
                         *              \
                         *               9
                         * In the above example, to delete 7, 8 is 7's
                         * successor. And 8 has its right child. We need to
                         * replace data with curr and its successor, then
                         * connect 9 to successor's parent!!!
                         */
                        if (successorPtr == successorPtr->parent->left) {
                            curr->setData(successorPtr->getData());
                            successorPtr->right->parent = successorPtr->parent;
                            successorPtr->parent->left = successorPtr->right;
                            delete successorPtr;
                            this->isize = this->isize - 1;
                            this->iheight = finddepth(this->root);
                            return true;
                        }
                        /**              7
                         *              / \
                         *             5  20
                         *                  \
                         *                   25
                         *                   / \
                         *                  21  30
                         */
                        else {
                            curr->setData(successorPtr->getData());
                            // connect successorPtr's child with its partent
                            successorPtr->right->parent = curr;
                            curr->right = successorPtr->right;
                            // then delete successorPtr
                            delete successorPtr;
                            this->isize = this->isize - 1;
                            this->iheight = finddepth(this->root);
                            return true;
                        }
                    }
                }
                // case3: node has exactly one child
                else {
                    // First, the condition of the current node has right child,
                    // but not left child.
                    // 1. If curr is root, then curr->left is the new root,
                    // then set this new root's parent as NULL. Then, delete
                    // curr node, update size, height, return true.
                    // 2. curr is its parent's left child，then set
                    // curr->parent->left = curr->left. 3. If curr is its
                    // parent's right child，then set curr->parent->right =
                    // curr->left.
                    if (curr->left != NULL) {
                        /**         7
                         *         /
                         *        3
                         *       / \
                         *      2   5
                         */
                        if (curr->parent == NULL) {
                            this->root = curr->left;
                            this->root->parent = NULL;
                            delete curr;
                            this->isize = this->isize - 1;
                            this->iheight = finddepth(this->root);
                            return true;
                        } else {
                            curr->left->parent = curr->parent;
                            /** 1.if curr node is its parent's left node
                             *            10
                             *            /
                             *           5
                             *          /
                             *         3
                             *        / \
                             *       1   4
                             */
                            if (curr == curr->parent->left) {
                                curr->parent->left = curr->left;
                                delete curr;
                                this->isize = this->isize - 1;
                                this->iheight = finddepth(this->root);
                                return true;
                            }

                            /** 2.if curr node is its parent's right node
                             *             5
                             *              \
                             *               15
                             *               /
                             *              10
                             *              / \
                             *             9   12
                             */
                            else {
                                curr->parent->right = curr->left;
                                delete curr;
                                this->isize = this->isize - 1;
                                this->iheight = finddepth(this->root);
                                return true;
                            }
                        }
                    }
                    // The next is, the condition of current node has right
                    // child, but not left child.
                    // 1. If curr is root, then set curr->right as root,
                    // then set root->parent as NULL.
                    // Then delete curr node, update size, height, return
                    // true.
                    // 2.If curr is its parent's left
                    // child，then set curr->parent->left = curr->right.
                    // 3. If curr is its parent's right child,
                    // then set curr->parent->right = curr->right.
                    // when curr node's only one child is on the right
                    else {
                        if (curr->parent == NULL) {
                            this->root = curr->right;
                            this->root->parent = NULL;
                            delete curr;
                            this->isize = this->isize - 1;
                            this->iheight = finddepth(this->root);
                            return true;
                        } else {
                            curr->right->parent = curr->parent;
                            // 1.if curr node is its parent's left node
                            if (curr == curr->parent->left) {
                                curr->parent->left = curr->right;
                                delete curr;
                                this->isize = this->isize - 1;
                                this->iheight = finddepth(this->root);
                                return true;
                            }
                            // 2.if curr node is its parent's right node
                            else {
                                curr->parent->right = curr->right;
                                delete curr;
                                this->isize = this->isize - 1;
                                this->iheight = finddepth(this->root);
                                return true;
                            }
                        }
                    }  // else: the condition of curr has right child, but not
                       // left child.
                }      // All the conditions in case3
            }  // else: when found the node in the tree, concludes case1,2,3.
        }  // while: when not found the node in the tree, which reaches the end
           // of tree,
        // return false
        // not found the node with item that need to be deleted
        return false;
    }  // The whole deleteNode() function

    /** TODO
     * return the size of BST
     */
    unsigned int size() const { return this->isize; }

    /** TODO
     * return the height of BST.
     * If it's an empty BST, return -1.
     */
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
        // call first(), and create an object pointing to the smallest
        // element in BST
        iterator start(first(this->root));
        return start;
    }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO
     * return a vector that contains all the data in BST in ascending
     * ordering.
     */
    vector<Data> inorder() const {
        vector<Data> vtr;
        // When BST is empty, return an empty vector.
        if (this->root == 0) return vtr;
        // call the private helper method: inorderpush
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
                    toVisit.front();  // returns a reference to the next
                                      // element in the queue; The next
                                      // element is the oldest element
                                      // in the queue and the same
                                      // element that is poped out from
                                      // the queue when pop is called.
                toVisit.pop();        // removes the next element in the
                                      // queue, reducing its size by 1
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
    /** TODO Helper function for begin()
     * Parameter: a BSTNode<Data> type pointer
     * returns a pointer to the node with the samllest data(the
     * left-most node)
     */
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        if (root == 0) return NULL;
        while (root->left != NULL) {
            root = root->left;
        }
        return root;
    }

    /** TODO
     * Parameter: a BSTNode<Data> type pointer
     * Being called in the destructor, to recursively delete all the
     * nodes.
     */
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

    /** TODO
     * using this function to let the old BST object to create an balanced BST
     */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        // Example: 7, 9 ,10, 11, 20, 30
        if (start > end) return 0;
        int median = (start + end + 1) / 2;
        BSTNode<Data>* rootptr = new BSTNode<Data>(data[median]);
        depth = depth + 1;
        if (this->iheight < depth) this->iheight = depth;
        // left subtree
        rootptr->left = buildSubtree(data, start, median - 1, depth);
        /** when the ptr is not null, we can connect it with its parent node.
         * Otherwise, we shouldn't connect it with its parent node because
         * it will cause segment fault if we connect nullptr with nullptr's
         * parent.
         */
        if (rootptr->left != NULL) (rootptr->left)->parent = rootptr;
        // right subtree
        rootptr->right = buildSubtree(data, median + 1, end, depth);
        if (rootptr->right != NULL) (rootptr->right)->parent = rootptr;
        return rootptr;
    }

    // Add more helper functions below
    /**private helper method to help inorder()
     * Parameter: a BSTNode<Data> type poiner, a vector reference
     *variable Being called in inorder(), recursively pushed all the
     *data in BST to the vector.
     */
    static void inorderpush(BSTNode<Data>* root1, vector<Data>& storevtr) {
        if ((root1 != 0) && (root1->left != 0)) {
            inorderpush(root1->left, storevtr);
        }
        storevtr.push_back(root1->getData());
        if ((root1 != 0) && (root1->right != 0)) {
            inorderpush(root1->right, storevtr);
        }
    }
    int finddepth(BSTNode<Data>* root) {
        if (root == NULL) return -1;
        // int height = 0;
        // depth = depth + 1;
        int lDepth = finddepth(root->left);
        int rDepth = finddepth(root->right);
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
        // int height = (lDepth < rDepth) ? rDepth : lDepth;
        // return height;
    }
    // int maxDepth(BSTNode<Data>* node) {
    //     if (node == NULL)
    //         return -1;
    //     else {
    //         int lDepth = maxDepth(node->left);
    //         int rDepth = maxDepth(node->right);
    //         if (lDepth > rDepth)
    //             return (lDepth + 1);
    //         else
    //             return (rDepth + 1);
    //     }
    // }
};

#endif  // BST_HPP
