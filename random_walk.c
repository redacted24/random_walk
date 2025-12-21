#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600

int main(int argc, const char *argv[]) {
  int num_agents;

  if (argc == 1) {
    num_agents = 0;
  } else if (argc == 2) {
    num_agents = atoi(argv[1]);
  } else {
    printf("Usage: %s <num-of-agents>\n", argv[0]);
    return 1;
  }

  // Create window
  SDL_Window *win = SDL_CreateWindow("Random walk", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, 0);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  int app_running = 1;
  while (app_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_running = 0;
      }
    }
  }
}
