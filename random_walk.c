#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600

int main(int argc, const char *argv[]) {
  int num_agents;
  SDL_CreateWindow("Random walk", WIDTH, HEIGHT, SDL_WINDOWPOS_CENTERED);
  SDL_Delay(3000);
}
