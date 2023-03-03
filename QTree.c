#include "QTree.h"

QTree* qtr_create()
{
    QTree* res = (QTree*)malloc(sizeof(QTree));
    res->key = null;
    return res;
}

QTree* qtr_clone(QTree* tree)
{
    QTree* res = (QTree*)malloc(sizeof(QTree));
    _qtr_clonen(tree, res);
    return res;
}

void _qtr_clonen(QNode* node1, QNode* node2)
{
    node2->free = node1->free;
    node2->key = node1->key;
    node2->value = node1->value;

    /* dont just copy pointers, allocate new node */
    if(node1->ln != null)
    {
        node2->ln = (QNode*)malloc(sizeof(QNode)); /* also clonen for childs*/
        _qtr_clonen(node1->ln, node2->ln);
    }
    if(node1->rn != null) /* do same for right child */
    { 
        node2->rn = (QNode*)malloc(sizeof(QNode));
        _qtr_clonen(node1->rn, node2->rn);
    }
}

void qtr_set(QTree* tree, long long key, void* value)
{
    unsigned char s = 0; /* shifting position */
    _ch: /* a node with <key> exists */
    if(tree->key == key)
    {
        tree->value = value;
        return;
    } else if(tree->free == 1)
    {
        tree->key = key;
        tree->value = value;
        tree->free = 0;
        return;  
    }
    else
        ++s;
    {
        if((key >> s) & 1)
        {
            if(tree->rn == null) /* if right node is null -> set right node to insert node */
            {
                QNode* insert = (QNode*)malloc(sizeof(QNode));
                insert->rn = null;
                insert->ln = null;
                insert->key = key;
                insert->value = value;
                tree->rn = insert;
                return;
            }
            tree = tree->rn;
            goto _ch; /* could also be done using a for loop */
        }
        if(tree->ln == null) /* if right node is null -> set right node to insert node */
        {
            QNode* insert = (QNode*)malloc(sizeof(QNode));
            insert->rn = null;
            insert->ln = null;
            insert->key = key;
            insert->value = value;
            tree->ln = insert;
            return;
        }
        tree = tree->ln;
        goto _ch;
    }
}

void* qtr_get(QTree* tree, long long key)
{
    unsigned char s = 0;
    _ch:
    if(tree->key == key)
        return tree->value;
    ++s;
    if((key >> s) & 1)
    {
        if(tree->rn == null)
        {
            return null;
        }
        tree = tree->rn;
        goto _ch;
    }
    if(tree->ln == null)
    {
        return null;
    }
    tree = tree->ln;
    goto _ch;
}

static inline void _qtr_insertn(QNode* start, unsigned char startb, QNode* insert)
{
    if(insert->rn != null)
    {
        _qtr_insertn(start, startb, insert->rn); /* reinsert right branch of removed node */
        insert->rn = null;
    }
    if(insert->ln != null)
    {
        _qtr_insertn(start, startb, insert->ln);
        insert->ln = null;
    }
    _ch:++startb;
    if((insert->key >> startb) & 1)
    {
        if(start->key == insert->key)
        {
            start->value = insert->value;
            return;
        }
        if(start->rn == null)
        {
            start->rn = insert; /* change right node  */
            return;
        }
        start = start->rn;
        goto _ch;
    }
    if(start->ln == null)
    {
        start->ln = insert; /* change left node */
        return;
    }
    start = start->ln;
    goto _ch;
}

void qtr_delete(QTree* tree, long long key)
{
    QNode* next;
    /* shifting position */
    unsigned char s = 0;
    _ch:
    ++s; /* increase shift variable */
    /* if current bit is 1 go right, if it is 0 go left */
    if((key >> s) & 1)
    {
        if(tree->rn == null)
        {
            /* return if branch ends */
            return;
        }
        /* not directly set tree node, to reinsert leafs of node that is beeing removed */
        next = tree->rn;
        if(next->key == key)
        {
            /* set right node to null, to remove old node out of structure */
            tree->rn = null;
            /* reinsert nodes */
            if(next->rn != null)
                _qtr_insertn(tree, s - 1, next->rn); /* reinsert right branch of removed node */
            if(next->ln != null)
                _qtr_insertn(tree, s - 1, next->ln); /* reinsert left branch of removed node */
            void* ret = next->value;
            free(next);
            return;
        }
        tree = next; 
        goto _ch;
    }
    if(tree->ln == null)
    {
        return;
    }
    next = tree->ln;
    if(next->key == key)
    {
        /* set right node to null, to remove old node out of structure */
        tree->ln = null;
        /* reinsert nodes */
        if(next->rn != null) /* reinsert right branch of removed node */
            _qtr_insertn(tree, s - 1, next->rn);
        if(next->ln != null) /* reinsert left branch of removed node */
            _qtr_insertn(tree, s - 1, next->ln);
        void* ret = next->value;
        free(next);
        return;
    }
    tree = next;
    goto _ch;
}

void qtr_remove(QTree* tree, long long key)
{
    /* shifting position */
    unsigned char s = 0;
    _ch:if(tree->key == key)
    {
        tree->free = 1;
        tree->value = 0;
        return;
    }
    ++s; /* increase shift variable */
    /* if current bit is 1 go right, if it is 0 go left */
    if((key >> s) & 1)
    {
        if(tree->rn == null)
        {
            /* return if branch ends */
            return;
        }
        /* not directly set tree node, to reinsert leafs of node that is beeing removed */
        tree = tree->rn; 
        goto _ch;
    }
    if(tree->ln == null)
    {
        return;
    }
    tree = tree->ln;
    goto _ch;
}

void* qtr_pop(QTree* tree, long long key)
{
    /* shifting position */
    unsigned char s = 0;
    _ch:if(tree->key == key)
    {
        tree->free = 1;
        void* ret = tree->value;
        tree->value = 0;
        return ret;
    }
    ++s; /* increase shift variable */
    /* if current bit is 1 go right, if it is 0 go left */
    if((key >> s) & 1)
    {
        if(tree->rn == null)
        {
            /* return null if branch ends */
            return null;
        }
        /* not directly set tree node, to reinsert leafs of node that is beeing removed */
        tree = tree->rn; 
        goto _ch;
    }
    if(tree->ln == null)
    {
        return null;
    }
    tree = tree->ln;
    goto _ch;
}

debug void qtr_print(QTree*tree)
{
    /* get window size */
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    /* print rows to prevent deletion of content*/
    int i;
    for(i = 0; i < w.ws_row; ++i)
        printf("\n");
    /* ansi escape codes */
    printf("\033[2J"); /* erase screen */
    printf("\033[0;0H"); /* move cursor */
    qtr_printn(tree, tree, w.ws_col/2, 1);
    printf("\033[%d;%dH", w.ws_row, 0);
}

debug void qtr_printn(QTree*tree, QNode*node, int col, int row)
{
    if (node == null) {
        return; /* return at end of branch*/
    }
    /* move cursor left */
    printf("\033[%dC", col); 
    /* move cursor down */
    printf("\033[%dB", row);
    /* using SString to get lenght of string */
    SString* str = sstr_createe(); /* string representates key of current node */
    sstr_appendd(str, node->key);
    printf("\033[%dm", 30 + rand()%9); /* colour text */
    sstr_printf(str);
    printf("\033[0m"); /* reset color */
    printf("\033[%dD", str->s_size); /* move cursor back by sizeof string */
    printf("\033[1B");
    sstr_clear(str);
    /* print "leafes" */
    if(node->ln != null)
        sstr_appendc(str, '/');
    if(node->rn != null)
        sstr_appendc(str, '\\');
    sstr_printf(str);
    /* move cursor back */
    printf("\033[%dD", str->s_size);
    printf("\033[%dD", col);
    printf("\033[%dA", row+1);
    sstr_delete(str);
    /* print subnodes*/
    qtr_printn(tree, node->rn, col + 2, row + 2); /* change col for tree structure */
    qtr_printn(tree, node->ln, col - 3, row + 2);
}

debug void qtr_printbin(QTree*tree)
{
    /* get window size */
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    /* print rows to prevent deletion of content*/
    int i;
    for(i = 0; i < w.ws_row; ++i)
        printf("\n");
    /* ansi escape codes */
    printf("\033[2J"); /* erase screen */
    printf("\033[0;0H"); /* move cursor */
    qtr_printnbin(tree, tree, w.ws_col/2, 1, 0);
    printf("\033[%d;%dH", w.ws_row, 0);
}

debug void qtr_printnbin(QTree*tree, QNode*node, int col, int row, char val)
{
    if (node == null) {
        return; /* return at end of branch*/
    }
    /* move cursor left */
    printf("\033[%dC", col); 
    /* move cursor down */
    printf("\033[%dB", row);
    /* using SString to get lenght of string */
    SString* str = sstr_createe(); /* string representates key of current node */
    sstr_appendd(str, val);
    printf("\033[%dm", 30 + rand()%9); /* colour text */
    sstr_printf(str);
    printf("\033[0m"); /* reset color */
    printf("\033[%dD", str->s_size); /* move cursor back by sizeof string */
    printf("\033[1B");
    sstr_clear(str);
    /* print "leafes" */
    if(node->ln != null)
        sstr_appendc(str, '/');
    if(node->rn != null)
        sstr_appendc(str, '\\');
    sstr_printf(str);
    /* move cursor back */
    printf("\033[%dD", str->s_size);
    printf("\033[%dD", col);
    printf("\033[%dA", row+1);
    sstr_delete(str);
    /* print subnodes*/
    qtr_printnbin(tree, node->rn, col + 1, row + 2, 1); /* change col for tree structure */
    qtr_printnbin(tree, node->ln, col - 2, row + 2, 0);
}
