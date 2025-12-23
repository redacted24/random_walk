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

// Converts HSL to RGB. Better for picking "good" colors, because balance is
// conserved across hues (compared to the RGB color space). Based on the color
// The conversion formulae is given by Wikipedia:
// https://en.wikipedia.org/wiki/HSL_and_HSV#Color_conversion_formulae
SDL_Color hsl2rgb(int hue, double saturation, double lightness) {
  double chroma = (1 - fabs(2.0 * lightness - 1)) * saturation;
  double hue_prime = (double)hue / 60;
  double x = chroma * (1 - fabs(fmod(hue_prime, 2) - 1));
  double m = lightness - (chroma / 2);

  double r1 = 0, g1 = 0, b1 = 0;
  if (0 <= hue_prime && hue_prime < 1) {
    r1 = chroma;
    g1 = x;
    b1 = 0;
  } else if (1 <= hue_prime && hue_prime < 2) {
    r1 = x;
    g1 = chroma;
    b1 = 0;
  } else if (2 <= hue_prime && hue_prime < 3) {
    r1 = 0;
    g1 = chroma;
    b1 = x;
  } else if (3 <= hue_prime && hue_prime < 4) {
    r1 = 0;
    g1 = x;
    b1 = chroma;
  } else if (4 <= hue_prime && hue_prime < 5) {
    r1 = x;
    g1 = 0;
    b1 = chroma;
  } else if (5 <= hue_prime && hue_prime < 6) {
    r1 = chroma;
    g1 = 0;
    b1 = x;
  }

  int r = (r1 + m) * 255;
  int g = (g1 + m) * 255;
  int b = (b1 + m) * 255;

  SDL_Color color = {r, g, b, 255};
  return color;
}

// Generates a random integer representing a direction for a node to take, based
// on a random double value.
// 0: North
// 1: South
// 2: East
// 3: West
int gen_rand_direction() {
  double random_value = (double)rand() / RAND_MAX;
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
  srand(time(NULL)); // seed
  int num_node;

  if (argc == 1) {
    num_node = 15;
  } else if (argc == 2) {
    num_node = atoi(argv[1]);
    if (num_node == 0) {
      printf("0 nodes. Exiting\n");
      return 0;
    }
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

  // Some variables to initialize before main loop
  int app_running = 1;
  int direction = 0;
  int min_travel_distance = MIN_TRAVEL_DISTANCE;

  // Create new nodes, change colors based on number of active node
  int hue = 0;
  int colors = 360 / num_node;
  for (int i = 0; i < num_node; i++) {
    SDL_Color rand_color = hsl2rgb(hue, 0.5, 0.5);
    hue += colors;

    Node new_node = {
        gen_rand_direction(), {WIDTH / 2, HEIGHT / 2, 2, 2}, rand_color};
    node_list[i] = new_node;
  }

  // Core loop
  while (app_running) {
    // event handling
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_running = 0;
      }
    }

    // Logic
    if (min_travel_distance <= 0) {
      min_travel_distance = MIN_TRAVEL_DISTANCE;
    }

    // Determine direction change
    if (rand() % 2 == 0 && min_travel_distance == MIN_TRAVEL_DISTANCE) {
      for (int i = 0; i < num_node; i++) {
        node_list[i].direction = gen_rand_direction();
      }
    }

    for (int i = 0; i < num_node; i++) {
      direction = node_list[i].direction;
      if (direction == 0) {
        node_list[i].rect.y--;
      } else if (direction == 1) {
        node_list[i].rect.x--;
      } else if (direction == 2) {
        node_list[i].rect.y++;
      } else if (direction == 3) {
        node_list[i].rect.x++;
      }
    }

    min_travel_distance--;

    // Draw next position for all nodes
    for (int i = 0; i < num_node; i++) {
      Node *curr = &node_list[i];
      SDL_SetRenderDrawColor(renderer, curr->color.r, curr->color.b,
                             curr->color.g, curr->color.a);
      SDL_RenderFillRect(renderer, &(curr->rect));
    }

    // Update renderer, and frame related stuff
    SDL_RenderPresent(renderer);
    SDL_Delay(8);
  }
  return 0;
}
