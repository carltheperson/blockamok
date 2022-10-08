#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Renderer *renderer;
const int HEIGHT = 700;
const int WIDTH = 800;
const int padH = 95;
const int padW = 25;
SDL_Event e;
SDL_Rect player;
SDL_Rect player2;
SDL_Rect Ball;
bool done = false;

void init() {
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("Blockamok", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  screen = SDL_GetWindowSurface(window);
  player.h = padH;
  player.w = padW;
  player2.h = padH;
  player2.w = padW;

  player.x = 20;
  player.y = HEIGHT / 2;
  player2.x = WIDTH - 40;
  player2.y = HEIGHT / 2;
  Ball.h = 20;
  Ball.w = 20;
  Ball.x = WIDTH / 2;
  Ball.y = HEIGHT / 2;
}

void draw() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &Ball);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &player);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &player2);

  SDL_RenderPresent(renderer);
}

void gamelogic() {
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_w:
          player.y = player.y + 1;
      }
    } else if (e.type == SDL_QUIT) {
      done = true;
    }
  }
}

int main(int arg, char *argv[]) {
  init();

  while (!done) {
    gamelogic();
    draw();
  }

  return 0;
}