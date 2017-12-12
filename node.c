#include <stdbool.h>
#include <stdlib.h>
#include "node.h"

// returns ownership
node* node_new(long d) {
    node* n = (node*) malloc(sizeof(node));
    n->l = NULL;
    n->r = NULL;
    n->p = NULL;
    n->d = d;
    n->b = 0;
    return n;
}

/*
    compare the values stored at the two tree nodes
*/
static bool _ptr_compare(node* ptr0, node* ptr1) {
    if (ptr0 == NULL && ptr1 != NULL) return false;
    if (ptr0 != NULL && ptr1 == NULL) return false;
    if (ptr0 == NULL && ptr1 == NULL) return true;
    if (ptr0->d == ptr1->d) return true;
    return false;
}

/*
    compare two tree nodes by comparing the contents of their
    pointers and at last, the data itself
*/
bool node_compare(node* n0, node* n1) {
    if (_ptr_compare(n0->p, n1->p)) {
        if (_ptr_compare(n0->r, n1->r)) {
            if (_ptr_compare(n0->l, n1->l)) {
                if (n0->d == n1->d) {
                    if (n0->b == n1->b) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/*
    is the node a leaf node?
*/
bool node_isleaf(node* n) {
    if (n->l == NULL && n->r == NULL) return true;
    return false;
}

/*
    recursively compare two nodes
    interface for comparison when structured into a tree

    note that this only works for carefully constructed
    trees
*/
bool node_compare_recurse(node* n0, node* n1) {
    /*
        since this is recursive, two identical nodes
        may have null pointers as leaf nodes
        that case will be "identical"
        though this has the side effect that two
        null pointers are the same, which is ok
    */
    if (n0 == NULL && n1 == NULL) return true;
    if (node_isleaf(n0) && node_isleaf(n1)) {
        return node_compare(n0, n1);
    }
    if (node_compare(n0, n1)) {
        if (node_compare_recurse(n0->l, n1->l)) {
            if (node_compare_recurse(n0->r, n1->r)) {
                return true;
            }
        }
    }
    return false;
}


