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
class TestBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    TestBSTFixture() {
        bst.insert(7);
        bst.insert(12);
        bst.insert(5);
        bst.insert(18);
        bst.insert(6);
    }
    ~TestBSTFixture() {}
};
TEST_F(TestBSTFixture, NON_EMPTY_ROOT) {
    // BST<int> bst;
    bst.insert(7);
    bst.insert(12);
    bst.insert(5);
    bst.insert(18);
    bst.insert(6);
    ASSERT_EQ(bst.empty(), false);
}
TEST_F(TestBSTFixture, NON_EMPTY_Size) {
    // BST<int> bst;
    bst.insert(7);
    bst.insert(12);
    bst.insert(5);
    bst.insert(18);
    bst.insert(6);
    ASSERT_EQ(bst.size(), 5) << "After inserting, the size is 5.";
}
TEST_F(TestBSTFixture, NON_EMPTY_Height) {
    // BST<int> bst;
    bst.insert(7);
    bst.insert(12);
    bst.insert(5);
    bst.insert(18);
    bst.insert(6);
    ASSERT_EQ(bst.height(), 2) << "After inserting, the height is 2.";
}
TEST_F(TestBSTFixture, CHECK_INSERT) {
    // BST<int> bst;
    EXPECT_FALSE(bst.insert(7));
    EXPECT_TRUE(bst.insert(4));
}
TEST_F(TestBSTFixture, CHECK_FIND) {
    // BST<int> bst;
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
