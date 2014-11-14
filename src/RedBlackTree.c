#include <stdio.h>
#include "RedBlackTree.h"
#include "Rotations.h"
#include "ErrorCode.h"

void _addRedBlackTree(Node **rootPtr, Node *newNode);
Node *_delRedBlackTreeX(Node **rootPtr, Node *delNode);

/**
 *
 * Add node to Red Black Tree
 *
 */
void addRedBlackTree(Node **rootPtr, Node *newNode)
{
    _addRedBlackTree(rootPtr, newNode);
    fixRootViolation(&(*rootPtr));
    (*rootPtr)->colour = 'b';
}

void _addRedBlackTree(Node **rootPtr, Node *newNode)
{
    Node *root = *rootPtr;

    if(root == NULL)
    {
        *rootPtr = newNode;
        return;
    }

    if(newNode->data < root->data)
    {
        _addRedBlackTree(&root->left, newNode);
        fixChildViolation(&root);
    }
    else
    {
        _addRedBlackTree(&root->right, newNode);
        fixChildViolation(&root);
    }

    if(root->left != NULL && root->right != NULL)
    {
        if(root->left->colour == 'r' && root->right->colour == 'r')     //indicate 4-nodes
            fixColourViolation(&root);
    }
}

void fixRootViolation(Node **rootPtr)
{
    Node *root = *rootPtr;

    if(root->left != NULL)
    {
        if(root->left->colour == 'r')
        {
            if(root->left->left != NULL)
            {
                if(!isNodeRedColour(&root->left))
                    return;
                else
                    rightRotate(&(*rootPtr));
            }
            else
            {
                if(!isNodeRedColour(&root->left))
                    return;
                else
                    leftRightRotate(&(*rootPtr));
            }

            (*rootPtr)->right->colour = 'r';
        }
    }
    else if(root->right != NULL)
    {
        if(root->right->colour == 'r')
        {
            if(root->right->right != NULL)
            {
                if(!isNodeRedColour(&root->right))
                    return;
                else
                    leftRotate(&(*rootPtr));
            }
            else
            {
                if(!isNodeRedColour(&root->right))
                    return;
                else
                    rightLeftRotate(&(*rootPtr));
            }

            (*rootPtr)->left->colour = 'r';
        }
    }
}

void fixChildViolation(Node **rootPtr)
{
    Node *root = *rootPtr;

    if(root->colour == 'r')
    {
        if(root->left != NULL)
        {
            if(!isNodeRedColour(&root->left))
                return;
            else
                rightRotate(&root);
        }
        else
        {
            if(!isNodeRedColour(&root->right))
                return;
            else
                leftRotate(&root);
        }
    }
}

void fixColourViolation(Node **rootPtr)
{
    Node *root = *rootPtr;

    if(root->left->left != NULL || root->left->right != NULL || root->right->left != NULL || root->right->right != NULL)
    {
        root->left->colour = 'b';
        root->right->colour = 'b';
        root->colour = 'r';
    }
}

int isNodeRedColour(Node **rootPtr)
{
    Node *root = *rootPtr;

    if(root->left != NULL)
    {
        if(root->left->colour == 'r')
            return 1;
    }
    else if(root->right != NULL)
    {
        if(root->right->colour == 'r')
            return 1;
    }

    return 0;
}

/**
 *
 * Delete node from Red Black Tree
 *
 */
Node *delRedBlackTree(Node **rootPtr, Node *delNode)
{
    Node *node = _delRedBlackTree(rootPtr, delNode);

    if((*rootPtr) != NULL)
        (*rootPtr)->colour = 'b';

    return node;
}

Node *_delRedBlackTree(Node **rootPtr, Node *delNode)
{
    Node *root = *rootPtr;
    Node *node;

    if(root == NULL)
        Throw(ERR_NODE_UNAVAILABLE);

    if(root->data == delNode->data)
    {
        *rootPtr = NULL;
        return root;
    }
    else if(root->data < delNode->data)
        node = _delRedBlackTree(&root->right, delNode);
    else if(root->data > delNode->data)
        node = _delRedBlackTree(&root->left, delNode);

    selectCases(&(*rootPtr), node);

    return node;
}

int isRed(Node *rootPtr)
{
    if(rootPtr == NULL)
        return 0;
    else if(rootPtr->colour == 'r')
        return 1;
}

int isBlack(Node *rootPtr)
{
    if(rootPtr == NULL || rootPtr->colour == 'b')
        return 1;
    else
        return 0;
}

int isDoubleBlack(Node *rootPtr, Node *removeNode)
{
    if((rootPtr == NULL || rootPtr->colour == 'd') && removeNode->colour == 'b')
        return 1;
    else
        return 0;
}

void selectCases(Node **rootPtr, Node *removeNode)
{
    if((*rootPtr)->left != NULL || (*rootPtr)->right != NULL)
    {
        if(isDoubleBlack((*rootPtr)->left, removeNode))           //left side case
        {
            if(checkCases((*rootPtr)->right) == 1)
                restructureRightBlackChildWithOneRedGrandchild(&(*rootPtr));
            else if(checkCases((*rootPtr)->right) == 2)
                restructureRightBlackChildWithBothBlackGrandchild(&(*rootPtr));
            else if(checkCases((*rootPtr)->right) == 3)
                restructureRightRedChild(&(*rootPtr), removeNode);
        }
        else if(isDoubleBlack((*rootPtr)->right, removeNode))     //right side case
        {
            if(checkCases((*rootPtr)->left) == 1)
                restructureLeftBlackChildWithOneRedGrandchild(&(*rootPtr));
            else if(checkCases((*rootPtr)->left) == 2)
                restructureLeftBlackChildWithBothBlackGrandchild(&(*rootPtr));
            else if(checkCases((*rootPtr)->left) == 3)
                restructureLeftRedChild(&(*rootPtr), removeNode);
                // printf("yes\n");
        }
    }
}

/**
 * To check which cases should be for the RBT
 *
 * Input:
 *      rootPtr     is pointer to Node
 *
 * Return
 *      1           indicate case: (1a) The sibling is black and it has a red nephew
                                   (1b) The sibling is black and it has a red nephew
 *      2           indicate case: (2a) The sibling is black and both nephew are black
                                   (2b) The sibling is black and both nephew are black
 *      3           indicate case: (3) The sibling is red
 */
int checkCases(Node *rootPtr)
{
    if(isBlack(rootPtr) && (isRed(rootPtr->left) || isRed(rootPtr->right)))             //case 1
        return 1;
    else if(isBlack(rootPtr) && (isBlack(rootPtr->left) || isBlack(rootPtr->right)))    //case 2
        return 2;
    else if(isRed(rootPtr))                                                             //case 3
    {
        if(rootPtr->left == NULL && rootPtr->right == NULL)
            return 0;

        return 3;
    }
}

void restructureRightBlackChildWithOneRedGrandchild(Node **rootPtr)
{
    Node *rightChild = (*rootPtr)->right;

    if(isRed(rightChild->right))
        leftRotate(&(*rootPtr));
    else if(isRed(rightChild->left))
        rightLeftRotate(&(*rootPtr));

    (*rootPtr)->colour = (*rootPtr)->left->colour;
    (*rootPtr)->left->colour = 'b';
    (*rootPtr)->right->colour = 'b';
}

void restructureLeftBlackChildWithOneRedGrandchild(Node **rootPtr)
{
    Node *leftChild = (*rootPtr)->left;

    if(isRed(leftChild->left))
        rightRotate(&(*rootPtr));
    else if(isRed(leftChild->right))
        leftRightRotate(&(*rootPtr));

    (*rootPtr)->colour = (*rootPtr)->right->colour;
    (*rootPtr)->left->colour = 'b';
    (*rootPtr)->right->colour = 'b';
}

void restructureRightBlackChildWithBothBlackGrandchild(Node **rootPtr)
{
    if((*rootPtr)->colour == 'r')
        (*rootPtr)->colour = 'b';
    else
        (*rootPtr)->colour = 'd';

    (*rootPtr)->right->colour = 'r';
}

void restructureLeftBlackChildWithBothBlackGrandchild(Node **rootPtr)
{
    if((*rootPtr)->colour == 'r')
        (*rootPtr)->colour = 'b';
    else
        (*rootPtr)->colour = 'd';

    (*rootPtr)->left->colour = 'r';
}

void restructureRightRedChild(Node **rootPtr, Node *removeNode)
{
    leftRotate(&(*rootPtr));

    (*rootPtr)->left->colour = 'r';

    if(isDoubleBlack((*rootPtr)->left->left, removeNode))
    {
        if(checkCases((*rootPtr)->left->right) == 1)
            restructureRightBlackChildWithOneRedGrandchild(&(*rootPtr)->left);
        else if(checkCases((*rootPtr)->left->right) == 2)
            restructureRightBlackChildWithBothBlackGrandchild(&(*rootPtr)->left);
    }
}

void restructureLeftRedChild(Node **rootPtr, Node *removeNode)
{
    rightRotate(&(*rootPtr));

    (*rootPtr)->right->colour = 'r';

    if(isDoubleBlack((*rootPtr)->right->right, removeNode))
    {
        if(checkCases((*rootPtr)->right->left) == 1)
            restructureLeftBlackChildWithOneRedGrandchild(&(*rootPtr)->right);
        else if(checkCases((*rootPtr)->right->left) == 2)
            restructureLeftBlackChildWithBothBlackGrandchild(&(*rootPtr)->right);
    }
}

/**
 *
 * Remove the next larger successor node from Red Black Tree
 *
 */
Node *removeNextLargerSuccessor(Node **parentPtr)
{
    Node *removeNode;

    if((*parentPtr)->left == NULL && (*parentPtr)->right == NULL)
    {
        removeNode = *parentPtr;
        *parentPtr = NULL;
        return removeNode;
    }
    else
    {
        if((*parentPtr)->left != NULL)
            removeNode = removeNextLargerSuccessor(&(*parentPtr)->left);
        else
        {
            removeNode = *parentPtr;
            *parentPtr = (*parentPtr)->right;
            (*parentPtr)->colour = 'b';
            return removeNode;
        }
    }

    if(*parentPtr != NULL)
        (*parentPtr)->colour = 'd';
}

////////////////////////////////////////////////////
//                                                //
//           Old delete node code                 //
//                                                //
////////////////////////////////////////////////////
Node *delRedBlackTreeX(Node **rootPtr, Node *delNode)
{
    Node *node = _delRedBlackTree(rootPtr, delNode);

    if((*rootPtr) != NULL)
        (*rootPtr)->colour = 'b';

    return node;
}

Node *_delRedBlackTreeX(Node **rootPtr, Node *delNode)
{
    Node *root = *rootPtr;
    Node *node;

    if(root == NULL)
        Throw(ERR_NODE_UNAVAILABLE);

    if(root->data == delNode->data)
    {
        *rootPtr = NULL;
        return root;
    }
    else if(root->data < delNode->data)
        node = _delRedBlackTree(&root->right, delNode);
    else if(root->data > delNode->data)
        node = _delRedBlackTree(&root->left, delNode);

    if(root != NULL)
    {
        if(root->left == NULL && root->right != NULL)
        {
            if(root->right->left != NULL || root->right->right != NULL)
            {
                leftRotate(&(*rootPtr));
                (*rootPtr)->left->right->colour = 'r';
            }

            if(root->colour == 'r')
            {
                // printf("yes\n");
                if(root->left != NULL)
                    (*rootPtr)->left->colour = 'r';
                else if(root->right != NULL)
                    (*rootPtr)->right->colour = 'r';

                (*rootPtr)->colour = 'b';
            }
        }
        else if(root->left != NULL && root->right == NULL)
        {
            if(root->left->left != NULL || root->left->right != NULL)
            {
                rightRotate(&(*rootPtr));
                (*rootPtr)->right->left->colour = 'r';
            }

            if(root->colour == 'r')
            {
                if(root->left != NULL)
                    (*rootPtr)->left->colour = 'r';
                else if(root->right != NULL)
                    (*rootPtr)->right->colour = 'r';

                (*rootPtr)->colour = 'b';
            }
        }
    }

    return node;
}