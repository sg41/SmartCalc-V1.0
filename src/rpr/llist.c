#include "llist.h"

#include <stdio.h>
#include <stdlib.h>

struct ll_node *ll_node_new(const unsigned int s, const double d) {
    struct ll_node *n = malloc(sizeof(*n));
    n->state = s;
    n->datum = d;
    n->next = NULL;
    return n;
}

void ll_node_destroy(struct ll_node **n) {
    free(*n);
    (*n) = NULL;
}

struct ll_node *ll_node_prepend(struct ll_node *n, const unsigned int s, const double d) {
    struct ll_node *m = ll_node_new(s, d);
    m->next = n;
    return m;
}

void ll_node_append(struct ll_node *n, const unsigned int s, const double d) {
    struct ll_node *o = ll_node_new(s, d);
    for (; n->next != NULL; n = n->next) {
    }
    n->next = o;
}
