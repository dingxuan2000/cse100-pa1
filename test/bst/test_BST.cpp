#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing ::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}
//----------------------------------------------------------
// TODO : add more BST tests here
TEST(BSTTests, EMPTY_HEIGHT) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1) << "Before inserting, the height is -1.";
}
TEST(BSTTests, EMPTY_SIZE) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0) << "Before inserting, the size is 0.";
}
TEST(BSTTests, EMPTY_ROOT) {
    BST<int> bst;
    ASSERT_EQ(bst.empty(), true) << "Before inserting, the tree is empty.";
}
TEST(BSTTests, EMPTY_INSERT) {
    BST<int> bst;
    ASSERT_EQ(bst.insert(7), true);
}
TEST(BSTTests, EMPTY_FIND) {
    BST<int> bst;
    ASSERT_EQ(bst.find(7), nullptr);
}
TEST(BSTTests, EMPTY_BEGIN) {
    BST<int> bst;
    ASSERT_EQ(bst.begin(), nullptr);
}
TEST(BSTTests, EMPTY_INORDER) {
    BST<int> bst;
    vector<int> vtr{};
    ASSERT_EQ(bst.inorder(), vtr);
}
class TestBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;
    // BST<int> newbst(*bst);

  public:
    TestBSTFixture() {
        bst.insert(7);
        bst.insert(12);
        bst.insert(5);
        bst.insert(18);
        bst.insert(6);
        // newbst.insert(7);
        // newbst.insert(12);
        // newbst.insert(5);
        // newbst.insert(18);
        // newbst.insert(6);
    }
    ~TestBSTFixture() {}
};
TEST_F(TestBSTFixture, NON_EMPTY_ROOT) { ASSERT_EQ(bst.empty(), false); }
TEST_F(TestBSTFixture, NON_EMPTY_Size) {
    ASSERT_EQ(bst.size(), 5) << "After inserting, the size is 5.";
}
TEST_F(TestBSTFixture, NON_EMPTY_Height) {
    ASSERT_EQ(bst.height(), 2) << "After inserting, the height is 2.";
}
TEST_F(TestBSTFixture, CHECK_INSERT) {
    EXPECT_FALSE(bst.insert(7));
    // bst.insert(4);
    EXPECT_TRUE(bst.insert(4));
    EXPECT_EQ(bst.height(), 2);
    // bst.insert(19);
    EXPECT_TRUE(bst.insert(19));
    EXPECT_EQ(bst.height(), 3);
}
TEST_F(TestBSTFixture, CHECK_FIND) {
    EXPECT_EQ(bst.find(4), nullptr);
    EXPECT_EQ(*(bst.find(7)), 7);
    EXPECT_EQ(*(bst.find(12)), 12);
    EXPECT_EQ(*(bst.find(5)), 5);
    EXPECT_EQ(*(bst.find(18)), 18);
    ASSERT_EQ(*(bst.find(6)), 6);
}
TEST_F(TestBSTFixture, CHECK_INORDER) {
    vector<int> vtr{5, 6, 7, 12, 18};
    ASSERT_EQ(bst.inorder(), vtr);
}
TEST_F(TestBSTFixture, CHECK_BEGIN) { ASSERT_EQ(*(bst.begin()), 5); }
TEST_F(TestBSTFixture, CHECK_END) { ASSERT_EQ(bst.end(), nullptr); }

TEST_F(TestBSTFixture, CHECK_PRINT) { bst.print(&cout); }
TEST(BSTTests, DELETENODE_RIGHT_LINKEDLIST) {
    BST<int> bstr;
    bstr.insert(2);
    bstr.insert(3);
    bstr.insert(6);
    bstr.insert(12);
    bstr.insert(18);
    bstr.insert(50);
    // vector<int> vtr = bstr.inorder();
    EXPECT_TRUE(bstr.deleteNode(2));
    ASSERT_EQ(bstr.size(), 5);
}
TEST(BSTTests, DELETENODE_LEFT_LINKEDLIST) {
    BST<int> bstr;
    bstr.insert(50);
    bstr.insert(18);
    bstr.insert(12);
    bstr.insert(6);
    bstr.insert(3);
    bstr.insert(2);
    // vector<int> vtr = bstr.inorder();
    EXPECT_TRUE(bstr.deleteNode(50));
    ASSERT_EQ(bstr.size(), 5);
}

TEST(BSTTests, DELETENODE_LEAFNODE_ROOT) {
    BST<int> bstr;
    bstr.insert(2);
    ASSERT_TRUE(bstr.deleteNode(2));
}
TEST(BSTTests, DELETENODE_RIGHT_LEAFNODE) {
    BST<int> bstr;
    bstr.insert(7);
    bstr.insert(5);
    bstr.insert(10);
    bstr.insert(20);
    EXPECT_TRUE(bstr.deleteNode(20));
    ASSERT_EQ(bstr.size(), 3);
}
TEST(BSTTests, DELETENODE_LEFT_LEAFNODE) {
    BST<int> bstr;
    bstr.insert(7);
    bstr.insert(5);
    bstr.insert(10);
    bstr.insert(8);
    EXPECT_TRUE(bstr.deleteNode(8));
    ASSERT_EQ(bstr.size(), 3);
}
TEST(BSTTests, DELETENODE_NODE_TWOCHILD_CASE1) {
    BST<int> bstr;
    bstr.insert(7);
    bstr.insert(5);
    bstr.insert(20);
    EXPECT_TRUE(bstr.deleteNode(7));
    ASSERT_EQ(bstr.size(), 2);
}
TEST(BSTTests, DELETENODE_NODE_TWOCHILD_CASE2) {
    BST<int> bstr;
    bstr.insert(7);
    bstr.insert(5);
    bstr.insert(20);
    bstr.insert(15);
    EXPECT_TRUE(bstr.deleteNode(15));
    ASSERT_EQ(bstr.size(), 3);
}
TEST(BSTTests, DELETENODE_NODE_TWOCHILD_CASE3) {
    BST<int> bstr;
    bstr.insert(7);
    bstr.insert(5);
    bstr.insert(10);
    bstr.insert(8);
    bstr.insert(9);
    EXPECT_TRUE(bstr.deleteNode(7));
    ASSERT_EQ(bstr.size(), 4);
}
TEST(BSTTests, DELETENODE_NODE_TWOCHILD_CASE4) {
    BST<int> bstr;
    bstr.insert(7);
    bstr.insert(5);
    bstr.insert(20);
    bstr.insert(25);
    bstr.insert(21);
    bstr.insert(30);
    EXPECT_TRUE(bstr.deleteNode(7));
    ASSERT_EQ(bstr.size(), 5);
}
TEST(BSTTests, DELETENODE_NODE_SINGLECHILD_CASE1) {
    BST<int> bstr;
    bstr.insert(7);
    bstr.insert(3);
    bstr.insert(2);
    bstr.insert(5);
    EXPECT_TRUE(bstr.deleteNode(7));
    ASSERT_EQ(bstr.size(), 3);
}
TEST(BSTTests, DELETENODE_NODE_SINGLECHILD_CASE2) {
    BST<int> bstr;
    bstr.insert(7);
    bstr.insert(10);
    bstr.insert(8);
    bstr.insert(15);
    EXPECT_TRUE(bstr.deleteNode(7));
    ASSERT_EQ(bstr.size(), 3);
}
TEST(BSTTests, DELETENODE_NODE_SINGLECHILD_CASE3) {
    BST<int> bstr;
    bstr.insert(10);
    bstr.insert(5);
    bstr.insert(3);
    bstr.insert(1);
    bstr.insert(4);
    EXPECT_TRUE(bstr.deleteNode(5));
    ASSERT_EQ(bstr.size(), 4);
}
TEST(BSTTests, DELETENODE_NODE_SINGLECHILD_CASE4) {
    BST<int> bstr;
    bstr.insert(5);
    bstr.insert(15);
    bstr.insert(10);
    bstr.insert(9);
    bstr.insert(12);
    EXPECT_TRUE(bstr.deleteNode(15));
    ASSERT_EQ(bstr.size(), 4);
}
TEST(BSTTests, DELETENODE_NODE_SINGLECHILD_CASE5) {
    BST<int> bstr;
    bstr.insert(20);
    bstr.insert(10);
    bstr.insert(25);
    bstr.insert(15);
    bstr.insert(13);
    bstr.insert(17);
    EXPECT_TRUE(bstr.deleteNode(10));
    ASSERT_EQ(bstr.size(), 5);
}
TEST(BSTTests, DELETENODE_NODE_SINGLECHILD_CASE6) {
    BST<int> bstr;
    bstr.insert(10);
    bstr.insert(5);
    bstr.insert(20);
    bstr.insert(30);
    bstr.insert(25);
    bstr.insert(35);
    EXPECT_TRUE(bstr.deleteNode(20));
    ASSERT_EQ(bstr.size(), 5);
}

TEST(BSTTests, CHECK_BALANCING) {
    BST<int> bstr = BST<int>();
    bstr.insert(7);
    bstr.insert(5);
    bstr.insert(12);
    bstr.insert(4);
    bstr.insert(6);
    bstr.insert(18);
    bstr.insert(17);
    bstr.insert(20);
    BST<int> copy = BST<int>(bstr);
    BST<int>::iterator it = copy.begin();
    vector<int> vtr{4, 5, 6, 7, 12, 17, 18, 20};
    for (int i = 0; i < bstr.size(); i++) {
        ASSERT_EQ(*it, vtr[i]);
        it++;
    }
}
