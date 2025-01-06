#ifndef TREE_c
#define TREE_c


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include <tree.h>

bt_node_t* bt_new_tree(element_t elem, bt_node_t* l_child, bt_node_t* r_child) {
    bt_node_t * tree = (bt_node_t*)malloc( sizeof *tree);
    assert(tree);
    tree->data = elem;
    tree->l_child = l_child;
    tree->r_child = r_child;
    return tree;
}

bt_node_t* bt_new_node(element_t elem) {
    return bt_new_tree(elem, NULL, NULL);
}

bt_node_t* bt_copy_tree(bt_node_t* tree){
    if (!tree)
        return NULL;
    return bt_new_tree(tree->data,
                       bt_copy_tree(tree->l_child),
                       bt_copy_tree(tree->r_child));
}

bt_node_t* bt_insert_node(bt_node_t** pos , bt_node_t* new_node) {
    bt_node_t* previous = *pos;
    *pos = new_node;
    if(previous != NULL) {
        if(previous->data < new_node->data)
            new_node->l_child = previous;
        else
            new_node->r_child = previous;
    }
    return new_node;
}

bt_node_t* bt_avl_insert_node(bt_node_t* tree, element_t elem){
    if (!tree)
        return bt_new_node(elem);

    if (elem < tree->data)
        tree->l_child = bt_avl_insert_node(tree->l_child, elem);
    else if (elem >= tree->data)
        tree->r_child = bt_avl_insert_node(tree->r_child, elem);

    int balance = bt_get_balance(tree);

    if (balance > 1 && elem < tree->l_child->data)
        return bt_right_rotation(tree);
    if (balance < -1 && elem > tree->r_child->data)
        return bt_left_rotation(tree);
    if (balance > 1 && elem < tree->l_child->data){
        tree->l_child = bt_left_rotation(tree->l_child);
        return bt_right_rotation(tree);
    }
    if(balance < -1 && elem > tree->r_child->data){
        tree->r_child = bt_right_rotation(tree->r_child);
        return bt_left_rotation(tree);
    }

    return tree;


}

void bt_free_tree(bt_node_t** ptree){
    assert(ptree);
    if (!*ptree)
        return;
    bt_free_tree(&((*ptree)->l_child));
    bt_free_tree(&((*ptree)->r_child));
    free(*ptree);
    *ptree = NULL;
}


void bt_prefix_print(bt_node_t* tree) {
    if (tree == NULL){
        return;
    }
    printf("%d ", tree->data);
    bt_prefix_print(tree->l_child);
    bt_prefix_print(tree->r_child);
}

void bt_suffix_print(bt_node_t* tree) {
    if (tree == NULL){
        printf("NULL ");
        return;
    }
    bt_suffix_print(tree->l_child);
    bt_suffix_print(tree->r_child);
    printf("%d ", tree->data);
}

void bt_infix_print(bt_node_t* tree) {
    if (tree == NULL)
        return;
    bt_infix_print(tree->l_child);
    printf("%d ", tree->data);
    bt_infix_print(tree->r_child);
}

int bt_nb_leaves(bt_node_t* tree){
    if (!tree)
        return 1;
    return bt_nb_leaves(tree->l_child) + bt_nb_leaves(tree->r_child);
}

int bt_height(bt_node_t* tree){
    if (!tree)
        return 0;
    int hleft = bt_height(tree->l_child);
    int hright = bt_height(tree->r_child);
    return 1 + (hleft > hright ? hleft : hright);
}


bt_node_t** bt_find_ordered_position(bt_node_t** ptree, element_t elem) {
    assert(ptree);
    if (*ptree == NULL)
        return ptree;
    if(elem < (*ptree)->data)
        return bt_find_ordered_position(&((*ptree)->l_child), elem);
    return bt_find_ordered_position(&((*ptree)->r_child), elem);
}

bt_node_t* bt_left_rotation(bt_node_t* tree){
    bt_node_t* pivot = tree->r_child;

    tree->r_child = pivot->l_child;
    pivot->l_child = tree;
    tree = pivot;
    return pivot;

}

bt_node_t* bt_right_rotation(bt_node_t* tree){
    bt_node_t* pivot = tree->l_child;

    tree->l_child = pivot->r_child;
    pivot->r_child = tree;
    tree = pivot;
    return pivot;
}

int bt_get_balance(bt_node_t* tree){
    if (!tree)
        return 0;
    return bt_height(tree->l_child) - bt_height(tree->r_child);
}



#endif
