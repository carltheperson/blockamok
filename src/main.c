#include <SDL.h>
#include <SDL_ttf.h>
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
SDL_Event e;
bool quit = false;
bool gameOver = false;

Uint64 now = 0;
Uint64 last = 0;
double deltaTime = 0;

int cubesLength = 0;
Cube cubes[1000];

void init() {
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("Blockamok", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  screen = SDL_GetWindowSurface(window);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  srand(time(NULL));
  TTF_Init();
}

void gameLoop() {
  SDL_PollEvent(&e);
  if (!gameOver) {
    gameOver = gameFrame(e, deltaTime, cubes, &cubesLength);
  }
  if (e.type == SDL_QUIT) {
    quit = true;
  }
}

int main(int arg, char *argv[]) {
  init();

  // SDL_Color White = {255, 255, 255};

  while (!quit) {
    last = now;
    now = SDL_GetTicks();

    gameLoop();

    draw(renderer);

    drawCubes(renderer, cubes, cubesLength);

    drawSpeedText(renderer);
    if (gameOver) {
      drawGameOverText(renderer);
    }

    SDL_RenderPresent(renderer);

    deltaTime = (double)((now - last) * 1000) / ((double)SDL_GetPerformanceFrequency());
  }

  return 0;
}