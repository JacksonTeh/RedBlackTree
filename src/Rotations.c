#include "Rotations.h"

void leftRotate(Node **nodePtr)
{

}

void rightRotate(Node **nodePtr)
{
    Node *tempNode1 = (*nodePtr)->left;
    Node *tempNode2 = tempNode1->right;

    tempNode1->right = *nodePtr;
    (*nodePtr)->left = tempNode2;

    *nodePtr = tempNode1;
}

void leftRightRotate(Node **nodePtr)
{

}

void rightLeftRotate(Node **nodePtr)
{

}