#ifndef LINKEDLIST_H
#  define LINKEDLIST_H

#  include <stdio.h>
#  include <stdlib.h>
#  include <assert.h>

#  ifdef __cplusplus
extern "C" {
#  endif

  typedef struct node node_t;

  typedef struct linkedlist linkedlist_t;

  struct node {
    int data;
    struct node * next;
  };

  struct linkedlist {
    node_t * head;
    node_t ** tail;
  };

  extern node_t *     ll_new_node(int data);
  extern node_t **    ll_insert_node(node_t ** pos, node_t * new_node);
  extern void           ll_print_from(node_t * list);
  extern void           ll_clear_from(node_t ** plist);
  extern linkedlist_t * ll_new(void);
  extern void           ll_push_back(linkedlist_t * llptr, int data);
  extern void           ll_push_front(linkedlist_t * llptr, int data);
  extern void           ll_print(linkedlist_t * llptr);
  extern void           ll_clear(linkedlist_t * llptr);
  extern void           ll_delete(linkedlist_t ** pllptr);

  extern int ll_empty(linkedlist_t * llptr);

  extern void ll_erase(linkedlist_t * llptr, node_t ** pos);

#  ifdef __cplusplus
}
#  endif

#endif

