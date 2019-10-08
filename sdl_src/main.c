#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480
#define NUM_BALLS 1000
#define RADIUS 5

int BOUNCE_VERTICAL = 1;
int BOUNCE_HORIZONTAL = 2;
int BOUNCE_ALL = 3;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Window;

typedef struct {
    int x;
    int y;
    int xdir;
    int ydir;
} Ball;

void Window_destroy(Window *self) {
    if (self->window != NULL) {
        SDL_DestroyWindow(self->window);
        self->window = NULL;
    }
    SDL_Quit();
    free(self);
}

Window* Window_new() {
    Window *self = calloc(1, sizeof(Window));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("ERROR: Could not initialize SDL! SDL_ERROR: %s\n", SDL_GetError());
        goto error;
    }

    self->window = SDL_CreateWindow(
        "Bouncing Balls",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (self->window == NULL) {
        printf("ERROR: Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
        goto error;
    }

    self->renderer = SDL_CreateRenderer(self->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(self->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return self;

error:
    Window_destroy(self);
    return NULL;
}

#define rand_pos() rand_between(0, 125)
#define rand_speed() rand_between(1, 8)

int rand_between(int low, int high)
{
    return rand() % (high - low + 1) + low;
}

Ball Ball_new() {
    Ball ball = {
      .x = rand_pos(),
      .y = rand_pos(),
      .xdir = rand_speed(),
      .ydir = rand_speed()
    };
    return ball;
}

void bounce(int *speed) {
    *speed = (*speed > 0) ? -rand_speed() : rand_speed();
}

void Ball_advance(Ball *self) {
    self->x += self->xdir;
    self->y += self->ydir;

    if (self->x >= WIDTH || self->x < 0) bounce(&self->xdir);
    if (self->y >= HEIGHT || self->y < 0) bounce(&self->ydir);
}


void RenderDrawCircle(SDL_Renderer *renderer, Ball *ball) {
    for (float angle = 0.0; angle < 360; angle += 2) {
        int x = ball->x - RADIUS * cos(angle);
        int y = ball->y - RADIUS * sin(angle);
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void bounce_collection(Ball balls[], int dir) {
    for (size_t i = 0; i < NUM_BALLS; ++i) {
        Ball *ball = &balls[i];
        if (dir & BOUNCE_VERTICAL) bounce(&ball->ydir);
        if (dir & BOUNCE_HORIZONTAL) bounce(&ball->xdir);
    }
}

int main() {
    Window *window = Window_new();

    bool quit = false;
    SDL_Event event;

    Ball balls[NUM_BALLS];
    for (size_t i = 0; i < NUM_BALLS; ++i) {
        balls[i] = Ball_new();
    }

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                quit = true;
            else if (event.type == SDL_KEYDOWN)
                switch(event.key.keysym.sym) {
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_x:
                        bounce_collection(balls, BOUNCE_HORIZONTAL);
                        break;
                    case SDLK_y:
                        bounce_collection(balls, BOUNCE_VERTICAL);
                        break;
                    case SDLK_b:
                        bounce_collection(balls, BOUNCE_ALL);
                        break;
                    default:
                        break;
                }
        }

        SDL_SetRenderDrawColor(window->renderer, 0xAA, 0xAA, 0xAA, 0xAA);
        SDL_RenderClear(window->renderer);

        SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0x00);

        for (size_t i = 0; i < NUM_BALLS; i++) {
            Ball *ball = &balls[i];
            Ball_advance(ball);
            RenderDrawCircle(window->renderer, ball);
        }
        SDL_RenderPresent(window->renderer);
        SDL_Delay(5);
    }

    return 0;
}
