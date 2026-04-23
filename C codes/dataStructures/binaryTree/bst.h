#ifndef BST_H
#define BST_H

typedef struct Node Node;
struct Node {
    int data;
    Node *left;
    Node *right;
};

Node *createNode(int value);
Node *insertTree(Node *node, int value);
// Node *searchTree(Node *node, int value);

void freeTree(Node *node);
void showTree(Node *root);

#endif
