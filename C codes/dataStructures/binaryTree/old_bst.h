#ifndef OLD_BST_H
#define OLD_BST_H

typedef struct Node Node;

// Create a node for the tree structure and returns its pointer
Node *createNode(int value);

// Inserts a value inside the tree
Node *insertTree(Node *node, int value);

// Searches for a specified value in the tree and returns its node's pointer
Node *searchTree(Node *node, int value);

// Searches for the smallest value and returns the pointer to its node
Node *searchMin(Node *node);

// Cleans the tree of all its nodes
void freeTree(Node *node);

// Prints the entire tree from left branch to the right one
void showTree(Node *root);

#endif
