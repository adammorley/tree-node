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
}

int main() {
    test_basic();
    test_compare();
}
