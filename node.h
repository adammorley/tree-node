#include <stdbool.h>

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
    compare the values stored at two nodes
*/
bool node_compare(node* n0, node* n1);

/*
    is the node a leaf node?
*/
bool node_isleaf(node* n);

/*
    recursive comparison, following pointers
*/
bool node_compare_recurse(node* n0, node* n1);

#endif //TREE_NODE_H
