#include "./game.h"

#include <SDL.h>

Player player;

void gameFrame(SDL_Event e, float deltaTime, Cube *cube) {
  // for (int i = 0; i < 24; i++) {
  //   (*cube)[i].x += 0.001;
  //   (*cube)[i].y += 0.001;
  // }
  float speed = 0.05;
  if (e.type != SDL_KEYDOWN) {
    return;
  }
  if (e.key.keysym.sym == SDLK_w) {
    for (int i = 0; i < 24; i++) {
      (*cube)[i].y -= speed;
    }
  }
  if (e.key.keysym.sym == SDLK_s) {
    for (int i = 0; i < 24; i++) {
      (*cube)[i].y += speed;
    }
  }
  if (e.key.keysym.sym == SDLK_a) {
    for (int i = 0; i < 24; i++) {
      (*cube)[i].x -= speed;
    }
  }
  if (e.key.keysym.sym == SDLK_d) {
    for (int i = 0; i < 24; i++) {
      (*cube)[i].x += speed;
    }
  }
}

Cube newCube(Point c, float s) {
  float half = s / 2.0;

  Cube cubeAddr;
  cubeAddr = malloc(CUBE_POINTS_N * sizeof(Point));

  /*
  ---> X+
  |
  V
  y+
  */

  // Up
  Point u1 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point u2 = {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point u3 = {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point u4 = {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z};

  // Down
  Point d1 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point d2 = {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point d3 = {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point d4 = {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z};

  // Left
  Point l1 = {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point l2 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point l3 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point l4 = {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z};

  // Right
  Point r1 = {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point r2 = {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point r3 = {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point r4 = {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z};

  // Front
  Point f1 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point f2 = {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point f3 = {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point f4 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};

  // Back
  Point b1 = {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point b2 = {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point b3 = {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point b4 = {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z};

  cubeAddr[0] = u1;
  cubeAddr[1] = u2;
  cubeAddr[2] = u3;
  cubeAddr[3] = u4;

  cubeAddr[4] = d1;
  cubeAddr[5] = d2;
  cubeAddr[6] = d3;
  cubeAddr[7] = d4;

  cubeAddr[8] = l1;
  cubeAddr[9] = l2;
  cubeAddr[10] = l3;
  cubeAddr[11] = l4;

  cubeAddr[12] = r1;
  cubeAddr[13] = r2;
  cubeAddr[14] = r3;
  cubeAddr[15] = r4;

  cubeAddr[16] = f1;
  cubeAddr[17] = f2;
  cubeAddr[18] = f3;
  cubeAddr[19] = f4;

  cubeAddr[20] = b1;
  cubeAddr[21] = b2;
  cubeAddr[22] = b3;
  cubeAddr[23] = b4;

  return cubeAddr;
}