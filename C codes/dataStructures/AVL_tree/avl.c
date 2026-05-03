#include "avl.h"
#include <stdio.h>

struct Node {
    void *data;
    void *key;
    Node *left;
    Node *right;
    Node *parent;
};

