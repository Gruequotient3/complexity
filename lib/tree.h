#ifndef TREE_h
#define TREE_h

typedef int element_t;
typedef struct bt_node bt_node_t;
struct bt_node {
    element_t data;
    struct bt_node*  l_child;
    struct bt_node* r_child;
};

// Create tree function
bt_node_t* bt_new_tree(element_t elem, bt_node_t* l_child, bt_node_t* r_child);
bt_node_t* bt_new_node(element_t elem);
bt_node_t* bt_copy_tree(bt_node_t* tree);
bt_node_t* bt_insert_node(bt_node_t** pos , bt_node_t* new_node);
bt_node_t* bt_avl_insert_node(bt_node_t* tree, element_t elem);

// Delte tree function
void bt_free_tree(bt_node_t** ptree);


// tree printing function
void bt_prefix_print(bt_node_t* tree);
void bt_suffix_print(bt_node_t* tree);
void bt_infix_print(bt_node_t* tree);

// tree information function
int bt_nb_leaves(bt_node_t* tree);
int bt_height(bt_node_t* tree);
bt_node_t** bt_find_ordered_position(bt_node_t** ptree, element_t elem);

// optimisation function
bt_node_t* bt_left_rotation(bt_node_t* tree);
bt_node_t* bt_right_rotation(bt_node_t* tree);
int bt_get_balance(bt_node_t* tree);
#endif
