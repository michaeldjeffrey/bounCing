CC = clang

HEADERS = $(wildcard ncurses_src/*.h)
SOURCES = $(wildcard ncurses_src/*.c)
OBJECTS = $(SOURCES:.c=.o)

SDL_HEADERS = $(wildcard sdl_src/*.h)
SDL_SOURCES = $(wildcard sdl_src/*.c)
SDL_OBJECTS = $(SDL_SOURCES:.c=.o)

CFLAGS = -std=gnu99 -march=native -O2
CFLAGS += -Wall -Wextra -pedantic -Wshadow -Wstrict-overflow -fno-strict-aliasing
FLAGS += -Wno-unused-parameter -Wno-gnu-zero-variadic-macro-arguments

LDFLAGS = -lncurses -lSDL2

all: sdl_run

ncurses_main: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o ncurses_main

sdl_main: $(SDL_OBJECTS)
	$(CC) $(SDL_OBJECTS) $(LDFLAGS) -o sdl_main

$(OBJECTS): $(HEADERS)
$(SDL_OBJECTS): $(SDL_HEADERS)

ncurses_clean:
	rm -rf *.dSYM
	rm -f $(OBJECTS)
	rm -f ncurses_main

sdl_clean:
	rm -rf *.dSYM
	rm -f $(SDL_OBJECTS)
	rm -f sdl_main

clean: ncurses_clean sdl_clean

ncurses_run: ncurses_main
	./ncurses_main

sdl_run: sdl_main
	./sdl_main

.PHONEY: all ncurses_clean sdl_clean
