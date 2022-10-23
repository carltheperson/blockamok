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
bool done = false;

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
  gameFrame(e, deltaTime, cubes, &cubesLength);
  if (e.type == SDL_KEYDOWN) {
  } else if (e.type == SDL_QUIT) {
    done = true;
  }
}

int main(int arg, char *argv[]) {
  init();

  TTF_Font *Sans = TTF_OpenFont("Mono.ttf", 24);
  SDL_Color White = {255, 255, 255};
  printf("\n %f \n", playerSpeed);
  char score[10];

  while (!done) {
    last = now;
    now = SDL_GetTicks();

    gameLoop();
    draw(renderer);

    drawCubes(renderer, cubes, cubesLength);

    deltaTime = (double)((now - last) * 1000) / ((double)SDL_GetPerformanceFrequency());

    sprintf(score, "%d", (int)playerSpeed);
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, score, White);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = -10;
    Message_rect.w = 24 * 3;
    Message_rect.h = 50;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}