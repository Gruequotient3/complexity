
#include <stdio.h>

#include <linkedlist.h>
#include <vector.h>
#include <my_timer.h>
#include <tree.h>
#include <file.h>


#define N1 100
#define N2 100
#define SEED 842

#define ERRORPARAMETER(parameter) \
    printf("Invalid arguments %s : $ ./<progName> <testid> <nbTest> (<percent>)\n", parameter);\
    printf("testid :\n");\
    printf("\t 1 = Test all structure\n");\
    printf("\t 2 = Test binary tree percent from 0.0 to 100.0\n");\
    printf("\t 3 = Test binary tree specific percent (need percent argument)\n");

static void get_data_time(int n);
static void get_bt_compare(int n);
static void get_bt_compare_fix(int n, float percent);

static double exec_linkedlist_test(int n);
static double exec_ivec_test(int n);
static double exec_bt_test(int n);
static double exec_bt_test_avl(int n, float percent);

static int find_ordered_pos_in_vec(ivec_t* vec, int data);
static int is_vec_ordered(ivec_t * vec);

static node_t ** find_ordered_pos_in_ll(linkedlist_t* llptr, int data);
static int is_ll_ordered(linkedlist_t * llptr);

static int is_bt_ordered(bt_node_t* tree);
static int is_bt_ordered_helper(bt_node_t* tree, int prev);


int main(int argv, char* argc[]) {
    int id = 0;
    int n = 0;
    float percent;
    if (argv < 2 || argv > 4){
        ERRORPARAMETER("number")
        return 1;
    }
    else{
        id = atoi(argc[1]);
        if (!id){
            ERRORPARAMETER("id");
            return 1;
        }
        n = atoi(argc[2]);
        if (!n){
            ERRORPARAMETER("nbTest");
            return 1;
        }
        if (id == 3){
            if (argv != 4){
                ERRORPARAMETER("percent");
                return 1;
            }
            percent = atoi(argc[3]);
            if (!percent){
                ERRORPARAMETER("percent");
                return 1;
            }
        }

    }

    switch (id){
        case 1:
            get_data_time(n);
            printf("1\n");
            break;
        case 2:
            get_bt_compare(n);
            printf("2\n");
            break;
        case 3:
            get_bt_compare_fix(n, percent);
            printf("3\n");
            break;

    }
    return 0;
}

void get_data_time(int n){
    FILE* llFile = openFile("./data/linkedlistPoints.dat", "w+");
    FILE* ivecFile = openFile("./data/vectorPoints.dat", "w+");
    FILE* btFile = openFile("./data/binaryTreePoints.dat", "w+");

    for (int i = 1; i < n; ++i){
        double llt = exec_linkedlist_test(i);
        writeData2(llFile, (double)i, llt);
        double vect = exec_ivec_test(i);
        writeData2(ivecFile, (double)i, vect);
        double btt = exec_bt_test(i);
        writeData2(btFile, (double)i, btt);
    }

    closeFile(llFile);
    closeFile(ivecFile);
    closeFile(btFile);
}

void get_bt_compare(int n){
    FILE* percentavlFile = openFile("./data/percentavlPoints.dat", "w+");

    double constant = exec_bt_test(n);
    for (float i = 0.0; i < 100.0; i += 0.1f){
        writeData3(percentavlFile, i, exec_bt_test_avl(n, i), constant);
    }
    closeFile(percentavlFile);
}

void get_bt_compare_fix(int n, float percent){
    FILE* fixpercentFile = openFile("./data/fixpercentPoints.dat", "w+");
    for (float i = 1; i < n; ++i){
        writeData3(fixpercentFile, i, exec_bt_test_avl(i, percent), exec_bt_test(i));
    }
    closeFile(fixpercentFile);

}

double exec_ivec_test(int n) {
    double el;
    int i, data, pos;
    ivec_t * vec = ivec_new();
    srand(SEED);
    initTimer();
    for(i = 0; i < n; ++i) {
        data = rand() % n;
        pos = find_ordered_pos_in_vec(vec, data);
        (void)pos;
        ivec_insert(vec, pos, data);
    }
    el = getElapsedTime();
    ivec_delete(&vec);
    return el;
}

int is_vec_ordered(ivec_t * vec) {
    int i, n = ivec_size(vec);
    for(i = 0; i < n - 1; ++i)
        if(ivec_at(vec, i) > ivec_at(vec, i + 1))
            return 0;
    return 1;
}

int find_ordered_pos_in_vec(ivec_t * vec, int data) {
    int i;
    for (i = 0; (long unsigned )i < vec->size; ++i){
        if (data < *((vec->data)+i))
            return i;
    }
    return vec->size;
}

double exec_linkedlist_test(int n) {
    double el;
    int i, data;
    linkedlist_t * ll = ll_new();

    srand(SEED);
    initTimer();
    for(i = 0; i < n; ++i) {
        node_t ** pos;
        data = rand() % n;
        pos = find_ordered_pos_in_ll(ll, data);
        pos = ll_insert_node(pos, ll_new_node(data));
        if(*pos == NULL)
            ll->tail = pos;
    }
    el = getElapsedTime();
    ll_delete(&ll);
    return el;
}

node_t ** find_ordered_pos_in_ll(linkedlist_t * llptr, int data) {
    node_t ** pos = &(llptr->head);
    while( *pos != NULL && (*pos)->data < data)
        pos = &((*pos)->next);
    return pos;
}

int is_ll_ordered(linkedlist_t * ll) {
    if (!ll->head || !ll->head->next)
        return 1;
    node_t* head = ll->head;
    while (!head->next){
        if (head->data > head->next->data){
            return 0;
        }
        head = head->next;
    }
    return 1;
}

double exec_bt_test(int n){
    double el = 0.0;
    bt_node_t* tree = NULL;
    int i, data;
    srand(SEED);
    initTimer();
    for (i = 0; i < n; i++){
        data = rand() % n;
        bt_node_t** pos = bt_find_ordered_position(&tree, data);
        *pos = bt_insert_node(pos, bt_new_node(data));
    }
    el = getElapsedTime();
    bt_free_tree(&tree);
    return el;
}

double exec_bt_test_avl(int n, float percent){
    double el = 0.0;
    bt_node_t* tree = NULL;
    int i, data;
    float nbPercent = n * percent / 100.0;
    int count = 0;
    srand(SEED);
    initTimer();
    for (i = 0; i < n; i++){
        data = rand() % n;
        if (i < nbPercent){
            count++;
            tree = bt_avl_insert_node(tree, data);
        }
        else{
            bt_node_t** pos = bt_find_ordered_position(&tree, data);
            *pos = bt_insert_node(pos, bt_new_node(data));
        }
    }
    el = getElapsedTime();
    bt_free_tree(&tree);
    return el;
}

int is_bt_ordered(bt_node_t* tree){
    int prev = -1;
    return is_bt_ordered_helper(tree, prev);
}

int is_bt_ordered_helper(bt_node_t* tree, int prev){
    if (!tree)
        return 1;
    if (!is_bt_ordered_helper(tree->l_child, prev)) return 0;
    if (prev > tree->data) return 0;
    prev = tree->data;
    return is_bt_ordered_helper(tree->r_child, prev);
}

