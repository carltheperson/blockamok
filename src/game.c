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

Cube newCube(Point c, float s) {
  float half = s / 2.0;

  Cube cubeAddr;
  cubeAddr = malloc(CUBE_POINTS_N * sizeof(Point));

  // Front
  Point f1 = {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point f2 = {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point f3 = {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point f4 = {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z};

  // Back
  Point b1 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point b2 = {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point b3 = {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point b4 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};

  // Up
  Point u1 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point u2 = {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point u3 = {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point u4 = {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z};

  // Down
  Point d1 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point d2 = {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point d3 = {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point d4 = {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z};

  // Left
  Point l1 = {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point l2 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point l3 = {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point l4 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};

  // Right
  Point r1 = {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point r2 = {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point r3 = {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point r4 = {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z};

  cubeAddr[0] = f1;
  cubeAddr[1] = f1;
  cubeAddr[2] = f1;
  cubeAddr[3] = f1;

  cubeAddr[4] = b1;
  cubeAddr[5] = b2;
  cubeAddr[6] = b3;
  cubeAddr[7] = b4;

  cubeAddr[8] = u1;
  cubeAddr[9] = u2;
  cubeAddr[10] = u3;
  cubeAddr[11] = u4;

  cubeAddr[12] = d1;
  cubeAddr[13] = d2;
  cubeAddr[14] = d3;
  cubeAddr[15] = d4;

  cubeAddr[16] = l1;
  cubeAddr[17] = l2;
  cubeAddr[18] = l3;
  cubeAddr[19] = l4;

  cubeAddr[20] = r1;
  cubeAddr[21] = r2;
  cubeAddr[22] = r3;
  cubeAddr[23] = r4;

  return cubeAddr;
}