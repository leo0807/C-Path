#include <stdio.h>
#include <string.h>
#include <assert.h>
#define LA_IMPLEMENTATION
#include "./la.h"

#define WIDTH 32
#define HEIGHT 32
static char display[WIDTH * HEIGHT];
static_assert(HEIGHT % 2 == 0, "If the amount of display rows is not divisible by 2 we can't properly compress it. See show(void) function");

typedef enum
{
  BACK = 0,
  FORE = 1,
} Pixel;

void fill(Pixel p)
{
  // memset(display, p, WIDTH * HEIGHT);
  Pixel *ptr = display;
  size_t n = WIDTH * HEIGHT;
  while (n-- > 0)
  {
    /* code */
    *ptr++ = p;
  }
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
  static char row[WIDTH];
  //                t  b
  static char table[2][2] = {
      //
      {' ', '_'}, // 0
      {'^', 'C'}, // 1
  };

  for (int y = 0; y < HEIGHT / 2; ++y)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      Pixel t = display[2 * y * WIDTH + x];
      Pixel b = display[(2 * y + 1) * WIDTH + x];
    }

    fwrite(&display[y * WIDTH], WIDTH, 1, stdout);
    fputc('\n', stdout);
  }
}

int main(void)
{
  fill(' ');
  circle(v2ii(0), WIDTH / 2);
  return 0;
}