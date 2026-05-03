#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#define INT_INPUT_ERROR 0

struct avl_node {
    Pair *pair;
    int height;
    struct avl_node *parent;
    struct avl_node *left, *right;
};

/* +++
struct tree_map {
    avl_node *root;
    avl_node *current;
}
--- */
// tree_map createTreeMap(int key, void *data);

void handleError(int errValue) {
    switch(errValue) {
        case INT_INPUT_ERROR:
            puts("Non-valid integer detected, please try again.");
            break;

        default:
            puts("Unexpected error, please try again.");
            break;
    }
    exit(EXIT_FAILURE);
}

avl_node *createNode(int key, void *data) {
    if(data==NULL) return NULL;


    avl_node *new = (avl_node *) malloc(sizeof(avl_node));
    if(!new) return NULL;

    new->pair = (Pair *) malloc(sizeof(Pair));
    if(!new->pair) {
        free(new);
        return NULL;
    }
    new->pair->key = key;
    new->pair->data = data;
    new->parent = new->right = new->left = NULL;
    new->height = 0;
    return new;
}

// avl_node *insertNode(avl_node *node, int key, void *data)

/* +++ Rotations ---*/

avl_node *rotateRight(avl_node *y) {
    if(y==NULL) return NULL;

    avl_node *x = node->left;
    avl_node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x;
}

avl_node *rotateLeft(avl_node *x) {
    if(x==NULL) return NULL;

    avl_node *y = x->right;
    avl_node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

/* +++ Helpers ---*/
int getHeight(avl_node *node) {
    return (node == NULL) ? 0 : node->height;
}

int max(int a, int b) {
    return (a>b) ? a : b;
}

int getBalance(avl_node *node) {
    return (node ==  NULL)? 0 : getHeight(node->right) - getHeight(node->left);
}