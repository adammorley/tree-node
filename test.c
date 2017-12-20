#include <assert.h>
#include <stdlib.h>
#include "node.h"

void test_basic() {
    tree_node* n0 = tree_node_new(5);
    assert(sizeof(tree_node) == sizeof(n0->l) + sizeof(n0->r) + sizeof(n0->p) + sizeof(n0->d) + sizeof(n0->b));
    assert(n0->b == 0);
    assert(n0->d == 5);
    assert(n0->l == NULL);
    assert(n0->r == NULL);
    tree_node* n1 = tree_node_new(6);
    n0->r = n1;
    assert(n0->r->d == 6);
    free(n0);
    free(n1);
}

void test_compare() {
    tree_node* n1_0 = tree_node_new(1);
    tree_node* n1_1 = tree_node_new(1);
    assert(tree_node_compare(n1_0, n1_1));

    tree_node* n5_0 = tree_node_new(5);
    tree_node* n5_1 = tree_node_new(5);
    tree_node* n6_0 = tree_node_new(6);
    tree_node* n6_1 = tree_node_new(6);

    n1_0->l = n5_0;
    n1_1->l = n5_1;
    n1_0->r = n6_0;
    n1_1->r = n6_1;

    assert(tree_node_compare(n1_0, n1_1));
    assert(tree_node_compare_recurse(n1_0, n1_1));
    tree_node_free_recurse(n1_0);
    tree_node_free_recurse(n1_1);
}

void test_check() {
    tree_node* n_1 = tree_node_new(-1);
    tree_node* n0 = tree_node_new(0);
    tree_node* n1 = tree_node_new(1);
    tree_node* n2 = tree_node_new(2);
    tree_node* n3 = tree_node_new(3);
    tree_node* n4 = tree_node_new(4);
    tree_node* n5 = tree_node_new(5);

    n3->r = n4;
    n4->p = n3;
    n3->l = n1;
    n1->p = n3;
    n1->l = n0;
    n0->p = n1;
    n0->l = n_1;
    n_1->p = n0;
    n0->b = -1;
    n1->b = -1;
    n1->r = n2;
    n2->p = n1;
    n4->r = n5;
    n4->b = 1;
    n5->p = n4;

    n3->b = -1;

    tree_node_check(n3);
    tree_node_free_recurse(n3);
}

int main() {
    test_basic();
    test_compare();
    test_check();
}
