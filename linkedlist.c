#include <linkedlist.h>

node_t * ll_new_node(int data) {
    node_t * n = malloc(1 * sizeof *n);
    assert(n);
    n->data = data;
    n->next = NULL;
    return n;
}

node_t ** ll_insert_node(node_t ** pos, node_t * new_node) {
    new_node->next = *pos;
    *pos = new_node;
    return &(new_node->next);
}

void ll_print_from(node_t * list) {
    while(list != NULL) {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

void ll_clear_from(node_t ** plist) {
    node_t * ptr = *plist;
    while(ptr != NULL) {
        node_t * tofree = ptr;
        ptr = ptr->next;
        free(tofree);
    }
    *plist = NULL;
}

linkedlist_t * ll_new(void) {
    linkedlist_t * ll = calloc(1, sizeof *ll);
    ll->tail = &(ll->head);
    return ll;
}

void ll_push_back(linkedlist_t * llptr, int data) {
    llptr->tail = ll_insert_node(llptr->tail, ll_new_node(data));
}

void ll_push_front(linkedlist_t * llptr, int data) {
    if(llptr->head != NULL)
        ll_insert_node(&(llptr->head), ll_new_node(data));
    else
        llptr->tail = ll_insert_node(&(llptr->head), ll_new_node(data));
}

void ll_print(linkedlist_t * llptr) {
    ll_print_from(llptr->head);
}

void ll_clear(linkedlist_t * llptr) {
    ll_clear_from( &(llptr->head) );
    llptr->tail = &(llptr->head);
}

void ll_delete(linkedlist_t ** pllptr) {
    ll_clear(*pllptr);
    free(*pllptr);
    *pllptr = NULL;
}

int ll_empty(linkedlist_t * llptr){
    assert(llptr);
    if (!llptr->head)
        return 1;
    return 0;
}
