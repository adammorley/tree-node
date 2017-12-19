#include <stdbool.h>
#include <stdlib.h>

#include "../log/log.h"
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

long node_calculate_height(node* n) {
    long h_l = 0;
    long h_r = 0;
    if (n->l != NULL) {
        h_l += 1;
        h_l += node_calculate_height(n->l);
    }
    if (n->r != NULL) {
        h_r += 1;
        h_r += node_calculate_height(n->r);
    }
    return (h_r >= h_l ? h_r : h_l);
}

void node_check_tree(node* n) {
    if (n != NULL) {
        if (n->l != NULL) {
            Assert(n->d > n->l->d, __func__, "node %lu d %li L child of %lu is misplaced", n->l, n->d, n->l->d);
            node_check_tree(n->l);
        }
        if (n->r != NULL) {
            Assert(n->d < n->r->d, __func__, "node %lu d %li R child of %lu is misplaced", n->r, n->d, n->r->d);
            node_check_tree(n->r);
        }
        node_validate_b(n);
    }
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

bool node_isleaf(node* n) {
    if (n->l == NULL && n->r == NULL) return true;
    return false;
}

void node_validate_b(node* n) {
    long h_l = 0;
    long h_r = 0;
    if (n->l != NULL) {
        h_l += 1;
        h_l += node_calculate_height(n->l);
    }
    if (n->r != NULL) {
        h_r += 1;
        h_r += node_calculate_height(n->r);
    }
    Assert(h_r - h_l == n->b, __func__, "node %lu d %li b %li invalid, height: l: %li r: %li", n, n->d, n->b, h_l, h_r);
}
