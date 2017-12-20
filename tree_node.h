#include <stdbool.h>

#include "../log/log.h"

#ifndef TREE_NODE_H
#define TREE_NODE_H

typedef struct tree_node tree_node;
struct tree_node {
    tree_node* p; // parent
    tree_node* l; // left child
    tree_node* r; // right child
    long d; // value
    /*
        balance factor
        height right - height left
    */
    long b;
};

/*
    create a node, return ownership
*/
tree_node* tree_node_new(long d);

/*
    calculate the height of the trees under a tree node
*/
long tree_node_calculate_height(tree_node* n);

/*
    check a tree under a node for consistency (b, binary search props, etc)
*/
void tree_node_check(tree_node* n);

/*
    compare the values stored at two nodes
*/
bool tree_node_compare(tree_node* n0, tree_node* n1);

/*
    recursive comparison, following pointers
*/
bool tree_node_compare_recurse(tree_node* n0, tree_node* n1);

/*
    recursively free nodes under n, including n
*/
void tree_node_free_recurse(tree_node* n);

/*
    is the node a leaf node?
*/
bool tree_node_isleaf(tree_node* n);

/*
    validate the balance factors for a node by calculating heights
*/
void tree_node_validate_b(tree_node* n);

#endif //TREE_NODE_H
