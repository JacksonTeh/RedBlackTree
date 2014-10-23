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
    Node *node;
    Node *root = &node1;

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
    Node *node;
    Node *root = &node1;

    node = delRedBlackTree(&root, &node1);

    TEST_ASSERT_EQUAL_PTR(root, NULL);
    TEST_ASSERT_EQUAL_PTR(node, &node1);
}

