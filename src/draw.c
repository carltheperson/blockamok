#include "./draw.h"

#include <SDL.h>
#include <math.h>
#include <stdbool.h>

#include "./game.h"
#include "./math.h"

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int FRONT = 4;

int TRANSFORMED_FRONT_I = FRONT * 5;

SDL_Point transformedCube[CUBE_POINTS_N + 1];

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

bool isPointOutsideFront(int f, int frontI) {
  float x = transformedCube[f].x;
  float y = transformedCube[f].y;
  float frontStartX = transformedCube[frontI].x;
  float frontEndX = transformedCube[frontI + 2].x;
  float frontStartY = transformedCube[frontI].y;
  float frontEndY = transformedCube[frontI + 2].y;
  bool outWithX = x < frontStartX || x > frontEndX;
  bool outWithY = y < frontStartY || y > frontEndY;
  return outWithX || outWithY;
}

void drawCubes(SDL_Renderer *renderer, Cube cubes[], int cubesLength) {
  for (int i = 0; i < cubesLength; i++) {
    drawCube(renderer, cubes[i]);
  }
}

void drawCube(SDL_Renderer *renderer, Cube cube) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  for (int f = 0; f < 5; f++) {
    int orgCubeI = f * 4;    // The way our cube is defined, a face has four cornes
    int transCubeI = f * 5;  // The way our transformed cube is defined, a face has 5 corners (last one connects back to the firt one)
    for (int p = 0; p < 4; p++) {
      Point point = cube[orgCubeI + p];
      SDL_Point sPoint = {screenX(transform3Dto2D(point.x, point.z)), screenY(transform3Dto2D(point.y, point.z))};
      transformedCube[transCubeI + p] = sPoint;
    }
    transformedCube[transCubeI + 4] = transformedCube[transCubeI + 0];
  }

  // If a have has at least two points outside of front, it gets to be drawn last
  int faceOrder[5];

  int lastI = 4;
  int firstI = 0;

  faceOrder[lastI--] = FRONT;  // Front always gets to be last

  for (int f = 0; f < 4; f++) {
    int cubeI = f * 5;
    bool sideOutsideFront = isPointOutsideFront(cubeI, FRONT * 5) && isPointOutsideFront(cubeI + 1, FRONT * 5);
    // If we are outside, we should draw this as last as possible
    if (sideOutsideFront) {
      faceOrder[lastI--] = f;
    } else {
      faceOrder[firstI++] = f;
    }
  }

  for (int f = 0; f < 5; f++) {
    int cubeI = faceOrder[f] * 5;

    SDL_FPoint triable1Points[] = {
        {.x = transformedCube[cubeI + 0].x, .y = transformedCube[cubeI + 0].y},
        {.x = transformedCube[cubeI + 1].x, .y = transformedCube[cubeI + 1].y},
        {.x = transformedCube[cubeI + 2].x, .y = transformedCube[cubeI + 2].y},
    };

    SDL_FPoint triable2Points[] = {
        {.x = transformedCube[cubeI + 2].x, .y = transformedCube[cubeI + 2].y},
        {.x = transformedCube[cubeI + 3].x, .y = transformedCube[cubeI + 3].y},
        {.x = transformedCube[cubeI + 4].x, .y = transformedCube[cubeI + 4].y},
    };

    SDL_Color color;

    if (f == FRONT) {
      SDL_Color c = {.r = 200, .b = 120, .g = 250};
      color = c;
    } else {
      SDL_Color c = {.r = 100, .b = 200, .g = 100};
      color = c;
    }

    SDL_Vertex triangle1[3];
    SDL_Vertex triangle2[3];

    triangle1[0].color = color;
    triangle1[1].color = color;
    triangle1[2].color = color;
    triangle2[0].color = color;
    triangle2[1].color = color;
    triangle2[2].color = color;

    triangle1[0].position = triable1Points[0];
    triangle1[1].position = triable1Points[1];
    triangle1[2].position = triable1Points[2];

    triangle2[0].position = triable2Points[0];
    triangle2[1].position = triable2Points[1];
    triangle2[2].position = triable2Points[2];

    SDL_Point linePoints[] = {
        transformedCube[cubeI + 0],
        transformedCube[cubeI + 1],
        transformedCube[cubeI + 2],
        transformedCube[cubeI + 3],
        transformedCube[cubeI + 4],
    };

    SDL_RenderGeometry(renderer, NULL, triangle1, 3, NULL, 0);
    SDL_RenderGeometry(renderer, NULL, triangle2, 3, NULL, 0);
    SDL_RenderDrawLines(renderer, linePoints, 5);
  }
}