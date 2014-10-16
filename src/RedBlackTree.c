#include "RedBlackTree.h"
#include "ErrorCode.h"

void addRedBlackTree(Node **nodePtr, Node *newNode)
{
    _addRedBlackTree(nodePtr, newNode);
}

void _addRedBlackTree(Node **nodePtr, Node *newNode)
{
    *nodePtr = newNode;
    (*nodePtr)->colour = 'b';
}