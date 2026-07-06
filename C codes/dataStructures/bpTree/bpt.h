#ifndef BPT_H
#define BPT_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int KeyType;
typedef struct Node Node;
typedef struct BpTree BpTree;

typedef enum {
    BPTREE_VALID = 0,
    BPTREE_DUPLICATE_KEY,
    BPTREE_KNF,
    BPTREE_ALLOC_ERROR,
    BPTREE_INVALID_PARAM,
    BPTREE_IE
} BpTreeStatus;

// ==== FORMAL KNUTH DEFINITION (Branching factor) ====
#define M 20
#define MAX_KEYS (M-1)
#define MIN_KEYS ((M+1) / 2-1)

// ==== PHYSICAL MEMORY ALLOCATION SIZES (included scratch slot) ====
#define PHYS_KEY_CAPACITY M
#define PHYS_PTR_CAPACITY (M+1)


struct Node {
    bool isLeaf;
    int numKeys;
    KeyType *keys;
    union {
        Node **children;
        void **dataPayloads;
    } content;
    Node *next;
};

struct BpTree {
    Node *root;
};

void destroyNode(Node *node) {
    if(!node) return;

    if(node->keys) free(node->keys);
    if(node->content.children) free(node->content.children);
    free(node);
}

Node *createNode(bool isLeaf) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if(!newNode) return NULL;

    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;
    newNode->next = NULL;
    newNode->keys = (KeyType *) malloc(sizeof(KeyType) * PHYS_KEY_CAPACITY);
    if(!newNode->keys) {
        free(newNode);
        return NULL;
    }
    
    if(isLeaf) {
        newNode->content.dataPayloads = (void **) malloc(sizeof(void *) * PHYS_PTR_CAPACITY);
        if(!newNode->content.dataPayloads) {
            destroyNode(newNode);
            return NULL;
        }
    }
    
    else {
        newNode->content.children = (Node **) malloc(sizeof(Node *) * (PHYS_PTR_CAPACITY));
        if(!newNode->content.children) {
            destroyNode(newNode);
            return NULL;
        }
    }
    return newNode;
}

BpTree *createTree(void) {
    BpTree *tree = (BpTree *) malloc(sizeof(BpTree));
    if(!tree) return NULL;

    tree->root = createNode(true);
    if(!tree->root) {
        free(tree);
        return NULL;
    }
    return tree;
}

BpTreeStatus search(BpTree *tree, KeyType targetKey, void **resultPayload) {
    if(!tree || !tree->root) return BPTREE_INVALID_PARAM;

    Node *current = tree->root;

    while(!current->isLeaf) {
        int i = 0;
        while(i < current->numKeys && targetKey >= current->keys[i]) i++;
        current = current->content.children[i];
    }

    for(int i=0; i<current->numKeys; i++) {
        if(current->keys[i] == targetKey) {
            if(resultPayload) *resultPayload = current->content.dataPayloads[i];
            return BPTREE_VALID;
        }
    }
    return BPTREE_KNF;
}

static void insertIntoNode(Node *node, KeyType key, void *payload, Node *childRight) {
    int i = node->numKeys-1;

    while(i >= 0 && node->keys[i] > key) {
        node->keys[i+1] = node->keys[i];
        if(node->isLeaf) node->content.dataPayloads[i+1] = node->content.dataPayloads[i];
        else node->content.children[i+2] = node->content.children[i+1];
        i--;
    }

    node->keys[i+1] = key;
    if(node->isLeaf) node->content.dataPayloads[i+1] = payload;
    else node->content.children[i+2] = childRight;
    
    node->numKeys++;
}

static BpTreeStatus insertRecursive(
    BpTree *tree,
    Node *current,
    KeyType key,
    void *payload,
    KeyType *promotedKey,
    Node **newRightChild
) {
    if (!tree || !current || !promotedKey || !newRightChild) {
        return BPTREE_INVALID_PARAM;
    }

    *promotedKey = 0;
    *newRightChild = NULL;

    if (current->isLeaf) {
        insertIntoNode(current, key, payload, NULL);

        if (current->numKeys <= MAX_KEYS) {
            return BPTREE_VALID;
        }

        int splitIndex = MAX_KEYS / 2;

        Node *right = createNode(true);
        if (!right) return BPTREE_ALLOC_ERROR;

        *promotedKey = current->keys[splitIndex];

        right->numKeys = current->numKeys - splitIndex; 
        for (int i = 0; i < right->numKeys; i++) {
            right->keys[i] = current->keys[splitIndex + i]; // Changed from: splitIndex + 1 + i
            right->content.dataPayloads[i] = current->content.dataPayloads[splitIndex + i];
        }
        
        right->next = current->next;
        current->next = right;

        current->numKeys = splitIndex;
        *newRightChild = right;

        return BPTREE_VALID;
    }

    int childIndex = 0;
    while (childIndex < current->numKeys && key >= current->keys[childIndex]) {
        childIndex++;
    }

    KeyType childPromotedKey = 0;
    Node *childRight = NULL;

    BpTreeStatus status = insertRecursive(
        tree,
        current->content.children[childIndex],
        key,
        payload,
        &childPromotedKey,
        &childRight
    );

    if (status != BPTREE_VALID) {
        return status;
    }

    if (!childRight) {
        return BPTREE_VALID;
    }

    insertIntoNode(current, childPromotedKey, NULL, childRight);

    if (current->numKeys <= MAX_KEYS) {
        return BPTREE_VALID;
    }

    int splitIndex = MAX_KEYS / 2;

    Node *right = createNode(false);
    if (!right) return BPTREE_ALLOC_ERROR;

    *promotedKey = current->keys[splitIndex];

    right->numKeys = current->numKeys - splitIndex - 1;

    for (int i = 0; i < right->numKeys; i++) {
        right->keys[i] = current->keys[splitIndex + 1 + i];
        right->content.children[i] =
            current->content.children[splitIndex + 1 + i];
    }

    right->content.children[right->numKeys] =
        current->content.children[current->numKeys];

    current->numKeys = splitIndex;
    *newRightChild = right;

    return BPTREE_VALID;
}


BpTreeStatus insert(BpTree *tree, KeyType key, void *payload) {
    if(!tree || !tree->root) return BPTREE_INVALID_PARAM;

    KeyType promotedKey;
    Node *newRightChild = NULL;

    BpTreeStatus status = insertRecursive(tree, tree->root, key, payload, &promotedKey, &newRightChild);
    if(status != BPTREE_VALID) return status;

    if(newRightChild) {
        Node *newRoot = createNode(false);
        if(!newRoot) return BPTREE_ALLOC_ERROR;

        newRoot->keys[0] = promotedKey;
        newRoot->content.children[0] = tree->root;
        newRoot->content.children[1] = newRightChild;
        newRoot->numKeys = 1;

        tree->root = newRoot;
    }
    return BPTREE_VALID;
}

#endif
