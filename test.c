#include <stdio.h>
#include <stdlib.h>

extern void *OSE_malloc(size_t size);
extern void OSE_free(void *p);
extern void *OSE_realloc(void *p, size_t size);

int main(){
  size_t initial_allocation_size = 16;
  void *alloc = OSE_malloc(initial_allocation_size);

  printf("initial allocation of %ld: %p\n", initial_allocation_size, alloc);
}
