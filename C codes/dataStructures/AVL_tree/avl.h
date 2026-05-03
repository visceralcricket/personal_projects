#ifndef AVL_H
#define AVL_H

typedef struct avl_node avl_node;
typedef struct tree_map tree_map;

typedef struct Pair {
    int key;
    void *value;
} Pair;

// Create a node for the tree structure and returns its pointer
avl_node *createNode(int key, void *data)

// Inserts a value inside the tree
avl_node *insertNode(avl_node *node, int data);

// Searches for a specified value in the tree and returns its node's pointer
avl_node *searchNode(avl_node *node, int data);

// Searches for the smallest value and returns the pointer to its node
avl_node *minimum(avl_node *node);

/*+++ Rotations ---*/

avl_node *rotateRight(avl_node *y);

avl_node *rotateLeft(avl_node *x);

/* +++ Helpers --- */
int getHeight(avl_node *node);

int max(int a, int b);

int getBalance(avl_node *node);

// Cleans the tree of all its nodes
void freeTree(avl_node *node);

// Prints the entire tree from left branch to the right one
void showTree(avl_node *root);


#endif