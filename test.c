#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h> 
#include <stdint.h>


extern void *OSE_malloc(size_t size);
extern void OSE_free(void *p);
extern void *OSE_realloc(void *p, size_t size);

unsigned int failed_allocations = 0;

void run_basic_tests(){
  size_t initial_allocation_size = 16;
  void *alloc = OSE_malloc(initial_allocation_size);
  if(alloc == NULL)
    failed_allocations++;

  printf("initial allocation of %ld: %p\n", initial_allocation_size, alloc);
  void *realloced = OSE_realloc(alloc, 0x100);
  OSE_free(realloced);
}

void test_edge_cases(){
  {
    void *alloc = OSE_malloc(0);
    OSE_free(alloc);

    alloc = OSE_realloc(0, 16);
    if(alloc == NULL)
      failed_allocations++;
    OSE_free(alloc);
  }
  {
    long *alloc = OSE_malloc(16);
    *alloc = 0xdeadbeef;
    long *reallocated = OSE_realloc(alloc, SIZE_MAX / 2);
    if(reallocated == NULL){
      assert(*alloc == 0xdeadbeef);
    } else {
      assert(*reallocated == 0xdeadbeef);
      for(size_t i = 0; i < (SIZE_MAX / 2); i+=(SIZE_MAX / 65536)){
        volatile long value = reallocated[i]; // Access reallocated[i] - check that memory actually exists
        (void)value;
      }
      fprintf(stderr, "\n\nWhat, how? OSE_realloc(*p, SIZE_MAX) didn't fail\n\n");
    }
  }
}

long int run_small_benchmark(){
  #define SMALL_TOTAL_ALLOCATIONS 1024
  clock_t t = clock();
  void *allocations[SMALL_TOTAL_ALLOCATIONS];
  for(size_t i = 0; i < SMALL_TOTAL_ALLOCATIONS; i++)
    allocations[i] = OSE_malloc(i * 17);
  for(size_t i = 0; i < SMALL_TOTAL_ALLOCATIONS; i++)
    OSE_free(allocations[i]);

  for(size_t i = 0; i < SMALL_TOTAL_ALLOCATIONS; i++){
    if(allocations[i] == NULL)
      failed_allocations++;
  }

  t = clock() - t; 

  return (t * 1000)/CLOCKS_PER_SEC; // Return time taken in milliseconds
}

long int run_big_benchmark(){
  #define BIG_TOTAL_ALLOCATIONS 65536
  clock_t t = clock();
  void *allocations[BIG_TOTAL_ALLOCATIONS];
  for(size_t i = 0; i < BIG_TOTAL_ALLOCATIONS; i++)
    allocations[i] = OSE_malloc(i * 17);
  for(size_t i = 0; i < BIG_TOTAL_ALLOCATIONS; i++)
    OSE_free(allocations[i]);

  for(size_t i = 0; i < BIG_TOTAL_ALLOCATIONS; i++){
    if(allocations[i] == NULL)
      failed_allocations++;
  }

  t = clock() - t; 

  return (t * 1000)/CLOCKS_PER_SEC; // Return time taken in milliseconds
}

void run_benchmarks(){
  printf("Time taken for run_small_benchmark(): %ldms\n", run_small_benchmark());
  printf("Time taken for run_big_benchmark(): %ldms\n", run_big_benchmark());
}

int main(){
  run_basic_tests();
  test_edge_cases();
  run_benchmarks();

  assert(failed_allocations == 0);
}
