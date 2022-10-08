#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./draw.h"
#include "./game.h"
#include "./math.h"

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Renderer *renderer;
const int HEIGHT = 700;
const int WIDTH = 800;
SDL_Event e;
bool done = false;

Uint64 now = 0;
Uint64 last = 0;
double deltaTime = 0;

void init() {
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("Blockamok", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  screen = SDL_GetWindowSurface(window);
}

void gameLoop() {
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_KEYDOWN) {
      gameFrame(e, deltaTime);
    } else if (e.type == SDL_QUIT) {
      done = true;
    }
  }
}

int main(int arg, char *argv[]) {
  init();

  while (!done) {
    last = now;
    now = SDL_GetPerformanceCounter();

    gameLoop();
    draw(renderer);

    deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
  }

  return 0;
}