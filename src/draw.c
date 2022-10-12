#include <SDL.h>

#include "./game.h"

extern Player player;

void draw(SDL_Renderer *renderer) {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 15, 255, 155, 255);
  SDL_RenderPresent(renderer);
}