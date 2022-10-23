#pragma once

#include <SDL.h>

#define CUBE_FACE_POINTS_N 4
#define CUBE_FACE_N 5
#define CUBE_POINTS_N 20  // 5 * 4
#define FRONT_I 16        // 4 * 4

extern float playerSpeed;

typedef struct {
  float z;
} Player;

typedef struct Point {
  float x;
  float y;
  float z;
} Point;

typedef struct {
} Block;

typedef Point* Cube;

int gameFrame(float deltaTime, Cube cubes[], int* cubesLength);

void gameInit(Cube cubes[], int* cubesLength);

Cube newCube(Point c, float s);