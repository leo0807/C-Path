#include <stdio.h>
#include <string.h>
#define LA_IMPLEMENTATION
#include "./la.h"

#define WIDTH 32
#define HEIGHT 32
static char display[WIDTH * HEIGHT];

void fill(char p)
{
  memset(display, p, WIDTH * HEIGHT);
}

void circle(V2i center, int radius)
{
  V2i b = v2i_sub(center, v2ii(radius));
  V2i e = v2i_sum(center, v2ii(radius));

  for (int y = b.y; y <= e.y; ++y)
  {
    for (int x = b.x; x <= e.x; ++x)
    {
      int dx = center.x - x;
      int dy = center.y - y;
      if (dx * dx + dy * dy <= radius * radius)
      {
        if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
        {
          display[y * WIDTH + x] = '*';
        }
      }
    }
  }
}

void show(void)
{
  for (int y = 0; y < HEIGHT; ++y)
  {
    fwrite(display[y * WIDTH], WIDTH, 1, stdout);
    fputc('\n', stdout);
  }
}

int main(void)
{
  fill(' ');
  circle(v2ii(0), WIDTH / 2);
  return 0;
}