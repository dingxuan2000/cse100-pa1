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

// TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
//     BST<int> bst;
//     ASSERT_EQ(bst.height(), -1);
// }

// /* Small BST test starts here */

// /**
//  * A simple test fixture from which multiple tests
//  * can be created. All fixture tests (denoted by the
//  * TEST_F macro) can access the protected members of this
//  * fixture. Its data is reset after every test.
//  *
//  * Builds the following BST:
//  *         3
//  *        / \
//  *       1   4
//  *      /     \
//  *    -33     100
//  */
// class SmallBSTFixture : public ::testing ::Test {
//   protected:
//     BST<int> bst;

//   public:
//     SmallBSTFixture() {
//         // initialization code here
//         vector<int> input{3, 4, 1, 100, -33};
//         insertIntoBST(input, bst);
//     }
//     // code in SetUp() will execute just before the test ensues
//     // void SetUp() {}
// };

// TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
//     // assert that the small BST has the correct size
//     ASSERT_EQ(bst.size(), 5);
// }

// TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
//     // assert failed duplicate insertion
//     ASSERT_FALSE(bst.insert(3));
// }

// TODO: add more BST tests here
// TEST(BSTTests, EMPTY_BST) {
//     BST<int>* bst;
//     ASSERT_TRUE((bst->isize) == 0);
// }
// template <typename T>
class TestBSTFixture : public ::testing::Test {
  public:
    BST<int> bstr;
    TestBSTFixture() {}
    ~TestBSTFixture() {}
};
// TEST_F(TestBSTFixture, EMPTY_ROOT) {
//     ASSERT_EQ(bstr.empty(), true) << "It's failed.";
// }
// TEST(TestBSTFixture, EMPTY_Size) {
//     BST<int> bstr;
//     ASSERT_EQ(bstr.size(), 0) << "It's failed.";
// }
// TEST(TestBSTFixture, EMPTY_Height) {
//     BST<int> bstr;
//     ASSERT_EQ(bstr.height(), -1) << "It's failed.";
// }
TEST_F(TestBSTFixture, CHECK_INSERT) {
    ASSERT_EQ(bstr.insert(7), true) << "It's failed.";
}
// TEST_F(TestBSTFixture, CHECK_FIND) {
//     bstr.insert(4);
//     ASSERT_EQ(*(bstr.find(4)), 4) << "It's failed.";
// }
// TEST_F(TestBSTFixture, EMPTY_ISIZE) { ASSERT_EQ(bstr->isize, 0); }
// TEST_F(TestBSTFixture, EMPTY_IHEIGHT) { ASSERT_EQ(bstr->iheight, 0); }

// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }