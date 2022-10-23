#include "./game.h"

#include <SDL.h>
#include <math.h>

float playerSpeed = 100;

const unsigned long cubeMemSize = CUBE_POINTS_N * sizeof(Point);

const float MAX_DEPTH = 150;
const float BOUNDS_X = 12;
const float BOUNDS_Y = 12;

float rr(float min, float max) {
  return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

void addNewCube(Cube cubes[], int *cubesLength) {
  Point p = {
      .x = rr(-BOUNDS_X, BOUNDS_X),
      .y = rr(-BOUNDS_Y, BOUNDS_Y),
      .z = MAX_DEPTH,
  };
  Cube cube = newCube(p, 0.5);
  cubes[(*cubesLength)++] = cube;
}

void addInitialCube(Cube cubes[], int *cubesLength) {
  Point p = {
      .x = rr(-BOUNDS_X, BOUNDS_X),
      .y = rr(-BOUNDS_Y, BOUNDS_Y),
      .z = rr(0, MAX_DEPTH),
  };
  Cube cube = newCube(p, 0.5);
  cubes[(*cubesLength)++] = cube;
}

void removeCube(Cube cubes[], int i) {
  free(cubes[i]);
  cubes[i] = NULL;
}

void rearrangeCubesToTakeOutRemoved(Cube cubes[], int *cubesLength, int removedN) {
  if (removedN == 0) {
    return;
  }

  int fullI = 0;
  for (int i = 0; i < (*cubesLength); i++) {
    if (cubes[i] != NULL) {
      cubes[fullI++] = cubes[i];
    }
  }
}

void flipCubeIfOutOfBounds(Cube cubes[], int i) {
  if (cubes[i][0].x < -BOUNDS_X) {
    for (int p = 0; p < 20; p++) {
      cubes[i][p].x += BOUNDS_X * 2;
    }
  } else if (cubes[i][0].x > BOUNDS_X) {
    for (int p = 0; p < 20; p++) {
      cubes[i][p].x -= BOUNDS_X * 2;
    }
  }
  if (cubes[i][0].y < -BOUNDS_Y) {
    for (int p = 0; p < 20; p++) {
      cubes[i][p].y += BOUNDS_X * 2;
    }
  } else if (cubes[i][0].y > BOUNDS_Y) {
    for (int p = 0; p < 20; p++) {
      cubes[i][p].y -= BOUNDS_Y * 2;
    }
  }
}

int compareSize(const void *a, const void *b) {
  Cube cube1 = *((Cube *)a);
  Cube cube2 = *((Cube *)b);

  if (cube1[0].z == cube2[0].z) {
    return (cube1[0].x < cube2[0].x) - (cube1[0].x > cube2[0].x);
  }

  return (cube1[0].z < cube2[0].z) - (cube1[0].z > cube2[0].z);
}

int gameFrame(SDL_Event e, float deltaTime, Cube cubes[], int *cubesLength) {
  float speed = playerSpeed * deltaTime;
  float moveSpeed = (30 + playerSpeed / 50) * deltaTime;
  if (*cubesLength == 0) {
    while ((*cubesLength) < 600) {
      addInitialCube(cubes, cubesLength);
    }
  } else {
    while ((*cubesLength) < 600) {
      addNewCube(cubes, cubesLength);
    }
  }

  playerSpeed += deltaTime * 300;

  int cubesRemoved = 0;

  const Uint8 *keyState = SDL_GetKeyboardState(NULL);

  float xDiff = 0;
  float yDiff = 0;
  if (keyState[SDL_SCANCODE_W]) {
    yDiff = +moveSpeed;
  }
  if (keyState[SDL_SCANCODE_S]) {
    yDiff = -moveSpeed;
  }
  if (keyState[SDL_SCANCODE_A]) {
    xDiff = +moveSpeed;
  }
  if (keyState[SDL_SCANCODE_D]) {
    xDiff = -moveSpeed;
  }
  float zSpeed = -speed;
  if (keyState[SDL_SCANCODE_LSHIFT]) {
    zSpeed *= 3;
  }

  for (int i = 0; i < (*cubesLength); i++) {
    if ((cubes[i][0].z + zSpeed) < 1.5) {
      removeCube(cubes, i);
      cubesRemoved += 1;
    } else {
      flipCubeIfOutOfBounds(cubes, i);
      for (int p = 0; p < 20; p++) {
        cubes[i][p].x += xDiff;
        cubes[i][p].y += yDiff;

        cubes[i][p].z += zSpeed;
      }

      float middleX = fabs(cubes[i][0].x + (cubes[i][2].x - cubes[i][0].x) / 2);
      float middleY = fabs(cubes[i][0].y + (cubes[i][2].y - cubes[i][0].y) / 2);
      if (cubes[i][0].z < 2 && middleX < 0.5 && middleY < 0.5) {
        return 1;
      }
    }
  }

  rearrangeCubesToTakeOutRemoved(cubes, cubesLength, cubesRemoved);

  *cubesLength -= cubesRemoved;

  qsort(cubes, *cubesLength, sizeof(Cube *), compareSize);

  return 0;
}

Cube newCube(Point c, float s) {
  float half = s / 2.0;

  Cube cubeAddr;
  cubeAddr = malloc(cubeMemSize);

  // Up
  Point u1 = {.x = -half + c.x, .y = -half + c.y, .z = +half * 2 + c.z};
  Point u2 = {.x = +half + c.x, .y = -half + c.y, .z = +half * 2 + c.z};
  Point u3 = {.x = +half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point u4 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};

  // Down
  Point d1 = {.x = -half + c.x, .y = +half + c.y, .z = +half * 2 + c.z};
  Point d2 = {.x = +half + c.x, .y = +half + c.y, .z = +half * 2 + c.z};
  Point d3 = {.x = +half + c.x, .y = +half + c.y, .z = -half + c.z};
  Point d4 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};

  // Left
  Point l1 = {.x = -half + c.x, .y = +half + c.y, .z = +half * 2 + c.z};
  Point l2 = {.x = -half + c.x, .y = -half + c.y, .z = +half * 2 + c.z};
  Point l3 = {.x = -half + c.x, .y = -half + c.y, .z = -half + c.z};
  Point l4 = {.x = -half + c.x, .y = +half + c.y, .z = -half + c.z};

  // Right
  Point r1 = {.x = +half + c.x, .y = +half + c.y, .z = +half * 2 + c.z};
  Point r2 = {.x = +half + c.x, .y = -half + c.y, .z = +half * 2 + c.z};
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