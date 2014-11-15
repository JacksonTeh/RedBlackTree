#include <stdio.h>
#include "unity.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

Node node1, node2, node5, node6, node7, node8, node10, node13, node14, node15, node17, node20, node25, node30;

void setUp(void)
{
    resetNode(&node1, 1);
    resetNode(&node2, 2);
    resetNode(&node5, 5);
    resetNode(&node6, 6);
    resetNode(&node7, 7);
    resetNode(&node8, 8);
    resetNode(&node10, 10);
    resetNode(&node13, 13);
    resetNode(&node14, 14);
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
        TEST_ASSERT_EQUAL_PTR(&node1, root);
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

    TEST_ASSERT_EQUAL_PTR(NULL, root);
    TEST_ASSERT_EQUAL_PTR(&node1, node);
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

    TEST_ASSERT_EQUAL_PTR(&node1, root);
    TEST_ASSERT_EQUAL_PTR(&node5, node);
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

    TEST_ASSERT_EQUAL_PTR(&node5, root);
    TEST_ASSERT_EQUAL_PTR(&node1, node);
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

    TEST_ASSERT_EQUAL_PTR(&node15, root);
    TEST_ASSERT_EQUAL_PTR(&node5, node);
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

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node13, node);
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

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node20, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
    TEST_ASSERT_EQUAL_NODE(&node13, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** 3-node case
 * root -> 10(b)                   10(b) <- root
 *        /    \      remove 1    /    \
 *      5(r)  15(b) ----------> 5(b)  15(b)
 *     /   \                       \
 *    1(b) 7(b)                   7(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_1_5_7_10_15_nodes(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'r');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node1);

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node1, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** 3-node case
 * root -> 10(b)                     10(b) <- root
 *        /    \      remove 7      /    \
 *      5(r)  15(b) ---------->   5(b)  15(b)
 *     /   \                     /
 *    1(b) 7(b)                1(r)
 */
void test_delRedBlackTree_remove_7_from_tree_with_1_5_7_10_15_nodes(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'r');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node7);

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node7, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** 3-node case
 * root -> 10(b)                     10(b) <- root                 5(b)  <- root
 *        /    \     remove 15      /                            /     \
 *      5(r)  15(b) ---------->   5(b)             ----------> 1(b)   10(b)
 *     /   \                     /   \                               /
 *   1(b)  7(b)                1(b) 7(b)                           7(r)
 */
void test_delRedBlackTree_remove_15_from_tree_with_1_5_7_10_15_nodes(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'r');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(&node5, root);
    TEST_ASSERT_EQUAL_PTR(&node15, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(&node7, NULL, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(&node1, &node10, 'b', &node5);
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

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node5, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
    TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
}

/** 4-node case
 * root -> 10(b)    remove 15   10(b) <- root
 *        /    \   --------->   /
 *      5(r)  15(r)           5(r)
 */
void test_delRedBlackTree_remove_15_from_tree_with_5_10_15_nodes(void)
{
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node15, node);
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

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node1, node);
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

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node7, node);
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
 *      5(r)      15(r)  ---------->  5(r)      15(b)
 *     /   \     /   \               /   \           \
 *   1(b) 7(b) 13(b) 20(b)         1(b) 7(b)        20(r)
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

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node13, node);
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
 *      5(r)      15(r)  ---------->  5(r)      15(b)
 *     /   \     /   \               /   \     /
 *   1(b) 7(b) 13(b) 20(b)         1(b) 7(b) 13(r)
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

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node20, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
    TEST_ASSERT_EQUAL_NODE(&node1, &node7, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
    TEST_ASSERT_EQUAL_NODE(&node13, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** Case (1a) The sibling is black and it has a red nephew (with parent being red)
 *
 *        /                       /                          /
 *     10(r)                    10(r)                     15(r)
 *    /    \      remove 5     //   \                     /   \
 *  5(b)  15(b)  ----------> NULL  15(b)   ----------> 10(b) 20(b)
 *            \                        \ 
 *           20(r)                    20(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_5_10_15_20_nodes_with_case_1(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'r');
    setNode(&node15, NULL, &node20, 'b');
    setNode(&node10, &node5, &node15, 'r');
    Node *root = &node10, *node;

    node = _delRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(&node15, root);
    TEST_ASSERT_EQUAL_PTR(&node5, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node10, &node20, 'r', &node15);
}

/** Case (1a) The sibling is black and it has a red nephew (with parent being red)
 *
 *          /                        /                        /
 *       10(r)                     10(r)                   5(r)
 *      /    \      remove 15     /   \\                  /   \
 *    5(b)  15(b)  ---------->  5(b)  NULL ---------->  1(b) 10(b)
 *    /                         / 
 *  1(r)                      1(r)
 */
void test_delRedBlackTree_remove_15_from_tree_with_1_5_10_15_nodes_with_case_1(void)
{
    setNode(&node1, NULL, NULL, 'r');
    setNode(&node5, &node1, NULL, 'b');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'r');
    Node *root = &node10, *node;

    node = _delRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(&node5, root);
    TEST_ASSERT_EQUAL_PTR(&node15, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(&node1, &node10, 'r', &node5);
}

/** Case (1b) The sibling is black and it has a red nephew (with parent being black)
 *
 *        /                       /                         /
 *     10(b)                    10(b)                     13(b)
 *    /    \      remove 5     //   \                    /   \
 *  5(b)  15(b)  ----------> NULL  15(b)  ----------> 10(b) 15(b)
 *        /                        / 
 *     13(r)                    13(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_5_10_13_15_nodes_with_case_1(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'r');
    setNode(&node15, &node13, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = _delRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(&node13, root);
    TEST_ASSERT_EQUAL_PTR(&node5, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node10, &node15, 'b', &node13);
}

/** Case (1b) The sibling is black and it has a red nephew (with parent being red)
 *
 *          /                        /                        /
 *       10(r)                     10(r)                   7(r)
 *      /    \      remove 15     /   \\                  /   \
 *    5(b)  15(b)  ---------->  5(b)  NULL ---------->  5(b) 10(b)
 *       \                         \ 
 *      7(r)                      7(r)
 */
void test_delRedBlackTree_remove_15_from_tree_with_5_7_10_15_nodes_with_case_1(void)
{
    setNode(&node7, NULL, NULL, 'r');
    setNode(&node5, NULL, &node7, 'b');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'r');
    Node *root = &node10, *node;

    node = _delRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(&node7, root);
    TEST_ASSERT_EQUAL_PTR(&node15, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(&node5, &node10, 'r', &node7);
}

/** Case (2a) The sibling is black and both nephew are black
 *
 *        /                       //
 *     10(b)                    10(d)
 *    /    \      remove 5          \
 *  5(b)  15(b)  ---------->       15(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_5_10_15_nodes_with_case_2(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = _delRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node5, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
    TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'd', &node10);
}

/** Case (2a) The sibling is black and both nephew are black
 *
 *        /                      //
 *     10(b)                   10(d)
 *    /    \      remove 15    /
 *  5(b)  15(b)  ----------> 5(r)
 */
void test_delRedBlackTree_remove_15_from_tree_with_5_10_15_nodes_with_case_2(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = _delRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node15, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'd', &node10);
}

/** Case (2b) The sibling is black and both nephew are black
 *
 *        /                       /
 *     10(r)                    10(b)
 *    /    \      remove 5          \
 *  5(b)  15(b)  ---------->       15(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_red_node_10_and_5_15_nodes_with_case_2(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'r');
    Node *root = &node10, *node;

    node = _delRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node5, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
    TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
}

/** Case (2b) The sibling is black and both nephew are black
 *
 *        /                      /
 *     10(r)                   10(b)
 *    /    \      remove 15    /
 *  5(b)  15(b)  ----------> 5(r)
 */
void test_delRedBlackTree_remove_15_from_tree_with_red_node_10_and_5_15_nodes_with_case_2(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'r');
    Node *root = &node10, *node;

    node = _delRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node15, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node10);
}

/** Case (3) The sibling is red (with case 2b appear after left rotate)
 *
 * root -> 10(b)                    10(b) <- root              15(b) <- root             15(b) <- root
 *        /    \      remove 5     //   \                      /   \                     /   \
 *      5(b)  15(r)  ----------> NULL  15(r)    ----------> 10(r) 20(b)   ----------> 10(b) 20(b)
 *            /   \                    /   \                //  \                         \
 *         13(b) 20(b)              13(b) 20(b)           NULL 13(b)                     13(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_5_10_13_15_20_nodes_with_case_3(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, &node13, &node20, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(&node15, root);
    TEST_ASSERT_EQUAL_PTR(&node5, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(NULL, &node13, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(&node10, &node20, 'b', &node15);
}

/** Case (3) The sibling is red (with case 2b appear after right rotate)
 *
 * root -> 10(b)                    10(b) <- root             5(b) <- root              5(b) <- root
 *        /    \      remove 15    /   \\                    /   \                     /   \
 *      5(r)  15(b)  ----------> 5(r)  NULL   ---------->  1(b) 10(r)   ---------->  1(b) 10(b)
 *     /   \                    /   \                           /  \\                     /
 *   1(b)  7(b)               1(b)  7(b)                      7(b) NULL                 7(r)
 */
void test_delRedBlackTree_remove_15_from_tree_with_1_5_7_10_15_nodes_with_case_3(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'r');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(&node5, root);
    TEST_ASSERT_EQUAL_PTR(&node15, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(&node7, NULL, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(&node1, &node10, 'b', &node5);
}

/** Case (3) The sibling is red (with case 1a appear after left rotate)
 *
 *     10(b) <- root            10(b) <- root               15(b)  <- root           15(b) <- root
 *    /    \      remove 5     //   \                      /   \                     /   \
 *  5(b)  15(r)  ----------> NULL  15(r)    ----------> 10(r) 20(b)   ----------> 13(r) 20(b)
 *        /   \                    /   \                //  \                     /   \
 *     13(b) 20(b)              13(b) 20(b)           NULL 13(b)               10(b)  14(b)
 *         \                        \                          \
 *        14(r)                    14(r)                      14(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_5_10_13_14_15_20_nodes_with_case_3(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node14, NULL, NULL, 'r');
    setNode(&node13, NULL, &node14, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, &node13, &node20, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(&node15, root);
    TEST_ASSERT_EQUAL_PTR(&node5, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node14);
    TEST_ASSERT_EQUAL_NODE(&node10, &node14, 'r', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'b', &node15);
}

/** Case (3) The sibling is red (with case 1a appear after left rotate)
 *
 *        10(b) <- root              10(b) <- root          5(b) <- root             5(b) <- root
 *       /    \      remove 15      /   \\                 /   \                    /   \
 *     5(r)  15(b)  ---------->   5(r)  NULL ----------> 1(b) 10(r)   ----------> 1(b)  7(r)
 *    /   \                      /   \                        /   \\                   /   \
 *  1(b)  7(b)                 1(b)  7(b)                   7(b)  NULL               6(b)  10(b)
 *        /                          /                      /
 *      6(r)                       6(r)                   6(r)
 */
void test_delRedBlackTree_remove_15_from_tree_with_1_5_6_7_10_15_nodes_with_case_3(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node6, NULL, NULL, 'r');
    setNode(&node7, &node6, NULL, 'b');
    setNode(&node5, &node1, &node7, 'r');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10, *node;

    node = delRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(&node5, root);
    TEST_ASSERT_EQUAL_PTR(&node15, node);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(&node6, &node10, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(&node1, &node7, 'b', &node5);
}

/**
 * parent's left               parent's left
 *      |                           |
 *      v        successor 10       v
 *    10(r)      ------------>    NULL
 */
void xtest_removeNextLargerSuccessor_given_10r_nodes_should_remove_successor_10(void)
{
    setNode(&node10, NULL, NULL, 'r');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(NULL, parent);
    TEST_ASSERT_EQUAL_PTR(&node10, removeNode);
}

/**
 * parent's left              parent's left
 *      |                         ||
 *      v       successor 10      v
 *    10(b)     ------------>   NULL
 */
void xtest_removeNextLargerSuccessor_given_10b_nodes_should_remove_successor_10(void)
{
    setNode(&node10, NULL, NULL, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL(1, isDoubleBlack(parent, removeNode));
    TEST_ASSERT_EQUAL_PTR(NULL, parent);
    TEST_ASSERT_EQUAL_PTR(&node10, removeNode);
}

/**
 * parent's left             parent's left
 *      |                         |
 *      v      successor 10       v
 *    10(b)    ------------>    15(b)
 *       \
 *      15(r)
 */
void xtest_removeNextLargerSuccessor_given_10_15_nodes_should_remove_successor_10(void)
{
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, NULL, &node15, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(&node15, parent);
    TEST_ASSERT_EQUAL_PTR(&node10, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
}

/**
 * parent's left             parent's left
 *      |                         |
 *      v      successor 5        v
 *    10(b)    ------------>    10(b)
 *    /   \                         \
 *  5(r) 15(r)                     15(r)
 */
void xtest_removeNextLargerSuccessor_given_nodes_5_10_15_should_remove_successor_5(void)
{
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(&node10, parent);
    TEST_ASSERT_EQUAL_PTR(&node5, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
    TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
}

/**
 *      parent's left                        parent's left
 *            |                                    |
 *            v                                    v
 *          10(b)                                10(b)
 *       /         \                          /         \
 *     5(b)       15(b)    successor 1      5(b)       15(b)
 *    /   \       /   \   ------------>    /   \       /   \
 *  1(b) 7(b)  13(b) 20(b)               2(b) 7(b)  13(b) 20(b)
 *     \
 *    2(r)
 */
void xtest_removeNextLargerSuccessor_given_nodes_1_2_5_10_13_15_20_should_remove_successor_1(void)
{
    setNode(&node2, NULL, NULL, 'r');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node1, NULL, &node2, 'b');
    setNode(&node5, &node1, &node7, 'b');
    setNode(&node15, &node13, &node20, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(&node10, parent);
    TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
    TEST_ASSERT_EQUAL_NODE(&node2, &node7, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/**
 *      parent's left                      parent's left                   parent's left                   parent's left
 *            |                                  |                               |                               ||
 *            v                                  v                               v                               v
 *          10(b)                              10(b)                           10(b)                           10(d)
 *       /         \       successor 1      /         \                     //        \                     /        \
 *     5(b)       15(b)   ------------>   5(b)       15(b)  ------------> 5(d)       15(b)  ------------> 5(b)       15(r)
 *    /   \       /   \                  //  \       /   \                   \       /   \                   \       /   \
 *  1(b) 7(b)  13(b) 20(b)             NULL 7(b)  13(b) 20(b)               7(r)  13(b) 20(b)               7(r)  13(b) 20(b)
 */
void test_removeNextLargerSuccessor_given_nodes_1_5_10_13_15_20_should_remove_successor_1(void)
{
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'b');
    setNode(&node15, &node13, &node20, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(&node10, parent);
    TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'r', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'd', &node10);
}