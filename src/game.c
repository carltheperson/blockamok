#include "./game.h"

#include <SDL.h>

const unsigned long cubeMemSize = CUBE_POINTS_N * sizeof(Point);

void addNewCube(Cube cubes[], int *cubesLength) {
  Point p = {
      .x = -0.5,
      .y = -0.5,
      .z = 20,
  };

  Cube cube = newCube(p, 0.5);
  cubes[(*cubesLength)++] = cube;
}

void removeCube(Cube cubes[], int *cubesLength, int i) {
  --(*cubesLength);
  free(cubes[i]);
}

void gameFrame(SDL_Event e, float deltaTime, Cube cubes[], int *cubesLength) {
  float speed = 20 * deltaTime;
  if ((*cubesLength) == 0) {
    addNewCube(cubes, cubesLength);
  }

  for (int i = 0; i < (*cubesLength); i++) {
    for (int p = 0; p < 20; p++) {
      cubes[i][p].z -= speed;
    }

    if (cubes[i][0].z < 1) {
      removeCube(cubes, cubesLength, i);
    }
  }

  // if (e.type != SDL_KEYDOWN) {
  //   return;
  // }
  // if (e.key.keysym.sym == SDLK_w) {
  //   for (int i = 0; i < 24; i++) {
  //     (*cube)[i].y -= speed;
  //   }
  // }
  // if (e.key.keysym.sym == SDLK_s) {
  //   for (int i = 0; i < 24; i++) {
  //     (*cube)[i].y += speed;
  //   }
  // }
  // if (e.key.keysym.sym == SDLK_a) {
  //   for (int i = 0; i < 24; i++) {
  //     (*cube)[i].x -= speed;
  //   }
  // }
  // if (e.key.keysym.sym == SDLK_d) {
  //   for (int i = 0; i < 24; i++) {
  //     (*cube)[i].x += speed;
  //   }
  // }
  // if (e.key.keysym.sym == SDLK_q) {
  //   for (int i = 0; i < 24; i++) {
  //     (*cube)[i].z -= speed;
  //   }
  // }
  // if (e.key.keysym.sym == SDLK_e) {
  //   for (int i = 0; i < 24; i++) {
  //     (*cube)[i].z += speed;
  //   }
  // }
}

Cube newCube(Point c, float s) {
  float half = s / 2.0;

  Cube cubeAddr;
  cubeAddr = malloc(cubeMemSize);

  // Up
  Point u1 = {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point u2 = {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point u3 = {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point u4 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};

  // Down
  Point d1 = {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point d2 = {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point d3 = {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point d4 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};

  // Left
  Point l1 = {.x = -half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point l2 = {.x = -half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point l3 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point l4 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};

  // Right
  Point r1 = {.x = +half + c.x, .y = +half + c.y, .z = +half + c.z};
  Point r2 = {.x = +half + c.x, .y = -half + c.y, .z = +half + c.z};
  Point r3 = {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point r4 = {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z};

  // Front
  Point f1 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point f2 = {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point f3 = {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point f4 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};

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

  return cubeAddr;
}