#include <stdio.h>
#include "RedBlackTree.h"
#include "Rotations.h"
#include "ErrorCode.h"

void _addRedBlackTree(Node **rootPtr, Node *newNode);
Node *_delRedBlackTree(Node **rootPtr, Node *delNode);

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
    else if(root->data <= delNode->data)
        node = _delRedBlackTree(&root->right, delNode);
    else if(root->data >= delNode->data)
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