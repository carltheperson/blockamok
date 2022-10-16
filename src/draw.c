#include "./draw.h"

#include <SDL.h>

#include "./game.h"

extern Player player;

void draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 15, 255, 155, 255);
  SDL_RenderClear(renderer);
}

float screenX(float x) {
  return x * WIDTH + WIDTH / 2;
}

float screenY(float y) {
  return y * HEIGHT + HEIGHT / 2;
}

void drawCube(SDL_Renderer *renderer, Cube cube) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  for (int f = 0; f < CUBE_FACE_N; f = f + 4) {
    SDL_Point points[] = {
        {screenX(cube[f].x), screenY(cube[f].y)},
        {screenX(cube[f + 1].x), screenY(cube[f + 1].y)},
        {screenX(cube[f + 2].x), screenY(cube[f + 2].y)},
        {screenX(cube[f + 3].x), screenY(cube[f + 3].y)},
        {screenX(cube[f].x), screenY(cube[f].y)},
    };
    SDL_RenderDrawLines(renderer, points, 5);
  }
}