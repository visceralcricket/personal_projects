#include "avl.h"
#include <stdio.h>

struct avl_node {
    void *data;
    void *key;
    Node *left;
    Node *right;
    Node *parent;
};