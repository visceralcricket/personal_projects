#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    int data;
    Node *left;
    Node *right;
};

// Still have to add the actual search function here
/* +++
Node *searchTree(Node *node, int value);
--- */

void freeTree(Node *node) {
    if(node==NULL) return;

    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

void showTree(Node *root) {

    if(!root) return;

    showTree(root->left);
    printf("%d ", root->data);
    showTree(root->right);

    return;
}

Node *createNode(int value) {

    Node *newNode = malloc(sizeof(Node));
    if(!newNode) {
        puts("Not enough memory for the program to work.");
        // closeProgram();
        exit(EXIT_SUCCESS);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *insertTree(Node *node, int value) {
    
    if(node==NULL) return createNode(value);
    if(value < node->data) node->left = insertTree(node->left, value);
    else if(value > node->data) node->right = insertTree(node->right, value);
    return node;
}
