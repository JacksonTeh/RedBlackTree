#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "Node.h"

void addRedBlackTree(Node **rootPtr, Node *newNode);
void _addRedBlackTree(Node **rootPtr, Node *newNode);
void fixRootViolation(Node **rootPtr);
void fixChildViolation(Node **rootPtr);
int isNodeRedColour(Node **rootPtr);

#endif // RedBlackTree_H
