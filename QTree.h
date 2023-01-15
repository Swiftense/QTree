#ifndef QTREE_H /* just little different to bs tree */
    #define QTREE_H

    #ifdef __cplusplus
        extern "C" {
    #endif

    #include <sys/ioctl.h>

    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>

    #include "SString.h"
    #include "debug.h"
    #include "null.h"

    typedef struct _qNode QNode;
    typedef struct _qNode QTree; /* Root node */

    /* creates new tree */
    QTree* qtr_create();
    /* recursively clone Tree */
    QTree* qtr_clone(QTree* tree);
    void _qtr_clonen(QNode* node1, QNode* node2);
    /* sets value of <key> to <value> */
    /* creates new node if there is no node with <key> */
    void qtr_set(QTree* tree, long long key, void* value);
    /* returns element that belongs to <key> */
    void* qtr_get(QTree* tree, long long key);
    /* completely deletes node out of tree, also cleans up tree structure, very slow, since every subnode has to be reinserted */
    void qtr_delete(QTree* tree, long long key);
    /* marks node with <key> as free */
    void qtr_remove(QTree* tree, long long key);
    /* marks node with <key> as free returns value of node that belongs to <key> */
    void*qtr_pop(QTree* tree, long long key);
    /* used to insert node at specific point */
    static inline void _qtr_insertn(QNode* start, unsigned char startb, QNode* insert);
    /* prints entire tree */
    debug void qtr_print(QTree*tree);
    /* prints node at row|col*/
    debug void qtr_printn(QTree*tree, QNode*node, int col, int row);
    /* print tree in "binary" format */
    debug void qtr_printbin(QTree*tree);
    debug void qtr_printnbin(QTree*tree, QNode*node, int col, int row, char val);

    struct _qNode
    {
        long long key;
        void* value;

        /* only con of qtree is that removed nodes are not directly removed, */
        char free; /* since they are important for all subnodes */

        struct _qNode* ln; /* left node */
        struct _qNode* rn; /* right node */
    };

    #ifdef __cplusplus
        }
    #endif
#endif 