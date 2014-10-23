#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "Node.h"

void addRedBlackTree(Node **rootPtr, Node *newNode);
Node *delRedBlackTree(Node **rootPtr, Node *delNode);
void fixRootViolation(Node **rootPtr);
void fixChildViolation(Node **rootPtr);
void fixColourViolation(Node **rootPtr);
int isNodeRedColour(Node **rootPtr);

#endif // RedBlackTree_H
