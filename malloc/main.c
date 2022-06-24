#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define HEAP_CAP 640000
#define HEAP_ALLOCED_CHUNKS_CAP 1024
#define HEAP_FREED_CAP 1024

typedef struct
{
  void *start;
  size_t size;
} Heap_Chunk;

char heap[HEAP_CAP] = {0};
size_t heap_size = 0;

Heap_Chunk heap_alloced[HEAP_ALLOCED_CHUNKS_CAP] = {0};
size_t heap_alloced_size = 0;

Heap_Chunk heap_freed[HEAP_FREED_CAP] = {0};
size_t heap_freed_size = 0;
void *heap_alloc(size_t size)
{
  if (size > 0)
  {
    assert(heap_size + size <= HEAP_CAP);
    void *result = heap_size + heap; // chunk的初始位置
    heap_size += size;               // chunk的大小
    const Heap_Chunk chunk = {
        .start = result,
        .size = size,
    };
    assert(heap_alloced_size < HEAP_ALLOCED_CHUNKS_CAP);
    heap_alloced[heap_alloced_size++] = chunk;
    return result;
  }
  else
  {
    return NULL;
  }
}
void heap_dump_alloced_chunks(void)
{
  printf("Allocated Chunks (%zu):\n", heap_alloced_size);
  for (size_t i = 0; i < heap_alloced_size; i++)
  {
    printf(" start: %p, size: %zu\n", heap_alloced[i].start, heap_alloced[i].size);
  }
}
// O(Alloced)
void heap_free(void *ptr)
{
  for (size_t i = 0; i < heap_alloced_size; i++)
  {
    if (heap_alloced[i].start == ptr)
    {
    }
  }
}
void heap_collect()
{
}
int main()
{
  for (size_t i = 0; i < 5; i++)
  {
    printf("%p\n", malloc(0));
  }

  return 0;
}
