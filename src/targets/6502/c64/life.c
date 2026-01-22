/**
 * @file life.c
 * @brief Simple Conway's Game of Life implementation for small targets.
 *
 * This file provides a straightforward implementation intended for
 * constrained builds (example: C64-style memory model). The code keeps
 * screen contents in a memory-mapped buffer at `SCREEN_BASE` and uses
 * `_field_count` as a temporary neighbor-count grid.
 */

#include <stdio.h>
#include <stdlib.h>

/** @brief Byte type used for screen and field storage. */
#define BYTE unsigned char

/** @brief Character value representing a live cell on the screen. */
#define ALIVE 88
/** @brief Character value representing a dead cell on the screen. */
#define DEAD 32
/** @brief Character value used to clear the screen (space). */
#define SPACE 32

/** @brief Base address of the screen buffer (memory-mapped). */
#define SCREEN_BASE 0x400
/** @brief Screen width in characters. */
#define WIDTH 40
/** @brief Screen height in characters. */
#define HEIGHT 25

/**
 * @brief Pointer to the screen buffer.
 *
 * Treated as a 2D array [HEIGHT][WIDTH] mapped at `SCREEN_BASE`.
 */
BYTE (*screen)[WIDTH] = (BYTE(*)[WIDTH])SCREEN_BASE;

/** @brief Temporary grid holding neighbour counts for each cell. */
BYTE _field_count[HEIGHT][WIDTH];

/** @brief Threshold used for random initialization. */
int _limit;
/** @brief Number of iterations to run during `calculate()` (default: 42). */
unsigned int _iterations;

/**
 * @brief Apply Game of Life rules to the screen using `_field_count`.
 *
 * Iterates over the inner screen area (ignores border) and updates the
 * `screen` buffer in-place according to the neighbor counts already
 * populated in `_field_count`.
 */
void calculate_field(void) {
  for (BYTE y = 1; y < HEIGHT - 1; y++) {
    for (BYTE x = 1; x < WIDTH - 1; x++) {
      BYTE count = _field_count[y][x];
      BYTE current = screen[y][x];

      if (current == ALIVE) {
        if (count < 2 || count > 3) {
          screen[y][x] = DEAD;
        }
      } else if (count == 3) {
        screen[y][x] = ALIVE;
      }
    }
  }
}

/**
 * @brief Zero the `_field_count` grid.
 */
void clear_count(void) {
  for (BYTE y = 0; y < HEIGHT; y++) {
    for (BYTE x = 0; x < WIDTH; x++) {
      _field_count[y][x] = 0;
    }
  }
}

/**
 * @brief Count live neighbours for a given cell.
 * @param y Row index of the cell.
 * @param x Column index of the cell.
 * @return Number of live neighbours (0..8).
 *
 * The function inspects the eight surrounding cells and returns how many
 * of them are equal to `ALIVE`.
 */
int count_neighbours(BYTE y, BYTE x) {
  int count = 0;

  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      if (dy == 0 && dx == 0) {
        continue;
      } else if (screen[y + dy][x + dx] == ALIVE) {
        count++;
      }
    }
  }
  return count;
}

/**
 * @brief Populate `_field_count` with neighbour counts for the inner area.
 */
void count_field(void) {
  for (BYTE y = 1; y < HEIGHT - 1; y++) {
    for (BYTE x = 1; x < WIDTH - 1; x++) {
      _field_count[y][x] = count_neighbours(y, x);
    }
  }
}

/**
 * @brief Fill the entire screen buffer with a character `c`.
 * @param c Character to write to every screen position.
 */
void fill_screen(BYTE c) {
  BYTE *ptr = (BYTE *)SCREEN_BASE;

  for (int offset = 0; offset < HEIGHT * WIDTH; offset++) {
    ptr[offset] = c;
  }
}

/**
 * @brief Prompt the user for `_limit` and `_iterations` values.
 *
 * Reads two integer values from standard input and stores them in the
 * global `_limit` and `_iterations` variables.
 */
void get_values(void) {
  printf("_limit: ");
  scanf("%d", &_limit);
  printf("_iterations: ");
  scanf("%u", &_iterations);
}

/**
 * @brief Initialize the inner screen area with random live/dead cells.
 *
 * Uses `_limit` as a threshold for deciding whether a cell is `ALIVE` or
 * `DEAD` when calling `rand()`.
 */
void init_screen(void) {
  for (BYTE y = 1; y < HEIGHT - 1; y++) {
    for (BYTE x = 1; x < WIDTH - 1; x++) {
      char c;
      if (rand() < _limit)
        c = DEAD;
      else
        c = ALIVE;

      screen[y][x] = c;
    }
  }
}

/**
 * @brief Run the Game of Life for `_iterations` steps.
 *
 * For each iteration, `count_field()` fills `_field_count` and
 * `calculate_field()` applies the rules to the `screen` buffer.
 */
void calculate(void) {
  for (unsigned int i = 0; i < _iterations; i++) {
    count_field();
    calculate_field();
  }
}

/**
 * @brief Demonstration helper that fills the screen with a sequence of
 * characters.
 *
 * Not used by the main calculation loop; useful for visual testing.
 */
void play_with_field(void) {
  for (BYTE c = 0; c < 255; c++)
    fill_screen(c);
}

/**
 * @brief Print usage/help text to standard output.
 */
void print_usage(void) {
  printf("Conways Game Of Life\r\n\r\n");
  printf("Enter the following values\r\n\r\n");
  printf("  _limit [0..32767] for random generation\r\n");
  printf("    0: filled completely\r\n");
  printf("    23000: pretty good value\r\n");
  printf("    32767: very little cells\r\n");
  printf("\r\n");
  printf("  _iterations [0..65535]\r\n");
  printf("    number of _iterations calculated\r\n");
  printf("\r\n");
  printf("\r\n");
}

/**
 * @brief Program entry point.
 * @return Exit code (0 on success).
 */
int main(void) {
  fill_screen(SPACE);
  print_usage();

  get_values();

  fill_screen(SPACE);
  init_screen();

  calculate();

  printf("  Press RUN/STOP + RESTORE to continue ");

  return 0;
}
