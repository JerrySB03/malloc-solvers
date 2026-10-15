#include "ose_malloc.h"
#include "helpers.h"
#include <sys/mman.h>
#include <assert.h>
#ifdef DEBUG
#include <stdio.h>
#endif //DEBUG

void *OSE_malloc(size_t size){
  return NULL;
}

void OSE_free(void *p){
  return;
}

void *OSE_realloc(void *p, size_t size){
  return NULL;
}

