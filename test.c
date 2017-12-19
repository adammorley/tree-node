#include <assert.h>
#include <stdlib.h>
#include "node.h"

void test_basic() {
    node* n0 = node_new(5);
    assert(sizeof(node) == sizeof(n0->l) + sizeof(n0->r) + sizeof(n0->p) + sizeof(n0->d) + sizeof(n0->b));
    assert(n0->b == 0);
    assert(n0->d == 5);
    assert(n0->l == NULL);
    assert(n0->r == NULL);
    node* n1 = node_new(6);
    n0->r = n1;
    assert(n0->r->d == 6);
    free(n0);
    free(n1);
}

void test_compare() {
    node* n1_0 = node_new(1);
    node* n1_1 = node_new(1);
    assert(node_compare(n1_0, n1_1));

    node* n5_0 = node_new(5);
    node* n5_1 = node_new(5);
    node* n6_0 = node_new(6);
    node* n6_1 = node_new(6);

    n1_0->l = n5_0;
    n1_1->l = n5_1;
    n1_0->r = n6_0;
    n1_1->r = n6_1;

    assert(node_compare(n1_0, n1_1));
    assert(node_compare_recurse(n1_0, n1_1));
    node_free_recurse(n1_0);
    node_free_recurse(n1_1);
}

void test_check() {
    node* n_1 = node_new(-1);
    node* n0 = node_new(0);
    node* n1 = node_new(1);
    node* n2 = node_new(2);
    node* n3 = node_new(3);
    node* n4 = node_new(4);
    node* n5 = node_new(5);

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

    node_check_tree(n3);
    node_free_recurse(n3);
}

int main() {
    test_basic();
    test_compare();
    test_check();
}
