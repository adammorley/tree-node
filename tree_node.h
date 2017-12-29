#include <stdbool.h>

#include "../log/log.h"
#include "../queue/queue.h"

#ifndef TREE_NODE_H
#define TREE_NODE_H

typedef struct tree_node tree_node;
struct tree_node {
    tree_node* p; // parent
    tree_node* l; // left child
    tree_node* r; // right child
    long d; // value
    /*
        count of values (if put twice, == 2)
        using int here so b can be a short
        and still have room for a mutex later
    */
    unsigned int c; 
    /*
        balance factor
        height right - height left
    */
    short b;
};

/*
    create a node, return ownership
*/
tree_node* tree_node_new(long d);

/*
    calculate the height of the tree under a tree node
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
    in-order traversal, returns a queue of the
    tree_node pointers in the order of the tree

    thought about:
        - function remembers next node and passes
          back a ptr to the tree node's data
        - iterator function

    this approach uses a queue which does an
    allocation for each tree node, which is
    sub-optimal.  iterator would fix this

    the other option is to provide a closure from
    the caller which handles the updates and the
    data, which would also be more efficient
    (but also pretty ugly in c-notation)
*/
void tree_node_inorder(tree_node* node, queue* queue);

/*
    validate the balance factors for a node by calculating heights
*/
void tree_node_validate_b(tree_node* n);

#endif //TREE_NODE_H
