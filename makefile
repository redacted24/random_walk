all:
	gcc -Wall -Wextra -o random_walk random_walk.c `sdl2-config --cflags --libs`
