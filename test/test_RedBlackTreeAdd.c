#include <stdio.h>
#include "unity.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

Node node1, node5, node6, node7, node8, node10, node13, node15, node17, node20, node30;

void setUp(void)
{
    resetNode(&node1, 1);
    resetNode(&node5, 5);
    resetNode(&node6, 6);
    resetNode(&node7, 7);
    resetNode(&node8, 8);
    resetNode(&node10, 10);
    resetNode(&node13, 13);
    resetNode(&node15, 15);
    resetNode(&node17, 17);
    resetNode(&node20, 20);
    resetNode(&node30, 30);
}

void tearDown(void)
{
}

/**
 *                add 10
 * root -> NULL  ------->  10(b)  <- root
 */
void test_addRedBlackTree_add_10_to_empty_tree(void)
{
	setNode(&node10, NULL, NULL, 'r');
    Node *root = NULL;

    addRedBlackTree(&root, &node10);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    //                     left right colour  node
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
    // TEST_ASSERT_EQUAL('b', node10.colour);
    // TEST_ASSERT_EQUAL_PTR(NULL, node10.left);
    // TEST_ASSERT_EQUAL_PTR(NULL, node10.right);
}

/**
 *                 add 5
 * root -> 10(b)  ------->   10(b)  <- root
 *                           /
 *                         5(r)
 */
void test_addRedBlackTree_add_5_to_use_tree_with_only_root_10(void)
{
	setNode(&node10, NULL, NULL, 'b');
	setNode(&node5, NULL, NULL, 'r');
    Node *root = &node10;

    addRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    //                      left  right colour  node
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
}

/**
 *                 add 15
 * root -> 10(b)  ------->   10(b)  <- root
 *                              \
 *                             15(r)
 */
void test_addRedBlackTree_add_15_to_use_tree_with_only_root_10(void)
{
	setNode(&node10, NULL, NULL, 'b');
	setNode(&node15, NULL, NULL, 'r');
    Node *root = &node10;

    addRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(root, &node10);

    TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}

/**
 *                               10(b)  <- root
 * root -> 10(b)   add 1         /                            5(b)   <- root
 *         /      ------->    5(r)              ------>      /   \
 *      5(r)                  /                           1(r)  10(r)
 *                          1(r)
 */
void test_addRedBlackTree_add_1_to_use_tree_with_root_10(void)
{
    setNode(&node1, NULL, NULL, 'r');
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node10, &node5, NULL, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node1);

    TEST_ASSERT_EQUAL_PTR(root, &node5);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
    TEST_ASSERT_EQUAL_NODE(&node1, &node10, 'b', &node5);
}

/**
 *                               10(b)  <- root
 * root -> 10(b)   add 7         /                            7(b)   <- root
 *         /      ------->    5(r)              ------>      /   \
 *      5(r)                    \                           5(r)  10(r)
 *                             7(r)
 */
void test_addRedBlackTree_add_7_to_use_tree_with_root_10(void)
{
    setNode(&node7, NULL, NULL, 'r');
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node10, &node5, NULL, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node7);

    TEST_ASSERT_EQUAL_PTR(root, &node7);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(&node5, &node10, 'b', &node7);
}

/**
 * root -> 10(b)   add 20      10(b)  <- root
 *         /      ------->    /   \
 *      5(r)               5(r)  20(r)
 */
void test_addRedBlackTree_add_20_to_use_tree_with_root_10(void)
{
    setNode(&node5, NULL, NULL, 'r');
	setNode(&node20, NULL, NULL, 'r');
	setNode(&node10, &node5, NULL, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node20);

    TEST_ASSERT_EQUAL_PTR(root, &node10);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
    TEST_ASSERT_EQUAL_NODE(&node5, &node20, 'b', &node10);
}

/**
 *                             10(b)  <- root
 * root -> 10(b)    add 30        \                      20(b)   <- root
 *            \    ------->      20(r)        ------>    /   \
 *           20(r)                  \                 10(r)  30(r)
 *                                 30(r)
 */
void test_addRedBlackTree_add_30_to_use_tree_with_root_10(void)
{
    setNode(&node30, NULL, NULL, 'r');
	setNode(&node20, NULL, NULL, 'r');
	setNode(&node10, NULL, &node20, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node30);

    TEST_ASSERT_EQUAL_PTR(root, &node20);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node30);
    TEST_ASSERT_EQUAL_NODE(&node10, &node30, 'b', &node20);
}

/**
 *                             10(b)  <- root
 * root -> 10(b)    add 15        \                       15(b)   <- root
 *            \    ------->      20(r)        ------>    /   \
 *           20(r)               /                    10(r)  20(r)
 *                            15(r)
 */
void test_addRedBlackTree_add_15_to_use_tree_with_root_10(void)
{
    setNode(&node15, NULL, NULL, 'r');
	setNode(&node20, NULL, NULL, 'r');
	setNode(&node10, NULL, &node20, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(root, &node15);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
    TEST_ASSERT_EQUAL_NODE(&node10, &node20, 'b', &node15);
}

/**
 * root -> 10(b)    add 5       10(b)  <- root
 *            \    ------->    /   \
 *           20(r)           5(r)  20(r)
 */
void test_addRedBlackTree_add_5_to_use_tree_with_root_10(void)
{
    setNode(&node5, NULL, NULL, 'r');
	setNode(&node20, NULL, NULL, 'r');
	setNode(&node10, NULL, &node20, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(root, &node10);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
    TEST_ASSERT_EQUAL_NODE(&node5, &node20, 'b', &node10);
}