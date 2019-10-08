#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "ball.h"

#define DELAY 70000
#define NUM_BALLS 250


void init_colors() {
  if (has_colors()) {
    start_color();

    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_CYAN,    COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);
  }
}

int main() {
  int max_x = 0;
  int max_y = 0;

  initscr();
  noecho();
  curs_set(FALSE);

  init_colors();
  getmaxyx(stdscr, max_y, max_x);

  Ball balls[NUM_BALLS];
  for(size_t i = 0; i < NUM_BALLS; ++i) {
    balls[i] = Ball_new();
  }

  while(1) {
    clear();
    for (int i = 0; i < NUM_BALLS; ++i) {
      Ball *ball = &balls[i];
      attrset(COLOR_PAIR(ball->color % 8));
      Ball_advance(ball, max_x, max_y);
      Ball_display(ball);
    }
    refresh();
    usleep(DELAY);
  }
  endwin();
  return 0;
}
