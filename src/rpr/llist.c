#include "llist.h"

#include <stdio.h>
#include <stdlib.h>

struct ll_node *ll_node_new(const unsigned int s, const double d) {
  struct ll_node *n = malloc(sizeof(*n));
  if (n != NULL) {
    n->state = s;
    n->datum = d;
    n->next = NULL;
  }
  return n;
}

void ll_node_destroy(struct ll_node **n) {
  if (n != NULL && *n != NULL) {
    free(*n);
    (*n) = NULL;
  }
}

struct ll_node *ll_remove_node(struct ll_node *n, struct ll_node *root) {
  struct ll_node *before = root, *result = NULL;
  if (n != NULL && root != NULL && n != root) {
    for (; before->next != NULL; before = before->next) {
      if (before->next == n) break;
    }
    before->next = n->next;
    ll_node_destroy(&n);
    result = before->next;
  } else if (n == root && root->next == NULL) {
    ll_node_destroy(&n);
  } else if (root->next != NULL) {
    assert("CAN'T REMOVE ROOT");
  }
  return result;
}

void ll_destroy_list(struct ll_node *root) {
  if (root != NULL) {
    struct ll_node *n = root->next;
    while (n != NULL) {
      ll_remove_node(n, root);
      n = root->next;
    }
    ll_node_destroy(&root);
  }
}

struct ll_node *ll_node_prepend(struct ll_node *n, const unsigned int s,
                                const double d) {
  struct ll_node *m = ll_node_new(s, d);
  if (m != NULL) m->next = n;
  return m;
}

void ll_node_append(struct ll_node *n, const unsigned int s, const double d) {
  if (n != NULL) {
    struct ll_node *o = ll_node_new(s, d);
    for (; n->next != NULL; n = n->next) {
    }
    n->next = o;
  }
}

struct ll_node *ll_last_node(struct ll_node *n) {
  struct ll_node *m = n;
  if (n != NULL)
    while (m->next != NULL) m = m->next;
  return m;
}

struct ll_node *ll_before_last_node(struct ll_node *n) {
  struct ll_node *m = n;
  struct ll_node *b = m;

  if (n != NULL) {
    while (m->next != NULL) {
      b = m;
      m = m->next;
    }
  }
  return b;
}