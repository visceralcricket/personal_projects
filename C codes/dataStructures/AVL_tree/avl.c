#include "avl.h"
#include <stdio.h>

struct avl_node {
    Pair *pair;
    int height;
    struct avl_node *left, *right;
};

struct tree_map {
    avl_node *root;
    avl_node *parent;
    avl_node *left, right;
}

avl_node createNode(void *key, void *data) {

}