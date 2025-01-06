#include <vector.h>

ivec_t * ivec_new(void) {
    ivec_t * vec = malloc(1 * sizeof *vec);
    assert(vec);
    vec->size = 0;
    vec->max_size = 1024;
    vec->data = malloc(vec->max_size * sizeof *(vec->data));
    assert(vec->data);
    return vec;
}

void ivec_insert(ivec_t* vec, int pos, int data){
    if(vec->size == vec->max_size) {
        void * ptr;
        vec->max_size = vec->max_size * 2;
        ptr = realloc(vec->data, vec->max_size * sizeof *(vec->data));
        if(ptr == NULL) {
            free(vec->data);
            free(vec);
            assert(ptr);
        } else
        vec->data = ptr;
    }

    int addData = data;
    int dtemp;
    if (!vec->size){
        vec->data[0] = data;
    }
    for (int i = pos; (long unsigned)i < vec->size+1; ++i){
        dtemp = vec->data[i];
        vec->data[i] = addData;
        addData = dtemp;
    }
    vec->size++;
}

void ivec_push_back(ivec_t * vec, int data) {
    if(vec->size == vec->max_size) {
        void * ptr;
        vec->max_size = vec->max_size * 2;
        ptr = realloc(vec->data, vec->max_size * sizeof *(vec->data));
        if(ptr == NULL) {
            free(vec->data);
            free(vec);
            assert(ptr);
        } else
        vec->data = ptr;
    }
    vec->data[vec->size] = data;
    ++(vec->size);
}

int ivec_size(ivec_t * vec) {
    return vec->size;
}

int ivec_empty(ivec_t * vec) {
    return !(vec->size);
}

int ivec_at(ivec_t * vec, int pos) {
    assert((long unsigned )pos < vec->size);
    return vec->data[pos];
}

void ivec_print(ivec_t * vec) {
    int i;
    for(i = 0; i < (int)vec->size; ++i)
        printf("%d ", vec->data[i]);
    printf("\n");
}

void ivec_delete(ivec_t ** pvec) {
    free((*pvec)->data);
    free(*pvec);
    *pvec = NULL;
}
