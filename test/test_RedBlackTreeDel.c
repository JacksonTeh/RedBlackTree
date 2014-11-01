#include <stdio.h>
#include "unity.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

Node node1, node5, node6, node7, node8, node10, node13, node15, node17, node20, node25, node30;

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
    resetNode(&node25, 25);
    resetNode(&node30, 30);
}

void tearDown(void)
{
}

/** 2-node case
 *                remove 5
 * root -> 1(b)  ---------> Throw ERR_NODE_UNAVAILABLE
 */
void test_delRedBlackTree_remove_5_from_tree_with_only_root_1(void)
{
    CEXCEPTION_T err;
    setNode(&node1, NULL, NULL, 'b');
    Node *root = &node1, *node;

    Try{
        node = delRedBlackTree(&root, &node5);
        TEST_FAIL_MESSAGE("Expected ERR_NODE_UNAVAILABLE to be thrown. But receive none");
    } Catch(err)
    {
        TEST_ASSERT_EQUAL_PTR(root, &node1);
        //                      left  right colour  node
        TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
    }
}

/** 2-node case
 *                remove 1
 * root -> 1(b)  ---------> NULL <- root
 */
void test_delRedBlackTree_remove_1_from_tree_with_only_root_1(void)
{
    setNode(&node1, NULL, NULL, 'b');
    Node *root = &node1, *node;

    node = delRedBlackTree(&root, &node1);

    TEST_ASSERT_EQUAL_PTR(root, NULL);
    TEST_ASSERT_EQUAL_PTR(node, &node1);
}

/** 3-node case
 * root -> 1(b)   remove 5
 *            \  ---------> 1(b) <- root
 *           5(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_1_5_nodes(void)
{
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node1, NULL, &node5, 'b');
    Node *root = &node1, *node;

    node = delRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(root, &node1);
    TEST_ASSERT_EQUAL_PTR(node, &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
}

/** 3-node case
 * root -> 5(b)   remove 1
 *        /      ---------> 5(b) <- root
 *      1(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_1_5_nodes(void)
{
    setNode(&node1, NULL, NULL, 'r');
    setNode(&node5, &node1, NULL, 'b');
    Node *root = &node5, *node;

    node = delRedBlackTree(&root, &node1);

    TEST_ASSERT_EQUAL_PTR(root, &node5);
    TEST_ASSERT_EQUAL_PTR(node, &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
}

/** 3-node case
 * root -> 10(b)                  10(b) <- root               15(b) <- root
 *        /    \      remove 5        \                       /   \
 *      5(b)  15(r)  ---------->     15(r)     ----------> 10(b) 20(b)
 *            /   \                  /   \                     \
 *         13(b) 20(b)            13(b) 20(b)                 13(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_5_10_13_15_20_nodes(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, &node13, &node20, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(root, &node15);
    TEST_ASSERT_EQUAL_PTR(node, &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, &node13, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node10, &node20, 'b', &node15);
}

/** 3-node case
 * root -> 10(b)                    10(b) <- root
 *        /    \      remove 13    /    \
 *      5(b)  15(r)  ----------> 5(b)  15(b)
 *            /   \                        \
 *         13(b) 20(b)                    20(r)
 */
void test_delRedBlackTree_remove_13_from_tree_with_5_10_13_15_20_nodes(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, &node13, &node20, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node13);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    TEST_ASSERT_EQUAL_PTR(node, &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
    TEST_ASSERT_EQUAL_NODE(NULL, &node20, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** 3-node case
 * root -> 10(b)                    10(b) <- root
 *        /    \      remove 20    /    \
 *      5(b)  15(r)  ----------> 5(b)  15(b)
 *            /   \                    /
 *         13(b) 20(b)              13(r)
 */
void test_delRedBlackTree_remove_20_from_tree_with_5_10_13_15_20_nodes(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, &node13, &node20, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node20);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    TEST_ASSERT_EQUAL_PTR(node, &node20);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
    TEST_ASSERT_EQUAL_NODE(&node13, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** 4-node case
 * root -> 10(b)    remove 5   10(b) <- root
 *        /    \   --------->      \
 *      5(r)  15(r)               15(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_5_10_15_nodes(void)
{
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    TEST_ASSERT_EQUAL_PTR(node, &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
    TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
}

/** 4-node case
 * root -> 10(b)    remove 15  10(b) <- root
 *        /    \   --------->      \
 *      5(r)  15(r)               15(r)
 */
void test_delRedBlackTree_remove_15_from_tree_with_5_10_15_nodes(void)
{
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    TEST_ASSERT_EQUAL_PTR(node, &node15);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node10);
}

/** 4-node case
 * root ->   10(b)                         10(b)   <- root
 *        /        \      remove 1      /        \
 *      5(r)      15(r)  ---------->  5(b)      15(r)
 *     /   \     /   \                    \     /   \
 *   1(b) 7(b) 13(b) 20(b)               7(r) 13(b) 20(b)
 */
 void test_delRedBlackTree_remove_1_from_tree_with_1_5_7_10_13_15_20_nodes(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'r');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, &node13, &node20, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node1);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    TEST_ASSERT_EQUAL_PTR(node, &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'r', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** 4-node case
 * root ->   10(b)                         10(b)   <- root
 *        /        \      remove 7      /        \
 *      5(r)      15(r)  ---------->  5(b)      15(r)
 *     /   \     /   \               /          /   \
 *   1(b) 7(b) 13(b) 20(b)         1(r)      13(b) 20(b)
 */
 void test_delRedBlackTree_remove_7_from_tree_with_1_5_7_10_13_15_20_nodes(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'r');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, &node13, &node20, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node7);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    TEST_ASSERT_EQUAL_PTR(node, &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'r', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** 4-node case
 * root ->   10(b)                         10(b)   <- root
 *        /        \      remove 13     /        \
 *      5(r)      15(r)  ---------->  5(b)      15(r)
 *     /   \     /   \               /   \           \
 *   1(b) 7(b) 13(b) 20(b)         1(r) 7(b)        20(b)
 */
 void test_delRedBlackTree_remove_13_from_tree_with_1_5_7_10_13_15_20_nodes(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'r');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, &node13, &node20, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node13);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    TEST_ASSERT_EQUAL_PTR(node, &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
    TEST_ASSERT_EQUAL_NODE(&node1, &node7, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
    TEST_ASSERT_EQUAL_NODE(NULL, &node20, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** 4-node case
 * root ->   10(b)                         10(b)   <- root
 *        /        \      remove 20     /        \
 *      5(r)      15(r)  ---------->  5(b)      15(r)
 *     /   \     /   \               /   \     /
 *   1(b) 7(b) 13(b) 20(b)         1(r) 7(b) 13(b)
 */
 void test_delRedBlackTree_remove_20_from_tree_with_1_5_7_10_13_15_20_nodes(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'r');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, &node13, &node20, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node20);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    TEST_ASSERT_EQUAL_PTR(node, &node20);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
    TEST_ASSERT_EQUAL_NODE(&node1, &node7, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
    TEST_ASSERT_EQUAL_NODE(&node13, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}