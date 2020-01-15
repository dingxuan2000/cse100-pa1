#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_NODE_TESTS, TEST_SUCCESSOR) {
    BSTNode<int> node(3);
    ASSERT_EQ(node.successor(), nullptr);
}
// class TestBSTNodeFixture : public ::testing::Test {
//   protected:
//     BSTNode<int> node;
//     int data;

//   public:
//     // TestBSTNodeFixture(const) {}
// };
TEST(TestBSTNodeFixture, CHECK_GETDATA) {
    BSTNode<int> node(8);
    ASSERT_EQ(node.getData(), 8);
}
TEST(TestBSTNodeFixture, CHECK_SUCCESSOR_CASE1) {
    BSTNode<int> node(5);
    BSTNode<int> node1(8);
    BSTNode<int> node2(2);
    BSTNode<int> node3(7);
    // node.left = node2;
    // node->right = node1;
    // node1->left = node3;
    // node2->parent = node;
    // node1->parent = node;
    // node3->parent = node1;
    // EXPECT_EQ(node->successor(), node3);
    // EXPECT_EQ(node1->successor(), nullptr);
    // EXPECT_EQ(node2->successor(), node);
    // EXPECT_EQ(node3->successor(), node1);
}
