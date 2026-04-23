#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

Node *createNode(int value) {

    Node *newNode = malloc(sizeof(Node));
    if(!newNode) {
        puts("Not enough memory for the program to work.");
        exit(EXIT_FAILURE);
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

Node *searchTree(Node *node, int value) {
    while(node!=NULL && node->data != value) {
        if(value<node->data) node = node->left;
        else node=node->right;
    }
    return node;
}

Node *searchMin(Node *node) {
    while(node->left != NULL) node = node->left;
    return node;
}

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
