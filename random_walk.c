#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define MIN_TRAVEL_TIME 10

// Generates a random double between 0 and 1.
double gen_rand_double() { return (double)rand() / RAND_MAX; }

// Generates a random integer representing a direction for a node to take, based
// on a random double value. 0: North 1: West 2: South 3: East
int gen_rand_direction() {
  double random_value = gen_rand_double();
  if (random_value < 0.25) {
    return 0;
  } else if (random_value < 0.5) {
    return 1;
  } else if (random_value < 0.75) {
    return 2;
  } else {
    return 3;
  }
}

int main(int argc, const char *argv[]) {
  srand(time(NULL));
  int num_node;

  if (argc == 1) {
    num_node = 0;
  } else if (argc == 2) {
    num_node = atoi(argv[1]);
  } else {
    printf("Usage: %s <num-of-nodes>\n", argv[0]);
    return 1;
  }

  // Create window
  SDL_Window *pwindow =
      SDL_CreateWindow("Random walk", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  // Create renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(pwindow, -1, 0);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Variables for Rect position
  SDL_Rect rect = (SDL_Rect){100, 100, 2, 2};

  // Some variables to initialize before main loop
  int app_running = 1;
  int direction = 0;
  int min_travel_time = MIN_TRAVEL_TIME;

  // Main loop
  while (app_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_running = 0;
      }
    }

    if (min_travel_time <= 0) {
      min_travel_time = MIN_TRAVEL_TIME;
    }

    if (rand() % 2 == 0 && min_travel_time == MIN_TRAVEL_TIME) {
      direction = gen_rand_direction();
    }

    if (direction == 0) {
      rect.y--;
    } else if (direction == 1) {
      rect.x--;
    } else if (direction == 2) {
      rect.y++;
    } else if (direction == 3) {
      rect.x++;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Update renderer, and frame related stuff
    min_travel_time--;
    SDL_RenderPresent(renderer);
    SDL_Delay(20);
  }
  return 0;
}
