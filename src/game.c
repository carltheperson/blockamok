#include "./game.h"

#include <SDL.h>

Player player;

void gameFrame(SDL_Event e, float deltaTime) {
  if (e.type != SDL_KEYDOWN) {
    return;
  }
  if (e.key.keysym.sym == SDLK_w) {
    player.z += 1 * deltaTime;
  }
  if (e.key.keysym.sym == SDLK_s) {
    player.z -= 1 * deltaTime;
  }
}

Cube* newCube(Point c, float s) {
  float half = s / 2.0;

  Cube* cubeAddr = malloc(CUBE_POINTS_N * sizeof(*cubeAddr));
  Cube c = {
      // Front
      {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z},
      {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z},
      {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z},
      {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z},
      // Back
      {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z},
      {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z},
      {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z},
      {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z},
      // Up
      {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z},
      {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z},
      {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z},
      {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z},
      // Down
      {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z},
      {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z},
      {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z},
      {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z},
      // Left
      {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z},
      {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z},
      {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z},
      {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z},
      // Right
      {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z},
      {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z},
      {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z},
      {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z},
  };

  cubeAddr = &c;

  return cubeAddr;
}