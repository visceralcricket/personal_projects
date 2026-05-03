#ifndef AVL_H
#define AVL_H

typedef struct avl_node avl_node;
typedef struct tree_map tree_map;

typedef struct Pair {
    int key;
    void *data;
} Pair;

// Testing function
void *handleData(int data) {
    void *pData = (void *) malloc(sizeof(int));
    if(!pData) return NULL;
    pData = &data;
    return pData;
}

// Create a node for the tree structure and returns its pointer
avl_node *createNode(int value);

// Inserts a value inside the tree
avl_node *insertTree(avl_node *node, int value);

// Searches for a specified value in the tree and returns its node's pointer
avl_node *searchTree(avl_node *node, int value);

// Searches for the smallest value and returns the pointer to its node
avl_node *minimum(avl_node *node);

int height(avl_node *node);

int max(int a, int b);

int getBalance(avl_node *node);

// Cleans the tree of all its nodes
void freeTree(avl_node *node);

// Prints the entire tree from left branch to the right one
void showTree(avl_node *root);


#endif