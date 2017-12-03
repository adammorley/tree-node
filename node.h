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
    unsigned long b;
};

/*
    create a node, return ownership
*/
node* node_new(long d);

#endif //TREE_NODE_H
