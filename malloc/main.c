#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#define HEAP_CAP 640000
#define HEAP_ALLOCED_CHUNKS_CAP 1024
typedef struct
{
  void *start;
  size_t size;
} Heap_Chunk;

char heap[HEAP_CAP] = {0};
Heap_Chunk heap_alloced_chunks[HEAP_ALLOCED_CHUNKS_CAP] = {0};
size_t heap_alloced_size = 0;
size_t heap_size = 0;
void *heap_alloc(size_t size)
{
  assert(heap_size + size <= HEAP_CAP);
  void *result = heap_size + size; // chunk的初始位置
  heap_size += size;               // chunk的大小
  return result;
}
void heap_free(void *ptr)
{
  (void)ptr;
}
void heap_collect()
{
}
int main()
{
  char *root = heap_alloc(69);
  for (size_t i = 0; i < 26; i++)
  {
    root[i] = i + 'A';
  }
  heap_free(root);
  return 0;
}