all:
	gcc -Wall -Wextra -o random_walk.out random_walk.c -lm `sdl2-config --cflags --libs`
debug:
	gcc -Wall -Wextra -fsanitize=address -g -o debug.out random_walk.c -lm `sdl2-config --cflags --libs`
