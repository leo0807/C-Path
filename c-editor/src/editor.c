#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include "./editor.h"
#include "./sv.h"

#define LINE_INIT_CAPACITY 1024
#define EDITOR_INIT_CAPACITY 128
static void editor_create_first_new_line(Editor *editor);

static void line_grow(Line *line, size_t n)
{
  size_t new_capacity = line->capacity;
  assert(new_capacity >= line->size);
  while (new_capacity - line->size < n)
  {
    if (new_capacity == 0)
    {
      new_capacity = LINE_INIT_CAPACITY;
    }
    else
    {
      new_capacity *= 2;
    }
  }

  if (new_capacity != line->capacity)
  {
    line->chars = realloc(line->chars, new_capacity);
    line->capacity = new_capacity;
  }
}