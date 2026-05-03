#include "avl.h"
#include <stdio.h>

struct avl_node {
    Pair *pair;
    int height;
    struct avl_node *parent;
    struct avl_node *left, *right;
};

struct tree_map {
    avl_node *root;
    avl_node *current;
}

avl_node createNode(void *key, void *data) {

}