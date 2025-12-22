#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define MIN_TRAVEL_DISTANCE 5

typedef struct {
  int direction;
  SDL_Rect rect;
  SDL_Color color;
} Node;

// Generates a random double between 0 and 1.
double gen_rand_double() { return (double)rand() / RAND_MAX; }

// Generates a random integer representing a direction for a node to take, based
// on a random double value.
// 1: North
// -1 : South
// 2: East
// -2: West
int gen_rand_direction() {
  double random_value = gen_rand_double();
  if (random_value < 0.25) {
    return 1;
  } else if (random_value < 0.5) {
    return -1;
  } else if (random_value < 0.75) {
    return 2;
  } else {
    return -2;
  }
}

int main(int argc, const char *argv[]) {
  srand(time(NULL)); // seed
  int num_node;

  if (argc == 1) {
    num_node = 5;
  } else if (argc == 2) {
    num_node = atoi(argv[1]);
  } else {
    printf("Usage: %s <num-of-nodes>\n", argv[0]);
    return 1;
  }

  Node node_list[num_node];

  // Create window
  SDL_Window *pwindow =
      SDL_CreateWindow("Random walk", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  // Create renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(pwindow, -1, 0);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Variables for Rect position
  SDL_Rect rect = (SDL_Rect){WIDTH / 2, HEIGHT / 2, 2, 2};

  // Some variables to initialize before main loop
  int app_running = 1;
  int direction = 0;
  int min_travel_distance = MIN_TRAVEL_DISTANCE;

  for (int i = 0; i < num_node; i++) {
    Node new_node = {gen_rand_direction(),
                     {WIDTH / 2, HEIGHT / 2, 2, 2},
                     {255, 255, 255, 255}};
    node_list[i] = new_node;
  }

  // Main loop
  while (app_running) {
    // event handling
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_running = 0;
      }
    }

    // Core loop
    if (min_travel_distance <= 0) {
      min_travel_distance = MIN_TRAVEL_DISTANCE;
    }

    if (rand() % 2 == 0 && min_travel_distance == MIN_TRAVEL_DISTANCE) {
      for (int i = 0; i < num_node; i++) {
        node_list[i].direction = gen_rand_direction();
      }
    }
    for (int i = 0; i < num_node; i++) {
      direction = node_list[i].direction;
      if (direction == 1) {
        node_list[i].rect.y--;
      } else if (direction == -2) {
        node_list[i].rect.x--;
      } else if (direction == -1) {
        node_list[i].rect.y++;
      } else if (direction == 2) {
        node_list[i].rect.x++;
      }
    }

    min_travel_distance--;

    // Draw all nodes
    for (int i = 0; i < num_node; i++) {
      Node *curr = &node_list[i];
      SDL_SetRenderDrawColor(renderer, curr->color.r, curr->color.b,
                             curr->color.g, curr->color.a);
      SDL_RenderFillRect(renderer, &(curr->rect));
    }

    // Update renderer, and frame related stuff
    SDL_RenderPresent(renderer);
    SDL_Delay(17);
  }
  return 0;
}
