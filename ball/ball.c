#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#define LA_IMPLEMENTATION
#include "./la.h"

#define WIDTH 64
#define HEIGHT 32
#define FPS 15
#define RADIUS (HEIGHT / 4.0f)
#define GRAVITY 100.0f
#define DT (1.0f / FPS)
#define DAMPER -0.90f
static char display[WIDTH * HEIGHT];
static_assert(HEIGHT % 2 == 0, "If the amount of display rows is not divisible by 2 we can't properly compress it. See show(void) function");

typedef enum
{
  BACK = 0,
  FORE = 1,
  PIXEL_N,
} Pixel;

void fill(Pixel p)
{
  // memset(display, p, WIDTH * HEIGHT);
  Pixel *ptr = display;
  size_t n = WIDTH * HEIGHT;
  while (n-- > 0)
  {
    *ptr++ = p;
  }
}

void circle(V2f center, float radius)
{
  V2i b = v2i2f(v2f_floor(v2f_sub(center, v2ff(radius))));
  V2i e = v2i2f(v2f_ceil(v2f_sum(center, v2ff(radius))));

  for (int y = b.y; y <= e.y; ++y)
  {
    for (int x = b.x; x <= e.x; ++x)
    {
      V2f p = v2f_sum(v2f2i(v2i(x, y)), v2ff(0.5f));
      V2f d = v2f_sub(center, p);
      if (v2f_sqrlen(d) <= radius * radius)
      {
        if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
        {
          display[y * WIDTH + x] = FORE;
        }
      }
    }
  }
}

void show(void)
{
  static char row[WIDTH];
  //                t  b
  static char table[PIXEL_N][PIXEL_N] = {
      //
      {' ', '_'}, // 0
      {'^', 'C'}, // 1
  };

  for (int y = 0; y < HEIGHT / 2; ++y)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      Pixel t = display[(2 * y + 0) * WIDTH + x];
      Pixel b = display[(2 * y + 1) * WIDTH + x];
      assert(0 <= t);
      assert(t < PIXEL_N);
      assert(0 <= b);
      assert(b < PIXEL_N);
      row[x] = table[t][b];
    }
    fwrite(row, WIDTH, 1, stdout);
    fputc('\n', stdout);
  }
}
void back(void)
{
  printf("\x1b[%dD", WIDTH);
  printf("\x1b[%dA", HEIGHT / 2);
}
int main(void)
{
  V2f pos = v2ff(RADIUS);
  V2f vel = v2f(50.0f, 0.0f);
  V2f gravity = v2f(0.0f, GRAVITY);

  // int quit = 0;
  while (pos.x < WIDTH + RADIUS + RADIUS * 0.5f)
  {
    vel = v2f_sum(vel, v2f_mul(gravity, v2ff(DT)));
    pos = v2f_sum(pos, v2f_mul(vel, v2ff(DT)));
    if (pos.y > HEIGHT - RADIUS)
    {
      pos.y = HEIGHT - RADIUS;
      vel.y *= DAMPER;
    }
    fill(BACK);
    circle(pos, RADIUS);
    show();
    back();
    usleep(1000 * 1000 / FPS);
  }

  return 0;
}