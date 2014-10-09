#ifndef Node_H
#define Node_H

typedef struct Node Node;

struct Node
{
    Node *left;
    Node *right;
    char colour;    //'b' or 'r' (black or red)
    int data;
};

#endif // Node_H
