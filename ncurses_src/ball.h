#ifndef __BALL_NCURSES_H_
#define __BALL_NCURSES_H_

typedef struct {
  int x;
  int y;
  int xdir;
  int ydir;
  int color;
} Ball;

Ball Ball_new(void);
void Ball_advance(Ball* self, int max_x, int max_y);
void Ball_display(Ball* self);

#endif // __BALL_NCURSES_H_
