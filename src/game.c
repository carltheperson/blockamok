#include "./game.h"

#include <SDL.h>
#include <math.h>

const unsigned long cubeMemSize = CUBE_POINTS_N * sizeof(Point);

const float MAX_DEPTH = 100;

float FAR_BOUNDS_X = 15;
float NEAR_BOUNDS_X = 6;

const float FAR_BOUNDS_Y = 15;
const float NEAR_BOUNDS_Y = 6;

const float X_CUBE_MAX = 6;
const float Y_CUBE_MAX = 6;

float xBounds(float z) {
  float xRatio = NEAR_BOUNDS_X / FAR_BOUNDS_X;
  return z * xRatio;
}

float yBounds(float z) {
  float yRatio = NEAR_BOUNDS_Y / FAR_BOUNDS_Y;
  return z * yRatio;
}

float rr(float min, float max) {
  return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

void addNewCube(Cube cubes[], int *cubesLength) {
  float z = MAX_DEPTH;

  Point p = {
      .x = rr(-xBounds(z), xBounds(z)),
      .y = rr(-yBounds(z), yBounds(z)),
      .z = z,
  };

  Cube cube = newCube(p, 0.5);
  cubes[(*cubesLength)++] = cube;
}

void addInitialCube(Cube cubes[], int *cubesLength) {
  float x, y, z;
  do {
    x = rr(-FAR_BOUNDS_X, FAR_BOUNDS_X);
    y = rr(-FAR_BOUNDS_Y, FAR_BOUNDS_Y);
    z = rr(0, MAX_DEPTH);
  } while (fabs(x) > xBounds(z) || fabs(y) > yBounds(z));
  Point p = {
      .x = x,
      .y = y,
      .z = z,
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

// void loopBackOutOfBoundsCubes(Cube cubes[], int *cubesLength, int *cubesRemoved) {
//   for (int i = 0; i < *cubesLength; i++) {
//     float cXBounds = xBounds(cubes[i][0].z);
//     if (cubes[i][0].x > cXBounds) {
//       // for (int p = 0; p < 20; p++) {
//       //   cubes[i][p].x -= cXBounds * 2;
//       // }
//       removeCube(cubes, i);
//       *cubesRemoved += 1;
//     } else if (cubes[i][0].x < -cXBounds) {
//       removeCube(cubes, i);
//       *cubesRemoved += 1;
//       // for (int p = 0; p < 20; p++) {
//       //   cubes[i][p].x += cXBounds * 2;
//       // }
//     }
//   }
// }

int removeOrFlipCubeIfOutOfBounds(Cube cubes[], int i, float xDiff, float yDiff, float zDiff) {
  float cXBounds = xBounds(cubes[i][0].z + zDiff);
  float cYBounds = yBounds(cubes[i][0].z + zDiff);

  // If out-of-bounds rn, just remove, this wasn't caused by movement
  // if (xDiff > 0)
  //  aka cubes moved to the right (pressing a)
  //  aka some cubes on the right might become out of bounds *because* we moved
  //      if That happens we should flip them

  if (xDiff == 0) {
    if (cubes[i][0].x > cXBounds || cubes[i][2].x < -cXBounds) {
      removeCube(cubes, i);
      return 1;
    }
  } else {
    if ((cubes[i][0].x + xDiff) > cXBounds || (cubes[i][2].x + xDiff) < -cXBounds) {
      float mod = xDiff > 0 ? -1 : 1;
      for (int p = 0; p < 20; p++) {
        cubes[i][p].x += cXBounds * 2 * mod;
      }
      return 0;
    }
  }

  if (yDiff == 0) {
    if (cubes[i][0].y > cYBounds || cubes[i][2].y < -cYBounds) {
      removeCube(cubes, i);
      return 1;
    }
  } else {
    if ((cubes[i][0].y + yDiff) > cYBounds || (cubes[i][2].y + yDiff) < -cYBounds) {
      float mod = yDiff > 0 ? -1 : 1;
      for (int p = 0; p < 20; p++) {
        cubes[i][p].y += cYBounds * 2 * mod;
      }
      return 0;
    }
  }

  return 0;
}

int compareSize(const void *a, const void *b) {
  Cube cube1 = *((Cube *)a);
  Cube cube2 = *((Cube *)b);

  return (cube1[0].z < cube2[0].z) - (cube1[0].z > cube2[0].z);
}

float timeSinceLastCube = 0;
int cubesRemovedForDistance = 0;

void gameFrame(SDL_Event e, float deltaTime, Cube cubes[], int *cubesLength) {
  float speed = 70 * deltaTime;
  float moveSpeed = 30 * deltaTime;
  if (*cubesLength == 0) {
    while ((*cubesLength) < 300) {
      addInitialCube(cubes, cubesLength);
    }
  } else {
    // printf("\nDistance %f %f", cubes[*cubesLength - 1][0].z, cubes[0][0].z);

    // if (cubes[0][0].z < MAX_DEPTH * 0.999) {
    //   for (int i = 0; i < 2; i++) {
    //     addNewCube(cubes, cubesLength);
    //   }
    // }

    for (int i = 0; i < cubesRemovedForDistance + 1; i++) {
      addNewCube(cubes, cubesLength);
    }
    cubesRemovedForDistance = 0;

    // timeSinceLastCube += deltaTime;
    // printf("\nTime %f", timeSinceLastCube);
    // if (timeSinceLastCube > 0.01) {
    // }
  }

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
    if (cubes[i][0].z < 1.5) {
      removeCube(cubes, i);
      cubesRemoved += 1;
      cubesRemovedForDistance += 1;
    } else {
      int removed = removeOrFlipCubeIfOutOfBounds(cubes, i, xDiff, yDiff, zSpeed);
      if (removed) {
        cubesRemoved += 1;
      } else {
        for (int p = 0; p < 20; p++) {
          cubes[i][p].x += xDiff;
          cubes[i][p].y += yDiff;

          cubes[i][p].z += zSpeed;
        }
      }
    }
  }

  rearrangeCubesToTakeOutRemoved(cubes, cubesLength, cubesRemoved);

  *cubesLength -= cubesRemoved;

  qsort(cubes, *cubesLength, sizeof(Cube *), compareSize);
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