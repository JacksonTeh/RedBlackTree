#include <stdio.h>
#include "RedBlackTree.h"
#include "Rotations.h"
#include "ErrorCode.h"

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