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

  SDL_Point transformedCube[CUBE_POINTS_N + 1];

  // Concerning order of non-front pieces:
  // If we're above middleY we should draw up last
  // If we're above middleX we should draw left last

  float middleX = cube[FRONT_I].x + (cube[FRONT_I + 2].x - cube[FRONT_I].x) / 2;
  float middleY = cube[FRONT_I].y + (cube[FRONT_I + 2].y - cube[FRONT_I].y) / 2;

  bool aboveMiddleX = middleX > 0;
  bool aboveMiddleY = middleY > 0;

  // Default order: up down left right front
  // New order: first-left/right last-up/down last-left/right first-up/down  front
  int faceOrder[5];

  // if (aboveMiddleY) {
  //   faceOrder[0] = DOWN;
  //   faceOrder[2] = UP;
  // } else {
  //   faceOrder[0] = UP;
  //   faceOrder[2] = DOWN;
  // }
  // if (aboveMiddleX) {
  //   faceOrder[1] = RIGHT;
  //   faceOrder[3] = LEFT;
  // } else {
  //   faceOrder[1] = LEFT;
  //   faceOrder[3] = RIGHT;
  // }

  // if (!aboveMiddleX && !aboveMiddleY) {
  //   faceOrder[0] = UP;
  //   faceOrder[1] = LEFT;
  //   faceOrder[2] = RIGHT;
  //   faceOrder[3] = DOWN;
  // } else if (aboveMiddleX && !aboveMiddleY) {
  //   faceOrder[0] = UP;
  //   faceOrder[1] = RIGHT;
  //   faceOrder[2] = LEFT;
  //   faceOrder[3] = DOWN;
  // } else if (aboveMiddleX && aboveMiddleY) {
  //   faceOrder[0] = UP;
  //   faceOrder[1] = LEFT;
  //   faceOrder[2] = DOWN;
  //   faceOrder[3] = RIGHT;
  // } else if (!aboveMiddleX && aboveMiddleY) {
  //   faceOrder[0] = UP;
  //   faceOrder[1] = RIGHT;
  //   faceOrder[2] = LEFT;
  //   faceOrder[3] = DOWN;
  // }

  // faceOrder[4] = FRONT;

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

  for (int f = 0; f < 5; f++) {
    int cubeI = f * 5;

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

    if (f == 4) {
      SDL_Color c = {.r = 200, .b = 120, .g = 250};
      color = c;
    } else if (f == 0 || f == 1) {
      SDL_Color c = {.r = 50, .b = 120, .g = 250};
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