#ifndef VECTOR_H
#  define VECTOR_H

#  include <stdio.h>
#  include <stdlib.h>
#  include <assert.h>

#  ifdef __cplusplus
extern "C" {
#  endif

  typedef struct ivec ivec_t;

  struct ivec {
    size_t size;
    size_t max_size;
    int * data;
  };

  extern ivec_t *   ivec_new(void);
  extern void       ivec_insert(ivec_t* vec, int pos, int data);
  extern void       ivec_push_back(ivec_t * vec, int data);
  extern int        ivec_size(ivec_t * vec);
  extern int        ivec_empty(ivec_t * vec);
  extern int        ivec_at(ivec_t * vec, int pos);
  extern void       ivec_print(ivec_t * vec);
  extern void       ivec_delete(ivec_t ** pvec);

#  ifdef __cplusplus
}
#  endif

#endif
