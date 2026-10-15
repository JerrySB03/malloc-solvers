#include <stddef.h>

void *OSE_malloc(size_t size);
void OSE_free(void *p);
void *OSE_realloc(void *p, size_t size);
