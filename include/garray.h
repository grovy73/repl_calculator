#ifndef GARRAY_H
#define GARRAY_H

#define gappend(array, item) ({ \
  typeof(item) _tmp = item; \
  _gappend((array), &_tmp); \
  })


#include <stdlib.h>
typedef struct {
  void* items;
  size_t item_size;
  size_t length;
  size_t capacity;
} garray_t;

void ginit_array(garray_t* array, size_t item_size, size_t initial_capacity);
void _gappend(garray_t* array, void* item);
void *gget(garray_t* array, size_t index);
void gremove(garray_t* array, size_t index);

#endif
