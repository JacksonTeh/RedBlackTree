#include <stdio.h>
#include "RedBlackTree.h"
#include "Rotations.h"
#include "ErrorCode.h"

void addRedBlackTree(Node **rootPtr, Node *newNode)
{
    _addRedBlackTree(rootPtr, newNode);
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
        _addRedBlackTree(&(root->left), newNode);

        if(!isNodeRedColour(&root->left))
            return;
    }
    else
    {
        _addRedBlackTree(&root->right, newNode);
    }

    // if(isNodeRedColour(&root))
        // printf("yes\n");
}

int isNodeRedColour(Node **rootPtr)
{
    Node *root = *rootPtr;

    if(root == NULL)
        return 0;

    if(root->colour == 'r')
        isNodeRedColour(&root->left);
}