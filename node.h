#include <stdbool.h>

#include "../log/log.h"

#ifndef TREE_NODE_H
#define TREE_NODE_H

typedef struct node node;
struct node {
    #include "../node/struct_node.h"
    node* p; // parent
    /*
        balance factor
        height right - height left
    */
    long b;
};

/*
    create a node, return ownership
*/
node* node_new(long d);

/*
    calculate the height of the trees under a tree node
*/
long node_calculate_height(node* n);

/*
    check a tree under a node for consistency (b, binary search props, etc)
*/
void node_check_tree(node* n);

/*
    compare the values stored at two nodes
*/
bool node_compare(node* n0, node* n1);

/*
    recursive comparison, following pointers
*/
bool node_compare_recurse(node* n0, node* n1);

/*
    recursively free nodes under n, including n
*/
void node_free_recurse(node* n);

/*
    is the node a leaf node?
*/
bool node_isleaf(node* n);

/*
    validate the balance factors for a node by calculating heights
*/
void node_validate_b(node* n);

#endif //TREE_NODE_H
