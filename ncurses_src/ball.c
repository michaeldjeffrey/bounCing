#include <ncurses.h>
#include "ball.h"
#include <stdlib.h>

#define rand_pos() rand_between(0, 125)
#define rand_speed() rand_between(1, 8)
#define rand_color() rand_between(3, 800)

int rand_between(int low, int high) {
    return rand() % (high - low + 1) + low;
}

/* int rand_pos() { return rand_between(0, 125); } */
/* int rand_speed() { return rand_between(1, 8); } */
/* int rand_color() { return rand_between(3, 800); } */

int is_oob(int coord, int max) {
    return coord >= max || coord < 0;
}

void bounce(int* speed) {
    *speed = (*speed > 0) ? -rand_speed() : rand_speed();
}

Ball Ball_new() {
    Ball one = {
      .x = rand_pos(),
      .y = rand_pos(),
      .xdir = rand_speed(),
      .ydir = rand_speed(),
      .color = rand_color()
    };
    return one;
}

void Ball_advance(Ball* self, int max_x, int max_y) {
    self->x += self->xdir;
    self->y += self->ydir;

    if (is_oob(self->x, max_x)) bounce(&self->xdir);
    if (is_oob(self->y, max_y)) bounce(&self->ydir);
}

void Ball_display(Ball* self) {
    mvprintw(self->y, self->x, "o");
}
